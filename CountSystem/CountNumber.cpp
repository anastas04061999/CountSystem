#include <iostream>

#define NUMBER_SYSTEM_BASE_CODE_1 -1; //define заменяет првое на второе
#define NUMBER_SYSTEM_BASE_TEXT_1 "The base of the number system is less than 2!";

#define NUMBER_SYSTEM_BASE_CODE_2 1; //define заменяет првое на второе
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
	int rest = num % p;  //остаток от деления
	num /= p;            //что за оператор?
	if (num == 0)
	{
		s[0] = digit(rest); return 1;
	}
	int k = integerPart(num, p, s);
	s[k++] = digit(rest);
	return k;
}

// Получение дробной части числа
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
	while (h == true) // цикл продолжается до тех пор, пока пользователь не введёт корректное значение
	{
		cout << "Enter the base of the number system: ";
		cin >> p;

		// Проверка на предыдущее извлечение
		if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
		{
			cin.clear(); // то возвращаем cin в 'обычный' режим работы
			cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			cout << "Oops, that input is invalid.  Please try again.\n";
		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем лишние значения (например, ввели 4+5, программа возьмёт только 4)
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
