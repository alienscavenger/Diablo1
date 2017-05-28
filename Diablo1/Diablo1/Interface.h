#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <cstdio>
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

	static void changeRed() { Console::setColor(Console::COLOR_RED); }
	static void changeGreen() { Console::setColor(Console::COLOR_GREEN); }
	static void resetColor() { Console::resetColor(); }
	static void setPos(int x, int y) { Console::setCursorPos(x, y); }
public:
	static int getInt(int min, int max)
	{
		int x = Console::getCursorX()+1;
		int y = Console::getCursorY(); 

		stringstream output;
		int output_int;
		string out;
		char buff;
		Console::setCursorPos(x, y);
		while (1)
		{
			buff = _getch();
			if (buff == VK_RETURN)
			{
				if (out.size() > 0)
				{
					out.push_back('\n');
					break;
				}
				else continue;
			}
			if (buff == VK_BACK)
			{
				if (out.size() > 0) // backspace kalau di dalem string out ada isinya
				{
					out.pop_back();
					printf("\b \b");
				}
				continue;
			}
			if (buff == VK_ESCAPE) continue;
			if (isalnum(buff))
			{
				out.push_back(buff);
				printf("%c", buff);
			}
		}
		output << out;
		output >> output_int;

		while(output.fail() || output_int<min || output_int>max)
		{
			// flush
			{
				output.clear();
				output.ignore(10000000, '\n');
				output.sync();
				output.clear();
				int counter = out.size();
				for (int i = 0; i < counter; i++) printf("\b \b");
				out.clear();
				Console::setCursorPos(x, y);
				Console::setColor(Console::COLOR_RED);
				printf("INVALID INPUT!");
				Console::delay(500);
				Console::setCursorPos(x, y);
				printf("               ");
				Console::resetColor();
			}
			Console::setCursorPos(x, y);
			// ulang lagi
			while (1)
			{
				buff = _getch();
				if (buff == VK_RETURN)
				{
					if (out.size() > 0)
					{
						out.push_back(buff);
						break;
					}
					else continue;
				}
				if (buff == VK_BACK)
				{
					if (out.size() > 0) // backspace kalau di dalem string out ada isinya
					{
						out.pop_back();
						printf("\b \b");
					}
					continue;
				}
				out.push_back(buff);
				printf("%c", buff);
			}
			output << out;
			output >> output_int;
		}

		return output_int;
	}

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

	static void shopMenu(vector<Item>& vShop, Human*& karakter)
	{
		int filterType = 0; // awalnya gk di-filter
		int sortType = 0; // awalnya gk di-sort
		int delayFlag = 1;
		int pickMenu = 0; // awalnya pilihan menu di yang pertama
		int nonBoughtSize = 0; // banyak item di shop yang blom dibeli
		bool yourClassOnly = false;
		/*
			pickMenu:
				0 = Sort Items
				1 = Buy Item
				2 = (insert job name here) class only: ON/OFF
				3 = Exit
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
				if (yourClassOnly)
				{
					int myJob = karakter->getJob();
					for (int i = 0; i < shopSize; i++)
					{
						if ((vShop[i].getRestriction()==myJob || vShop[i].getRestriction() == 0) && !(vShop[i].getBought()) && vShop[i].getType() == filterType) temporary.push_back(&vShop[i]);
					}
				}
				else
				{
					for (int i = 0; i < shopSize; i++)
					{
						if (!(vShop[i].getBought()) && vShop[i].getType() == filterType) temporary.push_back(&vShop[i]);
					}
				}
			}
			else // kalau gk di-filter
			{
				if (yourClassOnly)
				{
					int myJob = karakter->getJob();
					for (int i = 0; i < shopSize; i++) // ini buat baca di vShop, yang mana yang belum dibeli. (yang belum dibeli doang yang bakal di-push_back)
					{
						if ((vShop[i].getRestriction() == myJob || vShop[i].getRestriction()==0) && !(vShop[i].getBought())) temporary.push_back(&vShop[i]);
					}
				}
				else
				{
					for (int i = 0; i < shopSize; i++) // ini buat baca di vShop, yang mana yang belum dibeli. (yang belum dibeli doang yang bakal di-push_back)
					{
						if (!(vShop[i].getBought())) temporary.push_back(&vShop[i]);
					}
				}
				nonBoughtSize = temporary.size(); // update banyak item yang blom dibeli di shop
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
			Console::setColor(Console::COLOR_YELLOW);
			printf("                                 - Tristam Shop -\n");
			Console::resetColor();
			printf(" ======================================================================================\n");
			printf(" %3s | %18s | %5s | %-28s | %10s | %6s\n", "No.", "ITEM NAME", "PRICE", "ITEM EFFECTS", "RESTRICTION","TYPE");
			printf(" ======================================================================================\n");

			if (temporary.size() == 0)
			{
				if (nonBoughtSize > 0)
				{
					printf("\n                          // NO ITEM WITH THE TYPE ");
					int color;
					string type = "<";
					switch (filterType)
					{
					case 1: type += "HELMET"; color = Console::COLOR_BLUE; break;
					case 2: type += "GLOVES"; color = Console::COLOR_CYAN; break;
					case 3: type += "ARMOR"; color = Console::COLOR_GREEN; break;
					case 4: type += "BOOTS"; color = Console::COLOR_MAGENTA; break;
					case 5: type += "WEAPON"; color = Console::COLOR_RED; break;
					case 6: type += "SHIELD"; color = Console::COLOR_YELLOW; break;
					}
					type += ">";
					Console::setColor(color);
					printf("%s", type.c_str());
					Console::resetColor();
					printf(" //\n\n");
				}
				else printf("\n                              // EMPTY SHOP //\n\n"); // kalau inventory kosong
			}

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
			int color[7]{ Console::COLOR_WHITE,Console::COLOR_WHITE, Console::COLOR_WHITE, Console::COLOR_WHITE, Console::COLOR_WHITE,
				Console::COLOR_WHITE, Console::COLOR_WHITE };
			char* filterText[7] = { "NONE","HELMET","GLOVE","ARMOR","BOOTS","WEAPON","SHIELD" };
			switch (filterType)
			{
			case 0:
				color[0] = Console::COLOR_GRAY;
				break;
			case 1:
				color[1] = Console::COLOR_BLUE;
				break;
			case 2:
				color[2] = Console::COLOR_CYAN;
				break;
			case 3:
				color[3] = Console::COLOR_GREEN;
				break;
			case 4:
				color[4] = Console::COLOR_MAGENTA;
				break;
			case 5:
				color[5] = Console::COLOR_RED;
				break;
			case 6:
				color[6] = Console::COLOR_YELLOW;
				break;
			}
			// print filter by apa text
			{
				Console::setColor(color[0]);
				printf("%s", filterText[0]);
				for (int i = 1; i < 7; i++)
				{
					Console::resetColor();
					printf(",");
					Console::setColor(color[i]);
					printf("%s", filterText[i]);
				}
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
			//pickMenu = 0;

			int currY = Console::getCursorY();
			bool sortA = false; // saat di menu pilihan sort, click 'a'
			bool sortD = false; // saat di menu pilihan sort, click 'd' (SEBENERNYA GK PERLU, TAPI GPP, BUAT KONSISTENSI)
			delayFlag = 0;
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
					string job;
					switch (karakter->getJob())
					{
					case 1: job = "ASSASSIN"; break;
					case 2: job = "PALADIN"; break;
					case 3: job = "BARBARIAN"; break;
					}
					cout << job << " COMPATIBLE ONLY: ";
					Console::setColor(Console::COLOR_YELLOW);
					if (pickMenu == 2) Console::setColor(78);
					if (yourClassOnly) printf("YES");
					else printf("NO");

					Console::setColor(Console::COLOR_WHITE);
					printf("\n ");
					if (pickMenu == 3) Console::setColor(79);
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
							pickMenu = (pickMenu - 1 + 4) % 4;
							printFlag = true;
						}
						else if (buff == VK_DOWN || buff == 0x53) // 0x53 == 's'
						{
							pickMenu = (pickMenu + 1) % 4;
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
						else if (pickMenu == 0 && (buff == 0x41 || buff == VK_LEFT)) // 'a'
						{
							sortA = true;
							delayFlag = 0;
							break;
						}
						else if (pickMenu == 0 && (buff == 0x44 || buff == VK_RIGHT)) // 'd'
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
			{
				int maks;
				if (filterType == 0) maks = 3;
				else maks = 4;
				if (sortA) sortType = (sortType - 1 + maks) % maks;
				else sortType = (sortType + 1) % maks;
				continue; // continue while luar
			}
				break;
			case 1: // buy item
			{
				if (temporary.size() > 0)
				{
					Console::setCursorVisibility(true);
					printf("\n\n");
					printf(" Input item number to buy ( 0 = cancel) [ 0 to %d ]: ", temporarySize);
					index = Interface::getInt(0, temporarySize);

					if (index == 0)
					{
						delayFlag = 1;
						continue;
					}

					printf("\n ========== Confirmation ==========\n");
					printf(" Item name  : %s\n", temporary[index - 1]->getName().c_str());
					printf(" Item type  : ");

					switch (temporary[index - 1]->getType())
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

					printf("\n Effects    : %s", temporary[index - 1]->getEffect().c_str());
					printf("\n Restriction: ");

					switch (temporary[index - 1]->getRestriction())
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
						if ((temporary[index - 1]->getRestriction() > 0) && (temporary[index - 1]->getRestriction() != karakter->getJob()))
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
						int bufferDelay = 0;
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

					if (buy)
					{
						karakter->buyItem(temporary[index - 1]); // beli Itemnya
						karakter->setGold(-1 * (temporary[index - 1]->getPrice())); // kurangin gold sebanyak harga item nya
						Console::setColor(Console::COLOR_GREEN);
						printf("\n\n You have successfuly bought the item!\n");

						Console::setColor(COLOR_GREY);
						printf("\n (Press enter to continue)");
						pressEnterPlease();
						Console::setColor(Console::COLOR_WHITE);
						continue;
					}
				}
				else // kalau gk ada item di shop
				{
					Console::setColor(Console::COLOR_RED);
					printf("\n\n No Item detected!");
					Console::delay(700);
					Console::resetColor();
					continue;
				}
			}
				break;
			case 2:
				// toggle your class only
				if (yourClassOnly) yourClassOnly = false;
				else yourClassOnly = true;
				break;
			case 3: // exit
				return;
			} // end switch


		} // end while luar
	}

	static void printDiff(int doWhat,Human*& karakter, vector<Item*>temporary, int equipIndex, int itemIndex)
	{
		/*
			doWhat 0 = reset (gk kasih liatin difference nya)
			doWhat 1 = diff when equip
			doWhat 2 = diff when unequip
		*/
		Item x;
		Item* xP = NULL;
		if (!temporary.empty())
		{
			x = *temporary[itemIndex]; // local variable Item
			xP = &x;
		}

		Human compare = *karakter; // local variable Human
		if (doWhat == 0)
		{
			resetColor();
			for (int i = 0; i < 4; i++)
			{
				setPos(15, 8 + i);
				printf("       ");
			}
			setPos(41, 8);
			printf("       ");
			for (int i = 0; i < 2; i++)
			{
				setPos(42, 9 + i);
				printf("       ");
			}
			for (int i = 0; i < 4; i++)
			{
				setPos(41, 11 + i);
				printf("       ");
			}
		}
		else
		{
			if (doWhat == 1)
			{
				Item* temp = NULL;
				if (compare.getEquipStatus(equipIndex)) // kalau lagi ada yang di-equip, maka harus di-unequip dulu
				{
					temp = karakter->getEquipment(equipIndex); // buat ntar di-reequip. Soalnya, pas unequip item,bakal di setEquip ke 0
					if (temp == temporary[itemIndex])return; // kalau yang di-compare sama dengan yang sedang di-equip
					compare.unequipItem(equipIndex); // kalau sudah ada yg di-equip, maka unequip itu (secara implicit, manggil setEquip di item itu)
					
				}
				compare.equipItem(equipIndex,xP); // equip yang baru
				if(temp!=NULL)temp->setEquip(1); // di-set ke equipped lagi item yang lama (urutannya jgn dibalik sama setEquip yang di atas, karena bisa jadi item lama = item baru)
			}
			else if (doWhat == 2)
			{
				if (compare.getEquipStatus(equipIndex)) // kalau lagi ada yang di-equip
				{
					Item* temp = karakter->getEquipment(equipIndex);
					compare.unequipItem(equipIndex);
					temp->setEquip(1); // set equipped untuk karakter utama;
				}
				else return;
			}

			int str = compare.getStrength() - karakter->getStrength();
			int end = compare.getEndurance() - karakter->getEndurance();
			int agi = compare.getAgility() - karakter->getAgility();
			int dex = compare.getDexterity() - karakter->getDexterity();
			int dmg = compare.getDamage() - karakter->getDamage();
			int cth = floor(compare.getChanceToHit() - karakter->getChanceToHit());
			int eva = floor(compare.getEvade() - karakter->getEvade());
			int spd = floor(compare.getSpeed() - karakter->getSpeed());
			int hp = floor(compare.getMaxHealth() - karakter->getMaxHealth());
			int sta = floor(compare.getMaxStamina() - karakter->getMaxStamina());
			int amr = compare.getArmor() - karakter->getArmor();

			resetColor();
			if (str < 0)
			{
				setPos(12, 8);
				printf("%3d ", karakter->getStrength());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", str);
				resetColor();
				printf(")");
			}
			else if (str > 0)
			{
				setPos(12, 8);
				printf("%3d ", karakter->getStrength());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", str);
				resetColor();
				printf(")");

			}
			if (end < 0)
			{
				setPos(12, 9);
				printf("%3d ", karakter->getEndurance());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", end);
				resetColor();
				printf(")");
			}
			else if (end > 0)
			{
				setPos(12, 9);
				printf("%3d ", karakter->getEndurance());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", end);
				resetColor();
				printf(")");
			}
			if (agi < 0)
			{
				setPos(12, 10);
				printf("%3d ", karakter->getAgility());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", agi);
				resetColor();
				printf(")");
			}
			else if (agi > 0)
			{
				setPos(12, 10);
				printf("%3d ", karakter->getAgility());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", agi);
				resetColor();
				printf(")");
			}
			if (dex < 0)
			{
				setPos(12, 11);
				printf("%3d ", karakter->getDexterity());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", dex);
				resetColor();
				printf(")");
			}
			else if (dex > 0)
			{
				setPos(12, 11);
				printf("%3d ", karakter->getDexterity());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", dex);
				resetColor();
				printf(")");
			}
			if (dmg < 0)
			{
				setPos(38, 8);
				printf("%3.0f ", karakter->getDamage());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", dmg);
				resetColor();
				printf(")");
			}
			else if (dmg > 0)
			{
				setPos(38, 8);
				printf("%3.0f ", karakter->getDamage());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", dmg);
				resetColor();
				printf(")");
			}
			if (cth < 0)
			{
				setPos(38, 9);
				printf("%3.0f%% ", karakter->getChanceToHit());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", cth);
				resetColor();
				printf(")");
			}
			else if (cth > 0)
			{
				setPos(38, 9);
				printf("%3.0f%% ", karakter->getChanceToHit());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", cth);
				resetColor();
				printf(")");
			}
			if (eva < 0)
			{
				setPos(38, 10);
				printf("%3.0f%% ", karakter->getEvade());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", eva);
				resetColor();
				printf(")");
			}
			else if (eva > 0)
			{
				setPos(38, 10);
				printf("%3.0f%% ", karakter->getEvade());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", eva);
				resetColor();
				printf(")");
			}
			if (spd < 0)
			{
				setPos(38, 11);
				printf("%3.0f ", karakter->getSpeed());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", spd);
				resetColor();
				printf(")");
			}
			else if (spd > 0)
			{
				setPos(38, 11);
				printf("%3.0f ", karakter->getSpeed());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", eva);
				resetColor();
				printf(")");
			}
			if (hp < 0)
			{
				setPos(38, 12);
				printf("%3.0f ", karakter->getMaxHealth());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", hp);
				resetColor();
				printf(")");
			}
			else if (hp > 0)
			{
				setPos(38, 12);
				printf("%3.0f ", karakter->getMaxHealth());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", hp);
				resetColor();
				printf(")");
			}
			if (sta < 0)
			{
				setPos(38, 13);
				printf("%3.0f ", karakter->getMaxStamina());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", sta);
				resetColor();
				printf(")");
			}
			else if (sta > 0)
			{
				setPos(38, 13);
				printf("%3.0f ", karakter->getMaxStamina());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", sta);
				resetColor();
				printf(")");
			}
			if (amr < 0)
			{
				setPos(38, 14);
				printf("%3d ", karakter->getArmor());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", amr);
				resetColor();
				printf(")");
			}
			else if (amr > 0)
			{
				setPos(38, 14);
				printf("%3d ", karakter->getArmor());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", amr);
				resetColor();
				printf(")");
			}
			Console::setCursorPos(0, 18);
			// di bawah ini buat debug
			/*printf("(str=%d,end=%d,agi=%d,dex=%d,dmg=%d,cth=%d,eva=%d,spd=%d,hp=%d,sta=%d,amr=%d)", str, end, agi, dex, dmg, cth, eva, spd, hp, sta, amr);
			printf("(\nstr=%d,end=%d,agi=%d,dex=%d,dmg=%.0f,cth=%.0f,eva=%.0f,spd=%.0f,hp=%.0f,sta=%.0f,amr=%d)",
				compare.getStrength(), compare.getEndurance(), compare.getAgility(), compare.getDexterity(), compare.getDamage(), compare.getChanceToHit(),
				compare.getEvade(), compare.getSpeed(), compare.getMaxHealth(), compare.getMaxStamina(), compare.getArmor());*/
		}
	}

	static void equipmentMenu(Human*& karakter,vector<Item*>temporary, bool& active, int& state, int& filterType, bool& print, int& stillUnequiping, int which)
	{
		// int which -> CUMAN BUAT DEBUG
		Console::resetColor();
		Console::setCursorPos(50, 2);
		printf("============== Character Equipment ============%d=",which);

		if (print) // kalau print doang
		{
			int color[7];
			for (int i = 0; i < 7; i++) color[i] = Console::COLOR_WHITE;
			color[state] = 94; // highlight ungu-pink, text kuning
			char*text[7] = {" ","Head","Left Arm","Right Arm","Hands","Torso","Legs"};
			for (int i = 1; i < 7; i++)
			{
				Console::setColor(color[i]);
				Console::setCursorPos(51, 3 + i);

				if (karakter->getEquipStatus(i)) printf("%-9s: %s (%s)", text[i], karakter->getEquipment(i)->getName().c_str(), karakter->getEquipment(i)->getEffect().c_str());
				else printf("%-9s: (empty)", text[i]);
			}
			Console::resetColor();

			Console::setCursorPos(50, 11);
			printf("=================================================");

			return;
		}
		else
		{
			if (active) // lagi milih apa yang mau di-equip
			{
				Console::setCursorPos(50, 12);
				Console::setColor(Console::COLOR_GRAY);
				printf("(Preview when equipping/swapping item can be seen");
				Console::setCursorPos(50, 13);
				printf("On the left, with the difference inside the brackets)");
				Console::resetColor();
				Console::setCursorPos(50, 14);
				printf("===== Equipment Menu =====");
				Console::setCursorPos(50, 16);
				int maxItem = temporary.size();
				if (maxItem > 0)
				{
					int equipThis = 1;
					while (1)
					{
						Console::setCursorPos(50, 15);
						Console::setColor(79);
						printf("Select item to equip below (ESC to cancel) (ENTER to choose)");
						Console::resetColor();
						///Console::setCursorVisibility(true);
						///equipThis = Interface::getInt(0,maxItem);
						equipThis = compareEquipment(filterType, karakter, temporary, 1,equipThis-1); // -1 karena masalah indexingnya. Coba ganti ke 0 biar ngerti
						///Console::setCursorVisibility(false);

						Console::setCursorPos(50, 17);
						if (equipThis == -1)
						{
							active = false;
							filterType = 0;
							stillUnequiping = state-1;
							state = 0;
							print = true;
							return;
						}
						if (temporary[equipThis - 1]->getEquipped())
						{
							Console::setCursorPos(90, 23 + equipThis-1);
							printf("YOU ARE CURRENTLY EQUIPPING THIS!");
							Console::setCursorPos(90, 23 + equipThis);
							Console::setColor(Console::COLOR_GRAY);
							printf("(Press enter to continue)");
							Interface::pressEnterPlease();
							Console::resetColor();
							Console::setCursorPos(90, 23 + equipThis - 1);
							printf("                                  ");
							Console::setCursorPos(90, 23 + equipThis);
							printf("                         ");
							continue;
						}
						else if (temporary[equipThis - 1]->getRestriction() > 0 && temporary[equipThis - 1]->getRestriction() != karakter->getJob())
						{
							Console::setCursorPos(90, 23 + equipThis - 1);
							printf("YOU CANNOT EQUIP THIS! (see Restriction)");
							Console::setCursorPos(90, 23 + equipThis);
							Console::setColor(Console::COLOR_GRAY);
							printf("(Press enter to continue)");
							Interface::pressEnterPlease();
							Console::resetColor();
							Console::setCursorPos(90, 23 + equipThis - 1);
							printf("                                        ");
							Console::setCursorPos(90, 23 + equipThis);
							printf("                         ");
							continue;
						}
						else
						{
							printDiff(1,karakter, temporary, state, equipThis - 1);
							Console::setCursorPos(90, 23+equipThis-1);
							printf("Are you sure you want to equip");
							Console::setCursorPos(90, 23 + equipThis);
							Console::setColor(Console::COLOR_CYAN);
							printf("*%s*",temporary[equipThis-1]->getName().c_str());
							Console::resetColor();
							Console::printf(" ?");
							int pickWhat = 0;
							int bufferDelay = 0;
							bool flagPrint = true;
							int currY = Console::getCursorY();
							int currX = Console::getCursorX();
							bool equip = false;
							while (1)
							{
								if (flagPrint)
								{
									Console::setCursorPos(currX, currY);
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
											if (pickWhat == 0) equip = true;
											break;
										}
										bufferDelay = 0;
									}
									else bufferDelay++;
								}
							} // end while
							if (equip)
							{
								if (state == 2 && temporary[equipThis-1]->getType()==5 && !(karakter->getEquipStatus(3))) // kalau sedang equip weapon di left hand, tapi tangan kanan masih kosong
								{
									// prioritaskan tangan kanan
									Console::setColor(Console::COLOR_CYAN);
									Console::setCursorPos(90, 23 + equipThis+2);
									printf("RIGHT HAND IS EMPTY!");
									Console::setCursorPos(90, 23 + equipThis + 3);
									printf("EQUIPPING IN RIGHT HAND...");
									state = 3;
									Console::setCursorPos(90, 23 + equipThis+4);
									Console::setColor(Console::COLOR_GRAY);
									printf("(Press enter to continue)");
									Interface::pressEnterPlease();
									Console::resetColor();
								}
								else if (karakter->getEquipStatus(state))
								{
									karakter->unequipItem(state);
								}
								karakter->equipItem(state,temporary[equipThis - 1]);
								active = false;
								state = 0;
								filterType = 0;
								print = true;
								break;
							}
							else
							{
								Console::setCursorPos(90, 23 + equipThis - 1);
								printf("                                    ");
								Console::setCursorPos(90, 23 + equipThis);
								printf("                                    ");
								printDiff(0, karakter, temporary, 0, 0);
								Console::resetColor();
								Console::setCursorPos(91, 16);
								printf("                      ");
								Console::setCursorPos(50, 17);
								printf("                                                      ");
								Console::setCursorPos(currX, currY);
								printf("          ");
								continue;
							}
						} // end else
					} // end while
				}
				else
				{
					Console::setColor(79);
					printf("NO ITEM WITH THE TYPE: ");
					Console::resetColor();
					printf(" ");
					int color;
					string type = "<";
					switch (filterType)
					{
					case 1: type += "HELMET"; color = Console::COLOR_BLUE; break;
					case 2: type += "GLOVES"; color = Console::COLOR_CYAN; break;
					case 3: type += "ARMOR"; color = Console::COLOR_GREEN; break;
					case 4: type += "BOOTS"; color = Console::COLOR_MAGENTA; break;
					case 5: type += "WEAPON"; color = Console::COLOR_RED; break;
					case -1: type += "WEAPON/SHIELD"; color = Console::COLOR_YELLOW; break;
					}
					type += ">";
					Console::setColor(color);
					printf("%s", type.c_str());

					Console::setCursorPos(50, 18);
					Console::setColor(Console::COLOR_GRAY);
					printf("(press enter to continue)");
					Interface::pressEnterPlease();
					stillUnequiping = state-1;
					active = false;
					state = 0;
					filterType = 0;
					print = true;
				}
				return;
			}
			else
			{
				Console::setCursorPos(15, 1);
				Console::setColor(Console::COLOR_GRAY);
				printf("(Unequip Preview)");

				//Human preview = *karakter; // copy stats karakter ke temporary Objek
				
				Console::setCursorPos(50, 12);
				Console::setColor(Console::COLOR_GRAY);
				printf("(Choose the equipment slot above to CHANGE EQUIPMENT,");
				Console::setCursorPos(50, 13);
				printf("WSAD to pick, BACKSPACE to UNEQUIP item, ESC to go back.)");
				Console::resetColor();
				Console::setCursorPos(50, 14);
				printf("===== Equipment Menu =====");

				bool printFlag = true;
				int pickMenu = stillUnequiping<6? stillUnequiping : 6; // kalau pickMenu berada di 'back', tidak akan men-skip ke unequip
				stillUnequiping = 6;
				/*
					menu 0-5 = equipment slot
					menu 6 = back
				*/
				int delayFlag = 0;
				while (1)
				{
					if (printFlag)
					{
						printDiff(0, karakter, temporary, 0, 0);//reset yang sebelumnya ada aja)
						printDiff(2, karakter, temporary, pickMenu+1, 0);//print perbedaannya
						int color[7];
						for (int i = 0; i < 7; i++) color[i] = Console::COLOR_WHITE;
						color[pickMenu] = 79; // highlight merah, text putih
						char*text[6] = { "Head","Left Arm","Right Arm","Hands","Torso","Legs" };
						for (int i = 0; i < 6; i++)
						{
							Console::setColor(color[i]);
							Console::setCursorPos(51, 4 + i);

							if (karakter->getEquipStatus(i+1)) printf("%-9s: %s (%s)", text[i], karakter->getEquipment(i+1)->getName().c_str(), karakter->getEquipment(i+1)->getEffect().c_str());
							else printf("%-9s: (empty)", text[i]);
						}
						Console::setCursorPos(50, 15);
						Console::setColor(color[6]);
						printf("Back");

						Console::resetColor();

						printFlag = false;
					}
					char buff = Console::getKeyPressed();
					if (buff != -1)
					{
						if (delayFlag) // supaya key release tidak kebaca
						{
							if (buff == VK_UP || buff == 0x57) // 0x57 == 'w'
							{
								pickMenu = (pickMenu - 1 + 7) % 7;
								printFlag = true;
							}
							else if (buff == VK_DOWN || buff == 0x53) // 0x53 == 's'
							{
								pickMenu = (pickMenu + 1) % 7;
								printFlag = true;
							}
							else if (buff == VK_BACK)
							{
								if (pickMenu < 6 && karakter->getEquipStatus(pickMenu+1)) // kalau menu bukan di 'back', dan ada yang sedang di-equip
								{
									//unequip
									karakter->unequipItem(pickMenu + 1);
									stillUnequiping = pickMenu;
									print = true;
									break;
								}
							}
							else if (buff == VK_ESCAPE)
							{
								break;
							}
							else if (buff == VK_RETURN)
							{
								bool balik = false;
								switch (pickMenu)
								{
								case 0:
									filterType = 1;
									break;
								case 1:
									filterType = -1; // weapon dan shield (5 dan 6)
									break;
								case 2:
									filterType = 5;
									break;
								case 3:
									filterType = 2;
									break;
								case 4:
									filterType = 3;
									break;
								case 5:
									filterType = 4;
									break;
								case 6:
									balik = true;
									break;
								}
								if (balik)break;
								active = true;
								state = pickMenu + 1;
								break;
							}
							int sampah = Console::getKeyPressed();
							delayFlag = 0;
						}
						else delayFlag++;
					}
				} // end while
				printDiff(0, karakter, temporary, 0, 0);//reset yang sebelumnya ada aja)

			} // end else kalau gk active
		} // end else luar
	}

	static int compareEquipment(int currFilterType, Human*& karakter, vector<Item*>temporary, int type, int curr) // type 0 = cek doang, type 1 = equip, curr = i saat equip (balik ke pilihan sebelumnya)
	{
		Console::setCursorPos(18, 17);
		Console::setColor(Console::COLOR_GREEN);
		if (type == 1)
		{
			Console::setColor(Console::COLOR_RED);
			printf("        <CHOOSE THE ITEM TO BE EQUIPPED>");
		}
		else printf("<COMPARE CURRENTLY EQUIPPED WITH THE SELECTED ITEM>");

		Console::setCursorPos(28, 18);
		if (currFilterType == 5 || currFilterType == -1 && type != 1) Console::setCursorPos(16, 18); // kalau lagi filter weapon
		Console::setColor(Console::COLOR_GREEN);
		printf("<tab> ");

		Console::resetColor();
		printf("<Camera: ");

		Console::setColor(Console::COLOR_YELLOW);
		printf("DYNAMIC");
		
		Console::resetColor();
		printf(">  ");

		if (currFilterType == 5 || currFilterType == -1 && type != 1) // kalau lagi filter weapon
		{
			Console::resetColor();
			printf("<Compare with");

			Console::setColor(Console::COLOR_YELLOW);
			printf(" LEFT HAND>");

			Console::setColor(Console::COLOR_GREEN);
			printf(" <space>     ");
		}
		else
		{
			printf("                ");
		}
		

		Console::setCursorPos(0, 23);
		Console::resetColor();
		int size = temporary.size();
		int printDelay = 0;
		bool printFlag = true;
		int leftHand = 1;
		int i = 0;
		if (type == 1)
		{
			if (currFilterType == 5) leftHand = 0;
			else if (currFilterType == -1) leftHand = 1;
			i = curr;
			// reset warna sebelumnya ke putih/highlight merah dulu
			{
				if (temporary[i]->getEquipped())Console::setColor(79);
				else Console::resetColor();
				Console::setCursorPos(0, 23 + i);

				int res = temporary[i]->getRestriction();
				string restriction;
				if (res == 0) restriction = "-";
				else if (res == 1) restriction = "Assassin";
				else if (res == 2) restriction = "Paladin";
				else if (res == 3) restriction = "Barbarian";

				string type;
				int tmp = temporary[i]->getType();
				switch (tmp)
				{
				case 1: type = "Helmet"; break;
				case 2: type = "Gloves"; break;
				case 3: type = "Armor"; break;
				case 4: type = "Boots"; break;
				case 5: type = "Weapon"; break;
				case 6: type = "Shield"; break;
				}
				printf(" %2d.   %18s  %6d   %-28s   %11s   %6s\n", i + 1, temporary[i]->getName().c_str(), temporary[i]->getPrice(),
					temporary[i]->getEffect().c_str(), restriction.c_str(), type.c_str());
			}
		}
		int fixedCamera = 0;
		while (1)
		{
			if (printFlag)
			{
				Console::setCursorPos(0, 23 + i);
				
				int res = temporary[i]->getRestriction();
				string restriction;
				if (res == 0) restriction = "-";
				else if (res == 1) restriction = "Assassin";
				else if (res == 2) restriction = "Paladin";
				else if (res == 3) restriction = "Barbarian";

				string type_;
				int tmp = temporary[i]->getType();
				switch (tmp)
				{
				case 1: type_ = "Helmet"; break;
				case 2: type_ = "Gloves"; break;
				case 3: type_ = "Armor"; break;
				case 4: type_ = "Boots"; break;
				case 5: type_ = "Weapon"; break;
				case 6: type_ = "Shield"; break;
				}

				if (temporary[i]->getEquipped())Console::setColor(94);
				else Console::setColor(78);

				printf(" %2d.   %18s  %6d   %-28s   %11s   %6s\n",i+1,temporary[i]->getName().c_str(),temporary[i]->getPrice(),
					temporary[i]->getEffect().c_str(), restriction.c_str(), type_.c_str());
				
				int index;
				switch(temporary[i]->getType())
				{
				case 1:
					index = 1;
					break;
				case 2:
					index = 4;
					break;
				case 3:
					index = 5;
					break;
				case 4:
					index = 6;
					break;
				case 5:
				{
					//// kalau tangan kiri kosong atau tangan kiri ada shield, cek tangan kanan

					//if (!(karakter->getEquipStatus(2)) || (karakter->getEquipment(2)->getType()==2)) { index = 3; }
					//else
					//{
					//	// kalau kiri kanan weapon
					//	if (leftHand)index = 2;
					//	else index = 3;
					//}
					if (leftHand) index = 2;
					else index = 3;
					break;
				}
				break;
				case 6:
					index = 2;
					break;
				}
				printDiff(0, karakter, temporary, 0, 0);
				if (!(temporary[i]->getEquipped()) || (type!=1))printDiff(1, karakter, temporary, index, i); // kalau gk lagi di-equip atau type!=1, print difference nya
				if(fixedCamera)Console::setCursorPos(0, 0); // supaya gk loncat" cameranya
				else Console::setCursorPos(0, 23 + i);
				printFlag = false;
			}
			char buff = Console::getKeyPressed();
			if (buff != -1)
			{
				if (printDelay)
				{
					if (buff == VK_UP || buff == 0x57) // 0x57 == 'w'
					{
						// reset warna sebelumnya ke putih/highlight merah dulu
						{
							if (temporary[i]->getEquipped())Console::setColor(79);
							else Console::resetColor();
							Console::setCursorPos(0, 23 + i);

							int res = temporary[i]->getRestriction();
							string restriction;
							if (res == 0) restriction = "-";
							else if (res == 1) restriction = "Assassin";
							else if (res == 2) restriction = "Paladin";
							else if (res == 3) restriction = "Barbarian";

							string type;
							int tmp = temporary[i]->getType();
							switch (tmp)
							{
							case 1: type = "Helmet"; break;
							case 2: type = "Gloves"; break;
							case 3: type = "Armor"; break;
							case 4: type = "Boots"; break;
							case 5: type = "Weapon"; break;
							case 6: type = "Shield"; break;
							}
							printf(" %2d.   %18s  %6d   %-28s   %11s   %6s\n", i + 1, temporary[i]->getName().c_str(), temporary[i]->getPrice(),
								temporary[i]->getEffect().c_str(), restriction.c_str(), type.c_str());
						}
						i = (i - 1 + size) % size;
						printFlag = true;
					}
					else if (buff == VK_DOWN || buff == 0x53) // 0x53 == 's'
					{
						// reset warna sebelumnya ke putih/highlight dulu
						{
							if (temporary[i]->getEquipped())Console::setColor(79);
							else Console::resetColor();
							Console::setCursorPos(0, 23 + i);

							int res = temporary[i]->getRestriction();
							string restriction;
							if (res == 0) restriction = "-";
							else if (res == 1) restriction = "Assassin";
							else if (res == 2) restriction = "Paladin";
							else if (res == 3) restriction = "Barbarian";

							string type;
							int tmp = temporary[i]->getType();
							switch (tmp)
							{
							case 1: type = "Helmet"; break;
							case 2: type = "Gloves"; break;
							case 3: type = "Armor"; break;
							case 4: type = "Boots"; break;
							case 5: type = "Weapon"; break;
							case 6: type = "Shield"; break;
							}
							printf(" %2d.   %18s  %6d   %-28s   %11s   %6s\n", i + 1, temporary[i]->getName().c_str(), temporary[i]->getPrice(),
								temporary[i]->getEffect().c_str(), restriction.c_str(), type.c_str());
						}
						i = (i + 1) % size;
						printFlag = true;
					}
					else if (buff == VK_TAB)
					{
						fixedCamera = (fixedCamera + 1) % 2; // toggle fixed camera
						if (fixedCamera)Console::setCursorPos(0, 0); // supaya gk loncat" cameranya
						else Console::setCursorPos(0, 23 + i);
						{
							Console::setCursorPos(28, 18);
							if (currFilterType == 5 || currFilterType == -1 && type != 1) Console::setCursorPos(16, 18); // kalau lagi filter weapon
							Console::setColor(Console::COLOR_GREEN);
							printf("<tab> ");
							Console::resetColor();
							if (fixedCamera)
							{
								printf("<Camera: ");
								Console::setColor(Console::COLOR_YELLOW);
								printf("FIXED");
								Console::resetColor();
							}
							else
							{
								printf("<Camera: ");
								Console::setColor(Console::COLOR_YELLOW);
								printf("DYNAMIC");
							}

							Console::resetColor();
							printf(">  ");

							if (currFilterType == 5 || currFilterType == -1 && type != 1) // kalau lagi filter weapon
							{
								if (leftHand)
								{
									Console::resetColor();
									printf("<Compare with");

									Console::setColor(Console::COLOR_YELLOW);
									printf(" LEFT HAND>");

									Console::setColor(Console::COLOR_GREEN);
									printf("<space>      ");
								}
								else
								{
									Console::resetColor();
									printf("<Compare with");

									Console::setColor(Console::COLOR_YELLOW);
									printf(" RIGHT HAND>");

									Console::setColor(Console::COLOR_GREEN);
									printf("<space>     ");
								}
							}
							else
							{
								printf("                ");
							}
						}
					}
					else if (buff == VK_SPACE && ( currFilterType == 5 || currFilterType == -1 && type != 1))
					{
						leftHand = (leftHand + 1) % 2;
						{
							Console::setCursorPos(28, 18);
							if (currFilterType == 5 || currFilterType == -1 && type != 1) Console::setCursorPos(16, 18); // kalau lagi filter weapon
							Console::setColor(Console::COLOR_GREEN);
							printf("<tab> ");
							Console::resetColor();
							if (fixedCamera)
							{
								printf("<Camera: ");
								Console::setColor(Console::COLOR_YELLOW);
								printf("FIXED");
								Console::resetColor();
							}
							else
							{
								printf("<Camera: ");
								Console::setColor(Console::COLOR_YELLOW);
								printf("DYNAMIC");
							}

							Console::resetColor();
							printf(">  ");

							if (currFilterType == 5 || currFilterType == -1 && type != 1) // kalau lagi filter weapon
							{
								if (leftHand)
								{
									Console::resetColor();
									printf("<Compare with");

									Console::setColor(Console::COLOR_YELLOW);
									printf(" LEFT HAND>");

									Console::setColor(Console::COLOR_GREEN);
									printf("<space>      ");
								}
								else
								{
									Console::resetColor();
									printf("<Compare with");

									Console::setColor(Console::COLOR_YELLOW);
									printf(" RIGHT HAND>");

									Console::setColor(Console::COLOR_GREEN);
									printf("<space>     ");
								}
							}
							else
							{
								printf("                ");
							}
						}
						printFlag = true;
					}
					else if (buff == VK_RETURN && type==1)
					{
						Console::resetColor();
						return i+1;
					}
					else if (buff == VK_ESCAPE)
					{
						if (type == 1)
						{
							Console::resetColor();
							return -1;
						}
						break;
					}
					printDelay = 0;
				}
				else printDelay++;
			}
		}
		Console::resetColor();
		return 0;
	}

	static void playerStatus(Human*& karakter, vector<Monster>& vMonster) // print player status
	{
		Console::setCursorPos(0, 2);
		Console::resetColor();
		printf(" =============== Player Status ==============\n\n");
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
		if (karakter->getLevel() < Human::MAX_LEVEL)
		{
			temp << karakter->getExperience() << '/' << karakter->getExpRequirement(karakter->getLevel() + 1);
		}
		else
		{
			temp << "MAX LEVEL!!!";
		}
		string exp_string;
		getline(temp, exp_string);
		printf(" %-5s: %-14s %-13s: %3d\n\n", "Exp", exp_string.c_str(), "Armor", karakter->getArmor());
		printf(" ============================================\n");
	}

	static void homeMenu(vector<Item>& vShop, vector<Monster>& vMonster, Human*& karakter, vector<Item*>& vInventory)
	{
		// 99% COPAS DARI SHOPMENU
		int filterType = 0; // awalnya gk di-filter
		int sortType = 0; // awalnya gk di-sort
		int delayFlag = 0;
		bool equipMenuPrintOnly = true; // true kalau mau print character equipment aja
		bool equipMenuActive = false; // awalnya equipment menu gk active (kalau active, artinya, di dalem loop, akan masuk ke equipment menu, bukan player menu
		int stillUnequiping = 6; // SATU"NYA WORKAROUND SUPAYA BISA CEPET BALIK KE UNEQUIP ITEM
		int equipMenuState = 0; // kalau >0, artinya, equipment menu saat sedang ada di state "pick item to equip". Valuenya adalah index dari eguipment yang sedang dipilih
		int pickMenu = 0; // awalnya pilihan menu di yang pertama
						  /*
						  pickMenu:
						  0 = Sort Items
						  1 = Sell Item
						  2 = My Equipment
						  3 = Compare Equipment
						  4 = Exit
						  */

		while (1) // print/update terus selama belum beli/exit dan masih filter/sort
		{
			system("cls");
			Console::setColor(Console::COLOR_RED);
			Console::setCursorPos(40, 0);
			printf("- %s's House -", karakter->getName().c_str());
			Console::resetColor();

			playerStatus(karakter, vMonster);

			printf("\n");
			int inventSize = vInventory.size(); // berapa item di inventory

			vector<Item*> temporary; // nampung semua item di vInventory yang sudah dibeli
			temporary.reserve(MAX_ITEM);

			temporary.clear(); // clear dulu

			// -------------- masukin data item ke temporary vector ---------------------
			if (filterType == -1) // kalau filternya <Weapon and Shield>
			{
				for (int i = 0; i < inventSize; i++)
				{
					if (vInventory[i]->getType() > 4) temporary.push_back(vInventory[i]); // filter 5 dan 6
				}
			}
			else if (filterType > 0) // kalau di-filter
			{
				for (int i = 0; i < inventSize; i++)
				{
					if (vInventory[i]->getType() == filterType) temporary.push_back(vInventory[i]);
				}
			}
			else // kalau gk di-filter
			{
				for (int i = 0; i < inventSize; i++) // ini buat baca di vShop, yang mana yang belum dibeli. (yang belum dibeli doang yang bakal di-push_back)
				{
					temporary.push_back(vInventory[i]);
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
			printf("                                 - My Inventory -\n");
			printf(" ======================================================================================\n");
			printf(" %3s | %18s | %5s | %-28s | %10s | %6s\n", "No.", "ITEM NAME", "PRICE", "ITEM EFFECTS", "RESTRICTION", "TYPE");
			printf(" ======================================================================================\n");

			if (temporary.size() == 0)
			{
				if (inventSize > 0)
				{
					printf("\n                          // NO ITEM WITH THE TYPE ");
					int color;
					string type = "<";
					switch (filterType)
					{
					case 1: type += "HELMET"; color = Console::COLOR_BLUE; break;
					case 2: type += "GLOVES"; color = Console::COLOR_CYAN; break;
					case 3: type += "ARMOR"; color = Console::COLOR_GREEN; break;
					case 4: type += "BOOTS"; color = Console::COLOR_MAGENTA; break;
					case 5: type += "WEAPON"; color = Console::COLOR_RED; break;
					case 6: type += "SHIELD"; color = Console::COLOR_YELLOW; break;
					case -1: type += "WEAPON OR SHIELD"; color = Console::COLOR_YELLOW; break;
					}
					type += ">";
					Console::setColor(color);
					printf("%s", type.c_str());
					Console::resetColor();
					printf(" //\n\n");
				}
				else printf("\n                              // EMPTY INVENTORY //\n\n"); // kalau inventory kosong
			}

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

				if ((*iter)->getEquipped())Console::setColor(79); // kalau sudah di-equip, maka ganti warnanya
				else Console::resetColor();

				printf(" %2d.   %18s  %6d   %-28s   %11s   %6s\n", i, (*iter)->getName().c_str(), (*iter)->getPrice(), (*iter)->getEffect().c_str(), restriction.c_str(), type.c_str());
				Console::resetColor();
			}
			printf(" ======================================================================================\n");

			//-----------------------------------------------------------------------------------------------------------------------------------------------------------

			cout << "\n";
			cout << " Filter by : <";
			int color[7]{ Console::COLOR_WHITE,Console::COLOR_WHITE, Console::COLOR_WHITE, Console::COLOR_WHITE, Console::COLOR_WHITE,
				Console::COLOR_WHITE, Console::COLOR_WHITE };
			char* filterText[7] = { "NONE","HELMET","GLOVE","ARMOR","BOOTS","WEAPON","SHIELD" };
			switch (filterType)
			{
			case -1:
				color[5] = Console::COLOR_RED;
				color[6] = Console::COLOR_YELLOW;
				break;
			case 0:
				color[0] = Console::COLOR_GRAY;
				break;
			case 1:
				color[1] = Console::COLOR_BLUE;
				break;
			case 2:
				color[2] = Console::COLOR_CYAN;
				break;
			case 3:
				color[3] = Console::COLOR_GREEN;
				break;
			case 4:
				color[4] = Console::COLOR_MAGENTA;
				break;
			case 5:
				color[5] = Console::COLOR_RED;
				break;
			case 6:
				color[6] = Console::COLOR_YELLOW;
				break;
			}
			// print filter by apa text
			{
				Console::setColor(color[0]);
				printf("%s", filterText[0]);
				for (int i = 1; i < 7; i++)
				{
					Console::resetColor();
					printf(",");
					Console::setColor(color[i]);
					printf("%s", filterText[i]);
				}
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

			

			cout << " ========= Player Menu ========\n\n";
			Console::setColor(Console::COLOR_WHITE);

			Console::setCursorVisibility(false);
			int flag = 0;
			bool printFlag = true;
			pickMenu = 0;
			if (equipMenuActive || stillUnequiping<=5) pickMenu = -1; // kalau equipMenu lagi active, jgn highlight selection di player menu

			int currY = Console::getCursorY();
			bool sortA = false; // saat di menu pilihan sort, click 'a'
			bool sortD = false; // saat di menu pilihan sort, click 'd' (SEBENERNYA GK PERLU, TAPI GPP, BUAT KONSISTENSI)

			// //////////////////////////////////////////////////////////// lokasi kode ini gk boleh diubah
			equipmentMenu(karakter, temporary, equipMenuActive, equipMenuState, filterType, equipMenuPrintOnly,stillUnequiping,1); // state 0 kalau mau print doang, state>0 saat ada yang sedang dipilih
			equipMenuPrintOnly = false;
			// ////////////////////////////////////////////////////////////

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
					cout << "SELL ITEM";

					Console::setColor(Console::COLOR_WHITE);
					printf("\n ");
					if (pickMenu == 2) Console::setColor(79);
					else Console::setColor(Console::COLOR_WHITE);
					cout << "MY EQUIPMENT";

					Console::setColor(Console::COLOR_WHITE);
					printf("\n ");
					if (temporary.size() == 0)
					{
						if (pickMenu == 3) Console::setColor(72); // highlight merah, text abu"
						else Console::setColor(Console::COLOR_GRAY);
					}
					else
					{
						if (pickMenu == 3) Console::setColor(79);
						else Console::setColor(Console::COLOR_WHITE);
					}
					cout << "COMPARE EQUIPMENT";

					Console::setColor(Console::COLOR_WHITE);
					printf("\n ");
					if (pickMenu == 4) Console::setColor(79);
					else Console::setColor(Console::COLOR_WHITE);
					cout << "EXIT";

					Console::setColor(Console::COLOR_WHITE);
					printFlag = false;
				}
				char buff = Console::getKeyPressed();
				if (buff != -1)
				{
					if (equipMenuActive || stillUnequiping<=5)break; // menjaga tidak tombol yang tak sengaja ditekan
					if (delayFlag)
					{
						if (buff == VK_UP || buff == 0x57) // 0x57 == 'w'
						{
							pickMenu = (pickMenu - 1 + 5) % 5;
							printFlag = true;
						}
						else if (buff == VK_DOWN || buff == 0x53) // 0x53 == 's'
						{
							pickMenu = (pickMenu + 1) % 5;
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
						else if (pickMenu == 0 && (buff == 0x41 || buff == VK_LEFT)) // 'a'
						{
							sortA = true;
							delayFlag = 0;
							break;
						}
						else if (pickMenu == 0 && (buff == 0x44 || buff == VK_RIGHT)) // 'd'
						{
							sortD = true;
							delayFlag = 0;
							break;
						}
						delayFlag = 0;
					}
					else delayFlag++;
				}
				if (equipMenuActive || stillUnequiping<=5)break; // kalau lagi di equp menu, break aja
			} // end while dalem

			if (equipMenuActive || stillUnequiping<=5) // kalau lagi active, artinya sedang milih item. kalau stillUnequiping<=5, artinya lagi unequip
			{
				equipmentMenu(karakter, temporary, equipMenuActive,equipMenuState, filterType, equipMenuPrintOnly,stillUnequiping,2);
				equipMenuPrintOnly = true;
				sortType = 0; // jangan di-sort
				continue;
			}

			if (flag == 1)
			{
				equipMenuPrintOnly = true;
				continue; // (teken tab) filter ulang
			}

			int index;
			int temporarySize = temporary.size();
			bool sell = false;
			switch (pickMenu)
			{
			case 0: // sort item by...
			{
				equipMenuPrintOnly = true;
				int maks;
				if (filterType == 0) maks = 3;
				else maks = 4;
				if (sortA) sortType = (sortType - 1 + maks) % maks;
				else sortType = (sortType + 1) % maks;
				continue; // continue while luar
			}
				break;
			case 1: // sell item
			{
				equipMenuPrintOnly = true;
				if (temporary.size() == 0)
				{
					Console::setColor(Console::COLOR_RED);
					printf("\n\n");
					printf(" No Item detected!");
					Console::delay(700);
					continue;
				}
				Console::setCursorVisibility(true);
				printf("\n\n");
				printf(" Input item number to sell ( 0 = cancel) [ 0 to %d ]:", temporarySize);
				index = Interface::getInt(0, temporarySize);

				if (index == 0)
				{
					delayFlag = 1;
					continue;
				}

				if (temporary[index - 1]->getEquipped())
				{
					Console::setColor(Console::COLOR_RED);
					printf("\n THAT ITEM IS CURRENTLY EQUIPPED!!!\n");
					Console::setColor(Console::COLOR_GRAY);
					printf(" (press enter to continue)");
					Console::resetColor();
					Interface::pressEnterPlease();
					continue; // ulang lagi
				}

				printf("\n ========== Confirmation ==========\n");
				printf(" Item name  : %s\n", temporary[index - 1]->getName().c_str());
				printf(" Item type  : ");

				switch (temporary[index - 1]->getType())
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

				printf("\n Effects    : %s", temporary[index - 1]->getEffect().c_str());
				printf("\n Restriction: ");

				switch (temporary[index - 1]->getRestriction())
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
				printf("\n You will receive ");
				Console::setColor(Console::COLOR_YELLOW);
				printf("%d G\n\n", (temporary[index - 1]->getPrice()) / 2);
				Console::setColor(Console::COLOR_WHITE);

				Console::setCursorVisibility(false);

				Console::setColor(Console::COLOR_WHITE);
				printf(" Are you sure you want to sell it?\n ");
				int pickWhat = 0;
				int bufferDelay = 0;
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
								if (pickWhat == 0) sell = true;
								break;
							}
							bufferDelay = 0;
						}
						else bufferDelay++;
					}
				} // end while

				if (sell)
				{
					karakter->sellItem(temporary[index - 1]); // jual Itemnya
					karakter->setGold((temporary[index - 1]->getPrice()) / 2); // tambah gold sebanyak 50% harga item nya
					Console::setColor(Console::COLOR_GREEN);
					printf("\n\n You have successfuly sold the item!\n");

					Console::setColor(COLOR_GREY);
					printf("\n (Press enter to continue)");
					pressEnterPlease();
					Console::setColor(Console::COLOR_WHITE);
					continue;
				}
			}
				break;
			case 2: // eguipment menu
				// PRINT DI SEBELAH KANAN PLAYER STATUS
				equipmentMenu(karakter, temporary, equipMenuActive,equipMenuState,filterType, equipMenuPrintOnly,stillUnequiping,3); // (state 0, sedang tidak active, tapi akan di-set ke active)
				sortType = 0;
				equipMenuPrintOnly = true;
				break;
			case 3: // compare equipment
				if (temporary.size() ==0)
				{
					Console::setColor(Console::COLOR_RED);
					printf("\n\n No item detected!");
					Console::resetColor();
					Console::delay(700);
				}
				else compareEquipment(filterType, karakter, temporary,0,0);
				equipMenuPrintOnly = true;
				continue;
			case 4: // exit
				return;
			} // end switch


		} // end while luar

	}


}; // END CLASS

int Interface::delayScreen = 0;
int Interface::delayFlag = 0; // GLOBAL VARIABLE BUAT PRE-GAME INTRO

#endif