#include <iostream>

#include "Game.h"

using namespace std;

void asciiFinder(bool run)
{
	if (run)
	{
		for (int i = 127; i <= 255; i++)
		{
			system("cls");
			printf("ASCII %d = (%c)", i, i);
			getchar();
		}
	}
	return;
}

void colorFinder(bool run)
{
	if (run)
	{
		for (int i = 0; i < 1000; i++)
		{
			Console::setColor(i);
			Console::printf("LOL - %d\n", i);
			cin.get();
		}
	}
	return;
}

int main()
{
	asciiFinder(false);
	colorFinder(false);

	Console::initialize();
	new Game();
	return 0;
}