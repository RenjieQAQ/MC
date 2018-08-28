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
int check(const int m_num, const int c_num,const unsigned char mask[16], const int miss_cross_num, const int Cann_cross_num) {
	assert((miss_cross_num *Cann_cross_num) >= 0);	//ͬ��
	assert( abs(miss_cross_num+Cann_cross_num)<=2 );//�������������Ƿ�����Ҫ��
	if ((m_num < miss_cross_num)|| (c_num < Cann_cross_num))//��������ʣ�������Ƿ�����Ҫ��
		return -1;
	if (mask[(m_num - miss_cross_num)*4+c_num - Cann_cross_num] == 1)//�������
		return -2;
	if ((m_num - miss_cross_num>0)&&((m_num - miss_cross_num)<(c_num - Cann_cross_num)))//���˰��Ƿ�ȫ
		return -3;
	if (((miss_total - m_num + miss_cross_num)>0) && ((miss_total - m_num + miss_cross_num)<(cann_total - c_num + Cann_cross_num)))//���˰��Ƿ�ȫ
		return -4;
	return 0;
}


int opiton(int m_num, int c_num, unsigned char mask[16],bool& is_back,int miss_cross_num, int Cann_cross_num) {
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
	if (abs(m) > 3) {
		;
	}
	if (abs(c) > 3) {
		;
	}
	cout << "����" << m << "���޵�ʿ" << c << "��Ұ��," ;
	if ((mcn > 0) || (ccn > 0))
		cout << mcn << "���޵�ʿ" << ccn << "��Ұ�˶ɺ�" << endl;
	else
		cout << 0 - mcn << "���޵�ʿ" << 0 - ccn << "��Ұ�˻ص��˰�"<< endl;

}
const int opt_table[5][2] = { {0,1},{1,0},{1,1},{0,2},{2,0} };
int workout(const int m_num, const int c_num,const unsigned char mask[16],const bool flag) {
	static int index = 0;
	if (sccuss(m_num, c_num, flag)) {
		cout << "succuss!" << endl;
		return 0;
	}

	for (int i = 0; i < 5; i++) {
		bool is_back = flag;
		//opiton(m_num, m_num, this_mask, is_back, opt_table[i][0], opt_table[i][1]);
		int mcn = opt_table[i][0], ccn = opt_table[i][1];
		int miss_num = m_num, cann_num = c_num;
		if (abs(miss_num) > 3) {
			;
		}
		if (abs(cann_num) > 3) {
			;
		}
		if (is_back) {
			mcn = 0 - mcn;
			ccn = 0 - ccn;
		}
		//printOpt1(miss_num, cann_num, mcn, ccn);
		int res = check(miss_num, cann_num, mask, mcn, ccn);
		if (res < 0) {
			/*if (res == -1)
				cout << "	������֧�ִ˲���" << endl;
			if (res == -2)
				cout << "	�ظ���ǰ��״̬" << endl;
			if(res == -3)
				cout << "	��Ұ��̫��" << endl;
			if (res == -4)
				cout << "	�Ұ�Ұ��̫��" << endl;*/
			continue;
		}
		unsigned char *this_mask = new unsigned char[16];
		memcpy(this_mask, mask, 16);
		this_mask[(miss_num - mcn) * 4 + cann_num - ccn] = 1;
		miss_num -= mcn;
		miss_num -= ccn;
		is_back = !is_back;
		int in = index;
		cout << index++ << endl;
		//printOpt(m_num, c_num,mcn, ccn);
		workout(miss_num, cann_num, this_mask, is_back);

		cout <<"d"<<in << endl;
		delete[] this_mask;
	}
	return -1;

}

int main() {
	unsigned char mask[16];
	memset(mask,0,16);
	mask[3*4+3] = 1;
	workout(miss_total, cann_total, mask,0);
	system("pause");
	return 0;
}

