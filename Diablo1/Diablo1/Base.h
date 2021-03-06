#pragma once // compiler specific (sama kyk ifndef dsb)

#ifndef BASE_H
#define BASE_H

#include <string>

using namespace std;

class Base
{
protected:
	// semua yang secondary stats, kecuali armor, adalah floating point
	float damage;
	float chanceToHit;
	float evade;
	float speed;
	float maxHealth;
	float maxStamina;
	int armor;
	int level;
	string name;

public:
	//getter
	float getDamage() const { return damage; }
	float getChanceToHit() const { return chanceToHit; }
	float getEvade() const { return evade; }
	float getSpeed() const { return speed; }
	float getMaxHealth() const { return maxHealth; }
	float getMaxStamina() const { return maxStamina; }
	int getArmor() const { return armor; }
	int getLevel() const { return level; }
	string getName() const { return name; }
};

#endif