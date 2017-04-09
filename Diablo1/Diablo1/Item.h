#pragma once

#ifndef ITEM_H
#define ITEM_H

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

#include "Base.h"
#include "Human.h"

class Item // bisa weapon, armor, atau apapun
{
private:
	///masa gk ada nama
	char name[50];
	
	int strength;
	int endurance;
	int agility;
	int dexterity;
	int damage;
	int chanceToHit;
	int evade;
	int speed;
	int maxHealth;
	int maxStamina;
	int armor;
	int type;
	/* 
	   type 1 = helmet
	   type 2 = gloves
	   type 3 = chest
	   type 4 = boots
	   type 5 = weapon
	   type 6 = shield
	*/
public:
	//constructor (gaada default constructor)
	Item(int str, int end, int agi, int dex, int dmg, int cth, int eva, int spd, int mhp, int mst, int amr,int type)
	{
		strength = str;
		endurance = end;
		agility = agi;
		dexterity = dex;
		damage = dmg;
		chanceToHit = cth;
		evade = eva;
		speed = spd;
		maxHealth = mhp;
		maxStamina = mst;
		armor = amr;
		this->type = type;
	}

	//getter
	int getStrength() { return strength; }
	int getEndurance() { return endurance; }
	int getAgility() { return agility; }
	int getDexterity() { return dexterity; }
	int getDamage() { return damage; }
	int getChanceToHit() { return chanceToHit; }
	int getEvade() { return evade; }
	int getSpeed() { return speed; }
	int getMaxHealth() { return maxHealth; }
	int getMaxStamina() { return maxStamina; }
	int getArmor() { return armor; }
	int getType() { return type; }
};


#endif