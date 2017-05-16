#pragma once

#ifndef HUMAN_H
#define HUMAN_H

#include "Base.h"
#include "Item.h"
#include "common.h"
#include <vector>
#include <string>
#define EQUIPMENT_SLOT 7
#define MAX_LEVEL 31
using namespace std;

class Human : public Base
{
private:
	int strength;
	int endurance;
	int agility;
	int dexterity;
	int gold;
	int experience;
	static int expRequirement[MAX_LEVEL]; // misalnya, expRequirement[2] = 1000, artinya, untuk level up ke 2, player memerlukan exp >= 1000 (di-initialize di bawah)
	int job;
	int monsterKilled;

	//untuk masukin primary saat mulai game pilih job (membuat character)
	void setPrimary(int pilihanJob) // 1<= pilihanJob <=3
	{
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
	}

	//set Secondary berdasarkan Primary
	void setSecondary(int str, int end, int agi, int dex)
	{
		damage = 3;
		chanceToHit = 80 + (2 * (float)dex);
		evade = (2 * (float)agi);
		speed = 100 + (5 * (float)agi) + (3 * (float)dex);
		maxHealth = (5 * (float)str) + (10 * (float)end);
		maxStamina = (3 * (float)str) + (10 * (float)end) + (2 * (float)dex);
		armor = 0;
	}


	//setter all primary and secondary berdasarkan item equipment (dipakai buat equip dan unequip item)
	void setAttributesItem(int str, int end, int agi, int dex, float dmg, float cth, float eva, float spd, float mhp, float mst, int amr)
	{
		//primary attributes
		strength += str;
		endurance += end;
		agility += agi;
		dexterity += dex;
		//secondary attributes
		damage += dmg;
		chanceToHit += cth + (2 * dex);
		evade += eva + (2 * agi);
		speed += spd + (5 * agi) + (3 * dex);
		maxHealth += mhp + (5 * str) + (10 * end);
		maxStamina += mst + (3 * str) + (10 * end) + (2 * dex);
		armor += amr;
	}

	/*
		Jadi gini cara kerja untuk inventory (beda New Game dan Load Game hanya pada actual parameternya saja):

			1. Di Main class, akan ada fungsi yang baca file untuk semua item yang ada di game.
			   (including yang di equip dan tidak) (save cuman 1 file kalo bisa) (read terjadi saat load game)

			2. Saat load game, semua informasi item yang dibaca akan dimasukkan ke dalam sebuah vector<Item> yang di-declare
			   di dalam class Main, bernama vShop. Vector ini tidak akan dapat berubah", jadi tidak usah khawatir akan
			   pointer invalidation. Nanti di file save-nya bakal ada variable yang menentukan sudah dibeli apa belum,
			   atau mungkin ada seperti pembatas saat membaca filenya (supaya tau ini item berada pada section apa gitu").

			3. Class Human mempunyai sebuah vector yang berisi pointer to Item object. Saat objek Human di-construct,
			   vector vShop (yang berisi semua item yang ada di game) akan di-pass by reference ke ctor Human, dan di
			   ctor Human sendiri lah yang akan mengecek apakah elemen (item) di vector vShop tersebut sudah dibeli atau
			   belum.

			4. Semua yang sudah kita beli akan berada di vector vInventory Human, berupa pointer to Item. Dan yang kita
			   equip berupa sebuah array of pointer to Item. Hanya perlu 7, karena hanya ada 7 tipe item (termasuk pendant,
			   yang sebenernya ditambahin biar ada tipe ke 0, alias index ke-0)

			5. Intinya, vShop tidak akan/dapat diubah oleh class Human, dan vInventory serta equipment hanyalah sebuah pointer
			   to const object, si vShop itu sendiri.

			6. vShop berisi semua item yang ada dalam game, entah itu unequipped item, equipped item, secret item, dsb.

			7. Kalau mau beli item, tinggal ganti status bought di vector vShop jadi true pake setBought, lalu di push_back
			   ke vector vInventory.

			8. Kalau mau menjual item, cek dulu apakah item di vector vInventory sedang di-equip atau tidak. Kita hanya bisa
			   menjual item yang sedang tidak di-equip

			9. Untuk menjual item, tinggal saja vInventory.erase(vInventory.begin() + index). Index ditentukan dari Main class aja.

			10. Untuk unequip item, tinggal set equipStatus[index] ke false, dan set equipment[index] ke NULL;

			11. Untuk equip item, validasi dilakukan di main Class dengan mengecek apakah equipStatus[index] false. Kalau true, break;
				kalau false, maka set ke true, set equipment[index] menjadi pointer ke Item tersebut, dan setEquipped(true) pada item tersebut.

			12. Setiap equip dan unequip, jangan lupa di-update attribute Humannya dengan setAttributesItem
	*/
	vector <Item*> vInventory; // yang ada di inventory (termasuk yang sudah di-equip)
	size_t nInventory; // jumlah barang yang ada di inventory

