#pragma once

#ifndef BATTLE_H
#define BATTLE_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include "common.h"
#include "Game.h"
#include "Human.h"
#include "Monster.h"
#include "Interface.h"
#include <cmath>

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
	// mechanism variable
	static int animationSpeed[4];
	static int index;
	static int autoAttack;

	//human and monster attributes
	static float hStamina;
	static float mStamina;
	static float hHP;
	static float mHP;

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
		int sec = 0;
		int speed = animationSpeed[index];
		float mySpeed = speed / speedYou;
		float enemySpeed = speed / speedEnemy;
		
		int inputDelay = 1;
		while (1)
		{
			char buff = Console::getKeyPressed();
			if(buff!=-1)
			{
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
			if (sec%(int)mySpeed == 0)
			{
				Console::setCursorPos(xYou, 7);
				printf("%c", ASCII_BOX_FULL);
				xYou++;
			}
			if (sec%(int)enemySpeed == 0)
			{
				Console::setCursorPos(xEnemy, 7);
				printf("%c", ASCII_BOX_FULL);
				xEnemy++;
			}
			Console::delay(1);
			sec++;
		}

		if (xYou == 29 ) return 1;
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
			printf("%c", ASCII_BOX_EMPTY);
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
	static void printDescription(int pickMenu, Human& karakter)
	{
		// clear box4
		{
			Console::resetColor();
			for (int i = 0; i < 3; i++)
			{
				for (int x = 0; x < 40; x++)
				{
					Console::setCursorPos(22+x, 19+i);
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
			printf("Damage: %-3.0f Chance to Hit: %-3.0f%%", karakter.getDamage(),karakter.getChanceToHit());
			Console::setCursorPos(23, 21);
			printf("Critical chance: %.0f%%", max(0,karakter.getChanceToHit() - 100.0f));			
		}
		else if (pickMenu == 1) // rest
		{
			//      !                                     !
			printf("Rest to gain %.0f stamina",50.0f+karakter.getLevel());
			Console::setCursorPos(23, 20);
			printf("Armor: %-3d   Evasion: %-3.0f", karakter.getArmor(), karakter.getEvade());
			Console::setCursorPos(23, 21);
			printf("Speed: %3.0f", karakter.getSpeed());
		}
		else if (pickMenu == 3) // coup de grace
		{
			//      !                                     !
			printf("Increase Critical Hit and Evasion");
			Console::setCursorPos(23, 20);
			printf("chance by 25 %% for 2 turns.");
			Console::setCursorPos(23, 21);
			printf("Skips turn, uses NO stamina.");
		}
		else if (pickMenu == 4) // riposte
		{
			//      !                                     !
			printf("Attack enemy with 1.5x multiplier,");
			Console::setCursorPos(23, 20);
			printf("then STUN the enemy.");
			Console::setCursorPos(23, 21);
			printf("Uses 25 stamina");
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
	static int pickAction(Human& karakter, int& pickMenu)
	{
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
					printDescription(pickMenu, karakter);
				}
				else printf(" Attack ");

				Console::setCursorPos(3, 20);
				if (pickMenu == 1)
				{
					Console::setColor(79);
					printf("<Rest>");
					Console::resetColor();
					printDescription(pickMenu, karakter);
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
					printDescription(pickMenu+karakter.getJob(), karakter);
				}
				else printf(" %s ", ability.c_str());
				
				printFlag = false;
			}
			buff = Console::getKeyPressed();
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
		if (pickMenu == 2) return pickMenu + karakter.getJob();
		else return pickMenu;
	}
	static void attack(int who, Human& karakter, Monster& enemy)
	{
		if (who == 0) // turn karakter
		{
			//float damage = karakter.getDamage() - enemy.getArmor();
			HPchange(0, 30, karakter, enemy);
		}
		else // turn monster
		{
			HPchange(0, 30, karakter, enemy);
		}
	}
	static void rest(int who,Human& karakter, Monster& enemy)
	{
		if (who == 0)
		{
			STAchange(who, 50 + karakter.getLevel(),karakter,enemy);
		}
		else
		{
			STAchange(who, 50 + enemy.getLevel(),karakter,enemy);
		}
	}
	// HP dan STA change animation
	// 22 box total
	static void HPchange(int who, float change, Human& karakter, Monster& enemy)
	{
		if (who == 0) // HP MONSTER yang berkurang
		{
			if (mHP <= change)
			{
				// insta kill
				mHP == 0;
				Console::setColor(RED);
				int x = 0;
				while (x<22)
				{
					Console::setCursorPos(40 + (x++), 4);
					printf("%c", ASCII_BOX_EMPTY);
				}
				Console::delay(1000);
				Console::resetColor();
			}
			else
			{
				float box = enemy.getMaxHealth() / 22.0f;
				mHP -= change;

				if (mHP > enemy.getMaxHealth()*0.5) Console::setColor(GREEN);
				else if (mHP < enemy.getMaxHealth()*0.20)Console::setColor(RED);
				else Console::setColor(YELLOW);

				float counter = 0;
				int x = 0;
				while (x<22 && counter<=mHP)
				{
					Console::setCursorPos(40+(x++), 4);
					printf("%c", ASCII_BOX_FULL);
					counter += box;
				}
				while (x < 22)
				{
					Console::setCursorPos(40 + (x++), 4);
					printf("%c", ASCII_BOX_EMPTY);
				}
				Console::delay(1000);
			}
		}
		else
		{
			if (hHP <= change)
			{
				// insta kill
				hHP == 0;
				Console::setColor(RED);
				int x = 0;
				while (x<22)
				{
					Console::setCursorPos(40 + (x++), 4);
					printf("%c", ASCII_BOX_EMPTY);
				}
				Console::delay(1000);
				Console::resetColor();
			}
			else
			{
				float box = karakter.getMaxHealth() / 22.0f;
				hHP -= change;

				if (hHP > karakter.getMaxHealth()*0.5) Console::setColor(GREEN);
				else if (hHP < karakter.getMaxHealth()*0.20)Console::setColor(RED);
				else Console::setColor(YELLOW);

				float counter = 0;
				int x = 0;
				while (x<22 && counter <= hHP)
				{
					Console::setCursorPos(7 + (x++), 4);
					printf("%c", ASCII_BOX_FULL);
					counter += box;
				}
				while (x < 22)
				{
					Console::setCursorPos(7 + (x++), 4);
					printf("%c", ASCII_BOX_EMPTY);
				}
				Console::delay(1000);
			}
		}
	}
	static void STAchange(int who, float change, Human& karakter, Monster& enemy)
	{
		if (who == 0) // STA karakter yang bertambah
		{
		}
		else
		{
		}
	}

public:
	static void startBattle(Human& karakter, Monster& enemy)
	{
		system("cls");
		Console::setCursorPos(32, 0);
		Console::resetColor();
		printf("BATTLE\n");
		printAnimationSpeed();
		autoAttack = 1;
		index = 0;
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
			temp << karakter.getName()  << " lv." << karakter.getLevel();
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
			Console::setCursorPos(2, 4); printf("HP");
			Console::setCursorPos(2, 5); printf("STA");
			Console::setCursorPos(35, 4); printf("HP");
			Console::setCursorPos(35, 5); printf("STA");
			for (int i = 0; i < 22; i++)
			{
				Console::setColor(GREEN);
				Console::setCursorPos(7+i, 4); printf("%c",ASCII_BOX_FULL);
				Console::setCursorPos(40 + i, 4); printf("%c", ASCII_BOX_FULL);
				Console::setColor(YELLOW);
				Console::setCursorPos(7+i, 5); printf("%c", ASCII_BOX_FULL);
				Console::setCursorPos(40+i, 5); printf("%c", ASCII_BOX_FULL);
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
				Console::setCursorPos(2+i, 7);
				printf("%c", ASCII_BOX_EMPTY);
				Console::setCursorPos(35+i, 7);
				printf("%c", ASCII_BOX_EMPTY);
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
		queue <string> log; // ===========================================  PERLU DIPIKIRIN CARA KERJANYA
		log.empty();
		string text = "Begin Battle!";
		log.push(text);

		int turn = 0;
		int xYou = 2;
		int xEnemy = 35;
		int pickMenu = 0;
		while (1)
		{
			// count speed
			turn = printSpeed(xYou, karakter.getSpeed(), xEnemy, enemy.getSpeed());
			colorSpeed(turn);
			if (turn == 1) // turn karakter
			{
				if (autoAttack)
				{
					// =========================================== LOGIKANYA SAMA KYK MONSTER
				}
				else
				{
					while (1)
					{
						pickMenu = pickAction(karakter, pickMenu);
						if (pickMenu == 0) // attack
						{
							if (hStamina < (10 + karakter.getArmor()))
							{
								// not enough stamina to attack
								// =========================================== TAMBAHIN PROMPT UNTUK REST
								continue;
							}
							else
							{
								attack(0, karakter, enemy);
								// NTAR KURANGIN STAMINA
								break;
							}
						}
						else if (pickMenu == 1) // rest
						{
							rest(0, karakter, enemy);
							// ===========================================  TAMBAHIN STAMINA
							break;
						}
						else // special ability
						{
							break;
						}
					}
				}

				xYou = 2;
			}
			else
			{
				// =========================================== KALAU STAMINA MONSTER CUKUP UNTUK ATTACK, MAKA ATACK
				// =========================================== KALAU TIDAK, REST

				xEnemy = 35;
			}
			clearSpeed(turn);
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

#endif