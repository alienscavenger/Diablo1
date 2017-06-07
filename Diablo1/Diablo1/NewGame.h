#pragma once

#ifndef NEWGAME_H
#define NEWGAME_H

#include "common.h"
#include "Interface.h"

class NewGame
{
public:
	static int startGame(bool saveGameAvailable)
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
				Console::setCursorPos(20, 24);
				Console::printf("Press up/down or WSAD to select, and enter to choose");

				Console::setCursorPos(42, 10);
				if (pickMenu == 0)Console::setColor(79);
				else Console::setColor(Console::COLOR_WHITE);
				Console::printf("  NEW GAME  ");

				if (saveGameAvailable)
				{
					Console::setCursorPos(42, 11);
					if (pickMenu == 1)Console::setColor(79);
					else Console::setColor(Console::COLOR_WHITE);
					Console::printf(" LOAD  GAME ");
				}
				int yExit = saveGameAvailable ? 12 : 11;
				Console::setCursorPos(42, yExit);
				if (pickMenu == (maxMenu - 1))Console::setColor(79);
				else Console::setColor(Console::COLOR_WHITE);
				Console::printf("    EXIT    ");

				printFlag = false;
			}
			charMenu = Console::getKeyPressed();
			if (charMenu != -1)
			{
				if (sampahFlag) // supaya key release tidak kebaca
				{
					if (charMenu =='M' || charMenu == 'm')
					{
						Music::playBackgroundMusic(-1);
					}
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
		else return pickMenu + 1;
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
			else if ((isalnum(buff) || buff == ' ') && myName.length()<20)
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
						if (buffer == 'M' || buffer == 'm')
						{
							Music::playBackgroundMusic(-1);
						}
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
					Console::setCursorPos(40 - ((int)name.length() / 2), 1);
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

			Console::setColor(Interface::COLOR_GREY);
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
						if (buf == 'M' || buf == 'm')
						{
							Music::playBackgroundMusic(-1);
						}
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
		return (job + 1); // 1 <= job <= 3
	}

};

#endif