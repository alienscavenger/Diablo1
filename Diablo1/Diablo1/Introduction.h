#pragma once

#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include "common.h"
#include "Interface.h"

class Introduction
{
private:
	static int delayScreen;
	static int delayFlag;

public:
	static void enter(int x, int y, int type) {
		Console::setCursorPos(x, y);
		Console::setColor(Console::COLOR_GRAY);
		if (type == 1) {
			Console::printf("  Press enter to skip  ");
		}
		else {
			Console::printf("Press enter to continue");
		}
		Console::setColor(Console::COLOR_WHITE);
	}

	static void titleScreen() {
		system("cls");
		Console::setCursorVisibility(false);
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
		enter(33, 20, 1);
		int flag = 0;
		int inputFlag = 0;
		Console::setCursorPos(26, 5);
		for (int x = 0; x < strlen(production); x++) {
			input = Console::getKeyPressed();
			if (input == 'M' || input == 'm')
			{
				if (inputFlag)
				{
					Music::playBackgroundMusic(-1);
					inputFlag = 0;
				}
				else inputFlag++;
			}
			if (input == VK_RETURN)
			{
				if (inputFlag)
				{
					flag = 1;
					delayFlag = 0;
					delayScreen = 0;
					inputFlag = 0;
				}
				else inputFlag++;
			}
			Console::printf("%c", production[x]);
			if (delayFlag) delayScreen = 50;
			Console::delay(delayScreen);
		}

		if (delayFlag)Interface::delaySec(500); // tambahin delay supaya bagus

		Console::setColor(Console::COLOR_RED); // ampun shifu >> HUEHUEHUEHUE
		if (delayFlag)
		{
			int inputFlag = 1;
			for (int x = 0; x < 7; x++) {
				input = Console::getKeyPressed();
				if (input == 'M' || input == 'm')
				{
					if (inputFlag)
					{
						inputFlag = 0;
						Music::playBackgroundMusic(-1);
					}
					else inputFlag++;
				}
				if (input == VK_RETURN) { delayFlag = 0; delayScreen = 0; };
				Console::setCursorPos(8, x + 10);
				Console::printf("%s", title[x]);
				if (x < 6)
				{
					if (delayFlag) delayScreen = 300;
					Console::delay(delayScreen);
				}
			}
		}
		else
		{
			for (int x = 0; x < 7; x++) {
				Console::setCursorPos(8, x + 10);
				Console::printf("%s", title[x]);
			}
		}

		//if (flag)
		//{
		//	int sampah;
		//	while (true)
		//	{
		//		sampah = Console::getKeyPressed(); // harus pake ini, supaya getKeyPressed lainnya nggak ada masalah
		//		if (sampah == VK_RETURN) break;
		//	}
		//	//return;
		//}

		//if (input == VK_RETURN) { return; }
		enter(33, 20, 2);
		//getchar(); // gw ganti jadi fungsi gw sendiri yah yh, soalnya kalo getchar, semua tombol yang diteken bakal muncul di screen
		Interface::pressEnterPlease();
	}

	static void loading() {
		system("cls");
		Console::setCursorVisibility(false);
		delayFlag = 1;
		int yes;
		int no;
		char input = NULL;
		no = 50;
		yes = 0;

		int flag = 0;
		srand(time(NULL));
		int inputFlag = 0;
		while (no >= 0) {
			input = Console::getKeyPressed();
			if (input == 'M' || input == 'm')
			{
				if (inputFlag)
				{
					Music::playBackgroundMusic(-1);
					inputFlag = 0;
				}
				else inputFlag++;
			}
			if (input == VK_RETURN) {
				//flag = 1;
				delayFlag = 0;
				delayScreen = 0;
				yes = 50;
				no = 0;
				//Interface::delaySec(500); // tambahin delay supaya bagus
				//break;
			}
			if (delayFlag) delayScreen = 100;
			Console::delay(delayScreen);
			system("cls");
			enter(37, 20, 1);
			Console::setCursorPos(0, 0);
			printf("\n\n\n\n\n\n\n\n\n\n");
			printf("\t\t\t");
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
				Console::printf("%c", wala);
			}
			Console::setColor(Interface::COLOR_GREY);
			for (int x = 0; x<no; x++) {
				do
				{
					wala = rand() % 241 + 14;
				} while (wala == 32 || wala == 27);
				Console::printf("%c", wala);
			}
			if (no>0) {
				//Console::setColor(rand()%8+1);
				printf("\n\n\t\t\t\t\t    LOADING...");
			}
			yes++;
			no--;
		}

