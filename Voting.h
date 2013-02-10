#ifndef Voting_h
#define Voting_h

#include <iostream>

bool read(std::istream&, int&);

int count(std::istream&);

void print(std::ostream&, String);

void solve(std::istream&, std::ostream&);

#endif
