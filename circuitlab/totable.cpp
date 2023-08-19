#include"totable.h"
using namespace std;

int totable::tolength(int t) {
	int temp = 1;
	while (t--) {
		temp *= 2;
	}
	return temp;
}

vector<int> get_location(int length, int number) {
	vector<int>t;
	for (int i = 0; i < length; i++) {
		int t1 = number % 2;
		number /= 2;

		t.push_back(t1);
	}

	return t;
}

bool totable::init1() {//给出第一种初始化的形式
	cout << "请输入变量的个数：";
	cin >> bits;
	cout << "请输入值为1的数的个数：";
	cin >> minn;

	cout << "输入为1的项的十进制数：";
	for (int i = 0; i < minn; i++) {
		int x;
		cin >> x;
		minint.push_back(x);
		minbin.push_back(funt.tostring(bits, x));
	}

	/*cout << "\n二进制的输入为：" << endl;
	for (int i = 0; i < minn; i++) {
		cout << "(" << i << ")" << minbin[i] << endl;
	}*/
	if (minint.size() == tolength(bits))return false;

	table = vector<vector<string>>(bits + 1);
	return true;
}

bool totable::init2() {
	cout << "请输入变量的个数：";
	cin >> bits;
	int cnt = 0;

	for (int i = 0; i < bits; i++) {
		char ch = 'A' + i;
		cout << ch << "  ";
	}
	cout << "Y" << endl;

	int len = tolength(bits);

	int check;
	for (int i = 0; i < len; i++) {
		int t1 = i;
		int t2 = i;
		vector<int>part;
		for (int j = 0; j < bits; j++) {
			part.push_back(t1 % 2);//先将其存进part数组里面
			t1 /= 2;
		}

		for (int j = bits - 1; j >= 0; j--) {
			cout << part[j] << "  ";
		}

		cin >> check;
		if (check == 1) {
			cnt++;
			minint.push_back(t2);
			minbin.push_back(funt.tostring(bits, t2));
		}

	}
	if (minint.size() == len)return false;

	this->minn = cnt;
	table = vector<vector<string>>(bits + 1);
	return true;
}

bool totable::init3() {
	vector<vector<char>>store;//这个来储存多个表达式

	vector<int>location;



	int cnt = 0;
	string line;
	cout << "请输入变量的个数：";
	cin >> bits;
	cout << "请输入需要化简的表达式(eg: AB+AB'+C )：" << endl;
	cin >> line;

	int maxn = tolength(bits);

	//check数组的目的一来防止重复的标记，二来实现真值表中为1的判别
	vector<bool>check(maxn);//先创建出来这样的空间来储存
	for (int i = 0; i < maxn; i++) {
		check[i] = false;//先全部初始化为false
	}


	//初始化来储存的两个数组
	vector<int>t0(bits);
	vector<int>t1(bits);
	for (int m = 0; m < bits; m++)t0[m] = 0;
	for (int m = bits - 1; m >= 0; m--) {
		int tt = bits - m - 1;
		t1[m] = tolength(tt);
	}
	//一个是储存为0时候的情况，一个是储存为1时的情况


	vector<char>t;
	//这部分把表达式给从+号中间拆开，然后放进存放的数组
	for (int i = 0; i < line.size(); i++) {
		if (line[i] != '+') {//如果不是+号的话
			char c = line[i];
			t.push_back(c);
		}

		if ((i == line.size() - 1) || (line[i] == '+')) {
			store.push_back(t);
			t.clear();
		}
	}



	//先初始化好标记
	bool sign = true;
	//开始遍历然后一步步的标记
	for (int i = 0; i < store.size(); i++) {
		for (int j = store[i].size() - 1; j >= 0; j--) {
			//从后往前看，这样能更好的判断出逆


			if (store[i][j] == '\'') {
				sign = false;//符号先变化
			}


			//先把t1 t0都进行修改
			else if (store[i][j] >= 'A' && store[i][j] <= 'Z') {
				if (sign == true) {
					int n = store[i][j] - 'A';
					t0[n] = t1[n];
				}
				else {
					int n = store[i][j] - 'A';
					t1[n] = 0;
				}

				sign = true;//在最后，把符号改回来
			}

			//cout << "1";	//测试


		}

		for (int k = 0; k < maxn; k++) {
			vector<int>location = get_location(bits, k);//定位，看看需要取出来是t0还是t1
			int all = 0;
			for (int p = 0; p < bits; p++) {
				if (location[p] == 0) {
					all += t0[p];
				}

				else {
					all += t1[p];
				}
			}

			if (check[all] == false) {
				check[all] = true;
				minint.push_back(all);
				minbin.push_back(funt.tostring(bits, all));
				cnt++;
			}

		}

		for (int m = 0; m < bits; m++)t0[m] = 0;
		for (int m = bits - 1; m >= 0; m--) {
			int tt = bits - m - 1;
			t1[m] = tolength(tt);
		}
	}
	int len = tolength(bits);
	if (minint.size() == len)return false;

	this->minn = cnt;
	table = vector<vector<string>>(bits + 1);
	return true;
}


