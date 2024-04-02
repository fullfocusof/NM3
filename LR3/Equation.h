#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include <Windows.h>
#include <conio.h>
#include <cmath>
#include <iomanip>

#include <vector>
#include <string>

using namespace std;
using namespace sf;

class Equation
{


public:

	Equation();

	float f(float x);
	float f1(float x);
	float f2(float x);
	float q(float x);
	void checkRoot(float x);

	void RootSeparation(float a, float b, float step);

	float Dichotomy(float a, float b, float eps);
	float Chords(float a, float b, float eps);
	float Tangent(float a, float b, float eps);
	float SimpleIterations(float a, float b, float eps);

	void outputData(string text);

	void getChart();

	void printQuit();

	~Equation();
};