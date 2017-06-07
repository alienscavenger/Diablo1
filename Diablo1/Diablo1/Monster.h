#pragma once

#ifndef MONSTER_H
#define MONSTER_H

#include "Base.h"
#include <string>
#include <cmath>

using namespace std;

class Monster : public Base
{
	// class Monster memiliki vector/array nya sendiri dalam class Main ( vector <Monster> vMonster ), karena experience dan gold dari monster
	// merupakan variabel yang dinamis (berganti", yaitu saat mati, berkurang setengahnya). Makanya itu perlu di-save.
private:
	// offense dan defense hanyalah jumlah bintang yang dimiliki oleh monster tersebut (ceil(offense/20) atau ceil(defense/20))
	int killed; // berapa banyak di-kill
	int offense;
	int defense;
	int gold; // ini sama exp adalah rewardnya
	float exp; // float supaya bisa nambah berdasarkan persentase

public:
	static int const MAX_MONSTER = 60;

	// constructor untuk Monster
	Monster(string name, int lvl, int gold, float dmg, float cth, float eva, float spd, float mhp, float mst, int amr,float exp, int off, int def, int kill)
	{
		killed = kill;
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
	int getKilled() const { return killed; }
	int getOffense() const { return offense; }
	int getDefense() const { return defense; }
	int getGold() const { return gold; }
	float getExp() const { return exp; }

	// setiap kali monster dibunuh:
	void die()
	{
		this->killed += 1;
		level += 1;
		// exp nambah 25%
		exp = ceil(exp*1.25f);
		// gold nambah 20%
		gold = (int)ceil(gold*1.2);
		// cth tambah 4 persen flat setial level up
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