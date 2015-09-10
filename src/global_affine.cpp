/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** global_affine.cpp
** The .cpp file where all the functions of the global affine algorithm are implemented
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#include "global_affine.h"


void GlobalAffine::initialize(const char* file1, const char* file2){

    //read all the necessary information from the external files so we can run the algorithm properly later on
    parse_dna_file(file1, seq1);
    parse_dna_file(file2, seq2);
    parse_global_affine_control_file(score,alpha,beta);
    n = seq1.size()+1;
    m = seq2.size()+1;
    S.resize(n, vector<int64_t>(m,inf));
    I.resize(n,vector<int64_t>(m,inf));
    D.resize(n,vector<int64_t>(m,inf));
    
}

uint64_t GlobalAffine::compute_S() {
    
    S[0][0] = 0;
    int i,j;
    
    /*
     * cover the boundary cases
     * 
     */
    for(i=1;i<m;i++){
        I[0][i] = min(I[0][i-1]+alpha, S[0][i-1]+alpha+beta);
        S[0][i] = I[0][i];
    }

    for(i=1;i<n;i++){
        D[i][0] = min(D[i-1][0]+alpha, S[i-1][0]+alpha+beta);
        S[i][0] = D[i][0];
    }
    
    /*
     * we have the first rows/columns of our tables filled in, so we can now take care of the case where i>0 and j>0
     * 
     */
    for(i=1;i<n;i++){
        for(j=1;j<m;j++){
                D[i][j] = min(S[i-1][j]+alpha+beta, D[i-1][j]+alpha);
                I[i][j] = min(S[i][j-1]+alpha+beta, I[i][j-1]+alpha);
                S[i][j] = min(S[i-1][j-1]+score[seq1[i-1]][seq2[j-1]], min(D[i][j],I[i][j]));
        }
    }
    
    return S[n-1][m-1];
    
}


void GlobalAffine::find_alignment_helper(int i, int j)
{
    if(i>0 && j>0){
        
        if(S[i][j] == S[i-1][j-1]+score[seq1[i-1]][seq2[j-1]]){
            find_alignment_helper(i-1,j-1);
            alignment.push_back(index_to_protein[seq1[i - 1]]);
            alignment.push_back(index_to_protein[seq2[j - 1]]);
        }
        else{
         
            
            int k = 1;
            while(true){
            
                if(i>=k && S[i][j] == S[i-k][j]+affline(k)){
                
                    find_alignment_helper(i-k,j);
                    for(int tmp=0; tmp<k; tmp++){
                        alignment.push_back(index_to_protein[seq1[i - tmp - 1]]);
                        alignment.push_back('-');
                    }
                    break;
                    
                }
                else if(j>=k && S[i][j] == S[i][j-k]+affline(k)){
  
                    find_alignment_helper(i,j-k);
                    for(int tmp=0; tmp<k; tmp++){
                        alignment.push_back('-');
                        alignment.push_back(index_to_protein[seq2[j - tmp - 1]]);
                    }
                    break;
                }
                
                k++;
            }
            
        }
    }
    else if(i == 0 && j > 0){
            while(j > 0){
                alignment.push_back('-');
                alignment.push_back(index_to_protein[seq2[j - 1]]);
                j--;
            }
    }
    else if(j == 0 && i>0){
            while(i>0){
                alignment.push_back(index_to_protein[seq1[i - 1]]);
                alignment.push_back('-');
                i--;
            }
    }
    return;
    
}


void GlobalAffine::find_alignment(vector<char>& alignment) {
    
    find_alignment_helper(n-1,m-1);
    alignment = this->alignment;
   
}

void GlobalAffine::markCells(int i, int j){

 
}

uint64_t GlobalAffine::num_alignments() {
    
    return 0;
}

const char *GlobalAffine::get_name() {
    return "global_affine";
}

int GlobalAffine::get_n() {
    return this->n;
}

int GlobalAffine::get_m() {
    return this->m;
}
