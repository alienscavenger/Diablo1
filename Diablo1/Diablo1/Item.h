#pragma once

#ifndef ITEM_H
#define ITEM_H

#include <cstring>

class Item // bisa weapon, armor, atau apapun
{
private:
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
	int restriction;
	int eguipped; // 1 = true, 0 = false
	int bought; // 1 = true, 0 = false
	/* 
	   type 0 = pendant
	   type 1 = helmet
	   type 2 = gloves
	   type 3 = chest
	   type 4 = boots
	   type 5 = weapon
	   type 6 = shield

	   restriction 0 = no restriction
	   restriction 1 = assassin
	   restriction 2 = paladin
	   restriction 3 = barbarian
	*/

public:
	//constructor (gaada default constructor)
	Item(char* name, int str, int end, int agi, int dex, int dmg, int cth, int eva, int spd, int mhp, int mst, int amr,int type,int restriction, int eguipped, int bought)
	{
		strcpy(this->name, name); // KALAU PAKE VS15 / VS17, JANGAN LUPA PAKE _CRT_SECURE_NO_WARNIGNS (CARI DI INTERNET)
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
		this->restriction = restriction;
		this->eguipped = eguipped;
		this->bought = bought;
	}

	//getter
	const char* getName() const { return name; }
	int getStrength() const { return strength; }
	int getEndurance() const { return endurance; }
	int getAgility() const { return agility; }
	int getDexterity() const { return dexterity; }
	int getDamage() const { return damage; }
	int getChanceToHit() const { return chanceToHit; }
	int getEvade() const { return evade; }
	int getSpeed() const { return speed; }
	int getMaxHealth() const { return maxHealth; }
	int getMaxStamina() const { return maxStamina; }
	int getArmor() const { return armor; }
	int getType() const { return type; }
	int getRestriction() const { return restriction; }
	int getEguipped() const { return eguipped; }
	int getBought() const { return bought; }

	//setter buat bought
	void setBought(int ok)
	{
		bought = ok;
	}
	//setter buat eguipped
	void setEguip(int ok)
	{
		eguipped = ok;
	}

	//setter kalo mau ada kyk "upgrade weapon" dsb, tapi itu nanti aja
};


#endif