#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <iostream>
#include "common.h"
#include "Game.h"

#define COLOR_GREY 7

using namespace std;

class Interface //untuk load screen, dll
{
private:
	static int delayScreen;
	static int delayFlag;
public:
	static void pressEnterPlease()
	{
		while (1)
		{
			char x = _getch();
			if (x == VK_RETURN)
			{
				int sampah;
				while (true)
				{
					sampah = Console::getKeyPressed(); // harus pake ini, supaya getKeyPressed lainnya nggak ada masalah
					if (sampah == VK_RETURN) {
						//printf(" <-");
						//Console::delay(50);
						break;
					}
				}
				break;
			}
			printf("\b"); // backspace
		}
	}
	static void flush()
	{
		cin.clear();
		cin.ignore(10000000, '\n');
	}
	static void setWindowSize(int width, int height)
	{
		HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console, &r); //stores the console's current dimensions

		MoveWindow(console, r.left, r.top, width, height, TRUE);
	}

	Interface() { // constructor
		Console::initialize();
		Console::setCursorVisibility(false);
	}

	static void enter(int x, int y, int type) {
		Console::setCursorPos(x, y);
		Console::setColor(Console::COLOR_WHITE);
		if (type == 1) {
			Console::printf("  Press enter to skip  ");
		}
		else {
			Console::printf("Press enter to continue");
		}
	}
	static void titleScreen() {
		system("cls");
		delayFlag = 1;
		char *title[] = {
			"oooooooooo.   ooooo       .o.       oooooooooo.  ooooo          .oooooo.",
			" 888'   `Y8b  `888'      .888.      `888'   `Y8b `888'         d8P'  `Y8b",
			" 888      888  888      .8\"888.      888     888  888         888      888",
			" 888      888  888     .8' `888.     888oooo888'  888         888      888",
			" 888      888  888    .88ooo8888.    888    `88b  888         888      888",
			" 888     d88'  888   .8'     `888.   888    .88P  888       o `88b    d88'",
			"o888bood8P'   o888o o88o     o8888o o888bood8P'  o888ooooood8  `Y8bood8P'",
		};
		float counter = 0;
		char *production = "Aditya n' Melvin Production presents";
		char input = NULL;
		enter(28, 20, 1);
		int flag = 0;
		Console::setCursorPos(21, 5);
		for (int x = 0; x<strlen(production); x++) {
			input = Console::getKeyPressed();
			if (input == VK_RETURN) { flag = 1; delayFlag = 0; delayScreen = 0;}
			Console::printf("%c", production[x]);
			if (delayFlag) delayScreen = 50;
			Console::delay(delayScreen);
		}
		
		if (flag)
		{
			int sampah;
			while (true)
			{
				sampah = Console::getKeyPressed(); // harus pake ini, supaya getKeyPressed lainnya nggak ada masalah
				if (sampah == VK_RETURN) break;
			}
			//return;
		}

		if(delayFlag)Console::delay(500); // tambahin delay supaya bagus

		Console::setColor(4); // BENERIN NIH 'MAGIC NUMBER' PLZZZ
		for (int x = 0; x<7; x++) {
			input = Console::getKeyPressed();
			if (input == VK_RETURN) { delayFlag = 0; delayScreen = 0; };
			Console::setCursorPos(3, x + 10);
			Console::printf("%s", title[x]);
			if (x < 6)
			{
				if (delayFlag) delayScreen = 300;
				Console::delay(delayScreen);
			}
		}
		if (input == VK_RETURN) { return; }
		enter(28, 20, 2);
		//getchar(); // gw ganti jadi fungsi gw sendiri yah yh, soalnya kalo getchar, semua tombol yang diteken bakal muncul di screen
		pressEnterPlease();
	}

	static void loading() {
		system("cls");
		delayFlag = 1;
		int yes;
		int no;
		char input = NULL;
		no = 50;
		yes = 0;

		int flag = 0;
		srand(time(NULL));
		while (no >= 0) {
			input = Console::getKeyPressed();
			if (input == VK_RETURN) {
				//flag = 1;
				delayFlag = 0;
				delayScreen = 0;
				yes = 50;
				no = 0;
				//Console::delay(500); // tambahin delay supaya bagus
				//break;
			}
			if (delayFlag) delayScreen = 100;
			Console::delay(delayScreen);
			system("cls");
			enter(29, 20, 1);
			Console::setCursorPos(0, 0);
			printf("\n\n\n\n\n\n\n\n\n\n");
			printf("\t\t");
			Console::setColor(Console::COLOR_GREEN);
			//255
			//222+33
			// ascii 27 dan 32 juga jelek (space dan esc)
			int wala;
			for (int x = 0; x<yes; x++) {
				do
				{
					wala = rand() % 241 + 14;
				} while (wala == 32 || wala == 27);
				Console::printf("%c", wala );
			}
			Console::setColor(COLOR_GREY);
			for (int x = 0; x<no; x++) {
				do
				{
					wala = rand() % 241 + 14;
				} while (wala == 32 || wala == 27);
				Console::printf("%c", wala);
			}
			if (no>0) {
				//Console::setColor(rand()%8+1);
				printf("\n\n\t\t\t\t    LOADING...");
			}
			yes++;
			no--;
		}

		Console::setColor(Console::COLOR_GREEN);
		Console::setCursorPos(0, 10);
		//if(!flag)Console::printf("\n\n\t\t\t\tLOAD SUCCESSFULL!");
		Console::printf("\n\n\t\t\t\tLOAD SUCCESSFULL!");
		//if (input == VK_RETURN) { return; }
		enter(29, 20, 2);
		pressEnterPlease();
	}

	static void displaySword() {
		system("cls");
		char *sword[] = {
			"                (O)",
			"                <M ",
			"     o          <M  ",
			"    /| ......  /:M\\------------------------------------------------,,,,,,",
			"  (O)[]XXXXXX[]I:K+}=====<{H}>================================------------>",
			"    \\| ^^^^^^  \\:W/------------------------------------------------''''''",
			"     o          <W  ",
			"                <W",
			"                (O)"

		};
		Console::setColor(3);
		for (int x = 0; x<9; x++) {
			//Console::delay(100);
			Console::printf("%s\n", sword[x]);
		}
	}

	static void intro() {
		system("cls");
		delayFlag = 1;
		char input = NULL;
		char *introText[] = { "After having lost your Monastery to demons,",
			"you follow the Dark Wanderer to Tristam Town.",
			"This is where your journey starts. ",
			"The demons are roaming the outskirt of this city ",
			"and soon everything will be devoured...",
			"Help liberate Tristam Town from hand of Diablo once and for all!" };
		enter(27, 20, 1);
		Console::setCursorPos(0, 0);
		printf("\n\n");
		displaySword();
		Console::setColor(Console::COLOR_WHITE);
		printf("\n");
		for (int y = 0; y<6; y++) {
			if (y == 5)
			{
				if(delayFlag) delayScreen = 650;
				Console::delay(delayScreen);
			}
			printf("\t");
			if (y == 5) { Console::setColor(3); }
			for (int x = 0; x<strlen(introText[y]); x++) {
				input = Console::getKeyPressed();
				if (input == VK_RETURN) {
					delayFlag = 0;
					delayScreen = 0;
					//Console::delay(500); // tambahin delay supaya bagus
					//break;
				}
				if (delayFlag) delayScreen = 30;
				Console::delay(delayScreen);
				Console::printf("%c", introText[y][x]);
			}
			if (input == VK_RETURN) { break; }
			printf("\n");
		}
		if (input == VK_RETURN) { return; }
		enter(27, 20, 2);
		pressEnterPlease();
	}

	static int startGame( bool saveGameAvailable)
	{
		system("cls");
		bool printFlag = true;
		int sampahFlag = 1;
		int pickMenu = 0;
		int maxMenu = saveGameAvailable ? 3 : 2;
		char charMenu;
		while (1)
		{
			if (printFlag)
			{
				Console::setCursorPos(40, 10);
				if(pickMenu ==0 )Console::setColor(79);
				else Console::setColor(Console::COLOR_WHITE);
				Console::printf("NEW GAME");

				if (saveGameAvailable)
				{
					Console::setCursorPos(40, 11);
					if (pickMenu == 1)Console::setColor(79);
					else Console::setColor(Console::COLOR_WHITE);
					Console::printf("LOAD GAME");
				}
				int yExit = saveGameAvailable ? 12 : 11;
				Console::setCursorPos(42, yExit);
				if (pickMenu == (maxMenu-1))Console::setColor(79);
				else Console::setColor(Console::COLOR_WHITE);
				Console::printf("EXIT");

				printFlag = false;
			}
			charMenu = Console::getKeyPressed();
			if (charMenu != -1)
			{
				if (sampahFlag) // supaya key release tidak kebaca
				{
					if (charMenu == VK_UP) // up
					{
						pickMenu = (pickMenu - 1 + maxMenu) % maxMenu;
						printFlag = true;
					}
					else if (charMenu == VK_DOWN) // down
					{
						pickMenu = (pickMenu + 1) % maxMenu;
						printFlag = true;
					}
					else if (charMenu == VK_RETURN)
					{
						break;
					}
					int sampah = Console::getKeyPressed();
					sampahFlag = 0;
				}
				else sampahFlag++;
			}
		} // endWhile
		Console::setColor(Console::COLOR_WHITE);
		system("cls");
		if (pickMenu == (maxMenu - 1)) return -1;
		else return pickMenu+1;
	}
};

int Interface::delayScreen = 0;
int Interface::delayFlag = 0;