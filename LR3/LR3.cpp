#include "Equation.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_BACKSPACE 8

const int W = 600, H = 600;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleTitle(L"Нелинейные уравнения");
	ConsoleCursorVisible(false, 100);

	Equation test;

	int active_menu = 0;
	int keyInput;
	bool exitProg = false;

	while (!exitProg)
	{
		int x = 50, y = 12;
		GoToXY(x, y);

		vector<string> menu =
		{
			"Вывести уравнение",
			"Отделить корень",
			"Уточнить корень половинным делением",
			"Уточнить корень методом хорд",
			"Уточнить корень методом касательных",
			"Уточнить корень методом простых итераций",
			"Построить график функции на отрезке",
			"Выход"
		};

		for (int i = 0; i < menu.size(); i++)
		{
			if (i == active_menu)
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			GoToXY(x, y++);
			cout << menu[i] << endl;
		}

		keyInput = _getch();
		switch (keyInput)
		{
			case KEY_ESC:
				exit(0);

			case KEY_UP:
			{
				if (active_menu > 0)
				{
					active_menu--;
				}
			}
			break;

			case KEY_DOWN:
			{
				if (active_menu < menu.size() - 1)
				{
					active_menu++;
				}
			}
			break;

			case KEY_ENTER:
			{
				switch (active_menu)
				{
					case 0:
					{
						system("cls");

						cout << "2*x*lg(x) = 1";

						test.printQuit();
					}
					break;

					case 1:
					{
						system("cls");
						
						float a, b, step;
						cout << "Введите левую границу, правую границу и шаг" << endl;
						cin >> a >> b >> step;

						system("cls");

						test.RootSeparation(a, b, step);

						test.printQuit();
					}
					break;

					case 2:
					{
						system("cls");

						float a, b, eps;
						cout << "Введите левую границу, правую границу и точность вычислений" << endl;
						cin >> a >> b >> eps;

						system("cls");

						float result = test.Dichotomy(a, b, eps);

						cout << "Корень уравнения с учетом точности " << eps << ": " << result << endl;

						test.checkRoot(result);

						test.printQuit();
					}
					break;

					case 3:
					{
						system("cls");
						
						float a, b, eps;
						cout << "Введите левую границу, правую границу и точность вычислений" << endl;
						cin >> a >> b >> eps;

						system("cls");

						float result = test.Chords(a, b, eps);

						cout << "Корень уравнения с учетом точности " << eps << ": " << result << endl;

						test.checkRoot(result);

						test.printQuit();
					}
					break;

					case 4:
					{
						system("cls");

						float a, b, eps;
						cout << "Введите левую границу, правую границу и точность вычислений" << endl;
						cin >> a >> b >> eps;

						system("cls");

						float result = test.Tangent(a, b, eps);

						cout << "Корень уравнения с учетом точности " << eps << ": " << result << endl;

						test.checkRoot(result);

						test.printQuit();
					}
					break;

					case 5:
					{
						system("cls");

						float a, b, eps;
						cout << "Введите левую границу, правую границу и точность вычислений" << endl;
						cin >> a >> b >> eps;

						system("cls");

						float result = test.SimpleIterations(a, b, eps);

						cout << "Корень уравнения с учетом точности " << eps << ": " << result << endl;

						test.checkRoot(result);

						test.printQuit();
					}
					break;

					case 6:
					{
						system("cls");

						float a, b;
						cout << "Введите левую границу и правую границу" << endl;
						cin >> a >> b;

						RenderWindow window(VideoMode(W, H), "Function graph [" + to_string(a) + ";" + to_string(b) + "]");

						float helpPoints = 200;
						int xMid = W / 2, yMid = H / 2, cntPoints = (abs(a) + b) * helpPoints + 1, scale = 30, anim = 0;

						CircleShape point(1.f);
						point.setFillColor(Color::Green);

						Font font;
						font.loadFromFile("ArialRegular.ttf");

						Text text;
						text.setFont(font);
						text.setCharacterSize(14);
						text.setFillColor(Color::Green);

						RectangleShape line[40];
						for (int i = 0; i < 40; i++)
						{
							line[i].setSize(Vector2f(1, 20));
							line[i].setFillColor(Color::Green);

							if (i < 20)
							{
								if (i < 10)
								{
									line[i].setPosition(xMid - (i + 1) * scale, yMid - 10);
								}
								else
								{
									line[i].setPosition(xMid + (i - 9) * scale, yMid - 10);
								}
							}
							else
							{
								line[i].setRotation(90);
								if (i < 30)
								{
									line[i].setPosition(xMid + 10, yMid + (i - 30) * scale);
								}
								else 
								{ 
									line[i].setPosition(xMid + 10, yMid + (i - 29) * scale); 
								}
							}
						}

						RectangleShape OsX(Vector2f(W, 1));
						OsX.setFillColor(Color::Green);
						OsX.setPosition(0, yMid);					

						RectangleShape OsY(Vector2f(1, H));
						OsY.setFillColor(Color::Green);
						OsY.setPosition(xMid, 0);

						RectangleShape arrow[4];
						for (int i = 0; i < 4; i++)
						{
							arrow[i].setSize(Vector2f(1, 25));
							arrow[i].setFillColor(Color::Green);

							if (i < 2) arrow[i].setPosition(xMid, 0);
							else arrow[i].setPosition(W, yMid);
						}
						arrow[0].setRotation(25);
						arrow[1].setRotation(-25);
						arrow[2].setRotation(60);
						arrow[3].setRotation(-250);				

						while (window.isOpen())
						{
							Event event;
							while (window.pollEvent(event))
							{
								if (event.type == Event::Closed)
								{
									window.close();
								}
							}

							if (anim < cntPoints) anim += 3;

							window.clear(Color::Black);
							window.draw(OsX);
							window.draw(OsY);
							for (int i = 0; i < 4; i++)
							{
								window.draw(arrow[i]);
							}
							for (int i = 0; i < 40; i++)
							{
								if (i != 19 && i != 20) window.draw(line[i]);
							}							
							for (int i = 0; i < anim; i++)
							{
								float x = a + i / helpPoints, y = 2 * x * log10(x) - 1;

								float x1 = xMid + x * scale, y1 = yMid - y * scale;

								point.setPosition(x1, y1);
								window.draw(point);
							}
							for (int i = -10; i <= 10; ++i)
							{
								if (i != -10 && i != 10)
								{
									if (i == 0)
									{
										text.setString(to_string(i));
										text.setPosition(xMid + 5 + i * scale, yMid + 10);
										window.draw(text);
									}
									else
									{
										if (i > 0)
										{
											text.setString(to_string(i));
											text.setPosition(xMid - 3 + i * scale, yMid + 12);
											window.draw(text);
										}
										else
										{
											text.setString(to_string(i));
											text.setPosition(xMid - 8 + i * scale, yMid + 12);
											window.draw(text);
										}

										text.setString(to_string(-i));
										text.setPosition(xMid + 12, yMid - 9 + i * scale);
										window.draw(text);
									}						
								}		
							}
							window.display();
						}

						test.printQuit();
					}
					break;

					case 7:
					{
						system("cls");
						exitProg = true;
					}
					break;
				}
			}
			break;
		}
	}
}