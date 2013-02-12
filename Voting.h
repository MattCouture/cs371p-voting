#ifndef Voting_h
#define Voting_h

#include <iostream>

using namespace std;

void sortVotes(std::istream&, vector<vector<string> >&, vector<int>&, string&);

vector<string> findWinners(vector<vector<string> >&, vector<int>&, vector<string>&);

vector<int> determineLosers(vector<int>&);

void reassignVotes(vector<vector<string> >&, vector<int>&);

vector<string> findWinners2(vector<int>&, vector<string>&);

void print(std::ostream&, vector<string>&);

void solve(std::istream&, std::ostream&);

void numElections(std::istream&);

#endif
