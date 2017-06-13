#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <memory>
#include <vector>
#include <ctime>
#include <algorithm>
#include <functional>

#include "Base.h"
#include "Human.h"
#include "Monster.h"
#include "Item.h"
#include "common.h"
#include "Battle.h"
#include "Music.h"

//
#include "Interface.h"
//
#include "Shop.h"
#include "NewGame.h"
#include "Introduction.h"
#include "Home.h"
//

class Game
{
private:
	// TEMPORARY VARIABLE:
	// base:
	float damage, hDamage; // kiri buat monster/item, kanan buat human
	float chanceToHit, hChanceToHit;
	float evade, hEvade;
	float speed, hSpeed;
	float maxHealth, hMaxHealth;
	float maxStamina, hMaxStamina;
	int armor, hArmor;
	int level, hLevel;
	string name, hName;
	char tempName[51];
	// human:
	int monsterKilled;
	int strength;
	int endurance;
	int agility;
	int dexterity;
	int gold, hGold;
	int experience; // int (human)
	int job;
	// monster:
	int killed;
	int offense;
	int defense;
	float exp; // float (monster)
			   // item:
	string effect;
	char tempEffect[100];
	int price;
	int type;
	int restriction;
	int equipped;
	int bought;

	// -------------------------------- MAIN VARIABLE ----------------------------------------------------
	FILE* save;
	FILE* default;
	Human* karakter; // karakternya
	vector<Item> vShop; // item yang ada di game
	vector<Monster> vMonster; // monster yang ada di game
	 // ----------------------------------- M A P ----------------------------------------------------------
	char map[23][64] = {
		"0000000000000000000000000000000000000000000000000000000000\n",
		"0SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS___SSSSS___SSSSSSS0\n",
		"0SSSS~~~~~~SSSSSSSSSSSSSSSSSSSSSSSSSSSS|S|SS_SS|S|SSSSSSS0\n",
		"0S~~~~~~~~~~~SSSSSSSS[]___SSSSSSSSSSSSS|-|_/_\\_|-|SSSSSSS0\n",
		"0~~~~~~~~~~~~~~SSSSS/SSSS/\\SSSSSSSSSSS_|S|store|S|_SSSSSS0\n",
		"0~~~~~~~~~~~~~~~SSS/____/__\\SSSSSSSSS|S|-|[·-·]|-|S|SSSSS0\n",
		"0~~~~SSSSS~~~~~~~~S|[][]||||SSSSSSSSS|S|_|-----|_|S|SSSSS0\n",
		"0~SSSSSSSSSS~~~~~~~SSHomeSSSSSSSSSSSSSSSSSTownSSSSSSSSSSS0\n",
		"0SSSSSSSSSSSSS~~~~~~SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS~~~~0\n",
		"0SSSSSSSSSSSSSS~~~~~~~SSSSSSSSSSSSSSSSSSSSSSSSSSS~~~~~~~~0\n",
		"0SSSSSSSSSSSSSSSS~~~~~~SSSSSSSSSSSSSSSSSS~~~~~~~~~~~~~~~~0\n",
		"0SSS___,-SSSSSSSSS~~~~~~SS0SSS0SSSSSSS~~~~~~~~~~~~~~~~~SS0\n",
		"0SS/\'SS\\``-SSSSSSSS~~~~~~~01110SSS~~~~~~~~~~~~~SSSSSSSSSS0\n",
		"0S/S__S\'\\```SSSSSSSSS~~~~~01110~~~~~~~~~~~~SSSSSSSSSSSSSS0\n",
		"0/S/111\\SS\\``,SSSSSSSSS~~~01110~~~~~~~~SSThe Great RiverS0\n",
		"0S/11111\\_S\\`/SSSSSSSSSSSS01110~~~~~SSSSSSSSSSSSSSSSSSSSS0\n",
		"0/1\'11\'111\\S\\`\'\"SSSSSSSSSS0SSS0SSSSSSSSSSSSSSSSSSSSSSSSSS0\n",
		"011111_1111\\_S\\``SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS0\n",
		"01111|1|1\'111\'\'\\``SSSSSSSSBridgeSSSSSSSSSSSSSSSSSSSSSSSSS0\n",
		"0\"\'\"\'\"\'\'\'\'\"\'\'\"\'\'\'`SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS0\n",
		"0SSSSCaveSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS~MadeSbySMelvinS0\n",
		"0SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSandSAditya~S0\n",
		"0000000000000000000000000000000000000000000000000000000000\n"
	};// 23 height , 58 width
	  // -------------------------------- SAVE function -----------------------------------------------------
	  /*
	  LANGKAH-LANGKAH BUAT NEW GAME DAN LOAD GAME:
	  1. lakukan checkSave() dan resetDefaultSave() (menjamin default.txt ada)
	  2. kalau saveGameAvailable, maka pilihan LOAD GAME ada
	  3. kalau pilih NEW GAME: (save.txt bisa ada, bisa tidak aja, tapi itu tidak penting. Karena tidak bakal di-write maupun overwrite)
	  3.1	lakukan newData() (ini buat reset data vMonster dan vShop yang ada kemungkinan sudah dibuat maupun belum ke default)
	  3.2 delete objek human lama (kalau ada)
	  3.3 bikin objek human baru
	  4. kalau pilih LOAD GAME: (save.txt sudah pasti ada, karena saveGameAvailable benar)
	  4.1 (optional) lakuin checkSave() lagi untuk benar" menjamin data save ada
	  4.2 delete objek human lama
	  4.3 lakukan loadSave()
	  */
	bool saveGameAvailable; // kalau save game ada, maka true. Kalo nggak, maka false

