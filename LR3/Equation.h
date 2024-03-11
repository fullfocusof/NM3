#pragma once
#include <iostream>
#include <fstream>

#include <Windows.h>
#include <conio.h>
#include <cmath>

#include <vector>
#include <string>

using namespace std;

class Equation
{


public:

	Equation();

	float getValue(float x);
	void RootSeparation(float a, float b, float step);

	float Dichotomy(float a, float b, float eps);
	float Chords();

	void printQuit();

	~Equation();
};