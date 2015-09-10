/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** global_linear.h
** Class implementing the functionalities of the global linear algorithm.
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#ifndef BIOSEQ_PROJECT2_GLOBAL_LINEAR_H
#define BIOSEQ_PROJECT2_GLOBAL_LINEAR_H

#include "common.h"

class GlobalLinear : public Common {
    
private:
    
    /*
     * variables
     * 
     */
    
    vector<vector<bool>> visited;
    vector<char> alignment;
    vector<vector<int64_t>> S;
    vector<vector<int64_t>> score;
    vector<unsigned char> seq1;
    int64_t gapcost;
    vector<unsigned char> seq2;
    
    /*
     * functions
     * 
     */
    void find_alignment_helper(int i, int j);
    void markCells(int i, int j);
    
public:
    int n, m;

    /*
     * read all the necessary information from the external files
     * 
     */
    void initialize(const char* file1, const char* file2);
    
    /*
     * compute the S matrix ( the cost matrix )
     */
    int64_t compute_S();
    
    /*
     * find an alignment and store it inside a vector
     * 
     */
    void find_alignment(vector<char>& alignment);
    /*
     * 
     * find the number of optimal alignments
     * 
     */
    int64_t num_alignments();

    const char *get_name();

    int get_n();
    int get_m();
    
    
    bool check();

};

#endif //BIOSEQ_PROJECT2_GLOBAL_LINEAR_H