	void checkSave() // check save.txt ada apa nggak
	{
		save = fopen("save.txt", "r");
		if (save == NULL) // save game gaada
		{
			saveGameAvailable = false;
		}
		else // save game ada (save!=NULL)
		{
			saveGameAvailable = true;
			fclose(save);
		}
	} // END checkSave()

	void createDefaultSave(); // definition di paling bawah (terlalu panjang)

	void loadSave() // DIJAMIN FILE SAVE.TXT UDAH ADA
	{
		vShop.clear();
		vMonster.clear();
		save = fopen("save.txt", "r");
		// baca ATTRIBUTE dari save
		if (fscanf(save, "%[^\n]\n", tempName) != 1)
			Interface::ErrorMsg("GAME.H", __LINE__, -1);//cout << "\nERROR IN READING 1ST LINE";
		if (fscanf(save, "%d,%d,%d,%d,%d,%d,%d,%d\n", &hLevel, &job, &hGold, &experience, &strength, &endurance, &agility, &dexterity) != 8)
			Interface::ErrorMsg("GAME.H", __LINE__, -1);//cout << "\nERROR IN READING 2ND LINE!";
		if (fscanf(save, "%f,%f,%f,%f,%f,%f,%d,%d\n", &hDamage, &hChanceToHit, &hEvade, &hSpeed, &hMaxHealth, &hMaxStamina, &hArmor, &monsterKilled) != 8)
			Interface::ErrorMsg("GAME.H", __LINE__, -1);//cout << "\nERROR IN READING 3RD LINE";
		hName = tempName;
		size_t ERRORCOUNT = 0;
		while (!feof(save))
		{
			ERRORCOUNT++;
			char ztype;
			ztype = fgetc(save);
			if (ztype == '#') // item
			{
				//#Nama Item, Price, *effect*, Type, Restriction, Equipped, Bought
				if (fscanf(save, "%[^,],%d,%[^,],%d,%d,%d,%d\n",
					tempName, &price, tempEffect, &type, &restriction, &equipped, &bought)
					!= 7)
				{
					Interface::ErrorMsg("GAME.H", __LINE__, ERRORCOUNT);
				}
				name = tempName;
				effect = tempEffect;
				vShop.push_back(Item(name, price, effect, type, restriction, equipped, bought));
			}
			else // monster
			{
				//@Nama Monster, Level, Gold, Damage, Chance to Hit, Evade, Speed, Max Health, Max Stamina, Armor, Experience, Offense, Defense, Killed
				if (fscanf(save, "%[^,],%d,%d,%f,%f,%f,%f,%f,%f,%d,%f,%d,%d,%d\n",
					tempName, &level, &gold, &damage, &chanceToHit, &evade, &speed, &maxHealth, &maxStamina, &armor, &exp, &offense, &defense, &killed)
					!= 14)
				{
					Interface::ErrorMsg("GAME.H", __LINE__, ERRORCOUNT);
				}
				name = tempName;
				vMonster.push_back(Monster(name, level, gold, damage, chanceToHit, evade, speed, maxHealth, maxStamina, armor, exp, offense, defense, killed));
			}
		}
		fclose(save);
	}

	void newData() // buat new Game (METHOD INI BUKAN WRITE KE FILE, TAPI HANYA RESET VMONSTER DAN VSHOP)
	{
		// baca dari default (DIJAMIN DEFAULT.TXT ADA)
		default = fopen("default.txt", "r");
		if (default == NULL) Interface::ErrorMsg("GAME.H", __LINE__, -1);
		vShop.clear();
		vMonster.clear();
		size_t ERRORCOUNT = 0;
		while (!feof(default))
		{
			ERRORCOUNT++;
			char ztype;
			ztype = fgetc(default);
			if (ztype == '#') // item
			{
				//#Nama Item, Price, *effect*, Type, Restriction, Equipped, Bought
				if (fscanf(default, "%[^,],%d,%[^,],%d,%d,%d,%d\n",
					tempName, &price, tempEffect, &type, &restriction, &equipped, &bought)
					!= 7)
				{
					Interface::ErrorMsg("GAME.H", __LINE__, ERRORCOUNT);
				}
				name = tempName;
				effect = tempEffect;
				vShop.push_back(Item(name, price, effect, type, restriction, equipped, bought));
			}
			else // monster (ztype == '@')
			{
				//@Nama Monster, Level, Gold, Damage, Chance to Hit, Evade, Speed, Max Health, Max Stamina, Armor, Experience, Offense, Defense, Killed
				if (fscanf(default, "%[^,],%d,%d,%f,%f,%f,%f,%f,%f,%d,%f,%d,%d,%d\n",
					tempName, &level, &gold, &damage, &chanceToHit, &evade, &speed, &maxHealth, &maxStamina, &armor, &exp, &offense, &defense, &killed)
					!= 14)
				{
					Interface::ErrorMsg("GAME.H", __LINE__, ERRORCOUNT);
				}
				name = tempName;
				vMonster.push_back(Monster(name, level, gold, damage, chanceToHit, evade, speed, maxHealth, maxStamina, armor, exp, offense, defense, killed));
			}
		}
		fclose(default);
	}

