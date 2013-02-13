#ifndef Voting_h
#define Voting_h

#include <iostream>

using namespace std;

void sortVotes(std::istream&, vector<vector<string> >&, vector<int>&, string&);

vector<string> findWinners(vector<vector<string> >&, vector<int>&, vector<string>&);

void reassignVotes(vector<vector<string> >&, vector<int>&, vector<int>&);

bool checkVote(int&, vector<int>&);

void findWinners2(vector<int>&, vector<string>&, vector<string>&);

void print(std::ostream&, vector<string>&);

void solve(std::istream&, std::ostream&);

void numElections(std::istream&);

#endif
