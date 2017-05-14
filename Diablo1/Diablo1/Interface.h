#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "common.h"
#include "Game.h"

#define COLOR_GREY 7
#define MAX_ITEM 110

using namespace std;

class Interface //untuk load screen, dll
{
private:
	static int delayScreen;
	static int delayFlag;
	// -------------------------------- SHOP FUNCTION ----------------------------------------------------
	struct ComparePrice { // comparator sort buat harga (ascending)
		bool operator()(Item* struct1, Item* struct2) {
			return (struct1->getPrice() < struct2->getPrice());
		}
	};
	struct CompareName { // comparator sort buat name (ascending)
		bool operator()(Item* struct1, Item* struct2) {
			return (struct1->getName() < struct2->getName());
		}
	};
	struct CompareArmor { // comparator sort buat armor (ascending)
		bool operator()(Item* struct1, Item* struct2) {
			return (struct1->getArmor() < struct2->getArmor());
		}
	};
	struct CompareDamage { // comparator sort buat armor (ascending)
		bool operator()(Item* struct1, Item* struct2) {
			return (struct1->getDamage() < struct2->getDamage());
		}
	};
	// -------------------------------------------------------------------------------------------------

public:
	static void pressEnterPlease()
	{
		while (1)
		{
			char x = _getch(); // tidak ngebaca key release (hanya key press), tapi getKeyPressed iya
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

	static void setDefaultFont(int font)
	{
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0; // Width of each character in the font
		cfi.dwFontSize.Y = font; // Height
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	}

	Interface() { // constructor
		Console::initialize();
		Console::setCursorVisibility(false);
	}

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
			if (input == VK_RETURN)
			{
				if (inputFlag)
				{
					flag = 1;
					delayFlag = 0;
					delayScreen = 0;
				}
				else inputFlag++;
			}
			Console::printf("%c", production[x]);
			if (delayFlag) delayScreen = 50;
			Console::delay(delayScreen);
		}

		if (delayFlag)Console::delay(500); // tambahin delay supaya bagus

		Console::setColor(4); // BENERIN NIH 'MAGIC NUMBER' PLZZZ
		if (delayFlag)
		{
			for (int x = 0; x < 7; x++) {
				input = Console::getKeyPressed();
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
		pressEnterPlease();
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
				printf("\n\n\t\t\t\t\t    LOADING...");
			}
			yes++;
			no--;
		}

		Console::setColor(Console::COLOR_GREEN);
		Console::setCursorPos(0, 10);
		//if(!flag)Console::printf("\n\n\t\t\t\tLOAD SUCCESSFULL!");
		Console::printf("\n\n\t\t\t\t\tLOAD SUCCESSFULL!");
		//if (input == VK_RETURN) { return; }
		enter(37, 20, 2);
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
		char *introText[] = {   "After having lost your Monastery to demons,",
								"you follow the Dark Wanderer to Tristam Town.",
								"This is where your journey starts. ",
								"The demons are roaming the outskirt of this city",
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
			printf("\t\t");
			if (y == 5) { Console::setColor(11); }
			else printf("\t");
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
		enter(32, 20, 2);
		pressEnterPlease();
	}

	static int startGame( bool saveGameAvailable)
	{
		char* wallpaper[20] = {
			"                          )       \\   /      (",
			"                         /|\\      )\\_/(     /|\\",
			"*                       / | \\    (/\\|/\\)   / | \\                      *",
			"|`.____________________/__|__o____\\`|'/___o__|__\\___________________.'|",
			"|                           '^`    \\|/   '^`                          |",
			"|                                   V                                 |",
			"|                                                                     |",
			"|                                                                     |",
			"|                                                                     |",
			"|                                                                     |",
			"|                                                                     |",
			"|                                                                     |",
			"|                                                                     |",
			"|                                                                     |",
			"|                                                                     |",
			"| ._________________________________________________________________. |",
			"|'               l    /\\ /     \\\\            \\ /\\   l                `|",
			"*                l  /   V       ))            V   \\ l                 *",
			"                 l/            //                  \\I",
			"                               V"
		};

		system("cls");
		printf("\n");
		Console::setColor(Console::COLOR_RED);
		for (int i = 0; i < 20; i++)
		{
			printf("           %s\n", wallpaper[i]);
		}
		Console::setCursorVisibility(false);
		Console::setColor(Console::COLOR_WHITE);
		bool printFlag = true;
		int sampahFlag = 1;
		int pickMenu = 0;
		int maxMenu = saveGameAvailable ? 3 : 2;
		char charMenu;
		while (1)
		{
			if (printFlag)
			{
				//Interface::setWindowSize(1000, 550);
				Console::setColor(7);
				Console::setCursorPos(0, 24);
				Console::printf("Press up/down or WSAD to select, and enter to choose");

				Console::setCursorPos(43, 10);
				if(pickMenu ==0 )Console::setColor(79);
				else Console::setColor(Console::COLOR_WHITE);
				Console::printf("NEW GAME");

				if (saveGameAvailable)
				{
					Console::setCursorPos(43, 11);
					if (pickMenu == 1)Console::setColor(79);
					else Console::setColor(Console::COLOR_WHITE);
					Console::printf("LOAD GAME");
				}
				int yExit = saveGameAvailable ? 12 : 11;
				Console::setCursorPos(45, yExit);
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
			//Interface::setWindowSize(1000, 550);
			char buff = _getch();
			if (buff == VK_ESCAPE) return "3s0xla 81a;LKDJn(**A;"; // kode EXIT
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
		Console::setCursorVisibility(false);
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
			"the highest endurance and hit point and can withstand devastating",
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
						int sampah = Console::getKeyPressed();
						delayInput = 0;
					}
					else delayInput++;
				}
				if (printFlag)
				{
					system("cls");
					//Interface::setWindowSize(1000, 550);
					Console::setColor(7);
					Console::setCursorPos(23, 24);
					Console::printf("Press left/right or WSAD to select, and enter to choose");

					Console::setColor(Console::COLOR_WHITE);
					Console::setCursorPos(40-(name.length()/2), 1);
					cout << "What class are you, ";
					Console::setColor(Console::COLOR_RED);
					cout << name;
					Console::setColor(Console::COLOR_WHITE);
					cout << '?';
					Console::setCursorPos(7, 3);
					switch (job)
					{
					case 0:
						Console::setColor(Console::COLOR_RED);
						cout << "  ASSASSIN\n\n";
						for (int i = 0; i < 15; i++) // 31 = byk row assassin
						{
							printf("%s\n", assassin[i]);
						}
						for (int i = 0; i < 9; i++) // 9 = byk row assassinText
						{
							Console::setCursorPos(25, 9 + i);
							printf("%s", assassinText[i]);
						}
						break;
					case 1:
						Console::setColor(Console::COLOR_GREEN);
						cout << "  PALADIN\n\n\n";
						for (int i = 0; i < 12; i++)
						{
							printf("%s\n", paladin[i]);
						}
						for (int i = 0; i < 9; i++)
						{
							Console::setCursorPos(25, 9 + i);
							printf("%s", paladinText[i]);
						}
						break;
					case 2:
						Console::setColor(Console::COLOR_YELLOW);
						cout << " BARBARIAN\n\n\n\n";
						for (int i = 0; i < 11; i++)
						{
							printf("%s\n", barbarian[i]);
						}
						for (int i = 0; i < 7; i++)
						{
							Console::setCursorPos(25, 9 + i);
							printf("%s", barbarianText[i]);
						}
						break;
					} // end switch case
					printFlag = false;
				}
			} // end while dalem
			if (exit)
			{
				job = -2; // -2, soalnya ntar di akhir bakal return job+1
				break;
			}

			Console::setColor(Console::COLOR_MAGENTA);
			Console::setCursorPos(27, 23);
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
			Console::setCursorPos(17, 24);
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
		Console::setColor(Console::COLOR_WHITE);
		return (job+1); // 1 <= job <= 3
	}

