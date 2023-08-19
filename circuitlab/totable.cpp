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

bool totable::init1() {//������һ�ֳ�ʼ������ʽ
	cout << "����������ĸ�����";
	cin >> bits;
	cout << "������ֵΪ1�����ĸ�����";
	cin >> minn;

	cout << "����Ϊ1�����ʮ��������";
	for (int i = 0; i < minn; i++) {
		int x;
		cin >> x;
		minint.push_back(x);
		minbin.push_back(funt.tostring(bits, x));
	}

	/*cout << "\n�����Ƶ�����Ϊ��" << endl;
	for (int i = 0; i < minn; i++) {
		cout << "(" << i << ")" << minbin[i] << endl;
	}*/
	if (minint.size() == tolength(bits))return false;

	table = vector<vector<string>>(bits + 1);
	return true;
}

bool totable::init2() {
	cout << "����������ĸ�����";
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
			part.push_back(t1 % 2);//�Ƚ�����part��������
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
	vector<vector<char>>store;//��������������ʽ

	vector<int>location;



	int cnt = 0;
	string line;
	cout << "����������ĸ�����";
	cin >> bits;
	cout << "��������Ҫ����ı��ʽ(eg: AB+AB'+C )��" << endl;
	cin >> line;

	int maxn = tolength(bits);

	//check�����Ŀ��һ����ֹ�ظ��ı�ǣ�����ʵ����ֵ����Ϊ1���б�
	vector<bool>check(maxn);//�ȴ������������Ŀռ�������
	for (int i = 0; i < maxn; i++) {
		check[i] = false;//��ȫ����ʼ��Ϊfalse
	}


	//��ʼ�����������������
	vector<int>t0(bits);
	vector<int>t1(bits);
	for (int m = 0; m < bits; m++)t0[m] = 0;
	for (int m = bits - 1; m >= 0; m--) {
		int tt = bits - m - 1;
		t1[m] = tolength(tt);
	}
	//һ���Ǵ���Ϊ0ʱ��������һ���Ǵ���Ϊ1ʱ�����


	vector<char>t;
	//�ⲿ�ְѱ��ʽ����+���м�𿪣�Ȼ��Ž���ŵ�����
	for (int i = 0; i < line.size(); i++) {
		if (line[i] != '+') {//�������+�ŵĻ�
			char c = line[i];
			t.push_back(c);
		}

		if ((i == line.size() - 1) || (line[i] == '+')) {
			store.push_back(t);
			t.clear();
		}
	}



	//�ȳ�ʼ���ñ��
	bool sign = true;
	//��ʼ����Ȼ��һ�����ı��
	for (int i = 0; i < store.size(); i++) {
		for (int j = store[i].size() - 1; j >= 0; j--) {
			//�Ӻ���ǰ���������ܸ��õ��жϳ���


			if (store[i][j] == '\'') {
				sign = false;//�����ȱ仯
			}


			//�Ȱ�t1 t0�������޸�
			else if (store[i][j] >= 'A' && store[i][j] <= 'Z') {
				if (sign == true) {
					int n = store[i][j] - 'A';
					t0[n] = t1[n];
				}
				else {
					int n = store[i][j] - 'A';
					t1[n] = 0;
				}

				sign = true;//����󣬰ѷ��ŸĻ���
			}

			//cout << "1";	//����


		}

		for (int k = 0; k < maxn; k++) {
			vector<int>location = get_location(bits, k);//��λ��������Ҫȡ������t0����t1
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
	vector<vector<char>>store;//��������������ʽ

	vector<int>location;



	int cnt = 0;
	string line;
	cout << "����������ĸ�����";
	cin >> bits;
	cout << "��������Ҫת��Ϊ��ֵ��ı��ʽ(eg: AB+AB'+C )��" << endl;
	cin >> line;

	int maxn = tolength(bits);

	//check�����Ŀ��һ����ֹ�ظ��ı�ǣ�����ʵ����ֵ����Ϊ1���б�
	vector<bool>check(maxn);//�ȴ������������Ŀռ�������
	for (int i = 0; i < maxn; i++) {
		check[i] = false;//��ȫ����ʼ��Ϊfalse
	}


	//��ʼ�����������������
	vector<int>t0(bits);
	vector<int>t1(bits);
	for (int m = 0; m < bits; m++)t0[m] = 0;
	for (int m = bits - 1; m >= 0; m--) {
		int tt = bits - m - 1;
		t1[m] = tolength(tt);
	}
	//һ���Ǵ���Ϊ0ʱ��������һ���Ǵ���Ϊ1ʱ�����


	vector<char>t;
	//�ⲿ�ְѱ��ʽ����+���м�𿪣�Ȼ��Ž���ŵ�����
	for (int i = 0; i < line.size(); i++) {
		if (line[i] != '+') {//�������+�ŵĻ�
			char c = line[i];
			t.push_back(c);
		}

		if ((i == line.size() - 1) || (line[i] == '+')) {
			store.push_back(t);
			t.clear();
		}
	}



	//�ȳ�ʼ���ñ��
	bool sign = true;
	//��ʼ����Ȼ��һ�����ı��
	for (int i = 0; i < store.size(); i++) {
		for (int j = store[i].size() - 1; j >= 0; j--) {
			//�Ӻ���ǰ���������ܸ��õ��жϳ���


			if (store[i][j] == '\'') {
				sign = false;//�����ȱ仯
			}


			//�Ȱ�t1 t0�������޸�
			else if (store[i][j] >= 'A' && store[i][j] <= 'Z') {
				if (sign == true) {
					int n = store[i][j] - 'A';
					t0[n] = t1[n];
				}
				else {
					int n = store[i][j] - 'A';
					t1[n] = 0;
				}

				sign = true;//����󣬰ѷ��ŸĻ���
			}

			//cout << "1";	//����


		}

		for (int k = 0; k < maxn; k++) {
			vector<int>location = get_location(bits, k);//��λ��������Ҫȡ������t0����t1
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
			part.push_back(t1 % 2);//�Ƚ�����part��������
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

	/*cout << "\n�������Ľ��Ϊ��" << endl;
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

	/*cout << "\ntable��" << endl;
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

	for (int i = 0; i < table.size(); i++) {//������г�ʼ��,ȫ����Ϊfalse
		for (int j = 0; j < minn; j++) {
			check[i][j] = false;
		}
	}

	for (int i = 0; i < table1.size() - 1; i++) {//ȫ������
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

	//cout << "���ܵı��ʽΪ:" << endl;
	cout << endl;

	for (int i = 0; i < function.size(); i++) {
		set<int> functiont = function[i];
		set<int>::iterator it;
		cout << "����" << i + 1 << ":" << endl;
		for (it = functiont.begin(); it != functiont.end(); it++) {
			int temp = *it;
			cout << funt.bintostring(primed[temp]) << "+";
		}
		cout << "\b \n";
	}
}


void totable::minimise() {
	vector<vector<bool>> primechart(primed.size(), vector<bool>(minn));//vs�����÷ǳ�������ʼ��
	//ʵ�ֵĹ���������primechart[primed.size()][minn]={{false}}
	//���г�ʼ���Ĺ���
	for (int i = 0; i < primed.size(); i++) {
		for (int j = 0; j < minn; j++) {
			primechart[i][j] = false;
		}
	}


	//�Ƚ���������
	for (int i = 0; i < primed.size(); i++) {
		for (int j = 0; j < minn; j++) {
			primechart[i][j] = funt.is_prime(primed[i], minbin[j]);
		}
	}


	//�������̺�������
	//***Ϊ������ʵ�ʲ���ʱ�����

	/*cout << "���̺���ı��Ϊ��(��Ϊ���̺����Ϊ��С��)" << endl;
	for (int i = 0; i < primed.size(); i++) {
		for (int j = 0; j < minn; j++) {
			if (primechart[i][j] == true)cout << "1\t";
			else cout << "0\t";
		}
		cout << endl;
	}*/



	//�������Ʒ��������
	vector<set<int>> patlogic;
	for (int j = 0; j < minn; j++) {
		set<int> temp;
		for (int i = 0; i < primed.size(); i++) {
			if (primechart[i][j] == true)temp.insert(i);
		}
		patlogic.push_back(temp);
	}

	//***������
	/*cout << "Petrick method��չʾ(������С��������̺���)" << endl;

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

	//cout << "����������С��Ŀ��ܵ����Ϊ��" << endl;

	set<set<int>>::iterator it;
	it = poscom.begin();
	set<int>comb = *it;
	int min = 99999;

	for (it = poscom.begin(); it != poscom.end(); it++) {
		set<int>comb = *it;
		if (comb.size() < min) {
			min = comb.size();
		}

		//�����õ����
		/*set<int>::iterator itr;
		for (itr = comb.begin(); itr != comb.end(); itr++) {
			int temp = *itr;
			cout << temp << " ";
		}
		cout << endl; */
	}


	//cout << "�����Сֵ����Ϻ���С�ı���" << endl;

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
	//�ݹ麯������ʽ����patlogic�е�Ԫ�طŽ�poscom��

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