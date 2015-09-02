/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** main.cpp
** TODO: How to run this?
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/
#include <string.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ctime>
#include "alignment.h"
#include "global_linear.h"

using namespace std;

bool valid_action(const char *needle) {
    return strcmp(needle, "all") ||
           strcmp(needle, "global_linear");
}

char parse_protein(char in) {
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

void parse_file(const char *filename, vector<unsigned char> &sequence) {
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

int main(int argc, char** argv) {
    if(argc != 4 || !valid_action(argv[1])) {
        // TODO: Print usage
        return EXIT_FAILURE;
    }

    // Convert the input to indexes (in this alphabet 1 byte should be enough, i.e. at most 255 characters
    vector<unsigned char> seq1, seq2;
    unsigned long n, m;
    parse_file(argv[2], seq1);
    parse_file(argv[3], seq2);

    n = seq1.size() + 1;
    m = seq2.size() + 1;

    // Run the desired method
    if (strcmp(argv[1], "all") == 0) {
        // Run all algorithms once to produce the output
        vector<Alignment *> algorithms = {
                new GlobalLinear()
        };
        for(auto alg : algorithms) {

        }
    } else {
        // Run a specific algorithm to produce the output
        Alignment *algorithm;
        // Prepare the score matrix
        vector<vector<int64_t>> S;
        // Fill the n x m matrix with 0's
        S.resize(n, vector<int64_t>(m,0));
        // Prepare an alignment with initial size of the longest string
        vector<char> alignment(max(n, m));

        if (strcmp(argv[1], "global_linear") == 0) {
            algorithm = new GlobalLinear();
        } else {
            exit(EXIT_FAILURE);
        }
        cout << "n = " << n << " m = " << m << endl;

        cout << "Computing the score matrix using " << argv[1] << endl;
        clock_t start = clock();

        algorithm->compute_s(S, seq1, seq2);

        clock_t end = clock();
        cout << "Computed in " << (end - start) / CLOCKS_PER_SEC << " seconds." << endl << endl;

        cout << "Searching for an optimal alignment" << endl;
        start = clock();

        algorithm->find_alignment(S, alignment);

        end = clock();
        cout << "Found in " << (end - start) / CLOCKS_PER_SEC << " seconds." << endl << endl;

        cout << "Computing the total number of optimal alignments" << endl;

        start = clock();

        uint64_t num = algorithm->num_alignments(S);

        end = clock();
        cout << "There are " << num << " optimal alignments" << endl;
        cout << "Computed in " << (end - start) / CLOCKS_PER_SEC << " seconds." << endl << endl;

    }

    return EXIT_SUCCESS;
}

