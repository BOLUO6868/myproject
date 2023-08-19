#ifndef _FUN_H_
#define _FUN_H_

#include<iostream>
#include<vector>
#include<set>
#include<bitset>
#include<algorithm>
#include<string>
using namespace std;

class fun {
public:
	string tostring(int, int);
	int getone(string);
	bool compare(string, string);
	string getcombine(string, string);
	bool is_empty(vector<vector<string>>);
	string bintostring(string);
	bool is_prime(string, string);
	int getvar(set<int>, vector<string>);

};


#endif 


