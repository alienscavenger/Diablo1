#pragma once

#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item // bisa weapon, armor, atau apapun
{
private:
	string name;
	int price;
	int strength;
	int endurance;
	int agility;
	int dexterity;
	float damage;
	float chanceToHit;
	float evade;
	float speed;
	float maxHealth;
	float maxStamina;
	int armor;
	int type;
	int restriction;
	int eguipped; // 1 = true, 0 = false
	int bought; // 1 = true, 0 = false
	/* 
	   type 0 = pendant(?)
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
	Item(string name, int price, int str, int end, int agi, int dex, float dmg, float cth, float eva, float spd, float mhp, float mst,
		 int amr,int type,int restriction, int eguipped, int bought)
	{
		this->name = name; // KALAU PAKE VS15 / VS17, JANGAN LUPA PAKE _CRT_SECURE_NO_WARNINGS (CARI DI INTERNET)
		this->price = price;
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
	string getName() const { return name; }
	int getPrice() const { return price; }
	int getStrength() const { return strength; }
	int getEndurance() const { return endurance; }
	int getAgility() const { return agility; }
	int getDexterity() const { return dexterity; }
	float getDamage() const { return damage; }
	float getChanceToHit() const { return chanceToHit; }
	float getEvade() const { return evade; }
	float getSpeed() const { return speed; }
	float getMaxHealth() const { return maxHealth; }
	float getMaxStamina() const { return maxStamina; }
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