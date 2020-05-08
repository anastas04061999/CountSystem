#include <iostream>

#define NUMBER_SYSTEM_BASE_CODE_1 -1; //define �������� ����� �� ������
#define NUMBER_SYSTEM_BASE_TEXT_1 "The base of the number system is less than 2!";

#define NUMBER_SYSTEM_BASE_CODE_2 1; //define �������� ����� �� ������
#define NUMBER_SYSTEM_BASE_TEXT_2 "Translation in the number system more than 16 is not provided";

using namespace std;


class NumberSystemBase {
public:
	virtual const char* getMessage() { return NUMBER_SYSTEM_BASE_TEXT_1; };
	virtual int getCode() { return NUMBER_SYSTEM_BASE_CODE_1; };
};


class NumberSystemBase2 {
public:
	virtual const char* getMessage() { return NUMBER_SYSTEM_BASE_TEXT_2; };
	virtual int getCode() { return NUMBER_SYSTEM_BASE_CODE_2; };
};

char digit(int num)
{
	switch (num) {
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	case 10: return 'A';
	case 11: return 'B';
	case 12: return 'C';
	case 13: return 'D';
	case 14: return 'E';
	case 15: return 'F';
	}
}

int integerPart(int a, int p, char* s) {

	if (p < 2) {
		throw new NumberSystemBase();
	}

	if (p >= 16) {
		throw new NumberSystemBase2();
	}

	int num = (int)a;
	int rest = num % p;  //������� �� �������
	num /= p;            //��� �� ��������?
	if (num == 0)
	{
		s[0] = digit(rest); return 1;
	}
	int k = integerPart(num, p, s);
	s[k++] = digit(rest);
	return k;
}

// ��������� ������� ����� �����
void doublePart(double a, int p, char* s)
{
	int iter = 0;
	int k = 0;
	double a1 = a;
	do {
		a1 = a1 * p;
		int num = (int)(a1);
		s[k++] = digit(num);
		a1 -= (int)a1;
		iter++;
	} while (a1 > 0.00000001 && iter < 10);
	s[k] = '\0';
}


int main()
{
	double a;
	char s[80] = { 0 }; 
	
	int p;

	cout << "Enter a number: ";
	cin >> a;
	bool h = true;
	while (h == true) // ���� ������������ �� ��� ���, ���� ������������ �� ����� ���������� ��������
	{
		cout << "Enter the base of the number system: ";
		cin >> p;

		// �������� �� ���������� ����������
		if (cin.fail()) // ���� ���������� ���������� ��������� ���������,
		{
			cin.clear(); // �� ���������� cin � '�������' ����� ������
			cin.ignore(32767, '\n'); // � ������� �������� ����������� ����� �� �������� ������
			cout << "Oops, that input is invalid.  Please try again.\n";
		}
		else
		{
			cin.ignore(32767, '\n'); // ������� ������ �������� (��������, ����� 4+5, ��������� ������ ������ 4)
			h = false;

			try {
				int k = integerPart(a, p, s);
				s[k++] = ',';

				int intA;
				intA = (int)a;
				doublePart(a - intA, p, &s[k]);

				cout << s;
			}
			catch (NumberSystemBase* ex) {
				cout << ex->getMessage() << " Code: " << ex->getCode();
			}
			catch (NumberSystemBase2* ex) {
				cout << ex->getMessage() << " Code: " << ex->getCode();
			}

		}
	}

}
