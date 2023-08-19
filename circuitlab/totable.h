#ifndef _TOTABLE_H_
#define _TOTABLE_H_

#include<iostream>
#include<vector>
#include<set>
#include<bitset>
#include<algorithm>
#include<string>
#include"fun.h"
using namespace std;

class totable {
private:
	fun funt;
	vector<int>minint;//十进制形式
	vector<string>minbin;//二进制形式
	int bits;
	int minn;
	vector<vector<string>>table;
	vector<string>primed;
	vector<set<int>> function;

public:
	bool init1();
	bool init2();
	bool init3();
	void init4();
	int tolength(int);
	void setprime();
	void createtable();
	vector<vector<string>> combined(vector<vector<string>>, set<string>& tempprime);
	void show();
	void minimise();
	void get_allcombination(vector<set<int>>&, int, set<int>, set<set<int>>&);
};




#endif