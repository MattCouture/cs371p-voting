#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "Voting.h"

using namespace std;

bool checkVote(int& newVote, vector<int>& allLosers) {
  bool bad = false;
  for(vector<int>::size_type i = 0; i < allLosers.size(); ++i) {
//    cout << "LOSERS: " << allLosers[i] << " ";
    if(allLosers[i] == (newVote-1)) {
      bad = true;
      break;}
  }
//  cout << endl;
  return bad;
}

void reassignVotes(vector<int>& voteCount, vector<int>& losers, vector<vector<string> >& allVotes, vector<int>& allLosers) { 
  int loserIndex, newVote;
  bool voteBad;
  string restOfVote;
  for(vector<int>::size_type i = 0; i < losers.size(); ++i) {
    loserIndex = losers[i];
    for(vector<vector<string> >::size_type j = 0; j < allVotes[loserIndex].size(); ++j) {
    //  cout << allVotes[loserIndex].size() << endl;
      stringstream ss (allVotes[loserIndex][j]);
      ss >> newVote;
    //  cout << "NewVote " << newVote << "  ";
      voteBad = checkVote(newVote, allLosers);
      while(voteBad) {
        ss >> newVote;
    //    cout << "NewVote " << newVote << "  ";
        voteBad = checkVote(newVote, allLosers);
      }
      getline(ss, restOfVote);
      ++voteCount[newVote-1];
      allVotes[newVote-1].push_back(restOfVote);
   //   cout << endl;
    }
    voteCount[loserIndex] = 0;
  }
//   for(vector<int>::size_type i = 0; i < voteCount.size(); ++i) {
//     cout << voteCount[i] << " ";
//   }
//   cout << endl;
}

bool findWinner(vector<int>& voteCount, vector<string>& winners, vector<int>& losers, vector<string>& candidates, vector<int>& allLosers) {
  int total = 0, min = 1000, max = 0;
  bool noWinnerExists = true;
  winners.clear();
  losers.clear();
  for(vector<int>::size_type i = 0; i < voteCount.size(); ++i) {
    total += voteCount[i];
    if(voteCount[i] > max) {
      max = voteCount[i];}
    if(voteCount[i] < min && voteCount[i] > 0) {
      min = voteCount[i];}
  }
  
//  cout << "Max " << max << "   Min " << min << endl;
  if(max == min) {
    noWinnerExists = false;}

  for(vector<int>::size_type i = 0; i < voteCount.size(); ++i) {
    if(voteCount[i] > (total / 2)) {
      noWinnerExists = false;
      winners.push_back(candidates[i]);}
    else if(voteCount[i] == max) {
      winners.push_back(candidates[i]);}
    if(voteCount[i] == min) {
    //  cout << "Loser" << i+1 << " " << voteCount[i] << endl;
      losers.push_back(i);
      allLosers.push_back(i);}
  }
  return noWinnerExists;
}

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
//  for(vector<int>::size_type i = 0; i < voteCount.size(); ++i) {
//    cout << voteCount[i] << " ";
//  }
//  cout << endl;
  vector<string> winners;
  vector<int> losers, allLosers;
  bool noWinnerYet = findWinner(voteCount, winners, losers, candidates, allLosers);
  while(noWinnerYet) {
    reassignVotes(voteCount, losers, allVotes, allLosers);
    noWinnerYet = findWinner(voteCount, winners, losers, candidates, allLosers);
  }
  print(w, winners);

  allVotes.clear();
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
