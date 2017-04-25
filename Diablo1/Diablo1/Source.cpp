#include <iostream>

#include "Game.h"

using namespace std;

int main()
{
	Console::initialize();
	new Game();
	return 0;
}

/*
// ascii finder
{
for (int i = 127; i <= 255; i++)
{
system("cls");
printf("ASCII %d = (%c)", i, i);
getchar();
}
}
*/

/*
// color finder
for (int i = 0; i < 1000; i++)
{
	Console::setColor(i);
	Console::printf("LOL - %d\n", i);
	cin.get();
}
*/
