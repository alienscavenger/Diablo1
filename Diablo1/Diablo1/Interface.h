#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <iostream>
#include "common.h"

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
						Console::delay(200);
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
	Interface() {
		Console::initialize();
		Console::setCursorVisibility(false);
	}
	static void enter(int x, int y, int type) {
		Console::setCursorPos(x, y);
		Console::setColor(7);
		if (type == 1) {
			Console::printf("  Press enter to skip  ");
		}
		else {
			Console::printf("Press enter to continue");
		}
	}
	static void titleScreen() {
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

		Console::setColor(4);
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
			Console::setColor(2);
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
			Console::setColor(7);
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

		Console::setColor(2);
		Console::setCursorPos(0, 10);
		//if(!flag)Console::printf("\n\n\t\t\t\tLOAD SUCCESSFULL!");
		Console::printf("\n\n\t\t\t\tLOAD SUCCESSFULL!");
		//if (input == VK_RETURN) { return; }
		enter(29, 20, 2);
		pressEnterPlease();
	}

	static void displaySword() {
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
		Console::setColor(7);
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
	static string getPlayerName() {
		string tempPlayerName;
		system("cls");
		//gets(tempPlayerName); fflush(stdin); // ini di gw error btw, jadi gw ganti string yah wkwkwkw
		getline(cin, tempPlayerName);
		return tempPlayerName;
	}
};

int Interface::delayScreen = 0;
int Interface::delayFlag = 0;