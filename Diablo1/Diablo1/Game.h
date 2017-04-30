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
#include "Interface.h"

#define MAX_ITEM 110
#define MAX_MONSTER 60

class Game
{
private:

	friend class Interface; // supaya Interface bisa akses variable Game

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
	int strength;
	int endurance;
	int agility;
	int dexterity;
	int gold, hGold;
	int experience; // int (human)
	int job;
	// monster:
	int offense;
	int defense;
	float exp; // float (monster)
	// item:
	string effect;
	char tempEffect[100];
	int price;
	int type;
	int restriction;
	int eguipped;
	int bought;

	// -------------------------------- MAIN VARIABLE ----------------------------------------------------
	FILE* save;
	FILE* default;
	Human* karakter; // karakternya
	vector<Item> vShop; // item yang ada di game
	vector<Monster> vMonster; // monster yang ada di game
	// ---------------------------------------------------------------------------------------------------

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
		if (fscanf(save, "%[^\n]\n", tempName) != 1) cout << "\nERROR IN READING 1ST LINE";
		if (fscanf(save, "%d,%d,%d,%d,%d,%d,%d,%d\n", &hLevel, &job, &hGold, &experience, &strength, &endurance, &agility, &dexterity) != 8) cout << "\nERROR IN READING 2ND LINE!";
		if (fscanf(save, "%f,%f,%f,%f,%f,%f,%d\n", &hDamage, &hChanceToHit, &hEvade, &hSpeed, &hMaxHealth, &hMaxStamina, &hArmor) != 7) cout << "\nERROR IN READING 3RD LINE";
		hName = tempName;
		while (!feof(save))
		{
			char ztype;
			ztype = fgetc(save);
			if (ztype == '#') // item
			{
				//#Nama Item, Price, *effect*, Type, Restriction, Eguipped, Bought
				fscanf(save, "%[^,],%d,%[^,],%d,%d,%d,%d\n",
					tempName, &price, tempEffect, &type, &restriction, &eguipped, &bought);
				name = tempName;
				effect = tempEffect;
				vShop.push_back(Item(name, price, effect, type, restriction, eguipped, bought));
			}
			else // monster
			{
				//@Nama Monster, Level, Gold, Damage, Chance to Hit, Evade, Speed, Max Health, Max Stamina, Armor, Experience, Offense, Defense
				fscanf(save, "%[^,],%d,%d,%f,%f,%f,%f,%f,%f,%d,%f,%d,%d\n",
					tempName, &level, &gold, &damage, &chanceToHit, &evade, &speed, &maxHealth, &maxStamina, &armor, &exp, &offense, &defense);
				name = tempName;
				vMonster.push_back(Monster(name, level, gold, damage, chanceToHit, evade, speed, maxHealth, maxStamina, armor, exp, offense, defense));
			}
		}
		fclose(save);
	}

	void newData() // buat new Game (METHOD INI BUKAN WRITE KE FILE, TAPI HANYA RESET VMONSTER DAN VSHOP)
	{
		// baca dari default (DIJAMIN DEFAULT.TXT ADA)
		default = fopen("default.txt", "r");
		vShop.clear();
		vMonster.clear();
		while (!feof(default))
		{
			char ztype;
			ztype = fgetc(default);
			if (ztype == '#') // item
			{
				//#Nama Item, Price, *effect*, Type, Restriction, Eguipped, Bought
				fscanf(default, "%[^,],%d,%[^,],%d,%d,%d,%d\n",
					tempName, &price, tempEffect, &type, &restriction, &eguipped, &bought);
				name = tempName;
				effect = tempEffect;
				vShop.push_back(Item(name, price, effect, type, restriction, eguipped, bought));
			}
			else // monster (ztype == '@')
			{
				//@Nama Monster, Level, Gold, Damage, Chance to Hit, Evade, Speed, Max Health, Max Stamina, Armor, Experience, Offense, Defense
				fscanf(default, "%[^,],%d,%d,%f,%f,%f,%f,%f,%f,%d,%f,%d,%d\n",
					tempName, &level, &gold, &damage, &chanceToHit, &evade, &speed, &maxHealth, &maxStamina, &armor, &exp, &offense, &defense);
				name = tempName;
				vMonster.push_back(Monster(name, level, gold, damage, chanceToHit, evade, speed, maxHealth, maxStamina, armor, exp, offense, defense));
			}
		}
		fclose(default);
	}

	void resetDefaultSave()
	{
		default = fopen("default.txt", "r"); // WARNING: bakal di-overwrite di program ini sendiri kalau belum dibuat
		if (default == NULL) // kalau file default tidak exist
		{
			// create file default kalau nggak ada
			createDefaultSave();
		}
		else fclose(default);
	}

	void saveGame()
	{
		save = fopen("save.txt", "w");
		fprintf(save, "%s\n", karakter->getName().c_str());
		fprintf(save, "%d,%d,%d,%d,%d,%d,%d,%d\n", karakter->getLevel(), karakter->getJob(), karakter->getGold(), karakter->getExperience(),
			karakter->getStrength(), karakter->getEndurance(), karakter->getAgility(), karakter->getDexterity());
		fprintf(save, "%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%d\n", karakter->getDamage(), karakter->getChanceToHit(), karakter->getEvade(), karakter->getSpeed(), karakter->getMaxHealth(),
			karakter->getMaxStamina(), karakter->getArmor());

		// print data Item
		for (vector<Item>::iterator iterItem = vShop.begin(); iterItem != vShop.end(); iterItem++)
		{
			fprintf(save, "#%s,%d,%s,%d,%d,%d,%d\n", iterItem->getName().c_str(), iterItem->getPrice(), iterItem->getEffect().c_str(), iterItem->getType(),
				iterItem->getRestriction(), iterItem->getEguipped(), iterItem->getBought());
		}

		// print data Monster
		for (vector<Monster>::iterator iter = vMonster.begin(); iter != vMonster.end(); iter++)
		{
			fprintf(save, "@%s,%d,%d,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%d,%.1f,%d,%d\n", iter->getName().c_str(), iter->getLevel(), iter->getGold(), iter->getDamage(),
				iter->getChanceToHit(), iter->getEvade(), iter->getSpeed(), iter->getMaxHealth(), iter->getMaxStamina(), iter->getArmor(), iter->getExp(),
				iter->getOffense(), iter->getDefense());
		}

		saveGameAvailable = true;
		fclose(save);
	} // END saveGame()

	// ----------------------------------------------------------------------------------------------------


	// -------------------------------- SHOP FUNCTION ----------------------------------------------------
	void testShop();
	int filterType;
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
	struct CompareArmor { // comparator sort buat armor (descending)
		bool operator()(Item* struct1, Item* struct2) {
			return (struct1->getArmor() > struct2->getArmor());
		}
	};
	struct CompareDamage { // comparator sort buat armor (descending)
		bool operator()(Item* struct1, Item* struct2) {
			return (struct1->getDamage() < struct2->getDamage());
		}
	};
	// -------------------------------------------------------------------------------------------------
	
