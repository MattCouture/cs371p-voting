#include <cassert>
#include <iostream>

#include "Voting.h"

using namespace std;

bool read(std::istream& r, int i) {
}

int count(std::istream& r) {
}

void print(std::ostream& r, String winner) {
}

int solve(std::istream& r, std::ostream& w) {
  int numCand;
  r >> numCand;
}

void numElections(std::istream& r) {
  int x;
  r >> x;
  for(int y = 0; y < x; ++y) {
    char c;
    r >> c;
    r >> c;
    solve(r, cout);
  }
}
