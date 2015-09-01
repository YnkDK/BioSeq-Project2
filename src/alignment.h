/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** alignment.h
** TODO: Short description
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#ifndef BIOSEQ_PROJECT2_ALIGNMENT_H
#define BIOSEQ_PROJECT2_ALIGNMENT_H

#include <sys/types.h>
#include <vector>
#include <string>

using namespace std;

class Alignment {
public:
    virtual void compute_s(vector<vector<int64_t>> &cost, const vector<unsigned char> &seq1, const vector<unsigned char> &seq2) = 0;
    virtual void find_alignment(const vector<vector<int64_t>> &cost, vector<char> &alignment) = 0;
    virtual uint64_t num_alignments(vector<vector<int64_t>> &cost) = 0;

private:
    /**
     * Can be used to translate from unsigned char to char in find_alignment
     */
    const char index_to_protein[4] = { 'A', 'C', 'G', 'T' };
};

#endif //BIOSEQ_PROJECT2_ALIGNMENT_H