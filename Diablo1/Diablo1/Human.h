#pragma once

#ifndef HUMAN_H
#define HUMAN_H

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
#include "Item.h"

class Human : public Base
{
private:
	int strength;
	int endurance;
	int agility;
	int dexterity;
	vector <Item> eguipped; // yang lagi di-eguip
	vector <Item> inventory; // yang ada di inventory (exclude eguipped)

public:
	//constructor
	Human(int pilihanJob)
	{
		setPrimary(pilihanJob);

	}

	//getter
	int getStrength() { return strength; }
	int getEndurance() { return endurance; }
	int getAgility() { return agility; }
	int getDexterity() { return dexterity; }

	//setter all primary and secondary berdasarkan item equipment
	/// mungkin bakal gw ganti jadi "eguipItem" dan "removeItem", trus pake push_back dan delete-nya vector. Tapi blom kepikiran, ntar gw coba lagi
	void setAttributesItem(int str, int end, int agi, int dex, int dmg, int cth, int eva, int spd, int mhp, int mst, int amr)
	{
		//primary attributes
		strength += str;
		endurance += end;
		agility += agi;
		dexterity += dex;
		//secondary attributes
		damage += dmg;
		chanceToHit += cth+(2*dex);
		evade += eva + (2*agi);
		speed += spd + (5*agi) + (3*dex);
		maxHealth += mhp + (5 * str) + (10 * end);
		maxStamina += mst + (3 * str) + (10 * end) + (2 * dex);
		armor += amr;
	}

	//untuk masukin primary saat mulai game pilih job (membuat character)
	void setPrimary(int pilihanJob)
	{ // 1<= pilihanJob <=3
		switch (pilihanJob) {
		case 1: //Assassin
			strength = 7;
			endurance = 7;
			agility = 13;
			dexterity = 12;
			break;
		case 2: //Paladin
			strength = 14;
			endurance = 12;
			agility = 6;
			dexterity = 8;
			break;
		case 3: //Barbarian
			strength = 13;
			endurance = 15;
			agility = 5;
			dexterity = 6;
			break;
		}
		// set seconday saat membuat character
		setSecondary(strength,endurance,agility,dexterity);
	}

	//set Secondary berdasarkan Primary
	void setSecondary(int str, int end, int agi, int dex)
	{
		damage = 3;
		chanceToHit = 80 + (2 * dex);
		evade = (2 * agi);
		speed = 100 + (5 * agi) + (3 * dex);
		maxHealth = (5 * str) + (10 * end);
		maxStamina = (3 * str) + (10 * end) + (2 * dex);
		armor = 0;
	}

	//Ini fungsi untuk set primary saat level up
	void levelUp(int strength, int endurance, int agility, int dexterity)
	{
		this->strength += strength;
		this->endurance += endurance;
		this->agility += agility;
		this->dexterity += dexterity;
	}

};

#endif // !HUMAN_H
