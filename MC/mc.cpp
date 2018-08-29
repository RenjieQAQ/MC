#include <iostream>

#include <assert.h>

using std::cout;
using std::endl;
const int miss_total = 3;
const int cann_total = 3;
bool sccuss(int m_num, int c_num, bool flag) {
	if ((m_num == 0) && (c_num == 0))
		return true;
	else
		return false;
}
int check(const int m_num, const int c_num,const unsigned char mask[32], const int miss_cross_num, const int Cann_cross_num) {
	assert((miss_cross_num *Cann_cross_num) >= 0);	//ͬ��
	assert( abs(miss_cross_num+Cann_cross_num)<=2 );//�������������Ƿ�����Ҫ��
	int boot_is_right = 0;
	if ((miss_cross_num + Cann_cross_num) > 0)
		boot_is_right = 1;
	int new_m_num = m_num - miss_cross_num;
	int new_c_num = c_num - Cann_cross_num;

	if ((new_m_num < 0) || (new_m_num > miss_total) || (new_c_num < 0) || (new_c_num > cann_total)) {//��������ʣ�������Ƿ�����Ҫ��
		return -1;
	}
	
	if (mask[16 * boot_is_right + (m_num - miss_cross_num)*4+c_num - Cann_cross_num] == 1)//�������
		return -2;
	if ((new_m_num!=0)&&((m_num - miss_cross_num)<(c_num - Cann_cross_num)))//���˰��Ƿ�ȫ
		return -3;
	if (((miss_total - new_m_num)!=0) && ((miss_total - m_num + miss_cross_num)<(cann_total - c_num + Cann_cross_num)))//���˰��Ƿ�ȫ
		return -4;
	return 0;
}


int opiton(int m_num, int c_num, unsigned char mask[32],bool& is_back,int miss_cross_num, int Cann_cross_num) {
	int mcn = miss_cross_num, ccn = Cann_cross_num;

	if (is_back) {
		mcn = 0 - mcn;
		ccn = 0 - ccn;
	}
	if (check(m_num, c_num, mask,mcn, ccn) < 0)
		return -1;

	mask[(m_num - miss_cross_num)*4+c_num - Cann_cross_num] = 1;
	m_num += mcn;
	c_num += ccn;
	is_back = !is_back;
	return 0;
}

void printOpt(int m,int c,int mcn,int ccn) {
	if ((mcn > 0) || (ccn > 0))
		cout << mcn << "���޵�ʿ" << ccn << "��Ұ�˶ɺӣ�" ;
	else
		cout << 0-mcn << "���޵�ʿ" << 0-ccn << "��Ұ�˻ص��˰���";
	cout << "��ʣ" << m << "���޵�ʿ" << c << "��Ұ��" << endl;

}
void printOpt1(int m, int c, int mcn, int ccn) {
	//assert((abs(m)<=3) && (abs(c)<=3));
	cout << "����" << m << "���޵�ʿ" << c << "��Ұ��," ;
	if ((mcn > 0) || (ccn > 0))
		cout << mcn << "���޵�ʿ" << ccn << "��Ұ�˶ɺ�" << endl;
	else
		cout << 0 - mcn << "���޵�ʿ" << 0 - ccn << "��Ұ�˻ص��˰�"<< endl;

}
void printOpt2(int m, int c, int mcn, int ccn) {
	//assert((abs(m)<=3) && (abs(c)<=3));
	cout << "(" << m << "," << c << ")";
	if ((mcn + ccn) > 0) {
		cout << "---->(" << mcn << "," << ccn << ")  =";
	}
	else {
		cout << "<----(" << 0-mcn << "," << 0-ccn << ")  =";
	}
	cout << "(" << m - mcn << "," << c - ccn << ")" << endl;;

}
void printProblem(int res) {
	if (res == -1)
		cout << "	������֧�ִ˲���" << endl;
	if (res == -2)
		cout << "	�ظ���ǰ��״̬" << endl;
	if (res == -3)
		cout << "	��Ұ��̫��" << endl;
	if (res == -4)
		cout << "	�Ұ�Ұ��̫��" << endl;

}

const int opt_table[5][2] = { {0,1},{1,0},{1,1},{0,2},{2,0} };

void printStep(int *step,int n) {
	int m_num = miss_total;
	int c_num = cann_total;
	cout << "��ʼ״̬������" << m_num << "���޵�ʿ" << c_num << "��Ұ��"<<endl;
	for (int i = 0; i < n; i++) {
		cout << "����" << i + 1 << ":";
		if ((i % 2) == 0) {
			m_num -= opt_table[step[i]][0];
			c_num -= opt_table[step[i]][1];
			cout << opt_table[step[i]][0] << "���޵�ʿ" << opt_table[step[i]][1] << "��Ұ�˶ɺӣ�";
		}
		else {
			m_num += opt_table[step[i]][0];
			c_num += opt_table[step[i]][1];
			cout << opt_table[step[i]][0] << "���޵�ʿ" << opt_table[step[i]][1] << "��Ұ�˻ص��˰���";
		}

		cout << "��ʣ" << m_num << "���޵�ʿ" << c_num << "��Ұ��" << endl;
	}
}
int workout(const int m_num, const int c_num,const unsigned char mask[32],const bool flag,int n=0) {
	static int index = 0;
	static int step [20];
	static int ways = 0;
	if (sccuss(m_num, c_num, flag)) {
		ways++;
		cout<<"����"<<ways<<endl;
		printStep(step,n);
		cout << "�ɹ�����!���ܹ�"<<n<<"��" << endl;
		return ways;
	}

	for (int i = 0; i < 5; i++) {
		int level = n;
		bool boat_is_right = flag;
		//opiton(m_num, m_num, this_mask, is_back, opt_table[i][0], opt_table[i][1]);
		int mcn = opt_table[i][0], ccn = opt_table[i][1];
		int miss_num = m_num, cann_num = c_num;
		if (boat_is_right) {
			mcn = 0 - mcn;
			ccn = 0 - ccn;
		}
	
		int res = check(miss_num, cann_num, mask, mcn, ccn);
		if (res < 0) {
			//printProblem(res);
			
			continue;
		}
		//unsigned char *this_mask = new unsigned char[32];
		unsigned char this_mask[32];
		memcpy(this_mask, mask, 32);
		boat_is_right = !boat_is_right;
		int mask_index = 16 * boat_is_right + (miss_num - mcn) * 4 + cann_num - ccn;
		this_mask[mask_index] = 1;
		miss_num = miss_num - mcn;
		cann_num = cann_num - ccn;
		step[n] = i;
		workout(miss_num, cann_num, this_mask, boat_is_right,n+1);

	}
	return -1;

}

int main() {
	unsigned char mask[32];
	memset(mask,0,32);
	mask[3*4+3] = 1;
	workout(miss_total, cann_total, mask,0);
	system("pause");
	return 0;
}

