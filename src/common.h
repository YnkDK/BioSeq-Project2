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
    /*
     * 
     * we use this function to inialize all the necessary data for the functions of the algorithms to be able to run properly
     * 
     */
    virtual void initialize(const char* file1, const char* file2) = 0;
    /*
     * computes the cost matrix and returns the score of an optimal alignment
     */
    virtual int64_t compute_S() = 0;
    /*
     * 
     * finds an alignment and stores it inside the alignment vector
     * 
     */
    virtual void find_alignment(vector<char>& alignment) = 0;
    /*
     * 
     * finds the number of optimal alignments
     * 
     */
    virtual int64_t num_alignments() = 0;
    /*
     * 
     * returns the name of the algorithm
     * 
     */
    virtual const char *get_name() = 0;
    /*
     * 
     * returns n, the number of rows
     * 
     */
    virtual int get_n() = 0;
    /*
     * 
     * returns m, the number of columns
     * 
     * 
     */
    virtual int get_m() = 0;
    
    /*
     * 
     * checks whether the alignment that was computed matches the optimal alignment score
     * 
     */
    virtual bool check() = 0;


protected:
    /**
     * Can be used to translate from unsigned char to char in find_alignment
     */
    const char index_to_protein[4] = { 'A', 'C', 'G', 'T' };
};

#endif //BIOSEQ_PROJECT2_COMMON_H