	bool equipStatus[EQUIPMENT_SLOT]; // true kalau item type ke-index (sesuai type di Item.h) sudah di-equip, false kalau belum
	Item* equipment[EQUIPMENT_SLOT]; // yang sekarang sedang dipakai (penggunaan index sama dengan equipStatus)
	/*
		index 1 = helmet(type 1)
		index 2 = weapon&shield(type 5 dan type 6)
		index 3 = weapon(type 5)
		index 4 = gloves(type 2)
		index 5 = armor(type 3)
		index 6 = boots(type 4)

	*/
	void checkInventory(vector<Item>&fileRead)
	{
		int i = 0;
		for (vector<Item>::iterator iter = fileRead.begin(); iter != fileRead.end(); iter++, i++)
		{
			if (iter->getBought()) // kalau sudah dibeli, masukin ke vInventory
			{
				vInventory.push_back(&(*iter)); // ngambil alamat dari objek Item, dimana Item tersebut terdapat dalam vector vShop
			}
		}
		nInventory = vInventory.size();
	}


	// MINOR WEAKNESS: LOKASI KIRI/KANAN WEAPON (KALAU 2-2NYA WEAPON YANG DIEQUIP) TIDAK AKAN KETAHUAN
	void checkEquipped() // cek apakah yang ada di vInventory sudah di-equip atau belom
	{
		// initialize
		for (int i = 0; i < EQUIPMENT_SLOT; i++)
		{
			equipStatus[i] = false; // awalnya set equipped ke false dulu (character tidak wear apa")
			equipment[i] = NULL; // awalnya tidak menunjuk ke apa"
		}
		
		bool weaponEquipped = false; // awalnya belom ada weapon yang di-equip
		for (vector<Item*>::iterator iter = vInventory.begin(); iter != vInventory.end(); iter++)
		{
			// kalau sudah di-equip
			if ((*iter)->getEquipped()) // *iter = value dari vInventory = pointer to Item. jadi perlu di-dereference 2x
			{
				int index;
				switch ((*iter)->getType())
				{
				case 1:
					index = 1;
					break;
				case 2:
					index = 4;
					break;
				case 3:
					index = 5;
					break;
				case 4:
					index = 6;
					break;
				case 5:
				{
					if (weaponEquipped) { index = 2; } // kalau sudah ada weapon yang di-equipped, maka pindahin ke tangan kiri
					else { index = 3; weaponEquipped = true; } // tangan kanan di-prioritas
					break;
				}
					break;
				case 6:
					index = 2;
					break;
				}
				equipment[index] = *iter; // valuenya adalah pointer dari iter, yakni value dari vInventory, yakni pointer to objek Item
				equipStatus[index] = true; // artinya sekarang sudah ada yang di-equip
			}
		}
	}

public:
	//constructor buat new Game
	// walaupun cuman new Game, vInventory dan equipment juga perlu di-initialize
	Human(vector <Item>& fileRead,int pilihanJob,string name)
	{
		vInventory.reserve(110); // jadi ada maksimal 110 item di inventory
		monsterKilled = 0;
		level = 1;
		gold = 2000000;
		experience = 0;
		this->name = name;
		job = pilihanJob;
		setPrimary(pilihanJob); // set primary pertama kali saat membuat character
		setSecondary(strength, endurance, agility, dexterity); // set seconday pertama kali saat membuat character

		checkEquipped(); // fungsi yang digunakan dari method ini hanya buat initialize equipStatus dan equipment jadi false
						 // semua dan NULL semua, secara berurutan
		nInventory = vInventory.size(); // harusnya sama dengan 0 (nol)
	}

	//constructor buat load Game
	Human(vector <Item>& fileRead,string name, int lvl,  int pilihanJob, int gold,int exp, int str, int end, int agi,
		  int dex, float dmg, float cth, float eva, float spd, float mhp, float mst, int amr, int kill)
	{
		monsterKilled = kill;
		this->name = name;
		level = lvl;
		job = pilihanJob;
		this->gold = gold;
		experience = exp;
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

		vInventory.reserve(110);
		checkInventory(fileRead); // filter yang sudah di-bought
		checkEquipped(); // filter yang sedang di-equip
		nInventory = vInventory.size(); // update jumlah barang di inventory
	}

