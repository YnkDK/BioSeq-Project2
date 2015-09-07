/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** performance.cpp
** Main file
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#include "performance.h"

#include <iostream>

void Performance::run(std::vector<Common *> &algs, const char *file1, const char *file2) {
    int64_t opt, cpuClock;
    for(auto alg : algs) {
        // Initialize algorithm
        alg->initialize(file1, file2);
        for(int i = 0; i < PERFORMANCE_RUNS; i++) {
            // Clear cache
            // Allocate 6 MiB of data (CPU cache size of i7-4710HQ)
            const unsigned long long SIZE = 6 * 1024 * 1025;
            unsigned char *garbage = (unsigned char *) malloc(SIZE);
            garbage[0] = i+13;
            for (int j = 1; j < SIZE; j++) {
                // Use init of MT19937, which uses different instructions
                garbage[j] = (1812433253 * ((long long)garbage[j - 1] ^ ((long long)garbage[j - 1] >> 30) + j)) & 0xFFFF;
            }
            std::cout << (unsigned int) garbage[SIZE - 1] << "\t";
            free(garbage);

            // Reset counters
            ioctl(this->fd, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
            // Start counting
            ioctl(this->fd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
            // Compute S
            opt = alg->compute_S();
            // Stop counting
            ioctl(this->fd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
            // Get CPU clock count
            cpuClock = _get(PERF_TYPE_SOFTWARE, PERF_COUNT_SW_CPU_CLOCK);
            // Write cpu time
            // TODO: Make output in correct format
            std::cout << opt << "\t" << cpuClock << std::endl;
        }

    }
}

static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags) {
    int ret;

    ret = syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);

    return ret;
}

void Performance::_add(perf_type_id type, long long config) {
    struct perf_event_attr pe;
    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.size = sizeof(struct perf_event_attr);
    pe.exclude_kernel = 1;
    pe.exclude_hv = 1;

    pe.type = type;
    pe.config = config;


    order[events].type = type;
    order[events].config = config;
    events++;

    if (fd == -1) {
        /* if changed: change calculations in get */
        pe.read_format = PERF_FORMAT_GROUP;
        pe.disabled = 1;

        fd = perf_event_open(&pe, 0, -1, -1, 0);
        if (fd < 0) {
            fprintf(stderr, "Error opening leader for %llx / %llx\n", (long long) type, config);
            exit(EXIT_FAILURE);
        }
    } else {
        int ret = perf_event_open(&pe, 0, -1, fd, 0);
        if (ret < 0) {
            fprintf(stderr, "Error connecting to leader for %llx / %llx\n", (long long) type, config);
            exit(EXIT_FAILURE);
        }
    }
}

long long Performance::_get(perf_type_id type, long long config) {
    long long buffer[1 /* <nr> */ + (1 /* <value> */ * perf_size /* [nr] */)];
    int readSize = (1 + (1 * perf_size)) * sizeof(long long);
    int r = read(fd, &buffer, readSize);
    if (r == -1) {
        fprintf(stderr, "Error reading from fd\n");
        exit(EXIT_FAILURE);
    }
    for (int index = 0; index < events; index++) {
        if (order[index].config == config && order[index].type == type) {
            return buffer[1 + index];
        }
    }
    fprintf(stderr, "Could not find sw config: %llx\n", (long long) config);
    exit(EXIT_FAILURE);
}