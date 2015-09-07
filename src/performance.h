/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** performance.h
** Main file
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#ifndef BIOSEQ_PROJECT2_PERFORMANCE_H
#define BIOSEQ_PROJECT2_PERFORMANCE_H

#ifndef PERFORMANCE_RUNS
// This can be overwritten at compile time
#define PERFORMANCE_RUNS 10
#endif

#include "common.h"

#include <unistd.h> //< syscall, read
#include <string.h> //< memset
#include <fstream> //< lots of output stuff
#include <vector> //< vector
/* perf */
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>

struct e {
    uint64_t type, config;

    e() {
        type = 0;
        config = 0;
    };

    e(uint64_t init_type, uint64_t init_config) {
        type = init_type;
        config = init_config;
    };
};

class Performance {
private:
    int perf_size;
    int events;
    int fd;
    e *order;

    void _add(perf_type_id type, uint64_t config);

    long long _get(perf_type_id type, long long config);


public:
    virtual void run(std::vector<Common *> &algorithms, const char *file1, const char *file2);

    Performance() {
        this->perf_size = 1;
        this->events = 0;
        this->fd = -1;
        this->order = new e[perf_size];

        // This reports the CPU clock, a high-resolution per-CPU timer.
        // [https://lkml.org/lkml/2009/7/1/198] states it is nanoseconds.
        _add(PERF_TYPE_SOFTWARE, PERF_COUNT_SW_CPU_CLOCK);
    }

    ~Performance() {
        delete[] order;
    }
};


#endif //BIOSEQ_PROJECT2_PERFORMANCE_H
