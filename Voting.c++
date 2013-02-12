#include <cassert>
#include <iostream>
#include <vector>
#include <string>

#include "Voting.h"

using namespace std;

void sortVotes(std::istream& r, vector< vector<string> >& allVotes, vector<int>& voteCount, string& vote) {
  char c = r.peek();
  if(c == EOF || c == '\n') {
    return;}
  int index = c - 49;
  getline(r, vote);
  allVotes[index].push_back(vote);
  ++voteCount[index];
  sortVotes(r, allVotes, voteCount, vote);
}

vector<string> findWinners(vector< vector<string> >& allVotes, vector<int>& voteCount, vector<string>& candidates) {
  vector<string> winners;
  int total = 0;
  bool noWinner = true;
  for(vector<int>::size_type i = 0; i < voteCount.size(); ++i) {
    total += voteCount[i];
  }
  for(vector<int>::size_type i = 0; i < voteCount.size(); ++i) {
    if(voteCount[i] > (total/2)) {
      noWinner = false;
      winners.push_back(candidates[i]);
      break;}
  }
  if(noWinner) {
    vector<int> losers = determineLosers(voteCount);
    reassignVotes(allVotes, losers);
    winners = findWinners2(voteCount, candidates);
  }
  return winners; 
}

vector<int> determineLosers(vector<int>& voteCount) {
  vector<int> losers;
  return losers;
}

void reassignVotes(vector< vector<string> >& allVotes, vector<int>& losers) {

}

vector<string> findWinners2(vector<int>& voteCount, vector<string>& candidates) {
  vector<string> winners;
  return winners;
}

void print(std::ostream& w, vector<string>&  winners) {
  for(vector<string>::size_type i = 0; i < winners.size(); ++i) {
    w << winners[i] << "\n";
  }
}

void solve(std::istream& r, std::ostream& w) {
  int numCand;
  r >> numCand;
  vector<string> candidates(numCand);
  vector<int> voteCount(numCand);
  string candidate;
  for(int i = 0; i < numCand; ++i) {
    r >> candidates[i];
    voteCount[i] = 0;
  }
  r.ignore();
  string vote;
  vector< vector<string> > allVotes(numCand);
  sortVotes(r, allVotes, voteCount, vote);
  vector<string> winners = findWinners(allVotes, voteCount, candidates);
  print(w, winners);
  allVotes.clear();
  winners.clear();
  voteCount.clear();
  candidates.clear();
}

void numElections(std::istream& r) {
  int x;
  r >> x;
  r.ignore();
  for(int y = 0; y < x; ++y) {
    r.ignore();
    solve(r, cout);
  }
}
