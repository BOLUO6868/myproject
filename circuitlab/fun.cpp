#include"fun.h"
using namespace std;


string fun::tostring(int size, int val) {
	string bin;
	bin = bitset<100>(val).to_string();
	bin = bin.substr(100 - size);
	return bin;
}


int fun::getone(string t) {
	int cnt = 0;//用来记录数量
	for (int i = 0; i < t.size(); i++) {
		if (t[i] == '1') {//因为转化为了string的形式一定要加上''
			cnt++;
		}
	}
	return cnt;
}


bool fun::compare(string t1, string t2) {//查看两个字符串中的1相差是否为1
	int cnt = 0;
	for (int i = 0; i < t1.length(); i++) {
		if (t1[i] != t2[i])cnt++;
	}
	if (cnt == 1)return true;
	else return false;
}


string fun::getcombine(string t1, string t2) {
	for (int i = 0; i < t1.length(); i++) {
		if (t1[i] != t2[i])t1[i] = '-';
	}
	return t1;
}


bool fun::is_empty(vector<vector<string>>chart) {
	for (int i = 0; i < chart.size(); i++) {
		if (chart[i].size() != 0) {
			return false;//如果有一个不为空，就不为空
		}
	}
	return true;
}


string fun::bintostring(string t) {//转化为表达形式
	string total = "";
	for (int i = 0; i < t.size(); i++) {
		if (t[i] == '1') {
			char temp = 'A' + i;
			total += temp;
		}
		else if (t[i] == '0') {
			char temp = 'A' + i;
			total += temp;
			total += "'";
		}
	}
	return total;
}


bool fun::is_prime(string temp, string minterm) {//在其位数的位置不为-时且有不相等的时候返回false
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] != '-') {
			if (temp[i] != minterm[i]) {
				return false;
			}
		}
	}
	return true;
}


int fun::getvar(set<int>comb, vector<string>primeimp) {
	int cnt = 0;
	set<int>::iterator it;
	for (it = comb.begin(); it != comb.end(); it++) {
		int imp = *it;
		for (int i = 0; i < primeimp[imp].size(); i++) {
			if (primeimp[imp][i] != '-') {
				cnt++;
			}
		}
	}
	return cnt;
}