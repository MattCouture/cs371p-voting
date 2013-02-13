#ifndef Voting_h
#define Voting_h

#include <iostream>

using namespace std;

bool checkVote(int&, vector<int>&);

void reassignVotes(vector<int>&, vector<int>&, vector<vector<string> >&, vector<int>&);

bool findWinner(vector<int>&, vector<string>&, vector<int>&, vector<string>&, vector<int>&);

void sortVotes(std::istream&, vector<vector<string> >&, vector<int>&, string&);

void print(std::ostream&, vector<string>&);

void solve(std::istream&, std::ostream&);

void numElections(std::istream&);

#endif
