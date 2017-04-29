#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <vector>
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
		Console::setCursorVisibility(false);
		bool printFlag = true;
		int sampahFlag = 1;
		int pickMenu = 0;
		int maxMenu = saveGameAvailable ? 3 : 2;
		char charMenu;
		while (1)
		{
			if (printFlag)
			{
				Interface::setWindowSize(1000, 550);
				Console::setColor(7);
				Console::setCursorPos(0, 27);
				Console::printf("Press up/down or WSAD to select, and enter to choose");

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
					if (charMenu == VK_UP || charMenu == 0x57) // 0x57 == 'w'
					{
						pickMenu = (pickMenu - 1 + maxMenu) % maxMenu;
						printFlag = true;
					}
					else if (charMenu == VK_DOWN || charMenu == 0x53) // 0x53 == 's'
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

	static string newGameName()
	{
		system("cls");
		Console::setCursorVisibility(true);
		Console::setCursorPos(40, 10);
		Console::printf("What's your name?");
		Console::setCursorPos(38, 15);
		printf(">>");
		string myName;
		
		Console::setColor(Console::COLOR_RED);
		while (1)
		{
			Interface::setWindowSize(1000, 550);
			char buff = _getch();
			if (buff == VK_RETURN && myName.length()>0) break;
			else if (buff == VK_BACK && myName.length()>0)
			{
				printf("\b \b");
				myName.pop_back();
			}
			else if ((isalnum(buff) || buff==' ') && myName.length()<20)
			{
				printf("%c", buff);
				myName.push_back(buff);
			}
		}

		return myName;
	}

	static int newGameJob(string name)
	{
		char* assassin[] =
		{
			"       /^\\    (\"\"\")",
			"       |:|     III",
			"       |:|     III",
			"       |:|     III",
			"       |:|   __III__",
			"       |:| /:-.___,-:\\",
			"       |:| \\]  |:|  [/",
			"       |:|     |:|",
			"   /]  |:|  [\\ |:|",
			"   \\:-'\"\"\"`-:/ |:| ",
			"     \"\"III\"\"   |:|",
			"       III     |:|",
			"       III     |:|",
			"       III     |:|",
			"      (___)     \""
		};

		char* paladin[] =
		{
			"         ()",
			"       __)(__",
			"       '-<>-'",
			"         )(   __",
			"         ||  / \\\\",
			"         || [-- |]",
			"         || [-- |]",
			"         || [-- |]",
			"         || [-- |]",
			"         ||  \\_//",
			"         ||",
			"         \\/"
		};

		char* barbarian[] =
		{
			"        ,  /\\  .  ",
			"       //`-||-'\\\\ ",
			"      (| -=||=- |)",
			"       \\\\,-||-.// ",
			"        `  ||  '  ",
			"           ||     ",
			"           ||     ",
			"           ||     ",
			"           ||     ",
			"           ||     ",
			"           ()  "
		};

		char* assassinText[] =
		{
			"Fast moving and high agility make Assassin hard to hit and likely",
			"to land several small damages to enemy before enemy can move.",
			"Assassin suffers for weak protective gear and will easily go down",
			"by several devastating hits, assuming if the enemy is capable of",
			"hitting the Assassin. Assassin is likely to land critical hit,",
			"thanks to its high dexterity. Assassin will often encounter",
			"difficulty when facing enemies with heavy armor because of",
			"Assassin's low damage output. This is why Assassin relies heavily",
			"on critical hits, thus bypassing enemy armor!"
		};

		char* paladinText[] =
		{
			"Paladin is a balanced class that is good at both offensive and",
			"defensive. It can use one-handed weapon and wear heavy armor.",
			"Its main drawback is its lack of stamina due to heavy armor",
			"penalty. Paladin often cannot survive prolonged battle unless",
			"its stamina restored. Its faith in God makes paladin has the",
			"highest strength of all classes. While relatively slower than",
			"Assassin, paladin packs both high damage and ample chance of",
			"critical hit. Its heavy armor makes enemy attack feels like gentle",
			"touch!"
		};

		char* barbarianText[] =
		{
			"Very brutal at offensive while sacrificing its protection,",
			"barbarian has slow but deadly attack. It is likely to endure",
			"the longest battle, thanks to its high stamina. Barbarian has",
			" the highest endurance and hit point and can withstand devastating",
			"hits from enemy. Barbarian is also able touse all kind of weapons",
			"including two-handed weapon. But, what a disappointment, since",
			"barbarian can't wear any heavy armor!"
		};

		int job = 0;
		bool exit = false;
		Console::setCursorVisibility(false);
		while (1)
		{
			if (exit)
			{
				job = -1;
				break;
			}
			job = 0;
			bool printFlag = true;
			char buffer;
			int delayInput = 0;
			
			while (1)
			{
				buffer = Console::getKeyPressed();
				if (buffer != -1)
				{
					if (delayInput)
					{
						if (buffer == VK_LEFT || buffer == 0x41) // 41 == 'a'
						{
							job = (job - 1 + 3) % 3;
							printFlag = true;
						}
						else if (buffer == VK_RIGHT || buffer == 0x44) // 0x44 == 'd'
						{
							job = (job + 1) % 3;
							printFlag = true;
						}
						else if (buffer == VK_RETURN)
						{
							break;
						}
						else if (buffer == VK_ESCAPE)
						{
							exit = true;
							break;
						}
						delayInput = 0;
					}
					else delayInput++;
				}
				if (printFlag)
				{
					system("cls");
					Interface::setWindowSize(1000, 550);
					Console::setColor(7);
					Console::setCursorPos(23, 27);
					Console::printf("Press left/right or WSAD to select, and enter to choose");

					Console::setColor(Console::COLOR_WHITE);
					Console::setCursorPos(35, 3);
					cout << "What class are you, ";
					Console::setColor(Console::COLOR_RED);
					cout << name;
					Console::setColor(Console::COLOR_WHITE);
					cout << '?';
					Console::setCursorPos(7, 5);
					switch (job)
					{
					case 0:
						Console::setColor(Console::COLOR_RED);
						cout << "ASSASSIN\n\n";
						for (int i = 0; i < 15; i++) // 31 = byk row assassin
						{
							printf("%s\n", assassin[i]);
						}
						for (int i = 0; i < 9; i++) // 9 = byk row assassinText
						{
							Console::setCursorPos(25, 10 + i);
							printf("%s", assassinText[i]);
						}
						break;
					case 1:
						Console::setColor(Console::COLOR_GREEN);
						cout << "PALADIN\n\n\n";
						for (int i = 0; i < 12; i++)
						{
							printf("%s\n", paladin[i]);
						}
						for (int i = 0; i < 9; i++)
						{
							Console::setCursorPos(25, 10 + i);
							printf("%s", paladinText[i]);
						}
						break;
					case 2:
						Console::setColor(Console::COLOR_YELLOW);
						cout << "BARBARIAN\n\n\n\n";
						for (int i = 0; i < 11; i++)
						{
							printf("%s\n", barbarian[i]);
						}
						for (int i = 0; i < 7; i++)
						{
							Console::setCursorPos(25, 10 + i);
							printf("%s", barbarianText[i]);
						}
						break;
					} // end switch case
					printFlag = false;
				}
			} // end while dalem
			if (exit)
			{
				job = -1;
				break;
			}

			Console::setColor(Console::COLOR_MAGENTA);
			Console::setCursorPos(27, 26);
			printf("Are you sure you want to choose ");
			switch (job)
			{
			case 0: Console::setColor(Console::COLOR_RED); cout << "ASSASSIN"; break;
			case 1: Console::setColor(Console::COLOR_GREEN); cout << "PALADIN"; break;
			case 2: Console::setColor(Console::COLOR_YELLOW); cout << "BARBARIAN"; break;
			}
			Console::setColor(Console::COLOR_MAGENTA);
			cout << " ?";

			Console::setColor(COLOR_GREY);
			Console::setCursorPos(17, 27);
			cout << "           "; // untuk hilangin kata sebelumnya
			cout << "(press enter to continue, esc to repick)";
			cout << "               "; // untuk hilangin kata sebelumnya
			int tempCounter = 0;
			int what;
			while (1)
			{
				char buf = Console::getKeyPressed();
				if (buf != -1)
				{
					if (tempCounter)
					{
						if (buf == VK_ESCAPE)
						{
							what = -1;
							break;
						}
						else if (buf == VK_RETURN)
						{
							what = 1;
							break;
						}
						tempCounter = 0;
					}
					else
						tempCounter++;
				}
			}
			if (what == 1) break;
		} // end while
		Console::setCursorVisibility(true);
		return job;
	}
};

int Interface::delayScreen = 0;
int Interface::delayFlag = 0;