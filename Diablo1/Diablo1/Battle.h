﻿#pragma once

#ifndef BATTLE_H
#define BATTLE_H

#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include <cmath>
#include "common.h"
#include "Game.h"
#include "Human.h"
#include "Monster.h"
#include "Interface.h"
#include "Music.h"


using namespace std;

// for printing box
#define ASCII_DOUBLE_UPPER_LEFT 201  
#define ASCII_DOUBLE_LOWER_LEFT 200  
#define ASCII_DOUBLE_UPPER_RIGHT 187  
#define ASCII_DOUBLE_LOWER_RIGHT 188  
#define ASCII_DOUBLE_VERTICAL_SEPARATOR 186  
#define ASCII_DOUBLE_SEPARATOR 205

#define ASCII_SINGLE_SEPARATOR 196
#define ASCII_SINGLE_VERTICAL_SEPARATOR 179 
#define ASCII_SINGLE_UPPER_LEFT 218
#define ASCII_SINGLE_LOWER_LEFT 192
#define ASCII_SINGLE_UPPER_RIGHT 191  
#define ASCII_SINGLE_LOWER_RIGHT 217 

#define ASCII_BOX_FULL 219
#define ASCII_BOX_EMPTY 177

const int GREEN = Console::COLOR_GREEN;
const int YELLOW = Console::COLOR_YELLOW;
const int RED = Console::COLOR_RED;
const int WHITE = Console::COLOR_WHITE;
const int GREY = Console::COLOR_GRAY;
const int BLUE = Console::COLOR_BLUE;

class Battle
{
private:
	// post-battle variable
	static bool win;

	// mechanism variable
	static int animationSpeed[4];
	static int index;
	static int autoAttack;

	//human and monster attributes
	static float hStamina;
	static float mStamina;
	static float hHP;
	static float mHP;

	//special ability
	static int coupDeGrace;
	static int riposte;
	static int momentum;

	//adventure in cave
	static int monsterKilled;
	static int goldEarned;
	static int expGained;
	static char caveName[7][30];
	// helper function
	static void printBox1(int x, int y)
	{
		Console::setCursorPos(x, y);
		printf("%c", ASCII_DOUBLE_UPPER_LEFT);
		for (int i = 0; i < 27; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_UPPER_RIGHT);

		for (int i = 1; i <= 6; i++)
		{
			Console::setCursorPos(x, y + i);
			printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
			Console::setCursorPos(x + 28, y + i);
			printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
		}

		Console::setCursorPos(x, y + 7);
		printf("%c", ASCII_DOUBLE_LOWER_LEFT);
		for (int i = 0; i < 27; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_LOWER_RIGHT);
	}
	static void printBox2()
	{
		Console::setCursorPos(1, 10);
		printf("%c", ASCII_DOUBLE_UPPER_LEFT);
		for (int i = 0; i < 60; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_UPPER_RIGHT);

		for (int i = 1; i <= 5; i++)
		{
			Console::setCursorPos(1, 10 + i);
			printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
			Console::setCursorPos(1 + 61, 10 + i);
			printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
		}

		Console::setCursorPos(1, 10 + 6);
		printf("%c", ASCII_DOUBLE_LOWER_LEFT);
		for (int i = 0; i < 60; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_LOWER_RIGHT);
	}
	static void printBox3()
	{
		Console::setCursorPos(1, 18);
		printf("%c", ASCII_DOUBLE_UPPER_LEFT);
		for (int i = 0; i < 17; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_UPPER_RIGHT);

		for (int i = 1; i <= 3; i++)
		{
			Console::setCursorPos(1, 18 + i);
			printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
			Console::setCursorPos(1 + 18, 18 + i);
			printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
		}

		Console::setCursorPos(1, 18 + 4);
		printf("%c", ASCII_DOUBLE_LOWER_LEFT);
		for (int i = 0; i < 17; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_LOWER_RIGHT);
	}
	static void printBox4()
	{
		Console::setCursorPos(21, 18);
		printf("%c", ASCII_DOUBLE_UPPER_LEFT);
		for (int i = 0; i < 40; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_UPPER_RIGHT);

		for (int i = 1; i <= 3; i++)
		{
			Console::setCursorPos(21, 18 + i);
			printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
			Console::setCursorPos(21 + 41, 18 + i);
			printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
		}

		Console::setCursorPos(21, 18 + 4);
		printf("%c", ASCII_DOUBLE_LOWER_LEFT);
		for (int i = 0; i < 40; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_LOWER_RIGHT);
	}
	static void printXPBox()
	{
		Console::setCursorPos(1, 1);
		printf("%c", ASCII_DOUBLE_UPPER_LEFT);
		for (int i = 0; i < 25; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_UPPER_RIGHT);

		Console::setCursorPos(1, 2); printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
		Console::setCursorPos(27, 2); printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);

