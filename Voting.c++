#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "Voting.h"

using namespace std;

void sortVotes(std::istream& r, vector< vector<string> >& allVotes, vector<int>& voteCount, string& vote) {
  char c = r.peek();
  if(c == EOF || c == '\n' || !r) {
    return;}
  
  int a;
  r >> a;
  r.ignore(1);
  getline(r, vote);
  allVotes[a-1].push_back(vote);
  ++voteCount[a-1];
  sortVotes(r, allVotes, voteCount, vote);
}

vector<string> findWinners(vector< vector<string> >& allVotes, vector<int>& voteCount, vector<string>& candidates) {
  vector<string> winners;
  int total = 0, min = voteCount[0], max = voteCount[0];
  bool noWinner = true;
  vector<int> losers;
  for(vector<int>::size_type i = 0; i < voteCount.size(); ++i) {
    total += voteCount[i];
    if(voteCount[i] < min && voteCount[i] > 0) {
      min = voteCount[i];}
    if(voteCount[i] > max) {
      max = voteCount[i];
      if(min == 0){min = max;}
    }
  }
  if(max == min) {
    findWinners2(voteCount, candidates, winners);
    return winners;
  }
  for(vector<int>::size_type i = 0; i < voteCount.size(); ++i) {
    if(voteCount[i] > (total/2)) {
      noWinner = false;
      winners.push_back(candidates[i]);}
    if(voteCount[i] == min) {
      losers.push_back(i);}
  }
  if(noWinner) {
    reassignVotes(allVotes, losers, voteCount);
    findWinners2(voteCount, candidates, winners);
  }
  return winners; 
}

void reassignVotes(vector< vector<string> >& allVotes, vector<int>& losers, vector<int>& voteCount) {
  int loserIndex, newVote;
  bool voteIsBad;
  for(vector<int>::size_type i = 0; i < losers.size(); ++i) {
    loserIndex = losers[i];
    for(vector<vector<string> >::size_type j = 0; j < allVotes[loserIndex].size(); ++j) {
      string vot = allVotes[loserIndex][j];
      newVote = atoi(vot.substr(0, 1).c_str());
      voteIsBad = checkVote(newVote, losers);
      while(voteIsBad) {
        vot = vot.substr(2);
        newVote = atoi(vot.substr(0, 1).c_str());
        voteIsBad = checkVote(newVote, losers);
      } 
      ++voteCount[newVote-1]; 
    }
  }
}

bool checkVote(int& newVote, vector<int>& losers) {
  bool bad = false;
  for(vector<int>::size_type i = 0; i < losers.size(); ++i) {
    if(losers[i] == (newVote-1)) {
      bad = true;
      break;}
  }
  return bad;
}

void findWinners2(vector<int>& voteCount, vector<string>& candidates, vector<string>& winners) {
  int max = voteCount[0];
  for(vector<int>::size_type i = 0; i < voteCount.size(); ++i) {
    if(voteCount[i] > max) {
      max = voteCount[i];}
  }
  for(vector<int>::size_type i = 0; i < voteCount.size(); ++i) {
    if(voteCount[i] == max) {
      winners.push_back(candidates[i]);}
  }
}

void print(std::ostream& w, vector<string>&  winners) {
  for(vector<string>::size_type i = 0; i < winners.size(); ++i) {
    w << winners[i] << "\n";
  }
  w << endl;
}

void solve(std::istream& r, std::ostream& w) {
  int numCand;
  r >> numCand;
  r.ignore();
  vector<string> candidates(numCand);
  vector<int> voteCount(numCand);
  string cand;
  for(vector<string>::size_type i = 0; i < candidates.size(); ++i) {
    getline(r, cand);
    candidates[i] = cand;
    voteCount[i] = 0;
  }
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