	static void playerStatus(Human*& karakter, vector<Monster>& vMonster) // print player status
	{
		printf("\n");
		printf(" ============= Player Status =============\n\n");
		printf(" Character: '");
		Console::setColor(13); // warna ungu terang
		cout << karakter->getName();
		Console::setColor(Console::COLOR_WHITE);
		printf("' Level %d\n", karakter->getLevel());
		printf(" Class : ");
		switch (karakter->getJob())
		{
		case 1:
			Console::setColor(Console::COLOR_RED);
			cout << "Assassin";
			break;
		case 2:
			Console::setColor(Console::COLOR_GREEN);
			cout << "Paladin";
			break;
		case 3:
			Console::setColor(Console::COLOR_YELLOW);
			cout << "Barbarian";
			break;
		}
		printf("\n");
		Console::setColor(Console::COLOR_WHITE);
		printf(" Monsters killed : %d", karakter->getMonsterKilled());
		printf("\n\n");
		printf(" %-9s: %3d%7s %-13s: %3.0f\n", "Strength", karakter->getStrength(), " ", "Base Damage", karakter->getDamage());
		printf(" %-9s: %3d%7s %-13s: %3.0f%%\n", "Endurance", karakter->getEndurance(), " ", "Chance to Hit", karakter->getChanceToHit());
		printf(" %-9s: %3d%7s %-13s: %3.0f%%\n", "Agility", karakter->getAgility(), " ", "Evade", karakter->getEvade());
		printf(" %-9s: %3d%7s %-13s: %3.0f\n", "Dexterity", karakter->getDexterity(), " ", "Speed", karakter->getSpeed());
		printf(" %21s %-13s: %3.0f\n", " ", "Max Health", karakter->getMaxHealth());
		printf(" %-5s: %7d G%6s%-13s: %3.0f\n", "Gold", karakter->getGold(), " ", "Max Stamina", karakter->getMaxStamina());
		stringstream temp;
		temp << karakter->getExperience() << '/' << karakter->getExpRequirement(karakter->getLevel() + 1);
		string exp_string;
		getline(temp, exp_string);
		printf(" %-5s: %-14s %-13s: %3d\n\n", "Exp", exp_string.c_str(), "Armor", karakter->getArmor());
		printf(" =========================================\n");
	}