void totable::init4() {
	vector<vector<char>>store;//这个来储存多个表达式

	vector<int>location;



	int cnt = 0;
	string line;
	cout << "请输入变量的个数：";
	cin >> bits;
	cout << "请输入需要转化为真值表的表达式(eg: AB+AB'+C )：" << endl;
	cin >> line;

	int maxn = tolength(bits);

	//check数组的目的一来防止重复的标记，二来实现真值表中为1的判别
	vector<bool>check(maxn);//先创建出来这样的空间来储存
	for (int i = 0; i < maxn; i++) {
		check[i] = false;//先全部初始化为false
	}


	//初始化来储存的两个数组
	vector<int>t0(bits);
	vector<int>t1(bits);
	for (int m = 0; m < bits; m++)t0[m] = 0;
	for (int m = bits - 1; m >= 0; m--) {
		int tt = bits - m - 1;
		t1[m] = tolength(tt);
	}
	//一个是储存为0时候的情况，一个是储存为1时的情况


	vector<char>t;
	//这部分把表达式给从+号中间拆开，然后放进存放的数组
	for (int i = 0; i < line.size(); i++) {
		if (line[i] != '+') {//如果不是+号的话
			char c = line[i];
			t.push_back(c);
		}

		if ((i == line.size() - 1) || (line[i] == '+')) {
			store.push_back(t);
			t.clear();
		}
	}



	//先初始化好标记
	bool sign = true;
	//开始遍历然后一步步的标记
	for (int i = 0; i < store.size(); i++) {
		for (int j = store[i].size() - 1; j >= 0; j--) {
			//从后往前看，这样能更好的判断出逆


			if (store[i][j] == '\'') {
				sign = false;//符号先变化
			}


			//先把t1 t0都进行修改
			else if (store[i][j] >= 'A' && store[i][j] <= 'Z') {
				if (sign == true) {
					int n = store[i][j] - 'A';
					t0[n] = t1[n];
				}
				else {
					int n = store[i][j] - 'A';
					t1[n] = 0;
				}

				sign = true;//在最后，把符号改回来
			}

			//cout << "1";	//测试


		}

		for (int k = 0; k < maxn; k++) {
			vector<int>location = get_location(bits, k);//定位，看看需要取出来是t0还是t1
			int all = 0;
			for (int p = 0; p < bits; p++) {
				if (location[p] == 0) {
					all += t0[p];
				}

				else {
					all += t1[p];
				}
			}

			if (check[all] == false) {
				check[all] = true;
				minint.push_back(all);
				minbin.push_back(funt.tostring(bits, all));
				cnt++;
			}

		}

		for (int m = 0; m < bits; m++)t0[m] = 0;
		for (int m = bits - 1; m >= 0; m--) {
			int tt = bits - m - 1;
			t1[m] = tolength(tt);
		}
	}

	for (int i = 0; i < bits; i++) {
		char ch = 'A' + i;
		cout << ch << "  ";
	}
	cout << "Y" << endl;

	int len = tolength(bits);

	for (int i = 0; i < len; i++) {
		int t1 = i;
		int t2 = i;
		vector<int>part;
		for (int j = 0; j < bits; j++) {
			part.push_back(t1 % 2);//先将其存进part数组里面
			t1 /= 2;
		}

		for (int j = bits - 1; j >= 0; j--) {
			cout << part[j] << "  ";
		}

		if (check[i] == true)cout << "1" << endl;
		else cout << "0" << endl;
	}
}

void totable::setprime() {
	set<string>tempprime;
	createtable();

	while (!funt.is_empty(table)) {
		table = combined(table, tempprime);
	}

	set<string>::iterator it;
	for (it = tempprime.begin(); it != tempprime.end(); it++) {
		string t = *it;
		primed.push_back(t);
	}

	/*cout << "\n化简最后的结果为：" << endl;
	for (int i = 0; i < tempprime.size(); i++) {
		cout << "(" << i << ")" << funt.bintostring(primed[i]) << endl;
	}*/
}


void totable::createtable() {
	//vector<vector<string>>table(100,vector<string>(100));
	for (int i = 0; i < minn; i++) {
		int num = funt.getone(minbin[i]);
		table[num].push_back(minbin[i]);
	}

	/*cout << "\ntable：" << endl;
	for (int i = 0; i < bits + 1; i++) {
		cout << "(" << i << ")";
		for (int j = 0; j < table[i].size(); j++) {
			cout << table[i][j]<<",";
		}
		cout << endl;
	}*/
}


