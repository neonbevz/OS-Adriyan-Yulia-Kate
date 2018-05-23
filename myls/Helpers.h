#ifndef MYLS_HELPERS_H
#define MYLS_HELPERS_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// Check for options

bool checkOneDash(string str);

bool checkTwoDashes(string str);

// Parse args

vector<string> toVector(int argc, char *argv[]);

vector<string> toOptions(vector<string> argvec);

vector<string> toDirs(vector<string> argvec);

// Error to stderr

void printError(int errnum);

// Look for specific options

string getSort(vector<string> optsvec);

bool inVector(const string &value, const vector<string> &vec);


#endif //MYLS_HELPERS_H