	static void shopMenu(vector<Item>& vShop, Human*& karakter)
	{
		int filterType = 0; // awalnya gk di-filter
		int sortType = 0; // awalnya gk di-sort
		int delayFlag = 1;
		int pickMenu = 0; // awalnya pilihan menu di yang pertama
		/*
			pickMenu:
				0 = Sort Items
				1 = Buy Item
				2 = Exit
		*/

		while (1) // print/update terus selama belum beli/exit dan masih filter/sort
		{
			system("cls");

			vector<Item*> temporary; // nampung semua item di vShop yang belum dibeli
			temporary.reserve(MAX_ITEM);
			int shopSize = vShop.size(); // berapa item di vShop

			temporary.clear(); // clear dulu

			// -------------- masukin data item ke temporary vector ---------------------
			if (filterType > 0) // kalau di-filter
			{
				for (int i = 0; i < shopSize; i++)
				{
					if (!(vShop[i].getBought()) && vShop[i].getType() == filterType) temporary.push_back(&vShop[i]);
				}
			}
			else // kalau di-filter
			{
				for (int i = 0; i < shopSize; i++) // ini buat baca di vShop, yang mana yang belum dibeli. (yang belum dibeli doang yang bakal di-push_back)
				{
					if (!(vShop[i].getBought())) temporary.push_back(&vShop[i]);
				}
			}
			// --------------------------------------------------------------------------

			// --------- sort data vector temporary berdasarkan yg diinginkan -----------
			if (sortType > 0)
			{
				switch (sortType)
				{
				case 1:
					sort(temporary.begin(), temporary.end(), ComparePrice());
					break;
				case 2:
					sort(temporary.begin(), temporary.end(), CompareName());
					break;
				case 3:
					if (filterType == 5) // kalau weapon, sort berdasarkan damage
					{
						sort(temporary.begin(), temporary.end(), CompareDamage());
						break;
					}
					else sort(temporary.begin(), temporary.end(), CompareArmor()); // selain itu, sort berdasarkan armor
					break;
				}
			}
			// --------------------------------------------------------------------------


			// --------------------------- print vector temporary -----------------------------------------------------------------------------------------------------
			vector<Item*>::iterator iter; // iterator untuk vector temporary (Item*)
			int i = 1; // variable buat print index vector (tapi ini mulai dari 1, sedangkan vector mulai dari 0)
			printf("\n");
			printf("                                 - TRISTAM SHOP -\n");
			printf(" ======================================================================================\n");
			printf(" %3s | %18s | %5s | %-28s | %10s | %6s\n", "No.", "ITEM NAME", "PRICE", "ITEM EFFECTS", "RESTRICTION","TYPE");
			printf(" ======================================================================================\n");

			for (iter = temporary.begin(); iter != temporary.end(); iter++, i++)
			{
				int res = (*iter)->getRestriction();
				string restriction;
				if (res == 0) restriction = "-";
				else if (res == 1) restriction = "Assassin";
				else if (res == 2) restriction = "Paladin";
				else if (res == 3) restriction = "Barbarian";
				
				
				/*
				type 0 = GAADA
				type 1 = helmet
				type 2 = gloves
				type 3 = armor
				type 4 = boots
				type 5 = weapon
				type 6 = shield
				*/
				string type;
				int tmp = (*iter)->getType();
				switch (tmp)
				{
				case 1: type = "Helmet"; break;
				case 2: type = "Gloves"; break;
				case 3: type = "Armor"; break;
				case 4: type = "Boots"; break;
				case 5: type = "Weapon"; break;
				case 6: type = "Shield"; break;
				}

				printf(" %2d.   %18s  %6d   %-28s   %11s   %6s\n", i, (*iter)->getName().c_str(), (*iter)->getPrice(), (*iter)->getEffect().c_str(), restriction.c_str(), type.c_str());
			}
			printf(" ======================================================================================\n");

			//-----------------------------------------------------------------------------------------------------------------------------------------------------------

			cout << "\n";
			cout << " Filter by : <";
			switch (filterType)
			{
			case 0:
				Console::setColor(Console::COLOR_WHITE);
				cout << "NONE";
				break;
			case 1:
				Console::setColor(Console::COLOR_BLUE);
				cout << "HELMET";
				break;
			case 2:
				Console::setColor(Console::COLOR_CYAN);
				cout << "GLOVE";
				break;
			case 3:
				Console::setColor(Console::COLOR_GREEN);
				cout << "ARMOR";
				break;
			case 4:
				Console::setColor(Console::COLOR_MAGENTA);
				cout << "BOOT";
				break;
			case 5:
				Console::setColor(Console::COLOR_RED);
				cout << "WEAPON";
				break;
			case 6:
				Console::setColor(Console::COLOR_YELLOW);
				cout << "SHIELD";
				break;
			}
			Console::setColor(Console::COLOR_WHITE);
			cout << ">";
			Console::setColor(COLOR_GREY);
			cout << " (Press ";
			Console::setColor(Console::COLOR_GREEN);
			cout << "<tab>";
			Console::setColor(COLOR_GREY);
			cout << " to change filter)\n\n";
			Console::setColor(Console::COLOR_WHITE);

			cout << " ========= Shop Menu ========\n\n";
			cout << " Your Gold: ";
			Console::setColor(Console::COLOR_YELLOW);
			cout << karakter->getGold() << " G\n\n";
			Console::setColor(Console::COLOR_WHITE);

			Console::setCursorVisibility(false);
			int flag = 0;
			bool printFlag = true;
			pickMenu = 0;

			int currY = Console::getCursorY();
			bool sortA = false; // saat di menu pilihan sort, click 'a'
			bool sortD = false; // saat di menu pilihan sort, click 'd' (SEBENERNYA GK PERLU, TAPI GPP, BUAT KONSISTENSI)
			while (1)
			{	
				if (printFlag)
				{
					Console::setCursorPos(0, currY);

					// 79 = putih dengan highlight merah
					// 78 = kuning dengan highlight merah
					// 14 = kuning

					int color1 = Console::COLOR_WHITE;
					int color2 = 14;
					if (pickMenu == 0)
					{
						color1 = 79;
						color2 = 78;
					}
					Console::setColor(Console::COLOR_WHITE);
					printf(" ");
					Console::setColor(color1);
					cout << "SORT : ";

					if (sortType == 0)
					{
						Console::setColor(color2);
						cout << "<NONE> ";
					}
					else
					{
						Console::setColor(color1);
						cout << "NONE ";
					}
					if (sortType == 1)
					{
						Console::setColor(color2);
						cout << "<PRICE> ";
					}
					else
					{
						Console::setColor(color1);
						cout << "PRICE ";
					}
					if (sortType == 2)
					{
						Console::setColor(color2);
						cout << "<NAME>";
					}
					else
					{
						Console::setColor(color1);
						cout << "NAME";
					}
					if (filterType != 0)
					{
						if (sortType == 3)
						{
							Console::setColor(color2);
							if (filterType == 5) cout << " <DAMAGE>";
							else cout << " <ARMOR>";
						}
						else
						{
							Console::setColor(color1);
							if (filterType == 5) cout << " DAMAGE";
							else cout << " ARMOR";
						}
					}
					Console::setColor(Console::COLOR_WHITE);
					printf("\n ");
					if (pickMenu == 1) Console::setColor(79);
					else Console::setColor(Console::COLOR_WHITE);
					cout << "BUY ITEM";
					
					Console::setColor(Console::COLOR_WHITE);
					printf("\n ");
					if (pickMenu == 2) Console::setColor(79);
					else Console::setColor(Console::COLOR_WHITE);
					cout << "BACK";

					Console::setColor(Console::COLOR_WHITE);
					printFlag = false;
				}
				char buff = Console::getKeyPressed();
				if (buff != -1)
				{
					if (delayFlag)
					{
						if (buff == VK_UP || buff == 0x57) // 0x57 == 'w'
						{
							pickMenu = (pickMenu - 1 + 3) % 3;
							printFlag = true;
						}
						else if (buff == VK_DOWN || buff == 0x53) // 0x53 == 's'
						{
							pickMenu = (pickMenu + 1) % 3;
							printFlag = true;
						}
						else if (buff == VK_TAB)
						{
							flag = 1;
							filterType = (filterType + 1) % 7;
							sortType = 0;
							delayFlag = 0;
							break;
						}
						else if (buff == VK_RETURN)
						{
							delayFlag = 0;
							break;
						}
						else if (pickMenu == 0 && buff == 0x41) // 'a'
						{
							sortA = true;
							delayFlag = 0;
							break;
						}
						else if (pickMenu == 0 && buff == 0x44) // 'd'
						{
							sortD = true;
							delayFlag = 0;
							break;
						}
						delayFlag = 0;
					}
					else delayFlag++;
				}
			} // end while dalem

			if (flag == 1)
			{
				continue; // (teken tab) filter ulang
			}

			int index;
			int temporarySize = temporary.size();
			bool buy = false;
			switch (pickMenu)
			{
			case 0: // sort item by...
				int maks;
				if (filterType == 0) maks = 3;
				else maks = 4;
				if (sortA) sortType = (sortType - 1 + maks) % maks;
				else sortType = (sortType + 1) % maks;
				continue; // continue while luar
				break;
			case 1: // buy item
				Console::setCursorVisibility(true);
				printf("\n\n");
				printf(" Input item number to buy ( 0 = cancel) [ 0 to %d ]: ", temporarySize);
				cin >> index;
				while (cin.fail() || index<0 || index>temporarySize)
				{
					flush();
					Console::setColor(Console::COLOR_RED);
					cout << " INVALID INPUT\n";
					Console::setColor(Console::COLOR_WHITE);
					printf(" Input item number to buy ( 0 = cancel) [ 0 to %d ]: ", temporarySize);
					cin >> index;
				}
				flush();

				if (index == 0)
				{
					delayFlag = 1;
					continue;
				}

				printf("\n ========== Confirmation ==========\n");
				printf(" Item name  : %s\n", temporary[index-1]->getName().c_str());
				printf(" Item type  : ");

				switch (temporary[index-1]->getType())
				{
				case 1:
					printf("Helmet");
					break;
				case 2:
					printf("Gloves");
					break;
				case 3:
					printf("Armor");
					break;
				case 4:
					printf("Boots");
					break;
				case 5:
					printf("Weapon");
					break;
				case 6:
					printf("Shield");
					break;
				}

				printf("\n Effects    : %s", temporary[index-1]->getEffect().c_str());
				printf("\n Restriction: ");

				switch (temporary[index-1]->getRestriction())
				{
				case 0:
					cout << "-";
					break;
				case 1:
					cout << "Assassin";
					break;
				case 2:
					cout << "Paladin";
					break;
				case 3:
					cout << "Barbarian";
					break;
				}
				printf("\n ==================================\n");

				Console::setColor(Console::COLOR_WHITE);
				printf("\n It will cost you ");
				Console::setColor(Console::COLOR_YELLOW);
				printf("%d G\n\n", temporary[index - 1]->getPrice());
				Console::setColor(Console::COLOR_WHITE);

				Console::setCursorVisibility(false);
				if (temporary[index - 1]->getPrice() > karakter->getGold())
				{
					Console::setColor(Console::COLOR_RED);
					printf(" You don't have that much gold!\n");
					Console::setColor(COLOR_GREY);
					printf(" (press enter to continue)");
					pressEnterPlease();
					Console::resetColor();
				}
				else
				{
					if ((temporary[index - 1]->getRestriction() > 0) && (temporary[index - 1]->getRestriction() != karakter->getJob()) )
					{
						Console::setColor(Console::COLOR_MAGENTA);
						printf(" WARNING: THE ITEM HAS RESTRICTION <");
						switch (temporary[index - 1]->getRestriction())
						{
						case 1:
							Console::setColor(Console::COLOR_RED);
							printf("ASSASSIN");
							break;
						case 2:
							Console::setColor(Console::COLOR_GREEN);
							printf("PALADIN");
							break;
						case 3:
							Console::setColor(Console::COLOR_YELLOW);
							printf("BARBARIAN");
							break;
						}
						Console::setColor(Console::COLOR_MAGENTA);
						printf("> ONLY!\n");
					}
					Console::setColor(Console::COLOR_WHITE);
					printf(" Are you sure you want to buy it?\n ");
					int pickWhat = 0;
					int bufferDelay = 1;
					bool flagPrint = true;
					int currY = Console::getCursorY();
					while (1)
					{
						if (flagPrint)
						{
							Console::setCursorPos(0, currY);
							if (pickWhat == 0)
							{
								Console::setColor(79);
								printf("<YES>");
								Console::setColor(Console::COLOR_WHITE);
								printf(" NO ");
							}
							else
							{
								Console::setColor(Console::COLOR_WHITE);
								printf(" YES ");
								Console::setColor(79);
								printf("<NO>");
								Console::setColor(Console::COLOR_WHITE);
							}
							flagPrint = false;
						}
						int buff = Console::getKeyPressed();
						if (buff != -1)
						{
							if (bufferDelay)
							{
								if (buff == VK_LEFT || buff == 0x41) // 41 == 'a'
								{
									pickWhat = (pickWhat - 1 + 2) % 2;
									flagPrint = true;
								}
								else if (buff == VK_RIGHT || buff == 0x44) // 0x44 == 'd'
								{
									pickWhat = (pickWhat + 1) % 2;
									flagPrint = true;
								}
								else if (buff == VK_RETURN)
								{
									if (pickWhat == 0) buy = true;
									break;
								}
								bufferDelay = 0;
							}
							else bufferDelay++;
						}
					} // end while
				}

				if(buy)
				{
					karakter->buyItem(temporary[index - 1]); // beli Itemnya
					karakter->setGold(-1*(temporary[index - 1]->getPrice())); // kurangin gold sebanyak harga item nya
					Console::setColor(Console::COLOR_GREEN);
					printf("\n\n You have successfuly bought the item!\n");

					Console::setColor(COLOR_GREY);
					printf("\n (Press enter to continue)");
					pressEnterPlease();
					Console::setColor(Console::COLOR_WHITE);
					return;
				}
				break;
			case 2: // exit
				return;
			} // end switch


		} // end while luar
	}
	
