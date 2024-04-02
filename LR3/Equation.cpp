#include "Equation.h"

Equation::Equation()
{

}

float Equation::f(float x)
{
	return 2 * x * log10(x) - 1;
}

float Equation::f1(float x)
{
	return 2 * log10(x) + (2 / log(10));
}

float Equation::f2(float x)
{
	return 2 / (x * log(10));
}

float Equation::q(float x)
{
	return pow(10, 1 / (2 * x));
}

void Equation::checkRoot(float x)
{
	cout << "2 * " << x << " * log10(" << x << ") - 1 = " << f(x);
}

void Equation::RootSeparation(float a, float b, float step)
{
	float x1 = a, x2 = x1 + step, y1 = f(x1);

	while (x2 < b)
	{
		float y2 = f(x2);

		if (y1 * y2 < 0)
		{
			cout << "Корень уравнения находится между " << x1 << " и " << x2;
			return;
		}

		x1 = x2;
		x2 = x1 + step;
		y1 = y2;
	}

	cout << "На данном промежутке нет корня уравнения";
}

float Equation::Dichotomy(float a, float b, float eps)
{
	//string text = "#\tc\t\tf(c)\t\tdelta = abs(b - a)";
	//int iteration = 0;

	while ((b - a) / 2 >= eps)
	{
		float fa = f(a), fb = f(b);
		float c = (a + b) / 2;
		float fc = f(c);

		float delta = abs(b - a);

		//text += "\n" + to_string(iteration) + "\t" + to_string(c) + "\t" + to_string(fc) + "\t" + to_string(delta);
		//iteration++;

		if (abs(b - a) < eps)
		{
			//cout << text << endl;
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

	//cout << text << endl;
	float root = (b + a) / 2;
}

float Equation::Chords(float a, float b, float eps)
{
	string text = "#\txi\t\tf(xi)\t\tx(i + 1)\tdelta = abs(xi - x(i + 1))\tДостигнута ли точность?";
	int iteration = 0;

	float c, xNew, x, E1 = 0.8 * eps/ (1.5 - 0.8);

	if (f1((a + b)/2) < 0) c = b, xNew = a;
	else c = a, xNew = b;

	do
	{
		x = xNew;
		xNew = x - (f(x) / (f(c) - f(x))) * (c - x);
		float delta = abs(x - xNew);

		text += "\n" + to_string(iteration) + "\t" + to_string(x) + "\t" + to_string(f(x)) + "\t" + to_string(xNew) + "\t" + to_string(delta) + "\t\t\t" + (delta < E1 ? "Да" : "Нет");
		iteration++;
	} while (abs(xNew - x) > eps);

	outputData(text);

	return xNew;
}

float Equation::Tangent(float a, float b, float eps)
{
	string text = "#\txi\t\tf(xi)\t\tx(i + 1)\tdelta = abs(xi - x(i + 1))\tДостигнута ли точность?";
	int iteration = 0;

	float E1 = sqrt(2 * 0.8 * eps / 0.9), x0, x;

	if (f2(a) * f(a) > 0) x0 = b;
	else x0 = a;

	do
	{
		x = x0 - (f(x0) / f1(x0));
		float delta = abs(x - x0);

		text += "\n" + to_string(iteration) + "\t" + to_string(x0) + "\t" + to_string(f(x0)) + "\t" + to_string(x) + "\t" + to_string(delta) + "\t\t\t" + (delta < E1 ? "Да" : "Нет");
		iteration++;

		if (delta < eps)
		{
			break;
		}
		else
		{
			x0 = x;
		}

	} while (true);

	outputData(text);

	return x;
}

float Equation::SimpleIterations(float a, float b, float eps)
{
	string text = "#\txi\t\tf(xi)\t\tx(i + 1)\tdelta = abs(xi - x(i + 1))";
	int iteration = 0;

	float x0 = a, x, qmax = 0.725811561;

	do
	{
		x = q(x0);
		float delta = abs(x - x0);

		text += "\n" + to_string(iteration) + "\t" + to_string(x0) + "\t" + to_string(f(x0)) + "\t" + to_string(x) + "\t" + to_string(delta);
		iteration++;

		if (delta < (eps*(1 - qmax))/qmax)
		{
			break;
		}
		else
		{
			x0 = x;
		}
	} while (true);

	cout << text << endl << endl;

	return x;
}

void Equation::outputData(string text)
{
	ofstream ofs("dataOutput.txt");
	if (ofs.is_open())
	{
		ofs << text;
	}
	else
	{
		cerr << "Ошибка открытия файла";
	}
}

void Equation::getChart()
{

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