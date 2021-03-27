#include <iostream>
#include <cstring>
#include<fstream>
using namespace std;

char prog[800];	//�洢���� 
char token[10];	//�洢�����ַ���
char ch;	//��ǰ�ַ� 
int syn;	//�����ֱ��� 
int sum;	//���ͳ��� 
int p;	//progָ��
int m;	//tokenָ��
int n;  //ѭ������
int kk;	//������ 
//�ؼ��� 
const char* rwtab[6] = { "begin", "if", "then", "while", "do", "end" };

bool isLetter(char ch);	//�ж��Ƿ�Ϊ��ĸ 
bool isDigit(char ch);	//�ж��Ƿ�Ϊ���� 
void scanner();			//ɨ������� 
void Irparser();		//�﷨������ 
void yucu();			//��䴮�������� 
void statement();		//���������� 
void expression();		//���ʽ�������� 
void term();            //ע�ʹ���
void factor();          //���ӷ�������

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

void Irparser() {
	if (syn == 1) {
		scanner();
		yucu();
		if (syn == 6) {
			scanner();
			if (syn == 0 && (kk == 0)) {
				cout << "success" << endl;
			}
		}
		else {
			if (kk != 1) {
				cout << "ȱ��end��error" << endl;
				kk = 1;
			}
		}
	}
	else {
		cout << "begin��error!" << endl;
		kk = 1;
	}
}

void yucu() {
	statement();
	while (syn == 26) {
		scanner();
		statement();
	}
}

void statement() {
	if (syn == 10) {
		scanner();
		if (syn == 18) {
			scanner();
			expression();
		}
		else {
			cout << "��ֵ��error��" << endl;
			kk = 1;
		}
	}
	else {
		cout << "���(��ʶ��)error��" << endl;
		kk = 1;
	}
}

void expression() {
	term();
	while (syn == 13 || syn == 14) {
		scanner();
		term();
	}
}

void term() {
	factor();
	while (syn == 15 || syn == 16) {
		scanner();
		factor();
	}
}

void factor() {
	if (syn == 10 || syn == 11) {
		scanner();
	}
	else if (syn == 27) {
		scanner();
		expression();
		if (syn == 28) {
			scanner();
		}
		else {
			cout << "��error!" << endl;
			kk = 1;
		}
	}
}

int main(int argc, char** argv) {
	/*��ȡ�û������ַ���
	cout << "please input string: \n" << endl;

	p = 0;
	char str;

	//��ȡ���� 
	do {
		str = getchar();
		prog[p] = str;
		p++;
	} while (str != '#');
	*/
	//������������ȡ���Դ������ı��ļ�ceshi.txt
	char str;
	p = 0;
	ifstream inFile("ceshi.txt", ios::in | ios::binary); //�����ƶ���ʽ�������ȡ��Դ����
	if (!inFile) {
		cout << "error" << endl;
		return 0;
	}
	while (inFile.read((char*)&str, sizeof(str))) { //һֱ�����ļ�����
		prog[p++] = str;
	}
	p = 0;
	ch = prog[p];
	while (prog[p] != NULL) {
		cout << prog[p++];
	}
	cout << endl;
	//��progָ�븳��ֵ����Դ������дʷ����﷨����
	p = 0;
	ch = prog[p];
	scanner();
	Irparser();

	//��ʼ���� 
//	do{
//		scanner();
//		switch(syn){
//			case 11:
//				cout << "(" << syn << "," << sum << ")" << endl;
//				break;
//			case -1:
//				cout << "error" << endl;
//				break;
//			default:
//				cout << "("<< syn << "," << token << ")" <<endl;
//		}
//	}while(syn != 0);


	system("pause");

	return 0;
}