public:
	Game() // constructor
	{
		Interface::setWindowSize(1000, 550);
		/*Interface::titleScreen();
		Interface::loading();
		Interface::intro();*/

		karakter = NULL; // state karakter pertama
		vShop.reserve(MAX_ITEM);
		vMonster.reserve(MAX_MONSTER);

		while (1)
		{
			system("cls");
			checkSave();
			resetDefaultSave();
			int menu = Interface::startGame(saveGameAvailable);

			if (menu == -1) return; // kalau user pilih exit game

			if (menu == 1) // new game
			{
				hName = Interface::newGameName();
				if (hName == "3s0xla 81a;LKDJn(**A;") continue;
				job = Interface::newGameJob(hName);
				if (job == -1) continue; // kalau user teken esc (exit) saat milih new game

				system("cls");
				newData();
				if (karakter != NULL) delete karakter;
				karakter = new Human(vShop, job, hName); // CARA BIKIN HUMAN DENGAN NEW GAME
				cout << "SUCCESFULLY CREATED NEW CHARACTER!" << endl;
				Interface::flush();
			}
			else // menu==2 (load game)
			{
				// CARA BIKIN HUMAN DENGAN LOAD GAME
				if (karakter != NULL) delete karakter;
				checkSave();
				if (!saveGameAvailable)
				{
					cout << "\nSAVE GAME CORRUPTED WHILE READING\nPress enter to go back..";
					Interface::pressEnterPlease();
					return; // INI LANGSUNG EXIT
				}
				else
				{
					loadSave();
					karakter = new Human(vShop, hName, hLevel, job, hGold, experience, strength, endurance, agility, dexterity, hDamage, hChanceToHit, hEvade, hSpeed
						, hMaxHealth, hMaxStamina, hArmor);

					cout << "SUCCESFULLY LOADED OLD CHARACTER!" << endl;
					Interface::flush();
				}
			}

			Interface::shopMenu(vShop,karakter);

			testShop(); // TESTING SHOP DAN SORT

			cout << "game saved!";
			saveGame();
			Interface::flush();
		}
	} // END constructor
};