	//copy constructor
	Human(const Human& k)
	{
		agility = k.getAgility();
		dexterity = k.getDexterity();
		endurance = k.getEndurance();
		for (int i = 0; i < EQUIPMENT_SLOT; i++)
		{
			equipment[i] = k.getEquipment(i);
			equipStatus[i] = k.getEquipStatus(i);
		}
		armor = k.getArmor();
		chanceToHit = k.getChanceToHit();
		damage = k.getDamage();
		evade = k.getEvade();
		level = k.getLevel();
		maxHealth = k.getMaxHealth();
		maxStamina = k.getMaxStamina();
		name = k.getName();
		speed = k.getSpeed();

		experience = k.getExperience();
		gold = k.getGold();
		job = k.getJob();
		monsterKilled = k.getMonsterKilled();
		nInventory = k.getNumInventory();
		strength = k.getStrength();
		vInventory.reserve(110);
		vInventory.clear();
		vInventory = k.getInventory();

	}

	//getter baru (tidak ada pada Base.h)
	int getMonsterKilled() const { return monsterKilled; }
	int getStrength() const { return strength; }
	int getEndurance() const { return endurance; }
	int getAgility() const { return agility; }
	int getDexterity() const { return dexterity; }
	int getJob() const { return job; }
	int getGold() const { return gold; }
	int getExperience() const { return experience; }
	static int getExpRequirement(int index) { return expRequirement[index]; }

	vector <Item*> getInventory() const { return vInventory; }
	vector <Item*>& getInventoryRef() { return vInventory; }
	size_t getNumInventory() const { return nInventory; }
	bool getEquipStatus(int index) const { return equipStatus[index]; }
	Item* getEquipment(int index) const { return equipment[index]; }

	//Ini fungsi untuk set primary saat level up
	void levelUp(int strength, int endurance, int agility, int dexterity)
	{
		this->level++;
		this->strength += strength;
		this->endurance += endurance;
		this->agility += agility;
		this->dexterity += dexterity;
	}
	
	// ini fungsi buat nambahin monster yang dikill
	void kill()
	{
		this->monsterKilled += 1;
	}

	void buyItem(Item* pointer)
	{
		pointer->setBought(1); // set true
		vInventory.push_back(pointer);
		nInventory = vInventory.size(); // update nInventory
	}
	void sellItem(Item* pointer)
	{
		pointer->setBought(0); // set false
		vector<Item*>::iterator iter;
		for (iter = vInventory.begin(); iter != vInventory.end(); iter++)
		{
			if (*iter == pointer) break; // *iter adalah value dari vInventory = pointer ke sebuah objek Item
		}
		vInventory.erase(iter); // iter adalah sebuah pointer ke vInventory, dan pointernya adalah pointer ke objek Item yang dituju
		nInventory = vInventory.size(); // update nInventory
	}
	void unequipItem(int index)
	{
		Item* pointer = this->equipment[index];
		pointer->setEquip(0); // set status equipped di Item menjadi false
		equipStatus[index] = false; // set status equipped di Human menjadi false
		equipment[index] = NULL; // equipment[index] di-unequip
		setAttributesItem(-1 * (pointer->getStrength()), -1 * (pointer->getEndurance()), -1 * (pointer->getAgility()), -1 * (pointer->getDexterity()),
						-1 * (pointer->getDamage()), -1 * (pointer->getChanceToHit()), -1 * (pointer->getEvade()), -1 * (pointer->getSpeed()),
						-1 * (pointer->getMaxHealth()), -1 * (pointer->getMaxStamina()), -1 * (pointer->getArmor)());
	}
	void equipItem(int index,Item* pointer)
	{
		pointer->setEquip(1); // set true
		equipStatus[index] = true;
		equipment[index] = pointer;
		setAttributesItem(pointer->getStrength(), pointer->getEndurance(), pointer->getAgility(), pointer->getDexterity(),
							pointer->getDamage(), pointer->getChanceToHit(), pointer->getEvade(), pointer->getSpeed(),
							pointer->getMaxHealth(), pointer->getMaxStamina(), pointer->getArmor());
	}
	void setExperience(float exp)
	{
		experience += (int)exp;
	}

	//setter gold
	void setGold(int amount)
	{
		gold += amount;
		return;
	}
};

int Human::expRequirement[31] = {
	0,0,1000,5000,10000,15000,20000,25000,30000,40000,50000,65000,80000,95000,110000,125000,140000,160000,180000,200000,220000,240000,260000,280000,300000,330000,360000,390000,420000,450000,500000
}; //    ^lv2											^lv10															^lv20																	^lv30

#endif // !HUMAN_H
