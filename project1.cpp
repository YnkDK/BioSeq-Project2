#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

string str1,str2;

int subcost[4][4] = { {10,2,5,2},
		        {2,10,2,5},
		        {5,2,10,2},
			{2,5,2,10} };

int gapCost = -5;
int counter = 0;
/*
store the map between characters and integers (in our case we need to map the characters of the DNA string to array indexes)
insert and search queries take O(log(size of the map)) but since the size is 4, it's just O(1)
*/
map<char, int> myMap;
/*
2d vector to store DP cost table
*/
vector< vector<int> > cost;
/*
to store an optimal alignment
*/
vector< char > alignment;
/*
we need this 2d vector of booleans to be able to efficiently find the number of optimal alignments.
*/
vector< vector<bool> > visited;

/*
function that finds an optimal alignment and stores it in vector<char> alignment
Running time: O(n+m)
*/
void findAlignment(int i, int j){
	if(i>0 && j>0){
		int& k = myMap[str1[i-1]];
		int& m = myMap[str2[j-1]];
		if(cost[i][j] == cost[i-1][j-1]+subcost[k][m]){
			findAlignment(i-1,j-1);
			alignment.push_back(str1[i-1]);
			alignment.push_back(str2[j-1]);
		}
		else if(cost[i][j] == cost[i][j-1]+gapCost){
			findAlignment(i,j-1);
			alignment.push_back('-');
			alignment.push_back(str2[j-1]);
		}
		else if(cost[i][j] == cost[i-1][j]+gapCost){
			findAlignment(i-1,j);
			alignment.push_back(str1[i-1]);
			alignment.push_back('-');
		}
	}
	else if(i == 0 && j > 0){
		while(j > 0){
			alignment.push_back('-');
			alignment.push_back(str2[j-1]);
			j--;
		}
	}
	else if(j == 0 && i>0){
		while(i>0){
			alignment.push_back(str1[i-1]);
			alignment.push_back('-');
			i--;
		}
	}
	return;
}

/*
parsing the input
support files that store data of the form:

>some text
dna string
*/
void parseInput(char* file1, char* file2){

	ifstream fin;
	fin.open(file1);
	getline(fin,str1);
	str1 = "";
	string tmp;
	while(getline(fin,tmp)){
		tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '),tmp.end());
		str1+=tmp;
	}
	fin.close();

	fin.open(file2);
	getline(fin,str2);
	str2 = "";
	while(getline(fin,tmp)){
		tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '),tmp.end());
		str2+=tmp;
	}
	fin.close();

}

/*
mark all the cells that can be included in an optimal alignment
It's a simple DFS algorithm. As shown in the lectures, the DP table can be represented as a graph with n*m nodes, where each node has at most 3 outgoing edges. 
So the running time is O(|V|+|E|) = O(nm + 3nm) = O(nm)
*/
void markCells(int i, int j){

	visited[i][j] = true;
	if(i>0 && j>0){
		int& k = myMap[str1[i-1]];
		int& m = myMap[str2[j-1]];
		if(cost[i][j] == cost[i-1][j-1]+subcost[k][m] && !visited[i-1][j-1])
			markCells(i-1,j-1);
		if(cost[i][j] == cost[i][j-1]+gapCost && !visited[i][j-1])
			markCells(i,j-1);
		if(cost[i][j] == cost[i-1][j]+gapCost && !visited[i-1][j])
			markCells(i-1,j);
	}
	else if(i == 0 && j > 0 && !visited[i][j-1])
		markCells(i,j-1);
	else if(j == 0 && i>0 && !visited[i-1][j])
		markCells(i-1,j);

}

/*

having found all the cells that can be part of an optimal alignment, we can then use a simple top down dynamic programming approach that finds
all the paths that can be generated from cell (0,0) to cell (n-1,m-1) and visits only the marked cells.

*/
void findNumberOfOptimalAlignments(int n, int m){

	visited.resize(n,vector<bool>(m,false));
	markCells(n-1,m-1);

	int i,j;
	vector< vector<int> > dp(n, vector<int>(m,0));

	dp[0][0] = 1;
	for(i=1;i<n;i++)
		dp[i][0] = 1*visited[i][0];
	for(i=1;i<m;i++)
		dp[0][i] = 1*visited[0][i];
	for(i=1;i<n;i++){
		for(j=1;j<m;j++){
			if(visited[i][j]){
				int& k = myMap[str1[i-1]];
				int& m = myMap[str2[j-1]];
				if(cost[i][j] == cost[i-1][j-1]+subcost[k][m])
					dp[i][j] += dp[i-1][j-1];
				if(cost[i][j] == cost[i][j-1]+gapCost)
					dp[i][j] += dp[i][j-1];
				if(cost[i][j] == cost[i-1][j]+gapCost)
					dp[i][j] += dp[i-1][j];
				}
		}
	}
	counter = dp[n-1][m-1];

}

/*
main function
*/
int main(int argc, char** argv){

/*
read input data in fasta format
*/
parseInput(argv[1], argv[2]);

int n = str1.size()+1;
int m = str2.size()+1;

cost.resize(n, vector<int>(m,0));

/*
run the algorithm to fill in the cost matrix
*/
int i,j;
myMap['A']=0;
myMap['C']=1;
myMap['G']=2;
myMap['T']=3;

for(i=1;i<m;i++)
	cost[0][i] = cost[0][i-1] + gapCost;

for(i=1;i<n;i++)
	cost[i][0] = cost[i-1][0] + gapCost;

for(i=1;i<n;i++){
	for(j=1;j<m;j++){
		int& k = myMap[str1[i-1]];
		int& m = myMap[str2[j-1]];
		int v1 = cost[i-1][j-1]+subcost[k][m];
		int v2 = cost[i][j-1]+gapCost;
		int v3 = cost[i-1][j]+gapCost;
		cost[i][j] = max(v1,max(v2,v3));
	}
}

cout<<"Using the specified score matrix and a gap cost of "<<gapCost<<", the score of an optimal alignment is:"<<endl<<cost[n-1][m-1]<<endl;

cout<<"An optimal alignment looks like the following: "<<endl;

/*
find an alignment
*/
findAlignment(n-1,m-1);

for(i=0;i<alignment.size();i+=2)
	cout<<alignment[i];
cout<<endl;
for(i=1;i<alignment.size();i+=2)
	cout<<alignment[i];
cout<<endl;

int score = 0;
for(i=0;i<alignment.size();i+=2){
	
	int tmp = 0;
	int& k = myMap[alignment[i]];
	int& m = myMap[alignment[i+1]];
	if(alignment[i] == '-' || alignment[i+1] == '-')
		score += gapCost;
	else score += subcost[k][m];

}
cout<<"Score that is produced by the above optimal alignment: "<<score<<endl;
if(score == cost[n-1][m-1]) cout<<"We have a MATCH with the optimal score that was found via DP"<<endl;
else cout<<"We have a MISMATCH with the optimal score that was found via DP"<<endl;

/*
find the number of optimal alignments
*/
findNumberOfOptimalAlignments(n,m);
cout<<"The total number of optical alignments are: "<<counter<<endl;

return 0;
}
