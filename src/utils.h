/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** utils.h
** In this file we include all the utilities that are being used in our system
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#ifndef BIOSEQ_PROJECT2_UTILS_H
#define BIOSEQ_PROJECT2_UTILS_H

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

inline char parse_protein(char in) {
    if(in == 'A' || in == 'a') {
        return 'a';
    }
    if(in == 'C' || in == 'c') {
        return 'c';
    }
    if(in == 'G' || in == 'g') {
        return 'g';
    }
    if(in == 'T' || in == 't') {
        return 't';
    }
    cerr << "Unknown protein in sequence: " << in << " (aborted)." << endl;
    exit(EXIT_FAILURE);
}

inline void parse_dna_file(const char *filename, vector<char> &sequence) {
    string tmp;
    ifstream fin;

    fin.open(filename);

    // Skip name and comments
    while(getline(fin, tmp)) {
        if(tmp[0] != '>' && tmp[0] != ';') {
            break;
        }
    }
    // Ensure an empty starting point
    sequence.empty();
    // tmp now contains the first line
    do {
        for(string::iterator c = tmp.begin(); c < tmp.end(); c++) {
            // Map the character sequence to an index
            switch (*c) {
                case 'a':
                case 'A':
                    sequence.push_back(0);
                    break;
                case 'c':
                case 'C':
                    sequence.push_back(1);
                    break;
                case 'g':
                case 'G':
                    sequence.push_back(2);
                    break;
                case 't':
                case 'T':
                    sequence.push_back(3);
                    break;
                case ' ':
                    break;
                default:
                    cerr << "Unknown letter in alphabet: " << *c << " (aborted)." << endl;
            }
        }
    } while (getline(fin,tmp));
    
    fin.close();
}

inline void parse_control_file(vector<vector<int64_t>>& score, int64_t& gapCost){

/*
 * Control file example
  gapCost 
  0  5  2  5
  5  0  5  2
  2  5  0  5
  5  2  5  0
 * 
 * First line defines the gapcost
 * The remaining lines define the score matrix. We assume that the score matrix has the same form as the one in project 1.
 * We also assume that the control file always exists and has the correct form.
 * 
 * */

    ifstream fin;
    fin.open("control");
    if(fin.fail()){
        cout<<"control file does not exist."<<endl;
         exit(EXIT_FAILURE);
    }
    
    fin>>gapCost;
    score.resize(4, vector<int64_t>(4));
    
    int i,j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            fin>>score[i][j];
        
    fin.close();
    
}

inline void print_alignment_normal(vector<char>& alignment){

    size_t i;
    
    const char index_to_protein[4] = { 'A', 'C', 'G', 'T' };
    
    for(i=0;i<alignment.size();i+=2){
        if(alignment[i] == '-') cout<<'-';
        else cout<<index_to_protein[(int)alignment[i]];
    }
    cout<<endl;
    for(i=1;i<alignment.size();i+=2){
        if(alignment[i] == '-') cout<<'-';
        else cout<<index_to_protein[(int)alignment[i]];
    }
    cout<<endl;

}

inline void print_alignment_latex(vector<char> &alignment) {
    
        vector<char> seq1;
        vector<char> seq2;
        seq1.reserve(50);
        seq2.reserve(50);

        cout << "\\begin{figure}[H]" << endl;
        cout << "\t\\centering" << endl;
        cout << "\t\\begin{tabular}{L{0.15\\textwidth} L{0.7\\textwidth}}" << endl;

        for (size_t i = 0; i < alignment.size(); i += 2) {
            seq1.push_back(alignment[i]);
            seq2.push_back(alignment[i + 1]);
            if (seq1.size() == 50) {
                cout << "\t\tSequence 1 & \\texttt{";
                for (size_t j = 0; j < seq1.size(); j++) {
                    cout << seq1[j];
                    if (j == 9 || j == 19 || j == 29 || j == 39) {
                        cout << " ";
                    }
                }
                cout << "} \\\\" << endl;

                cout << "\t\tSequence 2 & \\texttt{";
                for (size_t j = 0; j < seq2.size(); j++) {
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
        for (size_t j = 0; j < seq1.size(); j++) {
            cout << seq1[j];
            if (j == 9 || j == 19 || j == 29 || j == 39) {
                cout << " ";
            }
        }
        cout << "} \\\\" << endl;

        cout << "\t\tSequence 2 & \\texttt{";
        for (size_t j = 0; j < seq2.size(); j++) {
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


#endif //BIOSEQ_PROJECT2_UTILS_H