		Console::setCursorPos(1, 3); printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
		for (int i = 1; i <= 25; i++) printf("%c", ASCII_SINGLE_SEPARATOR);
		Console::setCursorPos(27, 3); printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);

		Console::setCursorPos(1, 4); printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);
		Console::setCursorPos(27, 4); printf("%c", ASCII_DOUBLE_VERTICAL_SEPARATOR);

		Console::setCursorPos(1, 5);
		printf("%c", ASCII_DOUBLE_LOWER_LEFT);
		for (int i = 0; i < 25; i++) printf("%c", ASCII_DOUBLE_SEPARATOR);
		printf("%c", ASCII_DOUBLE_LOWER_RIGHT);
	}
	static int toggleAutoAttack()
	{
		Console::setCursorPos(3, 17);
		Console::resetColor();
		printf("Auto attack: ");
		if (autoAttack == 0) // off
		{
			// turn on
			Console::setColor(GREEN);
			printf("ON ");
			Console::resetColor();
			return 1;
		}
		else // on
		{
			//turn off
			Console::setColor(RED);
			printf("OFF");
			Console::resetColor();
			return 0;
		}
	}

	// speed bar
	static int printSpeed(int& xYou, float speedYou, int& xEnemy, float speedEnemy)
	{
		Console::setColor(BLUE);
		if (momentum) speedYou *= 3; // BARBARIAN
		int sec = 0;
		int speed = animationSpeed[index];
		float mySpeed = speed / speedYou;
		float enemySpeed = speed / speedEnemy;

		int inputDelay = 1;
		while (1)
		{
			char buff = Console::getKeyPressed();
			if (buff != -1)
			{
				if (buff == 'M' || buff == 'm')
				{
					if (inputDelay)
						Music::playBackgroundMusic(Music::TOGGLE);
					else
						inputDelay++;
				}
				if (buff == VK_TAB)
				{
					if (inputDelay)
					{
						// toggle speed
						index = (index + 1) % 3;
						speed = animationSpeed[index];
						mySpeed = speed / speedYou;
						enemySpeed = speed / speedEnemy;
						inputDelay = 0;
						printAnimationSpeed();
					}
					else inputDelay++;
				}
				else if (buff == VK_ESCAPE)
				{
					if (inputDelay)
					{
						autoAttack = toggleAutoAttack();
						inputDelay = 0;
					}
					else inputDelay++;
				}
				Console::setColor(BLUE);
			}
			if (xYou == 29 || xEnemy == 62) break;
			if (sec % (int)ceil(mySpeed) == 0)
			{
				Console::setCursorPos(xYou, 7);
				printf("%c", ASCII_BOX_FULL);
				xYou++;
			}
			if (sec % (int)ceil(enemySpeed) == 0)
			{
				Console::setCursorPos(xEnemy, 7);
				printf("%c", ASCII_BOX_FULL);
				xEnemy++;
			}
			Console::delay(1);
			sec++;
		}

		if (xYou == 29) return 1;
		else if (xEnemy == 62) return 2;
	}
	static void printAnimationSpeed()
	{
		Console::setCursorPos(30, 17);
		Console::resetColor();
		printf("Animation speed: ");
		if (index == 0)
		{
			Console::setColor(GREEN);
			printf("LOW");
			Console::resetColor();
			printf("   ");
		}
		else if (index == 1)
		{
			Console::setColor(YELLOW);
			printf("MEDIUM");
			Console::resetColor();
		}
		else
		{
			Console::setColor(RED);
			printf("HIGH");
			Console::resetColor();
			printf("  ");
		}
	}
	static void clearSpeed(int turn)
	{
		Console::setColor(BLUE);
		if (turn == 1)	Console::setCursorPos(2, 7);
		else Console::setCursorPos(35, 7);

		for (int i = 0; i < 27; i++)
		{
			printf(" ");
		}
	}
	static void colorSpeed(int turn)
	{
		Console::setColor(RED);
		if (turn == 1)	Console::setCursorPos(2, 7);
		else Console::setCursorPos(35, 7);

		for (int i = 0; i < 27; i++)
		{
			printf("%c", ASCII_BOX_FULL);
		}
	}

	// action
	static void printDescription(int pickMenu, Human& karakter, Monster& enemy)
	{
		// clear box4
		{
			Console::resetColor();
			for (int i = 0; i < 3; i++)
			{
				for (int x = 0; x < 40; x++)
				{
					Console::setCursorPos(22 + x, 19 + i);
					printf(" ");
				}
			}
		}
		Console::setCursorPos(23, 19);
		if (pickMenu == 0) // attack
		{
			//      !                                     !
			printf("Attack the enemy, uses %d stamina", 10 + karakter.getArmor());
			Console::setCursorPos(23, 20);
			printf("Damage: %-3.0f Chance to Hit: %-3.0f%%", karakter.getDamage(), karakter.getChanceToHit() + (coupDeGrace ? 25 : 0));
			Console::setCursorPos(23, 21);
			printf("Critical chance: %.0f%%(CTH - EVA)", max(0, karakter.getChanceToHit() + (coupDeGrace ? 25 : 0) - enemy.getEvade() - 100.0f));
		}
		else if (pickMenu == 1) // rest
		{
			//      !                                     !
			printf("Rest to gain %.0f stamina", 50.0f + karakter.getLevel());
			Console::setCursorPos(23, 20);
			printf("Armor: %-3d   Evasion: %-3.0f", karakter.getArmor(), karakter.getEvade());
			Console::setCursorPos(23, 21);
			printf("Speed: %3.0f", karakter.getSpeed()*(momentum ? 3 : 1));
		}
		else if (pickMenu == 3) // coup de grace
		{
			//      !                                     !
			printf("Increase Critical Hit and Evasion");
			Console::setCursorPos(23, 20);
			printf("chance by 25 %% for 2 turns.");
			Console::setCursorPos(23, 21);
			printf("Skips turn, uses 30 stamina.");
		}
		else if (pickMenu == 4) // riposte
		{
			//      !                                     !
			printf("Attack enemy with 1.5x multiplier,");
			Console::setCursorPos(23, 20);
			printf("then STUN the enemy if hit didn't miss.");
			Console::setCursorPos(23, 21);
			printf("Uses 30 stamina");
		}
		else if (pickMenu == 5) // momentum
		{
			//      !                                     !
			printf("Increase speed by 3x multiplier");
			Console::setCursorPos(23, 20);
			printf("for 3 turn, but SKIPS this turn.");
			Console::setCursorPos(23, 21);
			printf("Uses 30 stamina");
		}
	}
	static int pickAction(Human& karakter, int& pickMenu, Monster& enemy)
	{
		if (pickMenu > 2) pickMenu = 2;

		string ability;
		switch (karakter.getJob())
		{
		case 1:
			ability = "Coup de Grace";
			break;
		case 2:
			ability = "Riposte";
			break;
		case 3:
			ability = "Momentum";
			break;
		}

		bool printFlag = true;
		int delayFlag = 0;
		char buff;
		while (1)
		{
			if (printFlag)
			{
				Console::setCursorPos(3, 19);
				Console::resetColor();
				if (pickMenu == 0)
				{
					Console::setColor(79);
					printf("<Attack>");
					Console::resetColor();
					printDescription(pickMenu, karakter, enemy);
				}
				else printf(" Attack ");

				Console::setCursorPos(3, 20);
				if (pickMenu == 1)
				{
					Console::setColor(79);
					printf("<Rest>");
					Console::resetColor();
					printDescription(pickMenu, karakter, enemy);
				}
				else printf(" Rest ");

				Console::setCursorPos(3, 21);
				if (pickMenu == 2)
				{
					Console::setColor(79);
					printf("<");
					printf("%s", ability.c_str());
					printf(">");
					Console::resetColor();
					printDescription(pickMenu + karakter.getJob(), karakter, enemy);
				}
				else printf(" %s ", ability.c_str());

				printFlag = false;
			}
			buff = Console::getKeyPressed();
			if (buff != -1)
			{
				if (delayFlag)
				{
					if (buff == 'M' || buff == 'm')
					{
						Music::playBackgroundMusic(Music::TOGGLE);
					}
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
						index = (index + 1) % 3;
						printAnimationSpeed();
					}
					else if (buff == VK_ESCAPE)
					{
						autoAttack = toggleAutoAttack();
					}
					else if (buff == VK_RETURN)
					{
						break;
					}

					delayFlag = 0;
				}
				else delayFlag++;
			}
		}
		// unpick menu
		{
			Console::setCursorPos(3, 19);
			Console::resetColor();
			printf(" Attack ");

			Console::setCursorPos(3, 20);
			printf(" Rest ");

			Console::setCursorPos(3, 21);
			printf(" %s ", ability.c_str());;
		}
		// return value
		if (pickMenu == 2) return pickMenu + karakter.getJob();
		else return pickMenu;
	}
	static void attack(int who, Human& karakter, Monster& enemy, deque<string>& log)
	{
		srand((unsigned int)time(NULL));
		string text;
		if (who == 0) // turn karakter
		{
			float change = (10.0f + karakter.getArmor()); // kurangin stamina;
			hStamina -= change;
			STAchange(0, karakter, enemy);

			text += karakter.getName();
			text += " attacks ";
			text += enemy.getName();
			text += " with ";

			bool crit = false;
			bool hit = false;
			float chance = karakter.getChanceToHit() - enemy.getEvade();
			if (coupDeGrace) chance += 25; // ASSASSIN
			if (chance <= 100.0f)
			{
				text += to_string((int)(100 - chance));
				text += "% MISS chance.";
				if (chance < 10.0f) chance = 10.0f; // kalau chance kurang dari 10%, jadiin 10%

				int calculate = rand() % 100 + 1;
				if (calculate < chance) hit = true;
				else hit = false;
			}
			else
			{
				hit = true;
				text += to_string((int)(chance - 100));
				text += "% CRIT chance.";

				int calculate = (int)fmod(rand(), chance) + 1;
				if (calculate < 100.0f) crit = false;
				else crit = true;
			}
			log.push_back(text);
			printLog(log);

			text.clear();
			if (hit)
			{
				if (crit)
				{
					float damage = karakter.getDamage()*(1.0f + karakter.getStrength()*0.05f);
					if (riposte) damage *= 1.5; // PALADIN


					text += karakter.getName();
					text += " CRITICAL HIT with ";
					text += to_string((int)damage);
					text += " damage!";
					text += " (" + to_string((int)mHP) + "->" + to_string((int)max(0, mHP - (int)damage)) + ')';
					log.push_back(text);
					printLog(log);

					Music::playSoundEffect(Music::CRIT);
					HPchange(0, damage, karakter, enemy, crit);
				}
				else
				{
					float MinDamage = max(0, karakter.getDamage() - enemy.getArmor());
					float MaxDamage = max(0, (karakter.getDamage()*(1.0f + (float)karakter.getStrength()*0.05f)) - enemy.getArmor());
					int diff = (int)ceil(MaxDamage - MinDamage);
					float damage = MinDamage + (diff > 1 ? (rand() % diff) : 0);
					if (riposte) damage *= 1.5; // PALADIN

					text += karakter.getName();
					text += " HIT with ";
					text += to_string((int)damage);
					text += " damage!";
					text += " (" + to_string((int)mHP) + "->" + to_string((int)max(0, mHP - (int)damage)) + ')';
					log.push_back(text);
					printLog(log);

					Music::playSoundEffect(Music::HIT);
					HPchange(0, damage, karakter, enemy, crit); // UBAH INI KALAU MAU NGECHEAT
				}
				if (riposte) // PALADIN
				{
					text.clear();
					text = enemy.getName();
					text += " stunned!";
					log.push_back(text);
					printLog(log);
				}
			}
			else
			{
				if (riposte)riposte--; // PALADIN
				text += karakter.getName();
				text += " MISSED the hit!";
				log.push_back(text);
				printLog(log);
			}
		}
		else // turn monster
		{
			float change = (10.0f + enemy.getArmor()); // kurangin stamina;
			mStamina -= change;
			STAchange(1, karakter, enemy);

			text += enemy.getName();
			text += " attacks ";
			text += karakter.getName();
			text += " with ";

			bool crit = false;
			bool hit = false;
			float chance = enemy.getChanceToHit() - karakter.getEvade();
			if (chance <= 100)
			{
				text += to_string((int)(100 - chance));
				text += "% MISS chance.";
				if (chance < 10.0f) chance = 10.0f;

				int calculate = rand() % 100 + 1;
				if (calculate < chance) hit = true;
				else hit = false;
			}
			else
			{
				hit = true;
				text += to_string((int)(chance - 100));
				text += "% CRIT chance.";

				int calculate = (int)fmod(rand(), chance) + 1;
				if (calculate < 100.0f) crit = false;
				else crit = true;
			}
			log.push_back(text);
			printLog(log);

			text.clear();
			if (hit)
			{
				if (crit)
				{
					float damage = enemy.getDamage()*(1.0f + enemy.getLevel()*0.05f);

					text += enemy.getName();
					text += " CRITICAL HIT with ";
					text += to_string((int)damage);
					text += " damage!";
					text += " (" + to_string((int)hHP) + "->" + to_string((int)max(0, hHP - (int)damage)) + ')';
					log.push_back(text);
					printLog(log);

					Music::playSoundEffect(Music::CRIT);
					HPchange(1, damage, karakter, enemy, crit);
				}
				else
				{
					float MinDamage = max(0, enemy.getDamage() - karakter.getArmor());
					float MaxDamage = max(0, (enemy.getDamage()*(1.0f + (float)enemy.getLevel()*0.05f)) - karakter.getArmor());
					int diff = (int)ceil(MaxDamage - MinDamage);
					float damage = MinDamage + (diff > 1 ? (rand() % diff) : 0);

					text += enemy.getName();
					text += " HIT with ";
					text += to_string((int)damage);
					text += " damage!";
					text += " (" + to_string((int)hHP) + "->" + to_string((int)max(0, hHP - (int)damage)) + ')';
					log.push_back(text);
					printLog(log);

					Music::playSoundEffect(Music::HIT);
					HPchange(1, damage, karakter, enemy, crit); // UBAH INI KALAU MAU NGECHEAT
				}
			}
			else
			{
				text += enemy.getName();
				text += " MISSED the hit!";
				log.push_back(text);
				printLog(log);
			}
		}
	}
	static void rest(int who, Human& karakter, Monster& enemy, deque<string>& log)
	{
		string text;
		if (who == 0)
		{
			text += karakter.getName();
			text += " rested and gain ";
			text += to_string(50 + karakter.getLevel());
			text += " stamina.";
			text += " (" + to_string((int)hStamina) + "->" + to_string((int)min(karakter.getMaxHealth(), (hStamina + (50 + karakter.getLevel())))) + ')';
			hStamina += (50 + karakter.getLevel());
			STAchange(who, karakter, enemy);
			log.push_back(text);
			printLog(log);
		}
		else
		{
			text += enemy.getName();
			text += " rested and gain ";
			text += to_string(50 + enemy.getLevel());
			text += " stamina.";
			text += " (" + to_string((int)mStamina) + "->" + to_string((int)min(enemy.getMaxStamina(), (mStamina + (50 + enemy.getLevel())))) + ')';
			mStamina += (50 + enemy.getLevel());
			STAchange(who, karakter, enemy);
			log.push_back(text);
			printLog(log);
		}
	}
	// HP dan STA change animation
	// 22 box total
	static void HPchange(int who, float change, Human& karakter, Monster& enemy, bool crit)
	{
		if (who == 0) // HP MONSTER yang berkurang
		{
			Console::setCursorPos(47, 9);
			Console::setColor(RED);
			if (!riposte)if (crit) printf("CRITTTT!"); else printf("BAMMMMM!");
			else printf("STUNNED!");
			if (mHP <= change)
			{
				// insta kill
				float box = enemy.getMaxHealth() / 22.0f;
				float counter = 0;
				int x = 0;
				while (x < 22 && counter <= mHP)
				{
					Console::setColor(WHITE);
					Console::setCursorPos(40 + (x++), 4);
					printf("%c", ASCII_BOX_FULL);
					counter += box;
				}
				BattleDelay(1000);

				mHP = -1;
				Console::setColor(Console::COLOR_GRAY);
				x = 0;
				while (x < 22)
				{
					Console::setCursorPos(40 + (x++), 4);
					printf(" ");
				}
				Console::resetColor();
			}
			else
			{
				float box = enemy.getMaxHealth() / 22.0f;
				float HPbefore = mHP;
				mHP -= change;

				int color = WHITE;
				if (mHP > enemy.getMaxHealth()*0.5) color = GREEN;
				else if (mHP < enemy.getMaxHealth()*0.20) color = RED;
				else color = YELLOW;
				Console::setColor(color);

				float counter = 0;
				int x = 0;
				while (x < 22 && counter <= mHP)
				{
					Console::setCursorPos(40 + (x++), 4);
					printf("%c", ASCII_BOX_FULL);
					counter += box;
				}
				int xBefore = x; // simpen angka x sebelumnya
				while (x < 22 && counter <= HPbefore)
				{
					Console::setColor(WHITE);
					Console::setCursorPos(40 + (x++), 4);
					printf("%c", ASCII_BOX_FULL);
					counter += box;
				}
				BattleDelay(1000);
				x = xBefore;
				while (x < 22)
				{
					Console::setColor(color);
					Console::setCursorPos(40 + (x++), 4);
					printf(" ");
				}
			}


			Console::setCursorPos(47, 9);
			Console::resetColor();
			printf("        ");
		}
		else
		{
			Console::setCursorPos(10, 9);
			Console::setColor(RED);
			if (crit) printf("CRITTTT!"); else printf("BAMMMMM!");

			if (hHP <= change)
			{
				float box = karakter.getMaxHealth() / 22.0f;
				float counter = 0;
				int x = 0;
				while (x < 22 && counter <= hHP)
				{
					Console::setColor(WHITE);
					Console::setCursorPos(7 + (x++), 4);
					printf("%c", ASCII_BOX_FULL);
					counter += box;
				}
				BattleDelay(1000);

				// insta kill
				hHP = -1;
				Console::setColor(Console::COLOR_GRAY);
				x = 0;
				while (x < 22)
				{
					Console::setCursorPos(7 + (x++), 4);
					printf(" ");
				}
				Console::resetColor();
			}
			else
			{
				float box = karakter.getMaxHealth() / 22.0f;
				float HPbefore = hHP;
				hHP -= change;

				int color;
				if (hHP > karakter.getMaxHealth()*0.5) color = GREEN;
				else if (hHP < karakter.getMaxHealth()*0.20) color = RED;
				else color = YELLOW;
				Console::setColor(color);

				float counter = 0;
				int x = 0;
				while (x < 22 && counter <= hHP)
				{
					Console::setCursorPos(7 + (x++), 4);
					printf("%c", ASCII_BOX_FULL);
					counter += box;
				}
				int xBefore = x;
				while (x < 22 && counter <= HPbefore)
				{
					Console::setColor(WHITE);
					Console::setCursorPos(7 + (x++), 4);
					printf("%c", ASCII_BOX_FULL);
					counter += box;
				}
				BattleDelay(1000);
				x = xBefore;
				while (x < 22)
				{
					Console::setColor(color);
					Console::setCursorPos(7 + (x++), 4);
					printf(" ");
				}
			}


			Console::setCursorPos(10, 9);
			Console::resetColor();
			printf("        ");
		}
	}
	static void STAchange(int who, Human& karakter, Monster& enemy)
	{
		if (who == 0) // STA karakter yang bertambah
		{
			float box = karakter.getMaxStamina() / 22.0f;
			if (hStamina > karakter.getMaxStamina()) hStamina = karakter.getMaxStamina();

			Console::setColor(YELLOW);

			float counter = 0;
			int x = 0;
			while (x < 22 && counter <= hStamina)
			{
				Console::setCursorPos(7 + (x++), 5);
				printf("%c", ASCII_BOX_FULL);
				counter += box;
			}
			while (x < 22)
			{
				Console::setCursorPos(7 + (x++), 5);
				printf(" ");
			}
		}
		else
		{
			float box = enemy.getMaxStamina() / 22.0f;
			if (mStamina > enemy.getMaxStamina()) mStamina = enemy.getMaxStamina();

			Console::setColor(YELLOW);

			float counter = 0;
			int x = 0;
			while (x < 22 && counter <= mStamina)
			{
				Console::setCursorPos(40 + (x++), 5);
				printf("%c", ASCII_BOX_FULL);
				counter += box;
			}
			while (x < 22)
			{
				Console::setCursorPos(40 + (x++), 5);
				printf(" ");
			}
		}


	}

	static void printLog(deque<string>& log)
	{
		Console::resetColor();
		// bersihin dulu
		{
			for (int i = 0; i < 5; i++)
			{
				for (int x = 0; x < 60; x++)
				{
					Console::setCursorPos(2 + x, 11 + i);
					printf(" ");
				}
			}
		}

		if (log.size() > 5)
		{
			deque<string>::reverse_iterator iter = log.rbegin();
			for (int i = 4; i >= 0; i--, iter++)
			{
				Console::setCursorPos(2, 11 + i);
				printf(" %s", iter->c_str());
			}
		}
		else
		{
			size_t size = log.size();
			deque<string>::iterator iter = log.begin();
			for (int i = 0; i < size; i++, iter++)
			{
				Console::setCursorPos(2, 11 + i);
				printf(" %s", iter->c_str());
			}
		}

		BattleDelay(1000);
	}

	static void end(int who, Human& karakter, Monster& enemy, deque<string>& log)
	{
		string text;
		if (who == 0)
		{
			// YOU WIN
			win = true;
			Music::playBackgroundMusic(Music::VICTORY);
			text = enemy.getName();
			text += " died!";
			log.push_back(text);
			printLog(log);

			text.clear();
			text = karakter.getName();
			text += " WIN!";
			log.push_back(text);
			printLog(log);
		}
		else
		{
			// YOU LOST
			win = false;
			text = karakter.getName();
			text += " LOST!";
			log.push_back(text);
			printLog(log);

			text.clear();
			text = "GAME OVER...";
			log.push_back(text);
			printLog(log);
		}
	}

	static void levelUpMenu(int gain, Human& karakter)
	{
		char* wallpaper[22] =
		{
			"                                  /   \\       ",
			" _                        )      ((   ))     (",
			"(@)                      /|\\      ))_((     /|\\                       (@)",
			"|-|                     / | \\    (/\\|/\\)   / | \\                      |-|",
			"| | -------------------/--|-voV---\\`|'/--Vov-|--\\---------------------|-|",
			"|-|                         '^`   (o o)  '^`                          | |",
			"| |                               `\\Y/'                               |-|",
			"|-|              _     _____ _     _____ _       _     ____           | |",
			"|-|             / \\   /  __// \\ |\\/  __// \\     / \\ /\\/  __\\          | |",
			"|-|             | |   |  \\  | | //|  \\  | |     | | |||  \\/|          | |",
			"|-|             | |_/\\|  /_ | \\// |  /_ | |_/\\  | \\_/||  __/          | |",
			"| |             \\____/\\____\\\\__/  \\____\\\\____/  \\____/\\_/             |-|",
			"|-|                                                                   | |",
			"| |                                                                   |-|",
			"| |                                                                   |-|",
			"| |                                                                   |-|",
			"| |                                                                   |-|",
			"|_|___________________________________________________________________| |",
			"|-|/`            l   /\\ /         ( (       \\ /\\   l                `\\|-|",
			"(@)              l /   V           \\ \\       V   \\ l                  (@)",
			"                 l/                _) )_          \\I",
			"                                   `\\ /'"
		};

		system("cls");
		printf("\n");
		Console::setColor(Console::COLOR_RED);
		for (int i = 0; i < 22; i++)
		{
			printf("           %s\n", wallpaper[i]);
		}
		Console::setCursorVisibility(false);
		Console::setColor(Console::COLOR_WHITE);
		bool printFlag = true;
		int sampahFlag = 0;
		int pickMenu = 0;
		char charMenu;
		// stats counter
		int STR = 0;
		int END = 0;
		int AGI = 0;
		int DEX = 0;
		int* stats[4] = { &STR,&END,&AGI,&DEX };
		// -------------------------------------
		int skillPoint = gain * 3;
		while (1)
		{
			if (skillPoint == 0) // kalau sudah distribute semua skillPoint nya
			{
				Console::resetColor();
				Console::setCursorPos(30, 24);
				printf("Are you sure with the current configuration? ");
				{
					int pick = 1;
					int printFlag__ = true;
					int pickDelay = 0;
					while (1)
					{
						if (printFlag__)
						{
							Console::setCursorPos(75, 24);
							if (pick == 0)Console::setColor(79);
							else Console::setColor(Console::COLOR_WHITE);
							printf("YES");

							Console::resetColor();
							printf("/");

							Console::setCursorPos(79, 24);
							if (pick == 1)Console::setColor(79);
							else Console::setColor(Console::COLOR_WHITE);
							printf("NO");

							printFlag__ = false;
						}
						char buff = Console::getKeyPressed();
						if (buff != -1)
						{
							if (pickDelay)
							{
								if (buff == 'M' || buff == 'm')
								{
									Music::playBackgroundMusic(Music::TOGGLE);
								}
								if (buff == VK_LEFT || buff == 0x41) // 41 == 'a'
								{
									pick = (pick - 1 + 2) % 2;
									printFlag__ = true;
								}
								else if (buff == VK_RIGHT || buff == 0x44) // 0x44 == 'd'
								{
									pick = (pick + 1) % 2;
									printFlag__ = true;
								}
								else if (buff == VK_RETURN)
								{
									break;
								}
								pickDelay = 0;
							}
							else pickDelay++;
						}
					}

					{ // reset tulisannya
						Console::resetColor();
						Console::setCursorPos(30, 24);
						printf("                                                          ");
					}

					if (pick == 0) // YES
					{
						break; // keluar loop, lalu level up si karakter
					}
					else // NO
					{
						// reset variable awal
						pickMenu = 0;
						printFlag = true;
						sampahFlag = 0;

						// reset skill point lagi
						{
							for (int i = 0; i < 4; i++)
							{
								*stats[i] = 0;
								Console::resetColor();
								Console::setCursorPos(49, 14 + i);
								printf("                                ");
							}
							skillPoint = gain * 3; // reset skill point remaining
							Console::setCursorPos(64, 24);
							printf("%-2d", skillPoint);
						}
						continue;
					}
				}
			}
			if (printFlag)
			{
				//Interface::setWindowSize(1000, 550);
				Console::setColor(7);
				Console::setCursorPos(5, 26);
				Console::printf("Press WSAD to select, ENTER to add 1 skill point, DELETE to remove 1 skill point, and ESC to reset");
				Console::setCursorPos(40, 24);
				Console::resetColor();
				printf("Skill Points remaining: %-2d", skillPoint);

				Console::setCursorPos(24, 14);
				if (pickMenu == 0)Console::setColor(79);
				else Console::setColor(Console::COLOR_WHITE);
				Console::printf("STRENGTH");
				Console::resetColor();
				printf(" (curr: %-2d)", karakter.getStrength());

				Console::setCursorPos(24, 15);
				if (pickMenu == 1)Console::setColor(79);
				else Console::setColor(Console::COLOR_WHITE);
				Console::printf("ENDURANCE");
				Console::resetColor();
				printf(" (curr: %-2d)", karakter.getEndurance());


				Console::setCursorPos(24, 16);
				if (pickMenu == 2)Console::setColor(79);
				else Console::setColor(Console::COLOR_WHITE);
				Console::printf("AGILITY");
				Console::resetColor();
				printf(" (curr: %-2d)", karakter.getAgility());

				Console::setCursorPos(24, 17);
				if (pickMenu == 3)Console::setColor(79);
				else Console::setColor(Console::COLOR_WHITE);
				Console::printf("DEXTERITY");
				Console::resetColor();
				printf(" (curr: %-2d)", karakter.getDexterity());

				Console::resetColor();
				for (int i = 0; i < 4; i++)
				{
					Console::setCursorPos(47, 14 + i);
					printf(":");
				}
				printFlag = false;
			}
			charMenu = Console::getKeyPressed();
			if (charMenu != -1)
			{
				if (sampahFlag) // supaya key release tidak kebaca
				{
					if (charMenu == 'M' || charMenu == 'm')
					{
						Music::playBackgroundMusic(Music::TOGGLE);
					}
					if (charMenu == VK_UP || charMenu == 0x57) // 0x57 == 'w'
					{
						pickMenu = (pickMenu - 1 + 4) % 4;
						printFlag = true;
					}
					else if (charMenu == VK_DOWN || charMenu == 0x53) // 0x53 == 's'
					{
						pickMenu = (pickMenu + 1) % 4;
						printFlag = true;
					}
					else if (charMenu == VK_BACK) // delete
					{
						if ((*stats[pickMenu]) > 0) // kurangin kalau lebih dari 0
						{
							(*stats[pickMenu]) -= 1;
							Console::setCursorPos(49 + *stats[pickMenu], 14 + pickMenu);
							Console::setColor(GREEN);
							printf(" ");


							Console::resetColor();
							Console::setCursorPos(64, 24);
							skillPoint++;
							printf("%-2d", skillPoint);
						}
					}
					else if (charMenu == VK_ESCAPE) // reset
					{
						for (int i = 0; i < 4; i++)
						{
							*stats[i] = 0;
							Console::resetColor();
							Console::setCursorPos(49, 14 + i);
							printf("                                ");
						}
						skillPoint = gain * 3; // reset skill point remaining
						Console::setCursorPos(64, 24);
						printf("%-2d", skillPoint);
					}
					else if (charMenu == VK_RETURN) // pickSKill
					{
						Console::setCursorPos(49 + *stats[pickMenu], 14 + pickMenu);
						Console::setColor(GREEN);
						printf("+");

						(*stats[pickMenu]) += 1;

						Console::resetColor();
						Console::setCursorPos(64, 24);
						skillPoint--;
						printf("%-2d", skillPoint);
					}
					int sampah = Console::getKeyPressed();
					sampahFlag = 0;
				}
				else sampahFlag++;
			}
		} // endWhile
		Console::setColor(Console::COLOR_WHITE);

		karakter.levelUp(STR, END, AGI, DEX); // naik level sekali, untuk semua stats yang diambil
		for (int i = 1; i < gain; i++)	karakter.levelUp(0, 0, 0, 0); // khusus buat naikin level doang (jika naik level lebih dari 1x)
		system("cls");
	}
	static void gameOver()
	{
		char* text[] =
		{ " _______  _______  _______  _______    _______           _______  _______ ",
			"(  ____ \\(  ___  )(       )(  ____ \\  (  ___  )|\\     /|(  ____ \\(  ____ )",
			"| (    \\/| (   ) || () () || (    \\/  | (   ) || )   ( || (    \\/| (    )|",
			"| |      | (___) || || || || (__      | |   | || |   | || (__    | (____)|",
			"| | ____ |  ___  || |(_)| ||  __)     | |   | |( (   ) )|  __)   |     __)",
			"| | \\_  )| (   ) || |   | || (        | |   | | \\ \\_/ / | (      | (\\ (   ",
			"| (___) || )   ( || )   ( || (____/\\  | (___) |  \\   /  | (____/\\| ) \\ \\__",
			"(_______)|/     \\||/     \\|(_______/  (_______)   \\_/   (_______/|/   \\__/"
		};

		system("cls");
		printf("\n\n");
		Console::setColor(RED);
		for (int i = 0; i < 8; i++)
		{
			printf("          ");
			printf("%s\n", text[i]);
			Interface::delaySec(300);
		}
		printf("\n\n");
		Console::setColor(GREY);
		Interface::delaySec(300);
		printf("                        Press enter to go back to your home...");
		Interface::pressEnterPlease();
	}
	static void gameLog(deque<string>&log)
	{
		system("cls");
		Console::setColor(Console::COLOR_CYAN);
		printf("\n  === GAME LOG ===\n\n");
		Console::resetColor();
		deque<string>::iterator iter = log.begin();
		for (; iter != log.end(); iter++)
		{
			cout << ' ' << *iter << '\n';
		}
		Console::setColor(GREY);
		printf("\n Press enter to continue...");
		Interface::pressEnterPlease();
		system("cls");
		Console::resetColor();
	}
	//////////////////////////////////////////////////////////////////// delay
	static void BattleDelay(int delay)
	{
		int delayFlag = 0;
		char buff;
		int x = 0;
		float multiplier[3] = { 1.0f,0.8f,0.5f };
		float tempDelay = delay*multiplier[index];
		while (x <= tempDelay)
		{
			Console::delay(1);
			x++;
			buff = Console::getKeyPressed();
			if (buff != -1)
			{
				if (delayFlag)
				{
					if (buff == 'M' || buff == 'm')
					{
						Music::playBackgroundMusic(Music::TOGGLE);
					}
					if (buff == VK_TAB)
					{
						index = (index + 1) % 3;
						tempDelay = delay*multiplier[index];
						printAnimationSpeed();
					}
					else if (buff == VK_ESCAPE)
					{
						autoAttack = toggleAutoAttack();
					}
					else if (buff == VK_RETURN)
					{
						//break;
					}

					delayFlag = 0;
				}
				else delayFlag++;
			}
		}

		return;
	}
	//////////////////////////////////////////////////////////////////////////
	static void printCave(bool useRestriction,int caveWidth, int caveHeight, int shiftX, int shiftY, int caveLevel, vector<Monster*>vCaveMonster, Human *karakter, int lowBound, int highBound, int levelRequirement) {
		int totalMonster;

		Console::resetColor();
		caveHeight++;
		caveWidth++;

		//printing border
		for (int height = 0; height < caveHeight; height++) {
			for (int width = 0; width < caveWidth; width++) {
				Console::setCursorPos(shiftX + width, shiftY + height);
				if (height == 0 || height == (caveHeight - 1)) {
					Console::printf("%c", 219);
				}
				else if (width == 0 || width == caveWidth - 1) {
					Console::printf("%c", 219);
				}
				else {
					printf(" ");
				}
			}
		}

		//printing stats (NOT THE ACTUAL NUMBER)
		Console::setColor(79);
		/*Console::setCursorPos(caveWidth+ shiftX + 8, shiftY);
		Console::printf("C A V E");*/
		Console::setCursorPos(caveWidth + shiftX + 1, shiftY);
		Console::printf("%s", caveName[caveLevel - 1]);

		Console::resetColor();
		Console::setCursorPos(caveWidth + shiftX + 1, shiftY + 1);
		Console::printf("LEVEL : ");
		Console::printf("%d", caveLevel);
		Console::setCursorPos(caveWidth + shiftX + 1, shiftY + 3);
		Console::printf("Gold earned       : ");
		Console::printf("%d", goldEarned);
		Console::setCursorPos(caveWidth + shiftX + 1, shiftY + 4);
		Console::printf("Exp gained        : ");
		Console::printf("%d", expGained);
		Console::setCursorPos(caveWidth + shiftX + 1, shiftY + 5);
		Console::printf("Monster(s) killed : ");
		Console::printf("%d", monsterKilled);


		totalMonster = 0;
		Console::setCursorPos(caveWidth + shiftX + 1, Console::getCursorY() + 3);
		Console::printf("Monster lurking: ");
		/*for (vector<Monster*>::iterator iter = vCaveMonster.begin(); iter != vCaveMonster.end(); iter++, totalMonster++) {
			Console::setCursorPos(caveWidth + shiftX + 1, Console::getCursorY() + 1);
			Console::printf("%d. %s",totalMonster+1, vCaveMonster[totalMonster]->getName().c_str());
		}*/
		for (totalMonster = 0; totalMonster <= (useRestriction?min(highBound - lowBound, karakter->getLevel() - levelRequirement):vCaveMonster.size()-1); totalMonster++) { // sebenernya highBound-lowBound pasti sama dengan 4. Tapi biar lu ngerti
			Console::setCursorPos(caveWidth + shiftX + 1, Console::getCursorY() + 1);
			Console::printf("%d. %s", totalMonster + 1, vCaveMonster[totalMonster]->getName().c_str());
		}
		Console::setCursorPos(caveWidth + shiftX + 1, Console::getCursorY() + 3);
		Console::printf("Press WASD to move");
		Console::setCursorPos(caveWidth + shiftX + 1, Console::getCursorY() + 1);
		Console::printf("Press ESC  to go back");

		if (karakter->getLevel() >= (levelRequirement + (caveLevel<6?5:3)) && caveLevel<7 || (!useRestriction && caveLevel<7))
		{
			Console::setCursorPos(shiftX, caveHeight + shiftY + 1);
			Console::setColor(Console::COLOR_YELLOW);
			printf("CAVE LEVEL %d UNLOCKED!", caveLevel + 1);
			Console::resetColor();
		}
	}
	static void theEnd(Human *karakter)
	{
		char dialogue[12][70]{
			"                In the end, it was a mortal heart",
			"that saved two worlds from ruin and cast down the Prime Evil forever",
			"--------------------------------------------------------------------",
			"            A new day breaks for both angels and man",
			"                For mankind's greatest champion, ",
			"",
			" rose to confront the darkness that we in our pride would not face",
			"--------------------------------------------------------------------",
			"                 Forever we shall stand together, ",
			"         angels and men, in light of this glorious new dawn",
			"--------------------------------------------------------------------",
			"    The day is won. Diablo is vanquished, and all evil with him.."
		};
		char sun[9][70] = {
			"                         AAAAAAA                          ",
			"                      AAAPPPPPPPAAA                       ",
			"                    AAPPPPPPPPPPPPPAA                     ",
			"                   APPPPPPPPPPPPPPPPPA                    ",
			"                   APPPPPPPPPPPPPPPPPA                    ",
			"                   APPPPPPPPPPPPPPPPPA                    ",
			"                    AAPPPPPPPPPPPPPAA                     ",
			"                      AAAPPPPPPPAAA                       ",
			"                         AAAAAAA                          ",
		};
		char angel[10][25] = {
			"     __/)     (\\__",
			"  ,-\'~~(   _   )~~`-.",
			" /      \\/\'_`\\/      \\",
			"|       /_(_)_\\       |",
			"|     _(/(\\_/)\\)_     |",
			"|    / // \\ / \\\\ \\    |",
			" \\  | ``  / \\ \'\'  |  /",
			"  \\  )   /   \\   (  /",
			"   )/   /     \\   \\(",
			"   \'    `-`-\'-\'    `"
		};
		Console::resetColor();
		system("cls");
		Music::playBackgroundMusic(Music::OUTRO);
		
		//printing sun
		Console::setColor(Console::COLOR_YELLOW);
		for (int sunCounter = 0; sunCounter < 9; sunCounter++) {
			//Console::printf("%s\n",sun[sunCounter]);
			Console::setCursorPos(11, Console::getCursorY()+1);
			for (int sunChar = 0; sunChar < strlen(sun[sunCounter]); sunChar++) {
				if (sun[sunCounter][sunChar] == 'A') { Console::printf("%c", '#'); }
				else if (sun[sunCounter][sunChar] == 'P') { Console::printf("%c", 219); }
				else { Console::printf(" "); }
			}
			Interface::delaySec(500);
		}

		//printing angels
		for (int angelCounter = 0; angelCounter < 10; angelCounter++) {
			Console::setCursorPos(1, angelCounter+5);
			Console::printf("%s", angel[angelCounter]);
			Console::setCursorPos(55, angelCounter + 5);
			Console::printf("%s", angel[angelCounter]);
			Interface::delaySec(100);
		}
		
		//printing dialogue
		Console::resetColor();
		for (int dialogueCounter = 0; dialogueCounter < 12; dialogueCounter++) {
			Console::setCursorPos(7, Console::getCursorY()+1);
			if (dialogueCounter == 5) {
				Console::setCursorPos(39 - (karakter->getName().length() / 2), Console::getCursorY());
				Console::setColor(13);
				for (int karChar = 0; karChar < strlen(karakter->getName().c_str()); karChar++) {
					Console::printf("%c", karakter->getName().c_str()[karChar]);
					if (karakter->getName().c_str()[karChar] == ' ') {
						Interface::delaySec(250);
					}
					Interface::delaySec(500);
				}
				Console::resetColor();
			}
			for (int dialogueChar = 0; dialogueChar < strlen(dialogue[dialogueCounter]); dialogueChar++) {
					Console::printf("%c", dialogue[dialogueCounter][dialogueChar]);
					if (dialogue[dialogueCounter][dialogueChar] == ' ') {
						Interface::delaySec(50);
					}
					else if (dialogue[dialogueCounter][dialogueChar] == '-') {
						Interface::delaySec(10);
					}
					else {
						Interface::delaySec(100);
					}
			}
		}

		Interface::delaySec(1000);
		Console::setColor(GREY);
		printf("\n");
		printf("                         Press enter to continue...");
		Interface::pressEnterPlease();

		{
			system("cls");
			char* text[] =
			{   "_________          _______    _______  _        ______  ",
				"\\__   __/|\\     /|(  ____ \\  (  ____ \\( (    /|(  __  \\ ",
				"   ) (   | )   ( || (    \\/  | (    \\/|  \\  ( || (  \\  )",
				"   | |   | (___) || (__      | (__    |   \\ | || |   ) |",
				"   | |   |  ___  ||  __)     |  __)   | (\\ \\) || |   | |",
				"   | |   | (   ) || (        | (      | | \\   || |   ) |",
				"   | |   | )   ( || (____/\\  | (____/\\| )  \\  || (__/  )",
				"   )_(   |/     \\|(_______/  (_______/|/    )_)(______/ "
			};
			printf("\n\n");
			Console::setColor(Console::COLOR_GREEN);
			for (int i = 0; i < 8; i++)
			{
				printf("                  ");
				printf("%s\n", text[i]);
				Interface::delaySec(300);
			}
			printf("\n\n");
			Console::setColor(GREY);
			Interface::delaySec(300);
			printf("                        Press enter to go back to your home...");
			Interface::pressEnterPlease();
			Console::resetColor();
		}
	}

	static void diabloStart(Human *karakter) {
		Console::resetColor();
		system("cls");
		char dragon[28][70] = {
"                                          ",
"                               //        ",
"                              /:      ,",
"                             ;.(     //",
"                   |   ,     /`|    //",
"                   |\\  |\\    |,|   //",
"                |  (\\  (\\    |`|   |(",
"                (\\  \\\\  \\\\   |,|   ;|",
"            .   ||   \\\\  \\\\  |`(   ;(",
"            \\\\   \\\\  \\\\  \\\\  |.\\\\  ((",
"             \\\\   \\\\  \\\\  \\\\  \\\\ \\;/:\\",
"               \\\\  \\\\  \\\'. \\\\_,\\\\ /\\\"\"-.",
"                \\\\  \\\\  \\ \\-\"   \\/ `;._ \".",
"               ___\\\\-\\\\-\" \\ \\_  /,  |_ \"._\\",
"         _,--\"\"___ \\ \\,_   \"-_\"- |\".|(._ \".\".-.",
"     _,-\"_,--\"\"\"__ ) \".\"-_    \"--\\ \\\"(\"o\\_\\ \"- \".",
"   ,\",-\"\"\" _.-\'\'\'_-\"   \"-_\"-.__   \\ \\_\\_//\\)__\"\\_)",
" ,\"    \',-\'  ,-\"\"   7\"  _ \"-.._\"\"_>\\__`\"\"\'\"__ \"\"``-._",
"        ;  ,\" ,-\",\'/` ,\":\\.    `   `  `\"\"\"___`\"\"-._  \".   )",
"        ;,\"_,\" ,\' /`,\"}}::\\\\         `... \\____\'\'\' \"\\  \'.|\\",
"       ,\",\"   :  /`/{{)/:::\"\\__,---._    \\  \\_____\'\'\'\\    \\",
"      , ,\"_  ;  /`/ ///::::::::\' ,-\"-\\    \\__   \\____\'\'\\ \\ \\",
"     ,,\"   `;| \";; /}}/::\'``\':::(._``.\"-.__  \"\"\"--    \'_\\ \\ \\",
"    (\'       ;// / {;;:\'`````\':; /`._.\"\"\"  \"\"-.._ `\"-. \" (   )",
"    /         )(/ <\";\"\'``   ``/ /_.(             \"_  \"-_\"\\`);",
"              (/ <\";\"``     `/ /`,(                \"._ _\".\\;",
"               |<\";\"`   ``  / /\"-\"                    \"",
"               <\";\"` ``    / /__,;"
		};
		char dialogue[5][70] = {
			"Filthy mortals.....",
			"Coming here with the thought of killing me.",
			"I, The Prime Evil shall eradicate this light",
			"All that you have ever loved shall fall with it",
			"Prepare to die "
		};

		//printing dragon
		Console::setColor(Console::COLOR_RED);
		for (int dragonText = 0; dragonText < 28; dragonText++) {
			Console::printf("%s \n", dragon[dragonText]);
		}
		//DIABLO
		Console::setCursorPos(65, 3);
		Console::setColor(12);
		Console::printf(" D I A B L O ");
		Console::resetColor();

		//printing dialogue
		Console::setCursorPos(65, 5);
		for (int dialogueText = 0; dialogueText < 5; dialogueText++) {
			Console::setCursorPos(65, Console::getCursorY()+1);
			for (int letter = 0; letter < strlen(dialogue[dialogueText]); letter++) {
				Console::printf("%c", dialogue[dialogueText][letter]);
				Interface::delaySec(50);
			}
		}

		//printing nama karakter
		Console::setCursorPos(Console::getCursorX(), Console::getCursorY());
		Console::setColor(13);
		for (int tName = 0; tName < strlen(karakter->getName().c_str()); tName++) {
			Console::printf("%c", karakter->getName().c_str()[tName]);
			Interface::delaySec(50);
		}
		Console::resetColor();
		for (int i = 0; i < 3; i++)
		{
			printf("%c", '.');
			Interface::delaySec(50);
		}

		//enter
		Console::setColor(Console::COLOR_CYAN);
		Console::setCursorPos(75, Console::getCursorY()+5);
		Console::printf("Press enter to fight DIABLO!");
		Interface::pressEnterPlease();
		Console::resetColor();
	}
