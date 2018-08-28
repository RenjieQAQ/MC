#include <iostream>

#include <assert.h>

using std::cout;
using std::endl;
const int miss_total = 3;
const int Cann_total = 3;
int miss_num = 3;
int Cann_num = 3;
bool is_back = false;
int mask[4][4];
bool sccuss() {
	if ((miss_num == 0) && (Cann_num == 0))
		return true;
	else
		return false;
}
int check(int miss_cross_num, int Cann_cross_num) {
	assert((miss_cross_num *Cann_cross_num) >= 0);	//同号
	assert( abs(miss_cross_num+Cann_cross_num)<=2 );//检查操作的人数是否满足要求
	if ((miss_num < miss_cross_num)|| (Cann_num < Cann_cross_num))//检查操作的剩余人数是否满足要求
		return -1;
	if (mask[miss_num - miss_cross_num][Cann_num- Cann_cross_num] == 1)//检查掩码
		return -1;
	if ((miss_num - miss_cross_num)<(Cann_num- Cann_cross_num))//检查此岸是否安全
		return -1;
	if ((miss_total - miss_num + miss_cross_num)<(Cann_total - Cann_num + Cann_cross_num))//检查彼岸是否安全
		return -1;
	mask[miss_num - miss_cross_num][Cann_num - Cann_cross_num] = 1;
	return 0;
}
int crossMM() {
	if (check(2, 0) < 0)
		return -1;
	miss_num = miss_num - 2;
	is_back = true;
	return 0;
}
int crossCC() {
	if (check(0, 2) < 0)
		return -1;
	Cann_num = Cann_num - 2;
	is_back = true;
	return 0;
}
int crossMC() {
	if (check(1, 1) < 0)
		return -1;
	miss_num--;
	Cann_num--;
	is_back = true;
	return 0;
}

int crossM() {
	if (check(1, 0) < 0)
		return -1;
	miss_num--;
	is_back = true;
	return 0;
}

int crossC() {
	if (check(0, 1) < 0)
		return -1;
	Cann_num--;
	is_back = true;
	return 0;
}

int backMM() {
	if (check(-2, 0) < 0)
		return -1;
	miss_num = miss_num + 2;
	is_back = false;
	return 0;
}
int backCC() {
	if (check(0, -2) < 0)
		return -1;
	Cann_num = Cann_num + 2;
	is_back = false;
	return 0;
}
int backMC() {
	if (check(-1, -1) < 0)
		return -1;
	miss_num++;
	Cann_num++;
	is_back = false;
	return 0;
}

int backM() {
	if (check(-1, 0) < 0)
		return -1;
	miss_num++;
	is_back = false;
	return 0;
}
int backC() {
	if (check(0, -1) < 0)
		return -1;
	Cann_num++;
	is_back = false;
	return 0;
}

int workout() {
	if (sccuss()) {
		cout << "succuss!" << endl;
		return 0;
	}
	if (is_back) {
		if (backMM() == 0) {
			if (workout() < 0) {

			}
		}
		if (backCC() == 0) {
			workout();
		}
		if (backMC() == 0) {
			workout();
		}
		if (backM() == 0) {
			workout();
		}
		if (backC() == 0) {
			workout();
		}
	}
	else {
		if (crossMM() == 0) {
			workout();
		}
		if (crossCC() == 0) {
			workout();
		}
		if (crossMC() == 0) {
			workout();
		}
		if (crossM() == 0) {
			workout();
		}
		if (crossC() == 0) {
			workout();
		}
	}
	return -1;

}
int main() {
	cout<<"Hello!"<<endl;
	workout();
	system("pause");
	return 0;
}

