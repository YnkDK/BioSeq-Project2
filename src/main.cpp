/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** main.cpp
** Main file
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/
#include <string.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ctime>
#include "common.h"
#include "global_linear.h"
#include "global_affine.h"
#include "performance.h"

using namespace std;

bool valid_action(const char *needle) {
    return strcmp(needle, "all") ||
           strcmp(needle, "global_linear") ||
           strcmp(needle, "performance");
}

void usage(){

    cout<<"Type: ./executable [all,global_linear,global_affine] seq1 seq2"<<endl;

}
int main(int argc, char** argv) {
    if(argc != 4 || !valid_action(argv[1])) {
        usage();
        return EXIT_FAILURE;
    }

    // Run the desired method
    if (strcmp(argv[1], "all") == 0) {
        // Run all algorithms once to produce the output
        vector<Common *> algorithms = {
                new GlobalLinear(),
                new GlobalAffine()
        };
        Performance *p = new Performance();
        p->run(algorithms, argv[2], argv[3]);
    } else {
        // Run a specific algorithm to produce the output
        Common *algorithm;
        
        if (strcmp(argv[1], "global_linear") == 0) {
            algorithm = new GlobalLinear();
        } 
        else if (strcmp(argv[1], "global_affine") == 0){
            algorithm = new GlobalAffine();
        }else {
            usage();
            exit(EXIT_FAILURE);
        }
        
        algorithm->initialize(argv[2], argv[3]);
        
        cout << endl;
        cout << "Computing the cost matrix using " << argv[1] << endl;
        clock_t start = clock();
        uint64_t opt = algorithm->compute_S();
        clock_t end = clock();
        cout << "Optimal alignment cost: " << opt << endl;
        cout << "Computed in " << (end - start) / CLOCKS_PER_SEC << " seconds." << endl << endl;
        
        cout << "Searching for an optimal alignment" << endl;
        start = clock();
        vector<char> alignment;
        algorithm->find_alignment(alignment);
        end = clock();
        //print_alignment_latex(alignment);
        //cout << "To print remove the comments in the main.cpp file" << endl;
        print_alignment_normal(alignment);
        cout << "Found in " << (end - start) / CLOCKS_PER_SEC << " seconds." << endl << endl;
        if(algorithm->check()){
            cout << "SUCCESS!!! Alignment score matches the optimal alignment score!!!!" << endl;
        }
        else{
            cout << "FAIL!!! Alignment score DOES NOT MATCH the optimal alignment score!!!!" << endl;
        }
       
        if(strcmp(argv[1], "global_linear") == 0){ 
            cout << "Computing the total number of optimal alignments" << endl;
            start = clock();
            uint64_t num = algorithm->num_alignments();
            end = clock();
            cout << "There are " << num << " optimal alignments" << endl;
            cout << "Computed in " << (end - start) / CLOCKS_PER_SEC << " seconds." << endl << endl;
        }
        //print_alignment_latex(alignment);
    }

    return EXIT_SUCCESS;
}