public:
	// post-battle getter
	static bool getWin() { return win; }

	// MAIN FUNCTION
	static void mapPrintChar(int currX, int currY, int prevX, int prevY, int shiftX, int shiftY, int shiftKiri, int shiftKanan, char icon[][6], char* previous[])
	{
		currX -= 1; currY -= 1; prevX -= 1; prevY -= 1;
		currX -= shiftKiri;
		prevX -= shiftKiri;
		Console::resetColor();
		int xCounter = 0;
		int yCounter = 0;

		for (int i = 0; i < 3; i++)
		{
			xCounter = 0;
			for (int j = 1 - shiftKiri; j < 4 + shiftKanan; j++)
			{
				Console::setCursorPos(shiftX + prevX + xCounter, shiftY + prevY + yCounter);
				printf("%c", previous[i][j]);
				xCounter++;
			}
			yCounter++;
		}

		xCounter = 0;
		yCounter = 0;
		for (int i = 0; i < 3; i++)
		{
			xCounter = 0;
			for (int j = 1 - shiftKiri; j < 4 + shiftKanan; j++)
			{
				Console::setCursorPos(shiftX + currX + xCounter, shiftY + currY + yCounter);
				printf("%c", icon[i][j]);
				xCounter++;
			}
			yCounter++;
		}
	}

	static void foundMonster()
	{
		system("cls");
		char* background[14] =
		{
			" _    _    _    _    _    _    _    _    _    _    ",
			" \\\"-._\\\"-._\\\"-._\\\"-._\\\"-._\\\"-._\\\"-._\\\"-._\\\"-._\\\"-._",
			" \"    \"    \"    \"    \"    \"    \"    \"    \"    \"    ",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			" _    _    _    _    _    _    _    _    _    _    ",
			" \\\"-._\\\"-._\\\"-._\\\"-._\\\"-._\\\"-._\\\"-._\\\"-._\\\"-._\\\"-._",
			" \"    \"    \"    \"    \"    \"    \"    \"    \"    \"                  "
		};

		char* WILD[8] =
		{
			"                     (    (    (                      ",
			"		   (  (      )\\ ) )\\ ) )\\ )                 ",
			"           )\\))(   \'(()/((()/((()/(                 ",
			"           ((_)()\\ )  /(_))/(_))/(_)) (              ",
			"           _(())\\_)()(_)) (_)) (_))_  )              ",
			"           \\ \\((_)/ /|_ _|| |   |   \\              ",
			"            \\ \\/\\/ /  | | | |__ | |) |             ",
			"             \\_/\\_/  |___||____||___/               "
		};

		char* MONSTER[8] =
		{
			"              )      )  (                (            ",
			"    (  `    ( /(   ( /(  )\\ )  *   )      )\\ )      ",
			"    )\\))(   )\\())  )\\())(()/(` )  /( (   (()/(     ",
			"   ((_)()\\ ((_)\\  ((_)\\  /(_))( )(_)))\\   /(_))   ",
			"   (_()((_)  ((_)  _((_)(_)) (_(_())((_) (_))         ",
			"   |  \\/  | / _ \\ | \\| |/ __||_   _|| __|| _ \\    ",
			"   | |\\/| || (_) || .` |\\__ \\  | |  | _| |   /     ",
			"   |_|  |_| \\___/ |_|\\_||___/  |_|  |___||_|_\\     "
		};

		char* FOUND[8] =
		{
			"          (    (                 (        (      ",
			"   (      )\\ ) )\\ )       (      )\\ )     )\\ )    ",
			"   )\\    (()/((()/( (     )\\    (()/( (  (()/(      ",
			"((((_)(   /(_))/(_)))\\ ((((_)(   /(_)))\\  /(_))     ",
			" )\\ _ )\\ (_)) (_)) ((_) )\\ _ )\\ (_)) ((_)(_))_    ",
			" (_)_\\(_)| _ \\| _ \\| __|(_)_\\(_)| _ \\| __||   \\ ",
			"  / _ \\  |  _/|  _/| _|  / _ \\  |   /| _| | |) |    ",
			" /_/ \\_\\ |_|  |_|  |___|/_/ \\_\\ |_|_\\|___||___/  "
		};

		Console::setCursorPos(0, 4);
		Console::setCursorVisibility(false);
		Console::setColor(Console::COLOR_RED);
		for (int i = 0; i < 14; i++)
		{
			printf("               %s\n", background[i]);
		}
		{
			Console::setColor(Console::COLOR_YELLOW);
			Console::setCursorPos(0, 7);
			for (int i = 0; i < 8; i++)
			{
				if (i >= 5)Console::resetColor();
				printf("               %s\n", WILD[i]);
			}
			Interface::delaySec(700);
		}
		{
			Console::setColor(Console::COLOR_YELLOW);
			Console::setCursorPos(0, 7);
			for (int i = 0; i < 8; i++)
			{
				if (i >= 5)Console::resetColor();
				printf("               %s\n", MONSTER[i]);
			}
			Interface::delaySec(700);
		}
		{
			Console::setColor(Console::COLOR_YELLOW);
			Console::setCursorPos(0, 7);
			for (int i = 0; i < 8; i++)
			{
				if (i >= 5)Console::resetColor();
				printf("               %s\n", FOUND[i]);
			}
			Interface::delaySec(1000);
		}
	}

	static void selectCave(Human* karakter, vector<Monster>& vMonster) {
		bool useRestriction = false;

		Music::playBackgroundMusic(Music::CAVE);
		monsterKilled = 0;
		goldEarned = 0;
		expGained = 0;
		//Cave Level Selection format
		system("cls");
		Console::resetColor();
		Console::setCursorPos(15, 1);
		Console::setColor(79);
		Console::printf(" C A V E ");
		if (!useRestriction)
		{
			Console::setColor(Console::COLOR_YELLOW);
			printf("(NO RESTRICTION: ON)");
		}
		Console::resetColor();
		Console::printf("\n\n\n");

		//printing cave level detail
		int caveReq[7] = { 1,6,11,16,21,26,29 };	//level requirement
		Console::setCursorPos(1, 3);
		Console::printf("Lv. | %-23s | Lv. Req |\n", "Cave Name");
		Console::printf(" =========================================");
		for (int caveCounter = 0; caveCounter < 7; caveCounter++) {
			Console::setCursorPos(1, Console::getCursorY() + 1);
			Console::printf(" %d. | %-23s |    %2d   |", caveCounter + 1, caveName[caveCounter], caveReq[caveCounter]);
		}
		printf("\n\n");

		//asking cave level
		int caveLevel;
		bool canEnterCave;
		Console::setCursorVisibility(true);
		int x = Console::getCursorX();
		int y = Console::getCursorY();
		do {
			Console::setCursorPos(x, y);
			Console::printf(" Select level[1-7] ( 0 to go back ): ");
			caveLevel = Interface::getInt(0, 7);

			canEnterCave = false;
			if (karakter->getLevel() < caveReq[caveLevel - 1] && useRestriction)
			{
				Console::setCursorPos(x, y + 2);
				Console::setColor(Console::COLOR_RED);
				printf(" YOUR LEVEL (%d) IS NOT ENOUGH TO ENTER THIS CAVE!\n", karakter->getLevel());
				Console::setColor(Console::COLOR_YELLOW);
				printf(" Minimum requirement: LEVEL %d\n", caveReq[caveLevel - 1]);
				Console::setColor(Interface::COLOR_GREY);
				printf(" Press enter to continue..");
				Interface::pressEnterPlease();
				Console::resetColor();
				Console::setCursorPos(x + 38, y); // 39 = length dari " Select level[1-7] ( 0 to go back ): "
				printf("   ");
				Console::setCursorPos(x, y + 2);
				printf("                                                       \n");
				printf("                                    \n");
				printf("                             ");
			}
			else canEnterCave = true;
		} while (canEnterCave == false);
		if (caveLevel == 0)return;

		//initialize cave boundaries
		int lowestBoundary;	//lowest monster index in a cave
		int highestBoundary; //highest monster index in cave
		vector<Monster*> vCaveMonster; //monster yang ada di cave sekarang

		vCaveMonster.clear();
		vCaveMonster.empty();
		if (caveLevel < 6) {	//ordinary cave
			lowestBoundary = (caveLevel - 1) * 5;
			highestBoundary = (caveLevel * 5) - 1;
		}
		else if (caveLevel == 6) {	//mini boss cave
			lowestBoundary = 25;
			highestBoundary = 27;
		}
		else if (caveLevel == 7) {	//diablo's cave
			lowestBoundary = highestBoundary = 28;
		}
		//input monster to temporary vector
		for (int low = lowestBoundary; low <= highestBoundary; low++) {
			vCaveMonster.push_back(&vMonster[low]);
		}

		//first print
		Console::setCursorVisibility(false);
		int caveWidth = 30;	//max cave width
		int caveHeight = 17;	//max cave height

		int prevX, prevY;	//previous position
		int nextX, nextY;	//future position
		int currX, currY; //current position

		int shiftX = 2;
		int shiftY = 3;
		int shiftKiri = 0; // kalau ada weapon/shield
		int shiftKanan = 0;

		system("cls");
		printCave(useRestriction,caveWidth, caveHeight, shiftX, shiftY, caveLevel, vCaveMonster, karakter, lowestBoundary, highestBoundary, caveReq[caveLevel - 1]);

		currX = 2;
		currY = 2;

		int leftArm = -1;
		int rightArm = -1;
		if (karakter->getEquipStatus(Human::LeftArm))
		{
			if (karakter->getEquipment(Human::LeftArm)->getType() == Human::Shield) leftArm = Human::Shield;
			else leftArm = Human::Weapon;
		}
		if (karakter->getEquipStatus(Human::RightArm))
		{
			rightArm = Human::Weapon;
		}
		char karakterIcon[3][6] = { // 3x6
			//"  0~  ",
			//" /|\  ",
			//" / \  "
			' ',' ','0','~',' ',' ',
			' ','/','|','\\',' ',' ',
			' ','/',' ','\\',' ',' '
		};
		if (rightArm != -1)
		{
			karakterIcon[1][0] = '!';
			shiftKiri = 1;
			currX += 1;
		}
		if (leftArm != -1)
		{
			if (leftArm == Human::Shield)
			{
				karakterIcon[1][4] = '(';
				karakterIcon[1][5] = ')';
				shiftKanan = 2;
			}
			else
			{
				karakterIcon[1][4] = '!';
				shiftKanan = 1;
			}
		}
		nextX = prevX = currX;
		nextY = prevY = currY;

		char* previous[3] = {
			"       ",
			"       ",
			"       "
		};
		mapPrintChar(nextX, nextY, currX, currY, shiftX, shiftY, shiftKiri, shiftKanan, karakterIcon, previous);
		//moving
		char moveInput;	//user input
		bool canMove;	//can move or not
		int counter = 5;
		const int minStep = 5;
		while (true) {
			Console::resetColor();
			//ask input
			moveInput = _getch();
			moveInput = tolower(moveInput);
			if (moveInput == 27) {
				return;
			}
			if (moveInput == 'w' || moveInput == 'a' || moveInput == 's' || moveInput == 'd') {
				int nextY_ = nextY;
				int nextX_ = nextX;
				switch (moveInput) {
				case 'w':
					nextY = currY - 1;
					break;
				case 'a':
					nextX = currX - 1;
					break;
				case 's':
					nextY = currY + 1;
					break;
				case 'd':
					nextX = currX + 1;
					break;
				}
				if (nextX == 1 + shiftKiri || nextX == caveWidth - 1 - shiftKanan) {
					nextY = nextY_;
					nextX = nextX_;
					canMove = false;
				}
				else if (nextY == 1 || nextY == caveHeight - 1) {
					nextY = nextY_;
					nextX = nextX_;
					canMove = false;
				}
				else {
					canMove = true;
				}

				if (canMove)
				{
					//move player
					mapPrintChar(nextX, nextY, currX, currY, shiftX, shiftY, shiftKiri, shiftKanan, karakterIcon, previous);
					currX = prevX = nextX;
					currY = prevY = nextY;

					//minimum 5 step sampe bisa ketemu monster
					if (counter == 0)
					{
						//calculate chance
						int chance = rand() % 20;
						if (chance == 1) // 1/20 chance to meet monster
						{
							counter = minStep; // reset counter step jadi minStep lagi
							int caveMonsterSelect;
							//random available monster
							if ((karakter->getLevel() - 1) >= highestBoundary || !useRestriction) {
								caveMonsterSelect = rand() % vCaveMonster.size();
							}
							else {
								caveMonsterSelect = rand() % (karakter->getLevel() - lowestBoundary);
							}

							startBattle(*karakter, *(vCaveMonster[caveMonsterSelect]));
							if (win) {
								if (vCaveMonster[caveMonsterSelect]->getName() == "Diablo")
								{
									// MAKA RUN CREDIT / ENDING SCENE / APAPUN
									theEnd(karakter);
									return;
								}
								printCave(useRestriction,caveWidth, caveHeight, shiftX, shiftY, caveLevel, vCaveMonster, karakter, lowestBoundary, highestBoundary, caveReq[caveLevel - 1]);
								mapPrintChar(currX, currY, prevX, prevY, shiftX, shiftY, shiftKiri, shiftKanan, karakterIcon, previous);
								Music::playBackgroundMusic(Music::CAVE);
								continue;
							}
							else { return; } // kalau kalah
						}
					}
					else counter--;
				}
				else { continue; } // kalau gk bisa move
			} // end if
		} // end while(1)
	}

	static void selectMonster(Human* karakter, vector<Monster>& vMonster)
	{
		Music::playBackgroundMusic(Music::CAVE);
		system("cls");
		Console::setCursorPos(27, 1);
		Console::setColor(79);
		Console::printf(" M O N S T E R ");
		Console::setColor(Console::COLOR_WHITE);

		Console::setCursorPos(1, 3);
		cout << "===========================================================================";
		Console::setCursorPos(1, 4);
		printf("%-3s| %-18s| %-5s | %-8s| %-8s| %-11s | %-8s", "No.", "Name", "Level", "Offense", "Defense", "Experience", "Golds");


		int counter = 1;
		Console::setCursorPos(1, 5);
		cout << "===========================================================================";
		{
			int x = 1;
			int y = 6;
			for (vector<Monster>::iterator iter = vMonster.begin(); iter != vMonster.end(); iter++) {
				Console::setCursorPos(1, y);
				printf("%-3d| %-18s| %-5d | %-8d| %-8d| %-7.0f EXP | %-6d G", counter,
					iter->getName().c_str(), iter->getLevel(), iter->getOffense(), iter->getDefense(), iter->getExp(), iter->getGold());
				y++; counter++;
			}
			Console::setCursorPos(1, y);
			cout << "===========================================================================";
			Console::setCursorPos(1, y + 2);
		}
		counter--;
		Console::setCursorVisibility(true);
		int levelBoundary = karakter->getLevel() + 5;
		int monsterSelect;
		int y = Console::getCursorY();
		while (1)
		{
			Console::setCursorPos(1, y);
			Console::resetColor();
			cout << "Select Monster ( 0 = cancel ) [ 0 to " << counter << " ] : ";
			{
				int inputStartHere = Console::getCursorX();
				printf("                                 "); // buat hapus input sebelumnya
				Console::setCursorPos(inputStartHere, y);
			}
			monsterSelect = Interface::getInt(0, counter);
			if (monsterSelect == 0) return;
			int monsterLevel = vMonster[monsterSelect - 1].getLevel();
			
			if (monsterLevel > levelBoundary && false)
				//                                ^ gaush ada level restriction
			{
				Console::setCursorPos(1, y + 2);
				Console::setColor(Console::COLOR_RED);
				printf("MONSTER LEVEL IS WAY TO HIGH!!");
				Console::setCursorVisibility(false);
				Interface::delaySec(1000);
				Console::setCursorVisibility(true);
				Console::setCursorPos(1, y + 2);
				printf("                              ");
				continue;
			}
			else if (monsterLevel > karakter->getLevel())
			{
				Console::setCursorPos(1, y + 2);
				Console::setColor(Console::COLOR_YELLOW);
				printf("Monster level his higher than yours. Continue?");
				int x = Console::getCursorX() + 1;

				int inputDelay = 0;
				int print = 1;
				int pickMenu = 0;
				char pick;
				while (1)
				{
					if (print)
					{
						Console::setCursorPos(x, y + 2);
						if (pickMenu == 0) Console::setColor(79);
						else Console::resetColor();
						printf(" NO ");


						Console::setCursorPos(x + 5, y + 2);
						if (pickMenu == 1) Console::setColor(79);
						else Console::resetColor();
						printf(" YES ");

						Console::resetColor();
						print = 0;
					}

					pick = Console::getKeyPressed();
					if (pick != -1)
					{
						if (inputDelay)
						{
							if (pick == 'M' || pick == 'm')
							{
								Music::playBackgroundMusic(Music::TOGGLE);
							}
							if (pick == VK_LEFT || pick == 0x41) // 41 == 'a'
							{
								pickMenu = (pickMenu - 1 + 2) % 2;
								print = 1;
							}
							else if (pick == VK_RIGHT || pick == 0x44) // 0x44 == 'd'
							{
								pickMenu = (pickMenu + 1) % 2;
								print = 1;
							}
							else if (pick == VK_RETURN)
							{
								break;
							}
							inputDelay = 0;
						}
						else inputDelay++;
					}
				}

				// clear " NO  YES " dan "are you sure..."
				Console::resetColor();
				Console::setCursorPos(1, y + 2);
				printf("                                                           ");

				if (pickMenu == 0) continue;
				else break;
			}
			else break;
		}
		//
		Console::setCursorVisibility(false);
		startBattle(*karakter, vMonster[monsterSelect - 1]);
		system("cls");
		Music::playBackgroundMusic(Music::TOWN);
		return;
	}

	static void startBattle(Human& karakter, Monster& enemy)
	{
		Music::playBackgroundMusic(Music::BATTLE);
		foundMonster();
		if(enemy.getName()=="Diablo")diabloStart(&karakter);
		system("cls");
		if (rand()%20==1 && enemy.getName()!="Diablo")
		{
			Music::playBackgroundMusic(999);
			Console::setCursorPos(20, 7);
			printf("The monster flee..");
			Interface::delaySec(1500);
			system("cls");
			win = true;
			return;
		}
		Console::setCursorVisibility(false);
		Console::setCursorPos(25, 0);
		Console::setColor(79);
		printf(" B A T T L E ");
		Console::resetColor();
		autoAttack = 1;
		index = 0;
		printAnimationSpeed();
		autoAttack = toggleAutoAttack();
		hStamina = karakter.getMaxStamina();
		mStamina = enemy.getMaxStamina();
		hHP = karakter.getMaxHealth();
		mHP = enemy.getMaxHealth();
		// print box dan "vs"
		{
			printBox1(1, 1);
			printBox1(34, 1);
			printBox2();
			printBox3();
			printBox4();
			Console::setCursorPos(31, 4);
			printf("VS");
		}
		// print action
		{
			Console::setCursorPos(4, 19);
			printf("Attack");
			Console::setCursorPos(4, 20);
			printf("Rest");
			Console::setCursorPos(4, 21);
			switch (karakter.getJob())
			{
			case 1:
				printf("Coup de Grace");
				break;
			case 2:
				printf("Riposte");
				break;
			case 3:
				printf("Momentum");
				break;
			}
		}
		// print nama
		{
			stringstream temp;
			temp << karakter.getName() << " lv." << karakter.getLevel();
			string nama;
			getline(temp, nama);
			Console::setCursorPos(2, 2);
			printf(" %s", nama.c_str());
			temp.clear();
			temp << enemy.getName() << " lv." << enemy.getLevel();
			getline(temp, nama);
			Console::setCursorPos(35, 2);
			printf(" %s", nama.c_str());
		}
		//print garis
		{
			for (int i = 0; i < 27; i++)
			{
				Console::setCursorPos(2 + i, 3);
				printf("%c", ASCII_SINGLE_SEPARATOR);
				Console::setCursorPos(35 + i, 3);
				printf("%c", ASCII_SINGLE_SEPARATOR);
			}
		}
		//print HP dan STA
		{
			Console::setCursorPos(2, 4); printf(" HP");
			Console::setCursorPos(2, 5); printf(" STA");
			Console::setCursorPos(35, 4); printf(" HP");
			Console::setCursorPos(35, 5); printf(" STA");
			for (int i = 0; i < 22; i++)
			{
				Console::setColor(GREEN);
				Console::setCursorPos(7 + i, 4); printf("%c", ASCII_BOX_FULL);
				Console::setCursorPos(40 + i, 4); printf("%c", ASCII_BOX_FULL);
				Console::setColor(YELLOW);
				Console::setCursorPos(7 + i, 5); printf("%c", ASCII_BOX_FULL);
				Console::setCursorPos(40 + i, 5); printf("%c", ASCII_BOX_FULL);
			}
			Console::resetColor();
		}
		//print garis
		{
			for (int i = 0; i < 27; i++)
			{
				Console::setCursorPos(2 + i, 6);
				printf("%c", ASCII_SINGLE_SEPARATOR);
				Console::setCursorPos(35 + i, 6);
				printf("%c", ASCII_SINGLE_SEPARATOR);
			}
		}
		//print Speed Bar
		{
			Console::setColor(BLUE);
			for (int i = 0; i < 27; i++)
			{
				Console::setCursorPos(2 + i, 7);
				//printf("%c", ASCII_BOX_EMPTY);
				printf(" ");
				Console::setCursorPos(35 + i, 7);
				//printf("%c", ASCII_BOX_EMPTY);
				printf(" ");
			}
			Console::resetColor();
		}
		//print kata pengantar
		{
			Console::setCursorPos(23, 19);
			Console::resetColor();
			printf("TIPS: press TAB to change speed, WSAD");
			Console::setCursorPos(23, 20);
			printf("to choose, ESC to toggle Auto Attack");
			Console::setColor(GREY);
			Console::setCursorPos(23, 21);
			printf("Press ENTER key to continue");
			{
				int inputDelay = 0;
				while (1)
				{
					Console::resetColor();
					Console::setCursorPos(0, 9);
					char x = _getch(); // tidak ngebaca key release (hanya key press), tapi getKeyPressed iya
					if (x == 'M' || x == 'm')
					{
						Music::playBackgroundMusic(Music::TOGGLE);
					}
					if (x == VK_RETURN)
					{
						int sampah;
						while (true)
						{
							sampah = Console::getKeyPressed(); // harus pake ini, supaya getKeyPressed lainnya nggak ada masalah
							if (sampah == VK_RETURN) {
								break;
							}
						}
						break;
					}
					else if (x == VK_TAB)
					{
						// toggle speed
						index = (index + 1) % 3;
						inputDelay = 0;
						printAnimationSpeed();
					}
					else if (x == VK_ESCAPE)
					{
						// toggle autoAttack
						autoAttack = toggleAutoAttack();
					}
					printf("\b"); // backspace
				}
			}
			Console::setCursorPos(23, 21);
			Console::setColor(GREEN);
			printf("GOOD LUCK HAVE FUN           ");
			Console::resetColor();
		}
		deque <string> log; // ===========================================  PERLU DIPIKIRIN CARA KERJANYA
		log.empty();
		log.push_back("Begin Battle!");
		printLog(log);

		int turn = 0;
		int xYou = 2;
		int xEnemy = 35;
		int pickMenu = 0;
		coupDeGrace = 0;
		riposte = 0;
		momentum = 0;

		////////////////////////////////////////////////////// MAIN LOOP //////////////////////////////////////////////////////////
		while (1)
		{
			// kalau sudah menang
			if (mHP <= 0)
			{
				end(0, karakter, enemy, log);
				break;
			}
			else if (hHP <= 0)
			{
				end(1, karakter, enemy, log);
				break;
			}
			// count speed
			turn = printSpeed(xYou, karakter.getSpeed(), xEnemy, enemy.getSpeed());
			colorSpeed(turn);
			if (turn == 1) // turn karakter
			{
				if (coupDeGrace) coupDeGrace--; // ASSASSIN
				if (riposte)riposte--; // PALADIN
				if (momentum) momentum--; // BARBARIAN

				log.push_back(karakter.getName() + " turn.");
				printLog(log);
				if (autoAttack)
				{
					// =========================================== LOGIKANYA SAMA KYK MONSTER
					if (hStamina < (10 + karakter.getArmor())) rest(0, karakter, enemy, log);
					else attack(0, karakter, enemy, log);
				}
				else
				{
					while (1)
					{
						pickMenu = pickAction(karakter, pickMenu, enemy);
						if (pickMenu == 0) // attack
						{
							if (hStamina < (10 + karakter.getArmor()))
							{
								// not enough stamina to attack
								// clear box4
								{
									Console::resetColor();
									for (int i = 0; i < 3; i++)
									{
										for (int x = 0; x < 40; x++)
										{
											Console::setCursorPos(22 + x, 19 + i);
											printf(" ");
										}
									}
								}
								Console::setCursorPos(22, 19);
								printf(" You don't have enough STAMINA!");
								Console::setCursorPos(22, 20);
								printf(" Please go REST!");
								BattleDelay(1000);
								continue;
							}
							else
							{
								attack(0, karakter, enemy, log);
								break;
							}
						}
						else if (pickMenu == 1) // rest
						{
							rest(0, karakter, enemy, log);
							// ===========================================  TAMBAHIN STAMINA
							break;
						}
						else // special ability
						{
							Music::playSoundEffect(Music::SKILL);
							string text;
							switch (karakter.getJob())
							{
							case 1:
								// assassin;
								if (hStamina < 30)
								{
									// not enough stamina to use skill
									// clear box4
									{
										Console::resetColor();
										for (int i = 0; i < 3; i++)
										{
											for (int x = 0; x < 40; x++)
											{
												Console::setCursorPos(22 + x, 19 + i);
												printf(" ");
											}
										}
									}
									Console::setCursorPos(22, 19);
									printf(" You don't have enough STAMINA!");
									BattleDelay(1000);
									continue;
								}
								hStamina -= 30;
								STAchange(0, karakter, enemy);

								text = karakter.getName();
								text += " USES COUP DE GRACE!";
								log.push_back(text);
								printLog(log);
								text.clear();
								text = karakter.getName();
								text += "'s current turn skipped.";
								log.push_back(text);
								printLog(log);
								coupDeGrace = 3;
								break;
							case 2:
								if (hStamina < 30)
								{
									// not enough stamina to use skill
									// clear box4
									{
										Console::resetColor();
										for (int i = 0; i < 3; i++)
										{
											for (int x = 0; x < 40; x++)
											{
												Console::setCursorPos(22 + x, 19 + i);
												printf(" ");
											}
										}
									}
									Console::setCursorPos(22, 19);
									printf(" You don't have enough STAMINA!");
									BattleDelay(1000);
									continue;
								}
								hStamina -= 30;
								STAchange(0, karakter, enemy);

								text = karakter.getName();
								text += " USES RIPOSTE!";
								log.push_back(text);
								printLog(log);
								text.clear();
								riposte = 1;
								attack(0, karakter, enemy, log);
								break;
							case 3:
								if (hStamina < 30)
								{
									// not enough stamina to use skill
									// clear box4
									{
										Console::resetColor();
										for (int i = 0; i < 3; i++)
										{
											for (int x = 0; x < 40; x++)
											{
												Console::setCursorPos(22 + x, 19 + i);
												printf(" ");
											}
										}
									}
									Console::setCursorPos(22, 19);
									printf(" You don't have enough STAMINA!");
									BattleDelay(1000);
									continue;
								}
								hStamina -= 30;
								STAchange(0, karakter, enemy);

								text = karakter.getName();
								text += " USES MOMENTUM!";
								log.push_back(text);
								printLog(log);
								text.clear();
								text = karakter.getName();
								text += "'s current turn skipped.";
								log.push_back(text);
								printLog(log);
								momentum = 3;
								break;
							}
							break;
						}
					}
				}

				xYou = 2;
			}
			else // giliran monster
			{
				log.push_back(enemy.getName() + " turn.");
				printLog(log);
				if (riposte)
				{
					riposte--;
					string text = enemy.getName();
					text += " is still stunned!";
					log.push_back(text);
					printLog(log);
					xEnemy = 35;
					clearSpeed(turn);
					continue;
				}
				// =========================================== KALAU STAMINA MONSTER CUKUP UNTUK ATTACK, MAKA ATACK
				// =========================================== KALAU TIDAK, REST
				if (mStamina < enemy.getArmor() + 10)
				{
					// rest
					rest(1, karakter, enemy, log);
				}
				else
				{
					attack(1, karakter, enemy, log);
				}
				xEnemy = 35;
			}
			clearSpeed(turn);
		}

		if (win)
		{
			karakter.kill(); // nambahin jumlah monster yang dikill karakter sebesar 1
			bool levelUp;
			bool levelToMax = false;
			bool maxLevel = karakter.getLevel() >= 30 ? true : false;
			string text;

			int expBefore = karakter.getExperience();
			int levelBefore = karakter.getLevel();
			int expGained = (int)enemy.getExp();
			///expGained = 555000; // UBAH INI KALO MAU NGECHEAT
			int goldGained = enemy.getGold();
			int prevGold = karakter.getGold();

			text = karakter.getName();
			text += " got ";
			text += to_string((int)enemy.getExp());
			text += " EXP and ";
			text += to_string(enemy.getGold());
			text += " Gold!";
			log.push_back(text);

			karakter.setExperience((float)expGained); // tambahin exp
			karakter.setGold(goldGained); // tambahin gold
			if (maxLevel) // kalau sebelumnya sudah maxLevel
			{
				expGained = 0;
				levelUp = false;
				text.clear();
				text = karakter.getName();
				text += " already on MAX LEVEL!";
				log.push_back(text);
				printLog(log);
			}
			else if (karakter.getExperience() >= karakter.getExpRequirement(Human::MAX_LEVEL)) // kalau saat naik level menjadi MAX level
			{
				// maka level up
				expGained = karakter.getExpRequirement(Human::MAX_LEVEL) - expBefore;
				levelUp = true;
				levelToMax = true;
				text.clear();
				text = karakter.getName();
				text += " level UP to MAX!";
				log.push_back(text);
				printLog(log);
			}
			else if (karakter.getExperience() >= karakter.getExpRequirement(karakter.getLevel() + 1))
			{
				// maka level up
				levelUp = true;
				text.clear();
				text = karakter.getName();
				text += " level UP!";
				log.push_back(text);
				printLog(log);
			}
			else levelUp = false;


			//tambahin ke cave punya earnings
			Battle::expGained += expGained;
			Battle::goldEarned += goldGained;
			Battle::monsterKilled += 1;

			enemy.die();
			text.clear();
			text = enemy.getName();
			text += " level UP!";
			log.push_back(text);
			printLog(log);

			// prompt buat continue
			Console::setCursorPos(1, 23);
			Console::setColor(GREY);
			printf("Press enter to see LOG...");
			Console::resetColor();
			Interface::pressEnterPlease();
			gameLog(log);
			system("cls");

			// print XP bar and increment
			if (!maxLevel)
			{
				Console::setCursorPos(4, 9);
				printf("You get %d EXP!", expGained);
				Interface::delaySec(1000);

				printXPBox();
				Console::setCursorPos(3, 2); printf("Experience");

				//current XP
				Console::setCursorPos(14, 2); printf("%6d/%-6d", expBefore - karakter.getExpRequirement(levelBefore), karakter.getExpRequirement(levelBefore + 1) - karakter.getExpRequirement(levelBefore));
				// total ada 25 bar
				int levelCounter = 0;
				{
					int x = 0;

					int add = 0; // kalau level up berkali"
					int gain = 0;
					bool levelUp = false;
					while (1)
					{
						levelUp = false;
						if (gain == expGained) // kalau sudah sama
						{
							Console::setCursorPos(14, 2);
							if (!levelToMax) printf("%6d/%-6d", karakter.getExperience() - karakter.getExpRequirement(levelBefore + levelCounter), karakter.getExpRequirement(levelBefore + 1 + levelCounter) - karakter.getExpRequirement(levelBefore + levelCounter)); // update terus
							else printf("MAX LEVEL!!!");
							Console::setCursorPos(4, 10 + add);
							printf("Your EXP is now %d", karakter.getExperience());
							Interface::delaySec(1000);
							break; // kalau sudah dapat semua xp-nya
						}
						int expRequired = karakter.getExpRequirement(levelBefore + 1 + add) - karakter.getExpRequirement(levelBefore + add); // xp setelah - sebelum
						int box = expRequired / 25; // satu box berapa xp;
						int counter = expBefore - karakter.getExpRequirement(levelBefore + add);
						int sec = 0;
						int secondDelay = expRequired / 1000;
						//Console::setCursorPos(15, 15); printf("gain=%d,add=%d,levelBefore=%d,counter=%d,box=%d,expRequired=%d", gain, add, levelBefore, counter, box, expRequired);
						if (add == 0) // maka print BOX_FULL untuk xp sebelumnya
						{
							while (x < 25)
							{
								Console::setCursorPos(2 + (x++), 4);
								printf(" ");
							}
							x = 0;
							int counterPrint = 0;
							while (counterPrint < counter)
							{
								if (counterPrint%box == 0)
								{
									Console::setCursorPos(2 + (x++), 4);
									printf("%c", ASCII_BOX_FULL);
								}
								counterPrint++;
							}
							Interface::delaySec(500);
						}
						while ((x < 25 || counter < expRequired) && gain < expGained)
						{
							sec++;
							counter++;
							gain++;
							if (sec%secondDelay == 0)
							{
								Console::delay(1);
								Console::setCursorPos(14, 2); printf("%6d/%-6d", counter, karakter.getExpRequirement(levelBefore + 1 + add) - karakter.getExpRequirement(levelBefore + add)); // update terus
							}
							if (counter%box == 0 && x < 25)
							{
								Console::setCursorPos(2 + (x++), 4);
								printf("%c", ASCII_BOX_FULL);
							}
						}
						if (counter == karakter.getExpRequirement(levelBefore + 1 + add) - karakter.getExpRequirement(levelBefore + add)) // kalau level up
						{
							Console::setCursorPos(14, 2);
							printf("%6d/%-6d", karakter.getExpRequirement(levelBefore + 1 + add) - karakter.getExpRequirement(levelBefore + add), karakter.getExpRequirement(levelBefore + 1 + add) - karakter.getExpRequirement(levelBefore + add));

							Console::setCursorPos(4, 10 + add);
							levelCounter++;
							printf("LEVEL UP!");
							Interface::delaySec(500);
							levelUp = true;
						}
						// reset box kalau levelUp
						if (levelUp)
						{
							for (int i = 0; i < 25; i++)
							{
								Console::setCursorPos(2 + i, 4);
								printf(" ");
							}
						}

						expBefore = karakter.getExpRequirement(levelBefore + 1 + add); // set xp before ke setelah lvl up
						add++;
						x = 0;
					}
					///levelCounter = add - 1;
				}
				Console::setColor(GREY);
				Console::setCursorPos(4, 11 + levelCounter + 1); printf("Press enter to continue...");
				Interface::pressEnterPlease();
				Console::resetColor();
				if (levelCounter > 0) levelUpMenu(levelCounter, karakter);
			}

			system("cls");
			Console::setCursorPos(3, 3);
			Console::resetColor();
			printf("You gained ");
			Console::setColor(YELLOW);
			printf("%d", goldGained);
			Console::resetColor();
			printf(" gold!");

			Interface::delaySec(700);
			Console::setCursorPos(3, 5);
			printf("Your gold: ");

			int currGold = karakter.getGold();
			Console::setColor(YELLOW);
			int sec = 0;
			goldGained = max(goldGained, 1); // BUAT DIABLO (GOLDGAINED = 0)
			int secDelay = 2000 / goldGained;
			secDelay = max(secDelay, 5);
			while (prevGold < currGold)
			{
				prevGold++;
				if (sec%secDelay == 0)
				{
					Console::setCursorPos(14, 5);
					printf("%d", prevGold);
					Console::delay(1);
				}
				sec++;
			}
			Console::setCursorPos(14, 5);
			printf("%d", currGold);

			Interface::delaySec(700);
			Console::setColor(GREY);
			Console::setCursorPos(3, 7);
			printf("Press enter to continue...");
			Interface::pressEnterPlease();
		}
		else
		{
			Music::playBackgroundMusic(Music::LOSE);
			Console::setCursorPos(1, 23);
			Console::setColor(GREY);
			printf("Press enter to see LOG...");
			Console::resetColor();
			Interface::pressEnterPlease();
			gameLog(log);
			system("cls");
			gameOver();
			return;
		}
	}
};


int Battle::animationSpeed[4] = { 10000,5000,2500 }; // normal, fast, fastest
int Battle::index = 0;
int Battle::autoAttack = 0;
float Battle::hStamina = 0;
float Battle::hHP = 0;
float Battle::mStamina = 0;
float Battle::mHP = 0;
int Battle::coupDeGrace = 0;
int Battle::riposte = 0;
int Battle::momentum = 0;
bool Battle::win = false;

int Battle::monsterKilled = 0;
int Battle::expGained = 0;
int Battle::goldEarned = 0;
char Battle::caveName[7][30] = { "The Black Caverns","The Cursed Tombs","Mystical Sanctuary","Crypt of The Forgotten","Valley of the Dead","The Three Guardians", "The Crystal Arch" };
#endif