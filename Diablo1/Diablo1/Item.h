#pragma once

#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Item // bisa weapon, armor, atau apapun
{
private:
	string name;
	string effect;
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
	int equipped; // 1 = true, 0 = false
	int bought; // 1 = true, 0 = false
	/* 
	   type 0 = GAADA
	   type 1 = helmet
	   type 2 = gloves
	   type 3 = armor
	   type 4 = boots
	   type 5 = weapon
	   type 6 = shield

	   restriction 0 = no restriction
	   restriction 1 = assassin
	   restriction 2 = paladin
	   restriction 3 = barbarian
	*/
	template <class T>
	void effectHandling(T& attribute, string code)
	{
		int index;
		if ((index = effect.find(code)) != string::npos)
		{
			attribute = (effect[index + 3] == '+') ? (T)atoi(effect.c_str() + index + 4) : (T)atoi(effect.c_str() + index + 4)*-1;
		}
	}
public:
	static int const MAX_ITEM = 110;
	// empty constructor
	Item()
	{

	}

	//constructor
	Item(string name, int price,string effect,int type,int restriction, int equipped, int bought):
		strength(0),endurance(0),agility(0),dexterity(0),damage(0),chanceToHit(0),evade(0),speed(0),maxHealth(0),maxStamina(0),armor(0)
	{
		this->name = name; // KALAU PAKE VS15 / VS17, JANGAN LUPA PAKE _CRT_SECURE_NO_WARNINGS (CARI DI INTERNET)
		this->effect = effect;
		this->price = price;

		effectHandling(this->strength,"STR");
		effectHandling(this->endurance, "END");
		effectHandling(this->agility, "AGI");
		effectHandling(this->dexterity, "DEX");
		effectHandling(this->damage, "DMG");
		effectHandling(this->chanceToHit, "CTH");
		effectHandling(this->evade, "EVA");
		effectHandling(this->speed, "SPD");
		effectHandling(this->maxHealth, "MHP");
		effectHandling(this->maxStamina, "MST");
		effectHandling(this->armor, "AMR");

		this->type = type;
		this->restriction = restriction;
		this->equipped = equipped;
		this->bought = bought;
	}

	//getter
	string getName() const { return name; }
	string getEffect() const { return effect; }
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
	int getEquipped() const { return equipped; }
	int getBought() const { return bought; }

	//setter buat bought
	void setBought(int ok)
	{
		bought = ok;
	}
	//setter buat equipped
	void setEquip(int ok)
	{
		equipped = ok;
	}

	//setter kalo mau ada kyk "upgrade weapon" dsb, tapi itu nanti aja
};


#endif