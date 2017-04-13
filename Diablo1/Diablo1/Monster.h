#pragma once

#ifndef MONSTER_H
#define MONSTER_H

#include "Base.h"
#include "Human.h"
#include <cmath>

using namespace std;

class Monster : public Base
{
	// class Monster memiliki vector/array nya sendiri dalam class Main ( vector <Monster> vMonster ), karena experience dan gold dari monster
	// merupakan variabel yang dinamis (berganti", yaitu saat mati, berkurang setengahnya). Makanya itu perlu di-save.
private:
	// offense dan defense hanyalah jumlah bintang yang dimiliki oleh monster tersebut (1-10)
	int offense;
	int defense;
	int gold; // ini sama exp adalah rewardnya
	float exp; // float supaya bisa nambah berdasarkan persentase

public:
	// constructor untuk Monster
	Monster(string name, float dmg, float cth, float eva, float spd, float mhp, float mst, int amr, int lvl, int gold,float exp, int off, int def)
	{
		this->name = name;
		damage = dmg;
		chanceToHit = cth;
		evade = eva;
		speed = spd;
		maxHealth = mhp;
		maxStamina = mst;
		armor = amr;
		level = lvl; // level monster akan menentukan di cave level berapa monsternya akan muncul
		this->gold = gold;
		this->exp = exp;
		offense = off;
		defense = def;
	}
	int getOffense() const { return offense; }
	int getDefense() const { return defense; }
	int getGold() const { return gold; }
	int getExp() const { return exp; }

	// setiap kali monster dibunuh:
	void killed()
	{
		level += 1;
		exp = exp*1.25f;
		// cth tambah 4 persen setial level up
		chanceToHit = chanceToHit + 4; 
		// sisanya nambah 10 persen setiap level up
		damage = ceil(damage*1.1f);
		evade = ceil(evade*1.1f);
		speed = ceil(speed*1.1f);
		maxHealth = ceil(maxHealth*1.1f);
		maxStamina = ceil(maxStamina*1.1f);
	}
};

#endif