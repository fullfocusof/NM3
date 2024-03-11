#include "Equation.h"

Equation::Equation()
{

}

float Equation::getValue(float x)
{
	return 2 * x * log10(x) - 1;
}

void Equation::RootSeparation(float a, float b, float step)
{
	float x1 = a, x2 = x1 + step, y1 = getValue(x1);

	while (x2 < b)
	{
		float y2 = getValue(x2);

		if (y1 * y2 < 0)
		{
			cout << " орень уравнени€ находитс€ между " << x1 << " и " << x2;
			return;
		}

		x1 = x2;
		x2 = x1 + step;
		y1 = y2;
	}

	cout << "Ќа данном промежутке нет корн€ уравнени€";
}

float Equation::Dichotomy(float a, float b, float eps)
{
	while ((b - a) / 2 >= eps)
	{
		float fa = getValue(a), fb = getValue(b);

		float c = (a + b) / 2;
		float fc = getValue(c);

		if (abs(b - a) < eps)
		{
			return c;
		}

		if (fa * fc < 0)
		{
			b = c;
		}
		else if(fc * fb < 0)
		{
			a = c;
		}
	}

	float root = (b + a) / 2;
}

float Equation::Chords()
{
	return 0.0f;
}

void Equation::printQuit()
{
	cout << endl << endl << "Backspace - возврат в меню";

	int answ = _getch();
	bool press = false;

	while (!press)
	{
		if (answ == 8)
		{
			press = true;
			break;
		}
		else
		{
			answ = _getch();
		}
	}

	system("cls");
}

Equation::~Equation()
{

}