	static void homeMenu(Human*& karakter)
	{
		system("cls");

	}

	static void inventMenu(vector<Item>& vShop, vector<Monster>& vMonster, Human*& karakter)
	{
		system("cls");
		playerStatus(karakter, vMonster);
		printf("\n");
		int inventSize = (karakter->getInventory()).size();
		if (inventSize == 0)
		{
			printf(" - Empty Inventory -\n");
		}
		else
		{
			printf("                               - MY INVENTORY -\n");
			printf(" ======================================================================================\n");
			printf(" %3s | %18s | %5s | %-28s | %10s | %6s\n", "No.", "ITEM NAME", "PRICE", "ITEM EFFECTS", "RESTRICTION", "TYPE");
			printf(" ======================================================================================\n");

			int i = 1;
			for (auto iter = karakter->getInventory().begin(); iter != karakter->getInventory().end(); iter++, i++)
			{
				int res = (*iter)->getRestriction();
				string restriction;
				if (res == 0) restriction = "-";
				else if (res == 1) restriction = "Assassin";
				else if (res == 2) restriction = "Paladin";
				else if (res == 3) restriction = "Barbarian";


				/*
				type 0 = GAADA
				type 1 = helmet
				type 2 = gloves
				type 3 = armor
				type 4 = boots
				type 5 = weapon
				type 6 = shield
				*/
				string type;
				int tmp = (*iter)->getType();
				switch (tmp)
				{
				case 1: type = "Helmet"; break;
				case 2: type = "Gloves"; break;
				case 3: type = "Armor"; break;
				case 4: type = "Boots"; break;
				case 5: type = "Weapon"; break;
				case 6: type = "Shield"; break;
				}

				printf(" %2d.   %18s  %6d   %-28s   %11s   %6s\n", i, (*iter)->getName().c_str(), (*iter)->getPrice(), (*iter)->getEffect().c_str(), restriction.c_str(), type.c_str());
			}
			printf(" ======================================================================================\n");

			//-----------------------------------------------------------------------------------------------------------------------------------------------------------
		}
	}
};

int Interface::delayScreen = 0;
int Interface::delayFlag = 0;

#endif