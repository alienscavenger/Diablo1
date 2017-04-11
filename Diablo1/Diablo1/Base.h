#pragma once // compiler specific (sama kyk ifndef dsb)

#ifndef BASE_H
#define BASE_H

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
	int level;
	char name[50];

public:
	//getter
	int getDamage() const { return damage; }
	int getChanceToHit() const { return chanceToHit; }
	int getEvade() const { return evade; }
	int getSpeed() const { return speed; }
	int getMaxHealth() const { return maxHealth; }
	int getMaxStamina() const { return maxStamina; }
	int getArmor() const { return armor; }
	int getLevel() const { return level; }
	const char* getName() const { return name; }
};

#endif