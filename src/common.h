/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** alignment.h
** In this file we include all the functions that each algorithm should be able to support.
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#ifndef BIOSEQ_PROJECT2_COMMON_H
#define BIOSEQ_PROJECT2_COMMON_H

#include <sys/types.h>
#include <vector>
#include <string>
#include <iostream>
#include "utils.h"

using namespace std;

class Common {
public:
    virtual void initialize(const char* file1, const char* file2) = 0;
    virtual int64_t compute_S() = 0;
    virtual void find_alignment(vector<char>& alignment) = 0;
    virtual int64_t num_alignments() = 0;

private:
    
    /**
     * Can be used to translate from unsigned char to char in find_alignment
     */
    const char index_to_protein[4] = { 'A', 'C', 'G', 'T' };
    //TODO: is this index_to_protein actually needed?
};

#endif //BIOSEQ_PROJECT2_COMMON_H