/*
TEMPLATE SAVE

Nama Karakter
Level,Job,Gold,Experience,Strength,Endurance,Agility,Dexterity
Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor
#Nama Item1,Price,*effect*,Type,Restriction,Eguipped,Bought
#Nama Item2,Price,*effect*,Type,Restriction,Eguipped,Bought
#Nama Item3,Price,*effect*,Type,Restriction,Eguipped,Bought
@Nama Monster1,Level,Gold,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Experience,Offense,Defense
@Nama Monster2,Level,Gold,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Experience,Offense,Defense
@Nama Monster3,Level,Gold,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Experience,Offense,Defense
*/

void Game::createDefaultSave()
{
	vector<char*> itemSave =
	{
		//#Nama Item1,Price,*effect*,Type,Restriction,Eguipped,Bought

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
		"@Ghoul,1,300,20,86,3,66,120,90,2,1358,6,12\n",
		"@Giant Spider,2,600,7,114,18,210,120,90,0,2683,8,16\n",
		"@Vampire,4,800,30,109,8,112,142,100,1,4477,21,15\n",
		"@Gargoyle Trap,4,920,20,98,0,89,300,150,5,4682,14,41\n",
		"@Tainted One,4,900,12,116,9,152,198,120,3,4427,20,23\n",
		"@Goatman,3,650,12,104,12,154,135,120,1,3426,14,16\n",
		"@Mummy,5,1050,13,116,9,138,265,160,1,5424,20,29\n",
		"@Sand Raider,6,1280,13,122,14,180,278,120,3,6275,26,35\n",
		"@Claw Viper,7,1490,11,140,25,210,188,170,2,7867,39,32\n",
		"@Slinger,8,1510,28,149,26,180,130,120,1,8756,70,22\n",
		"@Sabre Cat,9,1620,18,110,42,200,195,150,4,9047,46,60\n",
		"@Vulture Demon,10,2200,15,156,44,242,180,180,2,10558,48,55\n",
		"@Sand Maggot,9,1640,26,118,23,182,228,130,6,9108,38,43\n",
		"@Fire Eye,10,2200,28,135,39,200,180,120,4,10332,50,50\n",
		"@Frog Demon,11,2550,22,130,35,226,312,180,2,11020,60,72\n",
		"@Thorned Hulk,10,2070,39,90,9,166,455,220,8,10122,47,70\n",
		"@Zakarum Zealot,12,3750,40,128,34,265,308,160,5,12646,112,78\n",
		"@Tentacle Beast,11,2630,30,116,20,226,380,280,3,11162,71,58\n",
		"@Willowisp,12,3400,9,162,68,390,128,380,0,12267,69,80\n",
		"@Temple Guard,13,4300,49,122,32,250,294,320,5,13285,124,71\n",
		"@Strangler,15,3600,55,98,33,220,459,200,2,15018,103,99\n",
		"@Megademon,16,4500,55,112,35,213,397,240,6,16115,142,110\n",
		"@Regurgitator,14,3430,52,102,24,180,589,220,4,14769,92,103\n",
		"@Oblivion Knight,17,4830,42,132,40,223,376,380,8,17700,178,142\n",
		"@Izuel,23,8800,66,140,41,240,448,520,10,23152,339,204\n",
		"@Grand Vizier,24,10000,42,150,55,290,395,380,12,24400,289,313\n",
		"@Baal,22,7400,185,118,52,120,490,300,6,22470,393,227\n",
		"@Mephisto,26,14500,65,138,40,288,725,600,15,26235,492,469\n",
		"@Diablo,30,0,90,148,35,300,1020,540,12,0,501,441\n"
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

void Game::testShop()
{
	while(1)
	{
		system("cls");
		cout << "Name: " << karakter->getName() << " (";
		switch (karakter->getJob())
		{
		case 1:
			cout << "Assassin ";
			break;
		case 2:
			cout << "Paladin ";
			break;
		case 3:
			cout << "Barbarian ";
			break;
		}
		cout << "lv. " << karakter->getLevel() << ") (exp: " << karakter->getExperience() << '/' << karakter->getExpRequirement(karakter->getLevel() + 1) << ")\n";
		cout << "You have (" << karakter->getNumInventory() << ") out of (" << vShop.size() << ") items\n";
		cout << "\n1 = Buy\n2 = Show inventory\n3 = Exit\n";
		cout << "choose: ";
		int menu;
		cin >> menu;
		while (cin.fail() || menu < 1 || menu>3)
		{
			Interface::flush();
			cout << "choose: ";
			cin >> menu;
		}
		Interface::flush();

		if (menu == 1)
		{
			system("cls");
			vector<Item*> temporary; // nampung semua item di vShop yang belum dibeli
			temporary.reserve(MAX_ITEM);
			int shopSize = vShop.size(); // berapa item di vShop

			// tanya dulu mau filter apa nggak
			filterType = 0;
			cout << "<Filter by: NONE>\n\n";
			while (1)
			{
				// INI BACA DARI VSHOP
				temporary.clear();
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

				int flag = 0;
				vector<Item*>::iterator iter; // iterator untuk vector temporary (Item*)
				int i = 1; // variable buat print index vector (tapi ini mulai dari 1, sedangkan vector mulai dari 0)

				
				// INI SETELAH DI-FILTER (KALAU DI-FILTER)
				for (iter = temporary.begin(); iter != temporary.end(); iter++, i++)
				{
					cout << setw(3) << left << i << ' ' << setw(20) << left << (*iter)->getName() << " Price: " << setw(6) << left << (*iter)->getPrice()
						<< " Restriction = " << (*iter)->getRestriction() << "  Type = " << (*iter)->getType();
					if ((*iter)->getArmor() != 0) cout <<  " Armor  = " << setw(3) << (*iter)->getArmor();
					if ((*iter)->getDamage() != 0) cout << " Damage = " << setw(3) << (*iter)->getDamage();
					cout << '\n';
				}

				cout << "\nPress tab to switch item filter, or enter to continue...\n";
				while (1)
				{
					char x = _getch();
					if (x == VK_RETURN) // press enter = keluar
					{
						int sampah;
						while (true)
						{
							sampah = Console::getKeyPressed();
							if (sampah == VK_RETURN) {
								//printf(" <-");
								Console::delay(50);
								flag = 1;
								break;
							}
						}
						break;
					}
					else if (x == '\t')
					{
						// --------------------------------------------------- MODIFIKASI DARI YANG DI INTERFACE
						filterType = (filterType + 1) % 7;
						// -------------------------------------------------------------------------------------
						break;
					}
					else printf("\b \b"); // backspace
				}

				if (flag) break; // kalau udah teken "enter", maka lanjut

				system("cls");
				cout << "<Filter by: ";
				switch (filterType)
				{
				case 0:
					cout << "NONE>";
					break;
				case 1:
					cout << "HELMET>";
					break;
				case 2:
					cout << "GLOVE>";
					break;
				case 3:
					cout << "ARMOR>";
					break;
				case 4:
					cout << "BOOT>";
					break;
				case 5:
					cout << "WEAPON>";
					break;
				case 6:
					cout << "SHIELD>";
					break;
				}
				cout << "\n\n";
			}

			// setelah di-filter (atau tidak), tanya mau sort atau tidak?
			cout << "\nSORT or not? [y/n]: ";
			string choose;
			tolower(choose[0]);
			getline(cin, choose);
			while (cin.fail() || (choose != "y" && choose != "n"))
			{
				cin.clear();
				cout << "SORT or not? [y/n]: ";
				getline(cin, choose);
			}
			if (choose == "y")
			{
				// sortir berdasarkan yang diinginkan
				int maks;
				cout << "\nSort by:" << '\n';
				cout << "1. Price\n2. Name\n";
				if (filterType == 0) // kalau tidak di-filter
				{
					cout << "3. Armor\n4. Damage\n";
					maks = 4;
				}
				else if (filterType == 3 || filterType == 4) // kalau di-filter armor yang gak punya effect +DMG
				{
					cout << "3. Armor\n";
					maks = 3;
				}
				else
				{
					cout << "3. Damage\n"; //kalau di-filter weapon (gk punya +AMR)
					maks = 3;
				}
				cout << "choose: ";
				int pilihSort;
				cin >> pilihSort;
				while (cin.fail() || pilihSort < 1 || pilihSort>maks)
				{
					cin.clear();
					cin.ignore(1000000, '\n');
					cout << "choose: ";
					cin >> pilihSort;
				}
				cin.clear();
				cin.ignore(1000000, '\n');
				int sortByApa;
				switch (pilihSort)
				{
				case 1:
					sort(temporary.begin(), temporary.end(), ComparePrice());
					sortByApa = 1;
					break;
				case 2:
					sort(temporary.begin(), temporary.end(), CompareName());
					sortByApa = 2;
					break;
				case 3:
					if (filterType != 3 && filterType != 4)
					{
						sortByApa = 4;
						sort(temporary.begin(), temporary.end(), CompareDamage()); // hanya tipe 3 dan 4 saja yang gk punya damage
						break;
					}
					else sort(temporary.begin(), temporary.end(), CompareArmor());
					sortByApa = 3;
					break;
				case 4:
					sort(temporary.begin(), temporary.end(), CompareDamage());
					sortByApa = 4;
					break;
				}
				system("cls");
				// tulis ulang filter by apa
				cout << "Filter by: ";
				switch (filterType)
				{
				case 0:
					cout << "NONE";
					break;
				case 1:
					cout << "HELMET";
					break;
				case 2:
					cout << "GLOVE";
					break;
				case 3:
					cout << "ARMOR";
					break;
				case 4:
					cout << "BOOT";
					break;
				case 5:
					cout << "WEAPON";
					break;
				case 6:
					cout << "SHIELD";
					break;
				}
				// tulis sorted by apa
				cout << "\n<Sorted by: ";
				switch (sortByApa)
				{
				case 1:
					cout << "PRICE>\n\n";
					break;
				case 2:
					cout << "NAME>\n\n";
					break;
				case 3:
					cout << "ARMOR>\n\n";
					break;
				case 4:
					cout << "DAMAGE>\n\n";
					break;
				}

				// KALAU MINTA SORT, PRINT ULANG (buat update-in dari sebelumnya)
				int i = 1; // variable buat print index vector (tapi ini mulai dari 1, sedangkan vector mulai dari 0)
				vector<Item*>::iterator iter; // iterator untuk vector temporary (Item*)
											  // INI SETELAH DI-SORT (KALAU DI-SORT)
				for (iter = temporary.begin(); iter != temporary.end(); iter++, i++)
				{
					cout << setw(3) << left << i << ' ' << setw(20) << left << (*iter)->getName() << " Price: " << setw(6) << left << (*iter)->getPrice()
						<< " Restriction = " << (*iter)->getRestriction() << "  Type = " << (*iter)->getType();
					if ((*iter)->getArmor() != 0) cout << " Armor  = " << setw(3) << (*iter)->getArmor();
					if ((*iter)->getDamage() != 0) cout << " Damage = " << setw(3) << (*iter)->getDamage();
					cout << '\n';
				}
			}

			int buy;
			int vectorSize = temporary.size();
			cout << "\nBuy what (-1 to cancel): "; // 0 to cancel itu bisa diganti supaya jadi lebih elegan
			cin >> buy;
			while (cin.fail() || buy<-1 || buy==0 || buy > vectorSize)
			{
				Interface::flush();
				cout << "\nBuy what (-1 to cancel): "; // -1 to cancel itu bisa diganti supaya jadi lebih "indah"
				cin >> buy;
			}
			Interface::flush();
			if (buy != -1)
			{
				karakter->buyItem(temporary[buy - 1]); // jangan lupa index dikurang 1 (buy-1)
				cout << "\n" << temporary[buy - 1]->getName() << '(' << temporary[buy-1]->getPrice() << ") succesfully bought!\n";
			}
			cout << "\n-> Press enter to continue <-\n";
			Interface::pressEnterPlease();
		}
		else if (menu == 2)// show inventory
		{
			vector<Item*> vec(karakter->getInventory());
			cout << "\n<MY INVENTORY>\n";
			vector<Item*>::iterator iter; //iter memiliki value dari Item*
			int i;
			if (karakter->getNumInventory() == 0) cout << "\n~ ~ ~ EMPTY! YOU GOT TO BUY SOME MORE BRUH! ~ ~ ~\n";
			for (iter = vec.begin(), i = 1; iter != vec.end(); iter++, i++)
			{
				cout << i << ' ' << (*iter)->getName() << " (price:" << (*iter)->getPrice() << ")\n";
			}

			cout << "\n-> Press enter to continue <-\n";
			Interface::pressEnterPlease();
			Console::delay(50);
		}
		else // menu == 3
		{
			return;
		}
	}
}

#endif // !GAME_H