	void resetDefaultSave()
	{
		default = fopen("default.txt", "w"); // WARNING: bakal di-overwrite di program ini sendiri
		if (default == NULL) // kalau entah gimana gak bisa write
		{
			Interface::ErrorMsg("GAME.H", __LINE__, -1);
		}
		else
		{
			// create file default kalau nggak ada
			createDefaultSave();
		}
		fclose(default);
	}

	void saveGame()
	{
		save = fopen("save.txt", "w");
		fprintf(save, "%s\n", karakter->getName().c_str());
		fprintf(save, "%d,%d,%d,%d,%d,%d,%d,%d\n", karakter->getLevel(), karakter->getJob(), karakter->getGold(), karakter->getExperience(),
			karakter->getStrength(), karakter->getEndurance(), karakter->getAgility(), karakter->getDexterity());
		fprintf(save, "%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%d,%d\n", karakter->getDamage(), karakter->getChanceToHit(), karakter->getEvade(), karakter->getSpeed(), karakter->getMaxHealth(),
			karakter->getMaxStamina(), karakter->getArmor(), karakter->getMonsterKilled());

		// print data Item
		for (vector<Item>::iterator iterItem = vShop.begin(); iterItem != vShop.end(); iterItem++)
		{
			fprintf(save, "#%s,%d,%s,%d,%d,%d,%d\n", iterItem->getName().c_str(), iterItem->getPrice(), iterItem->getEffect().c_str(), iterItem->getType(),
				iterItem->getRestriction(), iterItem->getEquipped(), iterItem->getBought());
		}

		// print data Monster
		for (vector<Monster>::iterator iter = vMonster.begin(); iter != vMonster.end(); iter++)
		{
			fprintf(save, "@%s,%d,%d,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%d,%.1f,%d,%d,%d\n",
				iter->getName().c_str(), iter->getLevel(), iter->getGold(), iter->getDamage(),
				iter->getChanceToHit(), iter->getEvade(), iter->getSpeed(), iter->getMaxHealth(),
				iter->getMaxStamina(), iter->getArmor(), iter->getExp(),
				iter->getOffense(), iter->getDefense(), iter->getKilled());
		}

		saveGameAvailable = true;
		fclose(save);
	} // END saveGame()


	void printMap(int place, bool reset) {
		if (reset)
		{
			// print map pertama kali
			system("cls");
			for (int height = 0; height < 23; height++) {
				Console::setCursorPos(15, 4 + height);
				for (int width = 0; width < strlen(map[height]); width++) {
					if (map[height][width] == 'S') printf(" ");
					else if (map[height][width] == '0') printf("%c", 219);
					else if (map[height][width] == '1') printf("%c", ' ');
					else printf("%c", map[height][width]);
				}
			}
		}
		Console::setCursorPos(37, 1);
		Console::setColor(79);
		Console::printf(" S K Y R I M ");
		Console::resetColor();

		// reset hightlight
		for (int height = 3; height <= 7; height++)
		{
			for (int width = 19; width <= 27; width++)
			{
				Console::setCursorPos(15 + width, 4 + height);
				if (map[height][width] == 'S') printf(" ");
				else if (map[height][width] == '0') printf("%c", 219);
				else if (map[height][width] == '1') printf("%c", ' ');
				else printf("%c", map[height][width]);
			}
		}
		for (int height = 1; height <= 7; height++)
		{
			for (int width = 37; width <= 51; width++)
			{
				Console::setCursorPos(15 + width, 4 + height);

				if (map[height][width] == 'S') printf(" ");
				else if (map[height][width] == '0') printf("%c", 219);
				else if (map[height][width] == '1') printf("%c", ' ');
				else printf("%c", map[height][width]);
			}
		}
		for (int height = 11; height <= 20; height++)
		{
			for (int width = 1; width <= 17; width++)
			{
				Console::setCursorPos(15 + width, 4 + height);

				if (map[height][width] == 'S') printf(" ");
				else if (map[height][width] == '0') printf("%c", 219);
				else if (map[height][width] == '1') printf("%c", ' ');
				else printf("%c", map[height][width]);
			}
		}
		for (int height = 20; height <= 21; height++)
		{
			for (int width = 41; width <= 56; width++)
			{
				Console::setCursorPos(15 + width, 4 + height);

				if (map[height][width] == 'S') printf(" ");
				else if (map[height][width] == '0') printf("%c", 219);
				else if (map[height][width] == '1') printf("%c", ' ');
				else printf("%c", map[height][width]);
			}
		}

		//BUAT HIGHLIGHT
		Console::setCursorPos(27, 28);
		if (place == 0) {
			Console::setColor(Console::COLOR_GREEN);
			Console::printf("Home");
			Console::resetColor();
			Console::printf(" : view inventory and equipment     ");
			Console::setColor(Console::COLOR_GREEN);
			for (int height = 3; height <= 7; height++)
			{
				for (int width = 19; width <= 27; width++)
				{
					Console::setCursorPos(15 + width, 4 + height);

					if (map[height][width] == 'S') printf(" ");
					else if (map[height][width] == '0') printf("%c", 219);
					else if (map[height][width] == '1') printf("%c", ' ');
					else printf("%c", map[height][width]);
				}
			}
		}
		else if (place == 1) {
			Console::setColor(Console::COLOR_MAGENTA);
			Console::printf("Town");
			Console::resetColor();
			Console::printf(" : visit Tristam's Shop                      ");
			Console::setColor(Console::COLOR_MAGENTA);
			for (int height = 1; height <= 7; height++)
			{
				for (int width = 37; width <= 51; width++)
				{
					Console::setCursorPos(15 + width, 4 + height);

					if (map[height][width] == 'S') printf(" ");
					else if (map[height][width] == '0') printf("%c", 219);
					else if (map[height][width] == '1') printf("%c", ' ');
					else printf("%c", map[height][width]);
				}
			}
		}
		else if (place == 2) {
			Console::setColor(Console::COLOR_RED);
			Console::printf("Cave");
			Console::resetColor();
			Console::printf(" : fight Monster                             ");
			Console::setColor(Console::COLOR_RED);
			for (int height = 11; height <= 20; height++)
			{
				for (int width = 1; width <= 17; width++)
				{
					Console::setCursorPos(15 + width, 4 + height);

					if (map[height][width] == 'S') printf(" ");
					else if (map[height][width] == '0') printf("%c", 219);
					else if (map[height][width] == '1') printf("%c", ' ');
					else printf("%c", map[height][width]);
				}
			}
			Console::resetColor(); //somehow the color gets into the list of monsters
		}
		else if (place == 3) {
			Console::setColor(Console::COLOR_BLUE);
			Console::printf("Credit");
			Console::resetColor();
			Console::printf(" : view credit                               ");
			Console::setColor(Console::COLOR_BLUE);
			for (int height = 20; height <= 21; height++)
			{
				for (int width = 41; width <= 56; width++)
				{
					Console::setCursorPos(15 + width, 4 + height);

					if (map[height][width] == 'S') printf(" ");
					else if (map[height][width] == '0') printf("%c", 219);
					else if (map[height][width] == '1') printf("%c", ' ');
					else printf("%c", map[height][width]);
				}
			}
		}

	}

