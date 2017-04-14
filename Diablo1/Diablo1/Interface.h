#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include "common.h"


class Interface //untuk load screen, dll
{
public:
	Interface() {
		Console::initialize();
		Console::setCursorVisibility(false);
	}
	static void enter(int x, int y) {
		Console::setCursorPos(x, y);
		Console::setColor(7);
		Console::printf("Press enter to continue");
	}

	static void titleScreen() {
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
		char input;
		enter(27, 20);
		Console::setCursorPos(21, 5);
		for (int x = 0; x < strlen(production); x++) {
			input = Console::getKeyPressed();
			if (input == VK_RETURN) { break; }
			Console::printf("%c", production[x]);
			Console::delay(50);
		}


		Console::setColor(4);
		for (int x = 0; x < 7; x++) {
			input = Console::getKeyPressed();
			if (input == VK_RETURN) { break; }
			Console::setCursorPos(3, x + 10);
			Console::printf("%s", title[x]);
			Console::delay(500);
		}
		if (input == VK_RETURN) { return; }
		getchar();
	}

	static void loading() {
		int yes;
		int no;
		char input;
		no = 50;
		yes = 0;

		while (no >= 0) {
			input = Console::getKeyPressed();
			if (input == VK_RETURN) { break; }
			Console::delay(100);
			system("cls");
			enter(28, 20);
			Console::setCursorPos(0, 0);
			printf("\n\n\n\n\n\n\n\n\n\n");
			printf("\t\t");
			Console::setColor(2);
			//255
			//222+33
			for (int x = 0; x < yes; x++) {
				Console::printf("%c", rand() % 241 + 14);
			}
			Console::setColor(7);
			for (int x = 0; x < no; x++) {
				Console::printf("%c", rand() % 241 + 14);
			}
			if (no > 0) {
				//Console::setColor(rand()%8+1);
				printf("\n\n\t\t\t\t    LOADING...");
			}
			yes++;
			no--;
		}

		Console::setColor(2);
		Console::setCursorPos(0, 10);
		Console::printf("\n\n\t\t\t\tLOAD SUCCESSFULL!");
		if (input == VK_RETURN) { return; }
		getchar();
	}
	static int getPlayerName() {
		system("cls");

	}

};
