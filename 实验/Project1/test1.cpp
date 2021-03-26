#include <iostream>
#include <cstring>
using namespace std;

char prog[800];	//�洢���� 
char token[10];	//�洢�����ַ���
char ch;	//��ǰ�ַ� 
int syn;	//�����ֱ��� 
int sum;	//���ͳ��� 
int p;	//progָ��
int m;	//tokenָ��
int n;
//�ؼ��� 
const char* rwtab[6] = { "begin", "if", "then", "while", "do", "end" };

bool isLetter(char ch);	//�ж��Ƿ�Ϊ��ĸ 
bool isDigit(char ch);	//�ж��Ƿ�Ϊ���� 
void scanner();			//ɨ������� 

bool isLetter(char ch) {
	if ((ch <= 'z' && ch >= 'a') || (ch < 'Z' && ch >= 'A')) {
		return true;
	}
	else {
		return false;
	}
}

bool isDigit(char ch) {
	if (ch >= '0' && ch <= '9') {
		return true;
	}
	else {
		return false;
	}

}

void scanner() {
	//���token 
	for (n = 0; n < 8; n++) {
		token[n] = NULL;
	}
	m = 0;

	//��ȡ��һ����Ч�ַ� 
	ch = prog[p];
	while (ch == ' ') {
		p++;
		ch = prog[p];
	}

	if (isDigit(ch)) {
		//�ַ�Ϊ���� 
		sum = 0;
		while (isDigit(ch)) {
			sum = sum * 10 + ch - '0';	//strת��Ϊ��ֵ����
			p++;
			ch = prog[p];
			syn = 11;
		}
	}
	//�ַ�Ϊ�ַ��� 
	else if (isLetter(ch)) {
		while (isDigit(ch) || isLetter(ch)) {
			token[m] = ch;
			m++;
			p++;
			ch = prog[p];
		}
		token[m] = '\0';
		m++;
		syn = 10;
		for (n = 0; n < 6; n++) {
			if (strcmp(token, rwtab[n]) == 0) {
				syn = n + 1;
				break;
			}
		}
	}
	else {
		switch (ch) {
		case '<':
			syn = 20;
			m = 0;
			token[m] = ch;
			m++;
			p++;
			ch = prog[p];
			if (ch == '>') {
				syn = 21;
				token[m] = ch;
				m++;
				p++;
				ch = prog[p];
			}
			else if (ch == '=') {
				syn = 22;
				token[m++] = ch;
				m++;
				p++;
				ch = prog[p];
			}
			break;

		case '>':
			syn = 23;
			m = 0;
			token[m++] = ch;
			p++;
			ch = prog[p];
			if (ch == '=') {
				syn = 24;
				token[m] = ch;
				m++;
				p++;
				ch = prog[p];
			}
			break;

		case ':':
			syn = 17;
			m = 0;
			token[m] = ch;
			m++;
			p++;
			ch = prog[p];
			if (ch == '=') {
				syn = 18;
				token[m] = ch;
				m++;
				p++;
				ch = prog[p];
			}
			break;

		case '+':
			syn = 13;
			token[0] = ch;
			p++;
			ch = prog[p];
			break;

		case '-':
			syn = 14;
			token[0] = ch;
			p++;
			ch = prog[p];
			break;

		case '*':
			syn = 15;
			token[0] = ch;
			p++;
			ch = prog[p];
			break;

		case '/':
			syn = 16;
			token[0] = ch;
			p++;
			ch = prog[p];
			break;

		case '=':
			syn = 25;
			token[0] = ch;
			p++;
			ch = prog[p];
			break;

		case ';':
			syn = 26;
			token[0] = ch;
			p++;
			ch = prog[p];
			break;

		case '(':
			syn = 27;
			token[0] = ch;
			p++;
			ch = prog[p];
			break;

		case ')':
			syn = 28;
			token[0] = ch;
			p++;
			ch = prog[p];
			break;

		case '#':
			syn = 0;
			token[0] = ch;
			break;
		default:
			syn = -1;
			break;
		}
	}

}

int main(int argc, char** argv) {

	cout << "please input string: \n" << endl;

	p = 0;//progָ����0���ӿ�ʼ���ļ�
	char str;//��ʱ�ַ�����

	//��ȡ���� 
	do {
		str = getchar();
		prog[p] = str;
		p++;
	} while (str != '#');//

	p = 0;
	ch = prog[p];

	//��ʼ���� 
	do {
		scanner();
		switch (syn) {
		case 11:
			cout << "(" << syn << "," << sum << ")" << endl;
			break;
		case -1:
			cout << "error" << endl;
			break;
		default:
			cout << "(" << syn << "," << token << ")" << endl;
		}
	} while (syn != 0);

	system("pause");

	return 0;
}