	bool exitPrompt()
	{
		system("cls");
		Console::setCursorPos(0, 2);
		Console::setColor(Console::COLOR_RED);
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

		for (int i = 0; i < 20; i++)
		{
			printf("           %s\n", wallpaper[i]);
		}

		int buffer;
		int sampahFlag = 0;
		int pickMenu = 1;
		bool printFlag = true;
		while (1)
		{
			Console::resetColor(); // LUMAYAN PENTING KALO GK MAU ADA ERROR (coba gk dipake, trus masuk ke game over. Warnanya berubah)
			Console::setCursorVisibility(false); // MINOR
			if (printFlag)
			{
				Console::setCursorPos(33, 11);
				Console::resetColor();
				printf("Are you sure you want to exit?");

				Console::setCursorPos(40, 13);
				if (pickMenu == 0)Console::setColor(79);
				else Console::resetColor();
				printf(" YES ");

				Console::setCursorPos(50, 13);
				if (pickMenu == 1)Console::setColor(79);
				else Console::resetColor();
				printf(" NO ");

				printFlag = false;
			}
			buffer = Console::getKeyPressed();
			if (buffer != -1)
			{
				if (sampahFlag)
				{
					if (buffer == VK_LEFT || buffer == 0x41) // 0x41 == 'a'
					{
						pickMenu = (pickMenu - 1 + 2) % 2;
						printFlag = true;
					}
					else if (buffer == VK_RIGHT || buffer == 0x44) // 0x44 == 'd'
					{
						pickMenu = (pickMenu + 1) % 2;
						printFlag = true;
					}
					else if (buffer == VK_RETURN)
					{
						break;
					}
					sampahFlag = 0;
				}
				else sampahFlag++;
			}
		}
		Console::resetColor();
		if (pickMenu == 1) return false; // tidak exit
		else return true; // exit
	}