		Console::setColor(Console::COLOR_GREEN);
		Console::setCursorPos(0, 10);
		//if(!flag)Console::printf("\n\n\t\t\t\tLOAD SUCCESSFULL!");
		Console::printf("\n\n\t\t\t\t\t   GAME LOADED!   ");
		//if (input == VK_RETURN) { return; }
		enter(37, 20, 2);
		Interface::pressEnterPlease();
	}

	static void improvedLoading() {
		int yes, no;
		yes = 0;
		no = 49;
		system("cls");
		Console::setCursorVisibility(false);
		while (yes!=54) {
			//resetting
			Console::setCursorPos(25, 10);
			for (int spasi = 0; spasi < 50; spasi++) {
				Console::printf(" ");
			}
			/*Console::setCursorPos(44, 13);
			Console::printf("                        ");*/
			
			//printing
			Console::setCursorPos(25, 10);
			Console::setColor(Console::COLOR_GREEN);
			for (int hijau = 0; hijau < yes; hijau++) {
				Console::printf("*");
			}
			Console::resetColor();
			for (int putih = 0; putih < no; putih++) {
				int wala;
				do
				{
					wala = rand() % 241 + 14;
				} while (wala == 32 || wala == 27);
				Console::printf("%c", wala);
			}

			Console::setCursorPos(44,13);
			if (yes!=53) {
				Console::resetColor();
				Console::printf("GAME LOADING ");
			}
			else {
				Console::setColor(Console::COLOR_GREEN);
				Console::printf(" GAME LOADED");
				Interface::delaySec(2000);
			}
			Interface::delaySec(100);
			yes++;
			no--;
		}
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
		Console::setColor(Console::COLOR_CYAN);
		printf("\n\n");
		for (int x = 0; x<9; x++) {
			//Console::delay(100);
			Console::printf("\t%s\n", sword[x]);
		}
	}

	static void intro() {
		system("cls");
		delayFlag = 1;
		char input = NULL;
		char *introText[] = { "After having lost your Monastery to demons,",
			"you follow the Dark Wanderer to Tristam Town.",
			"This is where your journey starts. ",
			"The demons are roaming the outskirt of this city",
			"and soon everything will be devoured...\n",
			"Help liberate Tristam Town from hand of Diablo once and for all!" };
		//enter(27, 21, 1);
		Console::setCursorPos(0, 0);
		printf("\n\n");
		displaySword();
		Console::setColor(Console::COLOR_WHITE);
		printf("\n");
		for (int y = 0; y<6; y++) {
			if (y == 5)
			{
				if (delayFlag) delayScreen = 650;
				Console::delay(delayScreen);
			}
			printf("\t\t");
			if (y == 5) { Console::setColor(11); }
			else printf("\t");
			for (int x = 0; x<strlen(introText[y]); x++) {
				input = Console::getKeyPressed();
				if (input == 'M' || input == 'm')
				{
					Music::playBackgroundMusic(-1);
					delayFlag = 0;
				}
				if (input == VK_RETURN) {
					delayFlag = 0;
					delayScreen = 0;
					//Interface::delaySec(500); // tambahin delay supaya bagus
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
		enter(32, 20, 2);
		Interface::pressEnterPlease();
	}

};

int Introduction::delayScreen = 0;
int Introduction::delayFlag = 0; // GLOBAL VARIABLE BUAT PRE-GAME INTRO

#endif