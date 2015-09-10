/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** global_affine.h
** Class implementing the functionalities of the global affine algorithm.
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#ifndef BIOSEQ_PROJECT2_GLOBAL_AFFINE_H
#define BIOSEQ_PROJECT2_GLOBAL_AFFINE_H

#include "common.h"
#define inf 9223372036853 //a very large number

class GlobalAffine : public Common {
    
private:
    
    /*
     * variables
     * 
     */
    
    vector<vector<bool>> visited;
    vector<char> alignment;
    vector<vector<int64_t>> S;
    vector<vector<int64_t>> D;
    vector<vector<int64_t>> I;
    vector<vector<int64_t>> score;
    vector<unsigned char> seq1;
    int n, m;
    int64_t alpha, beta;
    vector<unsigned char> seq2;
    
    /*
     * functions
     * 
     */
    
    void find_alignment_helper(int i, int j);
    void markCells(int i, int j);
    
    int64_t affline(int64_t k){
        return alpha*k+beta;
    }
    
public:
    /*
     * read all the necessary information from the external files
     * 
     */
    void initialize(const char* file1, const char* file2);
    
    /*
     * compute the S matrix ( the cost matrix ) and return the number of optimal aligments
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
    
    bool check();

    int get_n();
    int get_m();
     
};

#endif //BIOSEQ_PROJECT2_GLOBAL_AFFINE_H
