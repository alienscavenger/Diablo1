#pragma once

#ifndef HUMAN_H
#define HUMAN_H

#include "Base.h"
#include "Item.h"
#include <vector>

class Human : public Base
{
private:
	int strength;
	int endurance;
	int agility;
	int dexterity;

	/*
		Jadi gini cara kerja untuk inventory (beda New Game dan Load Game hanya pada actual parameternya saja):

			1. Di Main class, akan ada fungsi yang baca file untuk semua item yang ada di game.
			   (including yang di eguip dan tidak) (save cuman 1 file kalo bisa) (read terjadi saat load game)

			2. Saat load game, semua informasi item yang dibaca akan dimasukkan ke dalam sebuah vector<Item> yang di-declare
			   di dalam class Main, bernama vShop. Vector ini tidak akan dapat berubah", jadi tidak usah khawatir akan
			   pointer invalidation. Nanti di file save-nya bakal ada variable yang menentukan sudah dibeli apa belum,
			   atau mungkin ada seperti pembatas saat membaca filenya (supaya tau ini item berada pada section apa gitu").

			3. Class Human mempunyai sebuah vector yang berisi pointer to Item object. Saat objek Human di-construct,
			   vector vShop (yang berisi semua item yang ada di game) akan di-pass by reference ke ctor Human, dan di
			   ctor Human sendiri lah yang akan mengecek apakah elemen (item) di vector vShop tersebut sudah dibeli atau
			   belum.

			4. Semua yang sudah kita beli akan berada di vector vInventory Human, berupa pointer to Item. Dan yang kita
			   eguip berupa sebuah array of pointer to Item. Hanya perlu 7, karena hanya ada 7 tipe item (termasuk pendant,
			   yang sebenernya ditambahin biar ada tipe ke 0, alias index ke-0)

			5. Intinya, vShop tidak akan/dapat diubah oleh class Human, dan vInventory serta eguipment hanyalah sebuah pointer
			   to const object.

			6. vShop berisi semua item yang ada dalam game, entah itu uneguipped item, eguipped item, secret item, dsb.

			7. Kalau mau beli item, tinggal ganti status bought di vector vShop jadi true pake setBought, lalu di push_back
			   ke vector vInventory.

			8. Kalau mau menjual item, cek dulu apakah item di vector vInventory sedang di-eguip atau tidak. Kita hanya bisa
			   menjual item yang sedang tidak di-eguip

			9. Untuk menjual item, tinggal saja vInventory.delete(vInventory.begin() + index). Index ditentukan dari Main class aja.

			10. Untuk uneguip item, tinggal set eguipStatus[index] ke false, dan set eguipment[index] ke NULL;

			11. Untuk eguip item, validasi dilakukan di main Class dengan mengecek apakah eguipStatus[index] false. Kalau true, break;
				kalau false, maka set ke true, set eguipment[index] menjadi pointer ke Item tersebut, dan setEguipped(true) pada item tersebut.
	*/
	vector <const Item*> vInventory; // yang ada di inventory (termasuk yang sudah di-eguip)
	int nInventory; // jumlah barang yang ada di inventory

	bool eguipStatus[7]; // true kalau item type ke-index (sesuai type di Item.h) sudah di-eguip, false kalau belum
	const Item* eguipment[7]; // yang sekarang sedang dipakai (penggunaan index sama dengan eguipStatus)

	void checkInventory(vector<Item>&fileRead)
	{
		for (vector<Item>::const_iterator iter = fileRead.begin(), int i = 0; iter != fileRead.end(); iter++, i++)
		{
			if (iter->getBought()) // kalau sudah dibeli, masukin ke 
			{
				Item* temp = &fileRead[i];
				vInventory.push_back(temp); // kalau langsung masukin iter gabisa, soalnya itu const_iterator
			}
		}
	}
	void checkEguipped()
	{
		for (int i = 0; i < 7; i++)
		{
			eguipStatus[i] = false; // awalnya set eguipped ke false dulu (character tidak wear apa")
			eguipment[i] = NULL; // awalnya tidak menunjuk ke apa"
		}

		for (vector<const Item*>::const_iterator iter = vInventory.begin(); iter != vInventory.end(); iter++)
		{
			if ((*iter)->getEguipped()) // *iter = value dari vInventory = pointer to Item. jadi perlu di-dereference 2x
										// kalau sudah di-eguip
			{
				eguipment[(*iter)->getType()] = *iter; // valuenya adalah pointer dari iter, yakni value dari vInventory, yakni pointer to objek Item
				eguipStatus[(*iter)->getType()] = true; // artinya sekarang sudah ada yang di-eguip
			}
		}
	}

public:
	//constructor
	Human(int pilihanJob, vector <Item>& fileRead) // awalnya mau masukinnya itu const <Item>& fileRead, tapi bikin ribet, jadi dihilangin aja const-nya
	{
		vInventory.reserve(fileRead.size());
		setPrimary(pilihanJob); // secara implisit manggil setSecondary
		checkInventory(fileRead);
		checkEguipped();		
		nInventory = vInventory.size();
	}

	//getter baru (tidak ada pada Base.h)
	int getStrength() const { return strength; }
	int getEndurance() const { return endurance; }
	int getAgility() const { return agility; }
	int getDexterity() const { return dexterity; }

	//setter all primary and secondary berdasarkan item equipment

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
		// set seconday pertama kali saat membuat character
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

	void buyItem(Item& a)
	{
		a.setBought(true);
		vInventory.push_back(&a);
	}
	void sellItem(vector<const Item*>::const_iterator iter, Item* pointer)
	{
		pointer->setBought(false); // harus pake ini, habisnya iter adalah pointer ke const Item
		vInventory.erase(iter); // iter adalah sebuah pointer ke vInventory (const), dan pointer adalah pointer ke objek Item yang dituju
	}
	void uneguipItem(int index, Item* pointer)
	{
		pointer->setEguip(false);
		eguipStatus[index] = false;
		eguipment[index] = NULL;
	}
	void eguipItem(int index, Item* pointer)
	{
		pointer->setEguip(true);
		eguipStatus[index] = true;
		eguipment[index] = pointer;
	}
};

#endif // !HUMAN_H