	void viewCredit(Human &karakter) {
		string tempCheatCode;
		system("cls");
		string creditText[10] = {
			"            This game is inspired by Diablo",
			"  We do not intend to violate any copyrights, whatsoever",
			"        This game is made as our school project",
			"--------------------------------------------------------",
			"      If you found any bug, please kindly contact : ",
			"  adityawiryadarma@gmail.com OR melvinshb@yahoo.co.id",
			"--------------------------------------------------------",
			"",
			"           ~Thank you for trying this game~",
			"                   Have a good day"
		};
		system("cls");
		Console::setCursorPos(23, 1);
		Console::printf(" C R E D I T ");

		Console::setCursorPos(1, 3);
		for (int textCounter = 0; textCounter < 10; textCounter++) {
			Console::setCursorPos(2,Console::getCursorY()+1);
			Console::printf("%s",creditText[textCounter].c_str());
		}
		int y = Console::getCursorY();
		while (1)
		{
			Console::setCursorPos(2,y + 5);
			Console::printf("Input cheats (0 = back): ");
			
			Console::setCursorVisibility(true);
			getline(cin, tempCheatCode);
			Console::setCursorVisibility(false);

			if (tempCheatCode == "0") {
				return;
			}
			else {
				if (tempCheatCode == "monster")
				{
					Battle::selectMonster(&karakter, vMonster);
					return;
				}
				else if (karakter.cheat(tempCheatCode)==false)
				{
					Interface::delaySec(1000);
					// hapus yg sebelumnya
					Console::setCursorPos(0, Console::getCursorY());
					printf("                                                  ");
					{
						int len = tempCheatCode.size();
						Console::setCursorPos(27+len, y + 5);
						for (int i = 0; i < len; i++)
						{
							printf("\b \b");
						}
					}
					continue;
				}
				Console::resetColor();
				Console::setCursorPos(2, Console::getCursorY() + 1);
				Console::setColor(Interface::COLOR_GREY);
				Console::printf("Press any key to continue");
				Console::resetColor();
				_getch();
				return;
			}
		}
	}
	// ----------------------------------------------------------------------------------------------------

public:
	Game() // constructor
	{
		srand(time(NULL));
		Music::playBackgroundMusic(6);
		Interface::delaySec(1000);
		Interface::setDefaultFont(18);
		Interface::setWindowSize(1100, 600);
		Interface::introduction.titleScreen();
		//Interface::introduction.loading();
		Interface::introduction.improvedLoading();
		Interface::introduction.intro();

		karakter = NULL; // state karakter pertama
		vShop.reserve(Item::MAX_ITEM);
		vMonster.reserve(Monster::MAX_MONSTER);

		while (1) // GAME JALAN TERUS SELAMA BELUM PILIH EXIT
		{
			system("cls");
			checkSave();
			resetDefaultSave();
			int menu = Interface::newGame.startGame(saveGameAvailable);
			if (menu == -1) return; // kalau user pilih exit game

			if (menu == 1) // new game
			{
				hName = Interface::newGame.newGameName();
				if (hName == "3s0xla 81a;LKDJn(**A;") continue;
				job = Interface::newGame.newGameJob(hName);
				if (job == -1) continue; // kalau user teken esc (exit) saat milih new game

				system("cls");
				newData();
				if (karakter != NULL) delete karakter;
				karakter = new Human(vShop, job, hName); // CARA BIKIN HUMAN DENGAN NEW GAME

				Console::setColor(79);
				Console::setCursorPos(30, 13);
				printf("SUCCESSFULY CREATED NEW CHARACTER !");

				Console::setColor(Console::COLOR_GRAY);
				Console::setCursorPos(34, 14);
				printf("(Press enter to continue..)");
				Interface::pressEnterPlease();
				Console::setColor(Console::COLOR_WHITE);
			}
			else // menu==2 (load game)
			{
				// CARA BIKIN HUMAN DENGAN LOAD GAME
				if (karakter != NULL) delete karakter;
				checkSave();
				if (!saveGameAvailable) // ERROR
				{
					cout << "\nSAVE GAME DELETED WHILE READING\n(Press enter to exit game..)";
					Interface::pressEnterPlease();
					return; // INI LANGSUNG EXIT
				}
				else
				{
					loadSave();
					karakter = new Human(vShop, hName, hLevel, job, hGold, experience, strength, endurance, agility, dexterity, hDamage, hChanceToHit, hEvade, hSpeed
						, hMaxHealth, hMaxStamina, hArmor, monsterKilled);


					Console::setColor(79);
					Console::setCursorPos(35, 11);
					printf("GAME SUCCESFULLY LOADED !");

					Console::setColor(Console::COLOR_GRAY);
					Console::setCursorPos(34, 12);
					printf("(Press enter to continue..)");
					Interface::pressEnterPlease();
					Console::setColor(Console::COLOR_WHITE);
				}
			}
			Music::playBackgroundMusic(1);
			printMap(0, true);
			char mapMenu;
			int currentPlace = 0;
			bool print = false;
			int inputDelay = 0;

			//virtual key codes
			const int W_KEY = 0x57;
			const int S_KEY = 0x53;
			const int A_KEY = 0x41;
			const int D_KEY = 0x44;
			const int M_KEY = 0x4D;
			while (1)
			{
				Console::setCursorVisibility(false);
				Console::resetColor();
				if (print)
				{
					printMap(currentPlace, true);
					print = false;
				}
				// 0 = home
				// 1 = town
				// 2 = cave
				enum LOCATION { HOME = 0, TOWN, CAVE, CREDIT };
				mapMenu = Console::getKeyPressed();
				if (mapMenu == -1)continue;
				if (inputDelay == 0)
				{
					inputDelay++;
					continue;
				}
				inputDelay = 0;

				if (mapMenu == VK_ESCAPE)
				{
					if (exitPrompt()) break;
					print = true; // PENTING
					continue;
				}
				else if (mapMenu == M_KEY)
				{
					Music::playBackgroundMusic(-1);
					continue;
				}
				else if (currentPlace == HOME) {
					if (mapMenu == S_KEY || mapMenu == VK_DOWN || mapMenu == A_KEY || mapMenu == VK_LEFT) {
						printMap(CAVE, false);
						currentPlace = CAVE;
					}
					else if (mapMenu == D_KEY || mapMenu == VK_RIGHT) {
						printMap(TOWN, false);
						currentPlace = TOWN;
					}
					else if (mapMenu == VK_RETURN) {
						Interface::home.homeMenu(vShop, vMonster, karakter, karakter->getInventoryRef());
						print = true; // PENTING
					}
				}
				else if (currentPlace == TOWN) {
					if (mapMenu == S_KEY || mapMenu == VK_DOWN) {
						printMap(CREDIT, false);
						currentPlace = CREDIT;
					}
					else if (mapMenu == A_KEY || mapMenu == VK_LEFT) {
						printMap(HOME, false);
						currentPlace = HOME;
					}
					else if (mapMenu == VK_RETURN) {
						Interface::shop.shopMenu(vShop, karakter);
						print = true; // PENTING
					}
				}
				else if (currentPlace == CAVE) {
					if (mapMenu == W_KEY || mapMenu == VK_UP) {
						printMap(HOME, false);
						currentPlace = HOME;
					}
					else if (mapMenu == D_KEY || mapMenu == VK_RIGHT) {
						printMap(CREDIT, false);
						currentPlace = CREDIT;
					}
					else if (mapMenu == VK_RETURN) {
						{
							//Battle::selectMonster(karakter, vMonster);
							Battle::selectCave(karakter, vMonster);

							Music::playBackgroundMusic(TOWN);
							print = true; // PENTING
						}
					}
				}
				else {
					if (mapMenu == W_KEY || mapMenu == VK_UP) {
						printMap(TOWN, false);
						currentPlace = TOWN;
					}
					else if (mapMenu == A_KEY || mapMenu == VK_LEFT) {
						printMap(CAVE, false);
						currentPlace = CAVE;
					}
					else if (mapMenu == VK_RETURN) {
						//credit here
						viewCredit(*karakter);
						print = true;
					}
				}

			}

			// save game, terus exit
			saveGame();
			Console::setCursorPos(42, 15);
			Console::setColor(Console::COLOR_YELLOW);
			cout << "GAME SAVED!";
			Console::resetColor();
			Interface::delaySec(1000);
		}
	} // END constructor
};

