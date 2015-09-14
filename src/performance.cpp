/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** performance.cpp
** file where all the functions of performance.h are implemented
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#include "performance.h"

void Performance::run(std::vector<Common *> &algorithms, const char *file1, const char *file2) {
    int64_t opt;
    long long cpuClock;
    for(auto alg : algorithms) {
        // Initialize algorithm
        alg->initialize(file1, file2);
        const char *name = alg->get_name();
        const int n = alg->get_n();
        const int m = alg->get_m();
        for(int i = 0; i < PERFORMANCE_RUNS; i++) {
            // Clear cache
            // Allocate 12 MiB of data (CPU cache size of i7-4710HQ is 6 MiB)
            const unsigned long long SIZE = 12 * 1024 * 1024;
            unsigned char *garbage = (unsigned char *) malloc(SIZE * sizeof(unsigned char));
            garbage[0] = (unsigned char) ((unsigned char) (i + (unsigned long long) name) & 0xFF);
            for (unsigned int j = 1; j < SIZE; j++) {
                for(unsigned int k = 0; k < j; k += SIZE/8) { // Jump around in the garbage array
                    // Use inspiration from init of MT19937, which uses different instructions
                    garbage[j] = (unsigned char) (
                            (1812433253LL * ((long long)garbage[k] ^ (((long long)garbage[k] >> 30) + j))) & 0xFF);
                }
            }
            std::cout << (unsigned short) garbage[SIZE - 1] << "\t";
            free(garbage);

            vector<char> alignment;

            // Compute S
            opt = alg->compute_S();
            // Reset counters
            ioctl(this->fd, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
            // Start counting
            ioctl(this->fd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
            alg->find_alignment(alignment);
            // Stop counting
            ioctl(this->fd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
            // Get CPU clock count
            cpuClock = _get(PERF_TYPE_SOFTWARE, PERF_COUNT_SW_CPU_CLOCK);
            // Write cpu time
            std::cout << opt << "\t" << cpuClock << "\t" << name << "\t";
            std::cout << file1 << "\t" << n << "\t" << file2 << "\t" << m << std::endl;
            alignment.clear();
        }

    }
}

static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags) {
    long ret;

    ret = syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);

    return ret;
}

void Performance::_add(perf_type_id type, uint64_t config) {
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

        fd = (int) perf_event_open(&pe, 0, -1, -1, 0);
        if (fd < 0) {
            fprintf(stderr, "Error opening leader for %llx / %lu\n", (long long) type, config);
            exit(EXIT_FAILURE);
        }
    } else {
        long ret = perf_event_open(&pe, 0, -1, fd, 0);
        if (ret < 0) {
            fprintf(stderr, "Error connecting to leader for %llx / %lu\n", (long long) type, config);
            exit(EXIT_FAILURE);
        }
    }
}

long long Performance::_get(perf_type_id type, long long config) {
    long long buffer[1 /* <nr> */ + (1 /* <value> */ * perf_size /* [nr] */)];
    size_t readSize = (1 + (1 * perf_size)) * sizeof(long long);
    ssize_t r = read(fd, &buffer, readSize);
    if (r == -1) {
        fprintf(stderr, "Error reading from fd\n");
        exit(EXIT_FAILURE);
    }
    for (int index = 0; index < events; index++) {
        if (order[index].config == config && order[index].type == type) {
            return buffer[1 + index];
        }
    }
    fprintf(stderr, "Could not find sw config: %llx\n", config);
    exit(EXIT_FAILURE);
}