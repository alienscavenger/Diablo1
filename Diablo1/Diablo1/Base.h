#pragma once // compiler specific (sama kyk ifndef dsb)

#ifndef BASE_H
#define BASE_H

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

class Base
{
protected:
	int damage;
	int chanceToHit;
	int evade;
	int speed;
	int maxHealth;
	int maxStamina;
	int armor;

public:
	//getter
	int getDamage() { return damage; }
	int getChanceToHit() { return chanceToHit; }
	int getEvade() { return evade; }
	int getSpeed() { return speed; }
	int getMaxHealth() { return maxHealth; }
	int getMaxStamina() { return maxStamina; }
	int getArmor() { return armor; }
};

#endif