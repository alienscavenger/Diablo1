#pragma once

#ifndef BATTLE_H
#define BATTLE_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include "common.h"
#include "Game.h"
#include "Human.h"
#include "Monster.h"
#include "Interface.h"
#include <cmath>

using namespace std;

// for printing box
#define ASCII_DOUBLE_UPPER_LEFT 201  
#define ASCII_DOUBLE_LOWER_LEFT 200  
#define ASCII_DOUBLE_UPPER_RIGHT 187  
#define ASCII_DOUBLE_LOWER_RIGHT 188  
#define ASCII_DOUBLE_VERTICAL_SEPARATOR 186  
#define ASCII_DOUBLE_SEPARATOR 205

#define ASCII_SINGLE_SEPARATOR 196
#define ASCII_SINGLE_VERTICAL_SEPARATOR 179 
#define ASCII_SINGLE_UPPER_LEFT 218
#define ASCII_SINGLE_LOWER_LEFT 192
#define ASCII_SINGLE_UPPER_RIGHT 191  
#define ASCII_SINGLE_LOWER_RIGHT 217 

#define ASCII_BOX_FULL 219
#define ASCII_BOX_EMPTY 177

const int GREEN = Console::COLOR_GREEN;
const int YELLOW = Console::COLOR_YELLOW;
const int RED = Console::COLOR_RED;
const int WHITE = Console::COLOR_WHITE;
const int GREY = Console::COLOR_GRAY;
const int BLUE = Console::COLOR_BLUE;

class Battle
{
private:
	// none
	static void printBox1(int x, int y)
	{
		Console::setCursorPos(x, y);
		printf("%c", ASCII_DOUBLE_UPPER_LEFT);
		for (int i = 0; i < 27; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_UPPER_RIGHT);

		for (int i = 1; i <= 6; i++)
		{
			Console::setCursorPos(x, y + i);
			printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
			Console::setCursorPos(x + 28, y + i);
			printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
		}

		Console::setCursorPos(x, y + 7);
		printf("%c", ASCII_DOUBLE_LOWER_LEFT);
		for (int i = 0; i < 27; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_LOWER_RIGHT);
	}

	static void printBox2()
	{
		Console::setCursorPos(1, 10);
		printf("%c", ASCII_DOUBLE_UPPER_LEFT);
		for (int i = 0; i < 60; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_UPPER_RIGHT);

		for (int i = 1; i <= 5; i++)
		{
			Console::setCursorPos(1, 10 + i);
			printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
			Console::setCursorPos(1 + 61, 10 + i);
			printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
		}

		Console::setCursorPos(1, 10 + 6);
		printf("%c", ASCII_DOUBLE_LOWER_LEFT);
		for (int i = 0; i < 60; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_LOWER_RIGHT);
	}

	static int printSpeed(int& xYou, float speedYou, int& xEnemy, float speedEnemy, int speed)
	{
		Console::setColor(BLUE);
		int sec = 0;
		speedYou = speed / speedYou;
		speedEnemy = speed / speedEnemy;
		while (1)
		{
			if (xYou == 29 || xEnemy == 62) break;
			if (sec%(int)speedYou == 0)
			{
				Console::setCursorPos(xYou, 7);
				printf("%c", ASCII_BOX_FULL);
				xYou++;
			}
			if (sec%(int)speedEnemy == 0)
			{
				Console::setCursorPos(xEnemy, 7);
				printf("%c", ASCII_BOX_FULL);
				xEnemy++;
			}
			Console::delay(1);
			sec++;
		}

		if (xYou == 29 ) return 1;
		else if (xEnemy == 62) return 2;
	}

	static void clearSpeed(int turn)
	{
		Console::setColor(BLUE);
		if (turn == 1)	Console::setCursorPos(2, 7);
		else Console::setCursorPos(35, 7);

		for (int i = 0; i < 27; i++)
		{
			printf("%c", ASCII_BOX_EMPTY);
		}
	}
	static void colorSpeed(int turn)
	{
		Console::setColor(RED);
		if (turn == 1)	Console::setCursorPos(2, 7);
		else Console::setCursorPos(35, 7);

		for (int i = 0; i < 27; i++)
		{
			printf("%c", ASCII_BOX_FULL);
		}
	}

public:
	static void startBattle(Human& karakter, Monster& enemy)
	{
		system("cls");
		Console::setCursorPos(32, 0);
		Console::resetColor();
		printf("BATTLE\n");

		// print box dan "vs"
		printBox1(1, 1);
		printBox1(34, 1);
		printBox2();
		Console::setCursorPos(31, 4);
		printf("VS");

		// print nama
		{
			stringstream temp;
			temp << karakter.getName()  << " lv." << karakter.getLevel();
			string nama;
			getline(temp, nama);
			Console::setCursorPos(2, 2);
			printf(" %s", nama.c_str());
			temp.clear();
			temp << enemy.getName() << " lv." << enemy.getLevel();
			getline(temp, nama);
			Console::setCursorPos(35, 2);
			printf(" %s", nama.c_str());
		}

		//print garis
		{
			for (int i = 0; i < 27; i++)
			{
				Console::setCursorPos(2 + i, 3);
				printf("%c", ASCII_SINGLE_SEPARATOR);
				Console::setCursorPos(35 + i, 3);
				printf("%c", ASCII_SINGLE_SEPARATOR);
			}
		}
		//print HP dan STA
		{
			Console::setCursorPos(2, 4); printf("HP");
			Console::setCursorPos(2, 5); printf("STA");
			Console::setCursorPos(35, 4); printf("HP");
			Console::setCursorPos(35, 5); printf("STA");
			for (int i = 0; i < 22; i++)
			{
				Console::setColor(GREEN);
				Console::setCursorPos(7+i, 4); printf("%c",ASCII_BOX_FULL);
				Console::setCursorPos(40 + i, 4); printf("%c", ASCII_BOX_FULL);
				Console::setColor(YELLOW);
				Console::setCursorPos(7+i, 5); printf("%c", ASCII_BOX_FULL);
				Console::setCursorPos(40+i, 5); printf("%c", ASCII_BOX_FULL);
			}
			Console::resetColor();
		}

		//print garis
		{
			for (int i = 0; i < 27; i++)
			{
				Console::setCursorPos(2 + i, 6);
				printf("%c", ASCII_SINGLE_SEPARATOR);
				Console::setCursorPos(35 + i, 6);
				printf("%c", ASCII_SINGLE_SEPARATOR);
			}
		}

		//print Speed Bar
		{
			Console::setColor(BLUE);
			for (int i = 0; i < 27; i++)
			{
				Console::setCursorPos(2+i, 7);
				printf("%c", ASCII_BOX_EMPTY);
				Console::setCursorPos(35+i, 7);
				printf("%c", ASCII_BOX_EMPTY);
			}
			Console::resetColor();
		}

		queue <string> log;
		log.empty();
		string text = "Begin Battle!";
		log.push(text);

		int turn = 0;
		int xYou = 2;
		int xEnemy = 35;
		int animationSpeed[4] = { 10000,5000,2500,15000 }; // normal, fast, fastest, slow
		int index = 0;

		while (1)
		{
			// count speed
			turn = printSpeed(xYou, karakter.getSpeed(), xEnemy, enemy.getSpeed(), animationSpeed[index]);
			colorSpeed(turn);
			cin.get();
			if (turn == 1) // turn karakter
			{
				xYou = 2;
			}
			else
			{
				xEnemy = 35;
			}
			clearSpeed(turn);
		}
	}
};

#endif