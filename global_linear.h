//
// Created by mys on 8/31/15.
//

#ifndef BIOSEQ_PROJECT2_GLOBAL_LINEAR_H
#define BIOSEQ_PROJECT2_GLOBAL_LINEAR_H

#include "alignment.h"

class GlobalLinear : public Alignment {
    void compute_s(vector<vector<int64_t>> &cost, const string &seq1, const string &seq2);
    void find_alignment(const vector<vector<int64_t>> &cost, vector<char> &alignment);
    uint64_t num_alignments(vector<vector<int64_t>> &cost);
};

#endif //BIOSEQ_PROJECT2_GLOBAL_LINEAR_H