vector<vector<string>> totable::combined(vector<vector<string>> table1, set<string>& tempprime) {
	vector<vector<bool>>check(table1.size(), vector<bool>(minn));

	vector<vector<string>>newtable(table1.size() - 1);

	for (int i = 0; i < table.size(); i++) {//将其进行初始化,全部化为false
		for (int j = 0; j < minn; j++) {
			check[i][j] = false;
		}
	}

	for (int i = 0; i < table1.size() - 1; i++) {//全部遍历
		for (int j = 0; j < table1[i].size(); j++) {
			for (int k = 0; k < table1[i + 1].size(); k++) {
				if (funt.compare(table1[i][j], table1[i + 1][k])) {
					newtable[i].push_back(funt.getcombine(table[i][j], table[i + 1][k]));
					check[i][j] = true;
					check[i + 1][k] = true;
				}
			}
		}
	}

	for (int i = 0; i < table1.size(); i++) {
		for (int j = 0; j < table1[i].size(); j++) {
			if (!check[i][j]) {
				tempprime.insert(table1[i][j]);
			}
		}
	}

	return newtable;
}

void totable::show() {

	//cout << "可能的表达式为:" << endl;
	cout << endl;

	for (int i = 0; i < function.size(); i++) {
		set<int> functiont = function[i];
		set<int>::iterator it;
		cout << "函数" << i + 1 << ":" << endl;
		for (it = functiont.begin(); it != functiont.end(); it++) {
			int temp = *it;
			cout << funt.bintostring(primed[temp]) << "+";
		}
		cout << "\b \n";
	}
}


void totable::minimise() {
	vector<vector<bool>> primechart(primed.size(), vector<bool>(minn));//vs不能用非常量来初始化
	//实现的功能类似于primechart[primed.size()][minn]={{false}}
	//进行初始化的过程
	for (int i = 0; i < primed.size(); i++) {
		for (int j = 0; j < minn; j++) {
			primechart[i][j] = false;
		}
	}


	//先建立这个表格
	for (int i = 0; i < primed.size(); i++) {
		for (int j = 0; j < minn; j++) {
			primechart[i][j] = funt.is_prime(primed[i], minbin[j]);
		}
	}


	//对于质蕴含项的输出
	//***为测试项实际操作时不输出

	/*cout << "质蕴涵项的表格为：(行为质蕴涵项，列为最小项)" << endl;
	for (int i = 0; i < primed.size(); i++) {
		for (int j = 0; j < minn; j++) {
			if (primechart[i][j] == true)cout << "1\t";
			else cout << "0\t";
		}
		cout << endl;
	}*/



	//用佩德里科方法来求解
	vector<set<int>> patlogic;
	for (int j = 0; j < minn; j++) {
		set<int> temp;
		for (int i = 0; i < primed.size(); i++) {
			if (primechart[i][j] == true)temp.insert(i);
		}
		patlogic.push_back(temp);
	}

	//***测试用
	/*cout << "Petrick method的展示(行是最小项，列是质蕴涵项)" << endl;

	for (int i = 0; i < patlogic.size(); i++) {
		set<int>::iterator it;
		for (it = patlogic[i].begin(); it != patlogic[i].end(); it++) {
			int temp = *it;
			cout << temp << " ";
		}
		cout << endl;
	}*/


	set<set<int>>poscom;
	set<int>prod;
	get_allcombination(patlogic, 0, prod, poscom);

	//cout << "满足所有最小项的可能的组合为：" << endl;

	set<set<int>>::iterator it;
	it = poscom.begin();
	set<int>comb = *it;
	int min = 99999;

	for (it = poscom.begin(); it != poscom.end(); it++) {
		set<int>comb = *it;
		if (comb.size() < min) {
			min = comb.size();
		}

		//测试用的输出
		/*set<int>::iterator itr;
		for (itr = comb.begin(); itr != comb.end(); itr++) {
			int temp = *itr;
			cout << temp << " ";
		}
		cout << endl; */
	}


	//cout << "获得最小值的组合和最小的变量" << endl;

	vector<set<int>>mincom;
	//set<set<int>>::iterator it;
	for (it = poscom.begin(); it != poscom.end(); it++) {
		set<int>com = *it;
		if (com.size() == min) {
			mincom.push_back(com);
		}
	}


	//
	min = 0xffff;
	for (int i = 0; i < mincom.size(); i++) {
		if (funt.getvar(mincom[i], this->primed) < min) {
			min = funt.getvar(mincom[i], this->primed);
		}
	}


	for (int i = 0; i < mincom.size(); i++) {
		if (funt.getvar(mincom[i], this->primed) == min) {
			function.push_back(mincom[i]);
		}
	}


}



void totable::get_allcombination(vector<set<int>>& patlogic, int level, set<int>prod, set<set<int>>& poscom) {
	//递归函数的形式来将patlogic中的元素放进poscom中

	//
	if (level == patlogic.size()) {
		set<int> temp = prod;
		poscom.insert(temp);
		return;
	}

	else {
		set<int>::iterator it;
		for (it = patlogic[level].begin(); it != patlogic[level].end(); it++) {
			int temp = *it;
			bool inserted = prod.insert(temp).second;
			get_allcombination(patlogic, level + 1, prod, poscom);

			if (inserted) {
				prod.erase(temp);
			}
		}
	}


}