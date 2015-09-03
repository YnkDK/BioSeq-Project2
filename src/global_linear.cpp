/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** global_linear.cpp
** The .cpp file where all the functions of the global linear algorithm are implemented
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#include "global_linear.h"


void GlobalLinear::initialize(const char* file1, const char* file2){

    //read all the necessary information from the external files so we can run the algorithm properly later on
    
    parse_dna_file(file1, seq1);
    parse_dna_file(file2, seq2);
    parse_control_file(score,gapcost);
    n = seq1.size()+1;
    m = seq2.size()+1;

    S.resize(n, vector<int64_t>(m,0));
    
}

int64_t GlobalLinear::compute_S() {
    
    int i,j;
    
    for(i=1;i<m;i++)
        S[0][i] = S[0][i-1] + gapcost;

    for(i=1;i<n;i++)
        S[i][0] = S[i-1][0] + gapcost;

    for(i=1;i<n;i++){
       
        for(j=1;j<m;j++){
                int v1 = S[i-1][j-1]+score[seq1[i-1]][seq2[j-1]];
                int v2 = S[i][j-1]+gapcost;
                int v3 = S[i-1][j]+gapcost;
                S[i][j] = max(v1,max(v2,v3));
        }
        
    }
    
    return S[n-1][m-1];
}

void GlobalLinear::find_alignment_helper(int i, int j)
{
    
    if(i>0 && j>0){
        
        if(S[i][j] == S[i-1][j-1]+score[seq1[i-1]][seq2[j-1]]){
            find_alignment_helper(i-1,j-1);
            alignment.push_back(index_to_protein[seq1[i - 1]]);
            alignment.push_back(index_to_protein[seq2[j - 1]]);
        }
        else if(S[i][j] == S[i][j-1]+gapcost){
            find_alignment_helper(i,j-1);
            alignment.push_back('-');
            alignment.push_back(index_to_protein[seq2[j - 1]]);
        }
        else if(S[i][j] == S[i-1][j]+gapcost){
            find_alignment_helper(i-1,j);
            alignment.push_back(index_to_protein[seq1[i - 1]]);
            alignment.push_back('-');
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


void GlobalLinear::find_alignment(vector<char>& alignment) {
   
    find_alignment_helper(n-1,m-1);
    alignment = this->alignment;
        
}

void GlobalLinear::markCells(int i, int j){

        visited[i][j] = true;
        if(i>0 && j>0){
                if(S[i][j] == S[i-1][j-1]+score[seq1[i-1]][seq2[j-1]] && !visited[i-1][j-1])
                        markCells(i-1,j-1);
                if(S[i][j] == S[i][j-1]+gapcost && !visited[i][j-1])
                        markCells(i,j-1);
                if(S[i][j] == S[i-1][j]+gapcost && !visited[i-1][j])
                        markCells(i-1,j);
        }
        else if(i == 0 && j > 0 && !visited[i][j-1])
                markCells(i,j-1);
        else if(j == 0 && i>0 && !visited[i-1][j])
                markCells(i-1,j);
}

int64_t GlobalLinear::num_alignments() {
    
    
    visited.resize(n,vector<bool>(m,false));
    markCells(n-1,m-1);

    int i,j;
    vector< vector<int64_t> > dp(n, vector<int64_t>(m,0));

    dp[0][0] = 1;
    for(i=1;i<n;i++)
        dp[i][0] = 1*visited[i][0];
    for(i=1;i<m;i++)
        dp[0][i] = 1*visited[0][i];
    for(i=1;i<n;i++){
        for(j=1;j<m;j++){
            if(visited[i][j]){
                if(S[i][j] == S[i-1][j-1]+score[seq1[i-1]][seq2[j-1]])
                    dp[i][j] += dp[i-1][j-1];
                if(S[i][j] == S[i][j-1]+gapcost)
                    dp[i][j] += dp[i][j-1];
                if(S[i][j] == S[i-1][j]+gapcost)
                    dp[i][j] += dp[i-1][j];
            }
        }
    }
    return dp[n-1][m-1];

    return 0;
}

