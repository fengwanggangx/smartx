#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <ctime>
#include <exception>
#include <algorithm>
#include <cstdlib>

using namespace std;

void trimfl(string &str);

void trimall(string &str);

vector<string> split(const string& src, const string &separator);

int randint(int a, int b);
#endif // COMMON_H_INCLUDED
