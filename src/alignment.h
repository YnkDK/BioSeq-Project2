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
#include <iostream>

using namespace std;

class Alignment {
public:
    virtual void compute_s(vector<vector<int64_t>> &cost, const vector<unsigned char> &seq1, const vector<unsigned char> &seq2) = 0;
    virtual void find_alignment(const vector<vector<int64_t>> &cost, vector<char> &alignment) = 0;
    virtual uint64_t num_alignments(vector<vector<int64_t>> &cost) = 0;

    void print_alignment_latex(const vector<char> &alignment) {
        vector<char> seq1;
        vector<char> seq2;
        seq1.reserve(50);
        seq2.reserve(50);

        cout << "\\begin{figure}[H]" << endl;
        cout << "\t\\centering" << endl;
        cout << "\t\\begin{tabular}{L{0.15\\textwidth} L{0.7\\textwidth}}" << endl;

        for (int i = 0; i < alignment.size(); i += 2) {
            seq1.push_back(alignment[i]);
            seq2.push_back(alignment[i + 1]);
            if (seq1.size() == 50) {
                cout << "\t\tSequence 1 & \\texttt{";
                for (int j = 0; j < seq1.size(); j++) {
                    cout << seq1[j];
                    if (j == 9 || j == 19 || j == 29 || j == 39) {
                        cout << " ";
                    }
                }
                cout << "} \\\\" << endl;

                cout << "\t\tSequence 2 & \\texttt{";
                for (int j = 0; j < seq2.size(); j++) {
                    cout << seq2[j];
                    if (j == 9 || j == 19 || j == 29 || j == 39) {
                        cout << " ";
                    }
                }
                cout << "} \\\\" << endl;
                cout << "\t\t& \\\\" << endl;
                seq1.clear();
                seq1.reserve(50);
                seq2.clear();
                seq2.reserve(50);
            }
        }
        cout << "\t\tSequence 1 & \\texttt{";
        for (int j = 0; j < seq1.size(); j++) {
            cout << seq1[j];
            if (j == 9 || j == 19 || j == 29 || j == 39) {
                cout << " ";
            }
        }
        cout << "} \\\\" << endl;

        cout << "\t\tSequence 2 & \\texttt{";
        for (int j = 0; j < seq2.size(); j++) {
            cout << seq2[j];
            if (j == 9 || j == 19 || j == 29 || j == 39) {
                cout << " ";
            }
        }
        cout << "} \\\\" << endl;
        cout << "\t\t& \\\\" << endl;
        cout << "\t\\end{tabular}" << endl
        << "\t\\caption{TODO: Make caption.}" << endl
        << "\t\\label{tab:my_label}" << endl
        << "\\end{figure}" << endl;
    }

private:
    /**
     * Can be used to translate from unsigned char to char in find_alignment
     */
    const char index_to_protein[4] = { 'A', 'C', 'G', 'T' };
};

#endif //BIOSEQ_PROJECT2_ALIGNMENT_H