/*
TEMPLATE SAVE

Nama Karakter
Level,Job,Gold,Experience,Strength,Endurance,Agility,Dexterity
Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor
#Nama Item1,Price,*effect*,Type,Restriction,Equipped,Bought
#Nama Item2,Price,*effect*,Type,Restriction,Equipped,Bought
#Nama Item3,Price,*effect*,Type,Restriction,Equipped,Bought
@Nama Monster1,Level,Gold,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Experience,Offense,Defense,Killed
@Nama Monster2,Level,Gold,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Experience,Offense,Defense,Killed
@Nama Monster3,Level,Gold,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Experience,Offense,Defense,Killed
*/

void Game::createDefaultSave()
{
	vector<char*> itemSave =
	{
		//#Nama Item1,Price,*effect*,Type,Restriction,Equipped,Bought

		//armors (chestpiece)
		"#Quilted Armor,400,AMR+1 EVA+10,3,0,0,0\n",
		"#Leather Armor,800,AMR+2 EVA+8,3,0,0,0\n",
		"#Hard Leather Armor,1200,AMR+3 EVA+6,3,0,0,0\n",
		"#Studded Armor,1400,AMR+4 EVA+4,3,0,0,0\n",
		"#Ring Mail,1500,AMR+5 END+1,3,0,0,0\n",
		"#Scale Mail,1800,AMR+6 END+2,3,0,0,0\n",
		"#Breastplate,2200,AMR+10,3,2,0,0\n",
		"#Chain Mail,2500,AMR+8 END+2,3,0,0,0\n",
		"#Splint Mail,2900,AMR+9 END+4 STR+4,3,3,0,0\n",
		"#Light Plate,3200,AMR+11 STR+2,3,0,0,0\n",
		"#Field Plate,4100,AMR+15 STR+3,3,0,0,0\n",
		"#Plate Mail,5200,AMR+18 STR+4,3,0,0,0\n",
		"#Full Plate,7000,AMR+22 STR+4 END+4,3,2,0,0\n",
		"#Ancient Armor,12000,AMR+30,3,2,0,0\n",
		"#Ghost Armor,10000,AMR+11 AGI+10 DEX+4 EVA+10,3,1,0,0\n",
		"#Great Hauberk,18000,AMR+18 STR+4 MHP+120 MST+100,3,2,0,0\n",
		"#Bonewave,9000,AMR+15 STR+12 END+4 MST+150,3,3,0,0\n",
		"#Sacred Armor,20000,AMR+32 END+10 STR+4 MST+200,3,2,0,0\n",
		"#Kraken Shell,20000,AMR+18 END+10 STR+10 MHP+150,3,3,0,0\n",

		//boots
		"#Leather Boots,200,AMR+1 EVA+2,4,0,0,0\n",
		"#Heavy Boots,800,AMR+2 EVA+1,4,0,0,0\n",
		"#Chain Boots,1200,AMR+3 END+1,4,0,0,0\n",
		"#Light Plated Boots,1500,AMR+5,4,0,0,0\n",
		"#Greaves,2000,AMR+8 END+2,4,2,0,0\n",
		"#Mesh Boots,2000,AMR+2 EVA+10 AGI+3,4,1,0,0\n",
		"#Battle Boots,2200,AMR+6 END+2,4,0,0,0\n",
		"#War Boots,3000,AMR+9,4,0,0,0\n",
		"#Wyrmhide Boots,4200,AMR+5 EVA+10 AGI+4 DEX+2,4,1,0,0\n",
		"#Scarabshell Boots,4000,AMR+6 END+3 AGI+3,4,3,0,0\n",
		"#Boneweave Boots,5000,AMR+8 MST+80 MHP+80,4,3,0,0\n",
		"#Mirrored Boots,6000,AMR+10 STR+2 END+2,4,0,0,0\n",
		"#Myrmidon Boots,5500,AMR+12 MHP+50 MST+50,4,2,0,0\n",

		//gloves
		"#Leather Gloves,400,AMR+1 EVA+5,2,0,0,0\n",
		"#Heavy Gloves,800,AMR+2 EVA+3,2,0,0,0\n",
		"#Chain Gloves,1200,AMR+3 EVA+1,2,0,0,0\n",
		"#Light Gauntlets,2000,AMR+4,2,0,0,0\n",
		"#Gauntlets,3200,AMR+5,2,0,0,0\n",
		"#Demonhide Gloves,4000,AMR+4 EVA+10 CTH+10,2,1,0,0\n",
		"#Sharkskin Gloves,2000,AMR+3 STR+2 END+2 DMG+2,2,3,0,0\n",
		"#Heavy Bracers,4100,AMR+7,2,0,0,0\n",
		"#Battle Gauntlets,5500,AMR+9 CTH+10,2,0,0,0\n",
		"#Ogre Gauntlets,8200,AMR+11 CTH+10 DMG+4,2,0,0,0\n",
		"#Crusader Gauntlets,18000,AMR+12 MHP+60 MST+60,2,2,0,0\n",

		//helmet
		"#Cap,300,AMR+1 EVA+4,1,0,0,0\n",
		"#Skullcap,600,AMR+2 EVA+3,1,0,0,0\n",
		"#Basinet,1200,AMR+3 EVA+2,1,0,0,0\n",
		"#Shako,1500,AMR+3 EVA+5 AGI+2 DEX+1,1,1,0,0\n",
		"#Full Helm,2000,AMR+6,1,0,0,0\n",
		"#Hydraskull,1900,AMR+4 STR+3 END+3 DMG+2,1,3,0,0\n",
		"#Mask,2500,AMR+8 END+1,1,0,0,0\n",
		"#Bone Helm,5000,AMR+8 STR+4 MHP+80 DMG+2,1,3,0,0\n",
		"#Great Helm,4800,AMR+8 END+4 STR+4 MHP+40,1,2,0,0\n",
		"#Crown,3200,AMR+6 EVA+10,1,0,0,0\n",
		"#Spired Helm,6600,AMR+10 END+5 STR+5 MHP+50,1,2,0,0\n",
		"#Demonhead,2400,AMR+4 AGI+2 DEX+3,1,0,0,0\n",
		"#Diadem,4500,AMR+5 EVA+8 CTH+16,1,1,0,0\n",
		"#Death Mask,8000,AMR+8 STR+3 MHP+50 CTH+10,1,0,0,0\n",
		"#Grim Helm,7200,AMR+6 DEX+3 EVA+10 CTH+10,1,0,0,0\n",
		"#Winged Helm,9000,AMR+12 END+2 MHP+60 MST+60,1,2,0,0\n",
		"#Grand Crown,6900,AMR+9 EVA+10 CTH+10,1,0,0,0\n",

		//shield
		"#Buckler,600,AMR+2,6,0,0,0\n",
		"#Small Shield,1000,AMR+4,6,0,0,0\n",
		"#Large Shield,1500,AMR+6,6,0,0,0\n",
		"#Kite Shield,2000,AMR+8,6,0,0,0\n",
		"#Spiked Shield,2200,AMR+4 END+4 DMG+2,6,3,0,0\n",
		"#Bone Shield,4500,AMR+8 END+8 MST+100 DMG+4,6,3,0,0\n",
		"#Tower Shield,4800,AMR+12,6,2,0,0\n",
		"#Gothic Shield,8000,AMR+16,6,2,0,0\n",
		"#Barbed Shield,900,AMR+2 END+2 STR+2 DMG+1,6,3,0,0\n",
		"#Pavise,5000,AMR+10 MHP+100 MST+100,6,2,0,0\n",
		"#Ancient Shield,18000,AMR+22 STR+4 END+4,6,2,0,0\n",

		//weapon
		"#Hand Axe,500,DMG+4,5,0,0,0\n",
		"#Double Axe,1000,DMG+8,5,0,0,0\n",
		"#Military Pick,2000,DMG+12,5,0,0,0\n",
		"#Great Axe,4000,DMG+18,5,3,0,0\n",
		"#Berseker Axe,8000,DMG+24,5,3,0,0\n",
		"#Glorious Axe,18000,DMG+36 STR+4 END+2 DEX+4,5,3,0,0\n",
		"#Dagger,400,DMG+2 EVA+4 DEX+1,5,0,0,0\n",
		"#Dirk,1200,DMG+5 EVA+4 DEX+2,5,0,0,0\n",
		"#Kris,2500,DMG+8 EVA+4 DEX+4,5,0,0,0\n",
		"#Blade,3200,DMG+10 EVA+4 DEX+5,5,0,0,0\n",
		"#Stilleto,4600,DMG+11 CTH+10 DEX+4,5,1,0,0\n",
		"#Mithril Point,8000,DMG+15 CTH+12 EVA+4 DEX+4,5,1,0,0\n",
		"#Legend Blade,14000,DMG+20 CTH+15 EVA+10 DEX+5,5,0,0,0\n",
		"#Short Sword,400,DMG+5,5,0,0,0\n",
		"#Scimitar,1000,DMG+8,5,0,0,0\n",
		"#Sabre,1500,DMG+11,5,0,0,0\n",
		"#Falchion,3000,DMG+14,5,0,0,0\n",
		"#Broad Sword,5000,DMG+17,5,0,0,0\n",
		"#Long Sword,7000,DMG+20,5,0,0,0\n",
		"#Gladius,10000,DMG+24 END+4 DEX+2,5,2,0,0\n",
		"#Crystal Sword,13000,DMG+28 STR+4 DEX+2,5,2,0,0\n",
		"#Ancient Sword,16000,DMG+32 STR+4 END+2 DEX+2,5,2,0,0\n",
		"#Colossus Blade,22000,DMG+40 STR+4 END+4 DEX+4,5,2,0,0\n",
	};

	vector<char*> monsterSave =
	{
		"@Ghoul,1,300,20,86,3,66,120,90,2,1358,6,12,0\n",
		"@Giant Spider,2,600,7,114,18,210,120,90,0,2683,8,16,0\n",
		"@Vampire,4,800,30,109,8,112,142,100,1,4477,21,15,0\n",
		"@Gargoyle Trap,4,920,20,98,0,89,300,150,5,4682,14,41,0\n",
		"@Tainted One,4,900,12,116,9,152,198,120,3,4427,20,23,0\n",
		"@Goatman,3,650,12,104,12,154,135,120,1,3426,14,16,0\n",
		"@Mummy,5,1050,13,116,9,138,265,160,1,5424,20,29,0\n",
		"@Sand Raider,6,1280,13,122,14,180,278,120,3,6275,26,35,0\n",
		"@Claw Viper,7,1490,11,140,25,210,188,170,2,7867,39,32,0\n",
		"@Slinger,8,1510,28,149,26,180,130,120,1,8756,70,22,0\n",
		"@Sabre Cat,9,1620,18,110,42,200,195,150,4,9047,46,60,0\n",
		"@Vulture Demon,10,2200,15,156,44,242,180,180,2,10558,48,55,0\n",
		"@Sand Maggot,9,1640,26,118,23,182,228,130,6,9108,38,43,0\n",
		"@Fire Eye,10,2200,28,135,39,200,180,120,4,10332,50,50,0\n",
		"@Frog Demon,11,2550,22,130,35,226,312,180,2,11020,60,72,0\n",
		"@Thorned Hulk,10,2070,39,90,9,166,455,220,8,10122,47,70,0\n",
		"@Zakarum Zealot,12,3750,40,128,34,265,308,160,5,12646,112,78,0\n",
		"@Tentacle Beast,11,2630,30,116,20,226,380,280,3,11162,71,58,0\n",
		"@Willowisp,12,3400,9,162,68,390,128,380,0,12267,69,80,0\n",
		"@Temple Guard,13,4300,49,122,32,250,294,320,5,13285,124,71,0\n",
		"@Strangler,15,3600,55,98,33,220,459,200,2,15018,103,99,0\n",
		"@Megademon,16,4500,55,112,35,213,397,240,6,16115,142,110,0\n",
		"@Regurgitator,14,3430,52,102,24,180,589,220,4,14769,92,103,0\n",
		"@Oblivion Knight,17,4830,42,132,40,223,376,380,8,17700,178,142,0\n",
		"@Izuel,23,8800,66,140,41,240,448,520,10,23152,339,204,0\n",
		"@Grand Vizier,24,10000,42,150,55,290,395,380,12,24400,289,313,0\n",
		"@Baal,22,7400,185,118,52,120,490,300,6,22470,393,227,0\n",
		"@Mephisto,26,14500,65,138,40,288,725,600,15,26235,492,469,0\n",
		"@Diablo,30,0,90,148,35,300,1020,540,12,0,501,441,0\n"
	};

	default = fopen("default.txt", "w");

	vector<char*>::iterator iter;
	for (iter = itemSave.begin(); iter != itemSave.end(); iter++)
	{
		fprintf(default, "%s", *iter);
	}
	for (iter = monsterSave.begin(); iter != monsterSave.end(); iter++)
	{
		fprintf(default, "%s", *iter);
	}

	fclose(default);
}

#endif // !GAME_H