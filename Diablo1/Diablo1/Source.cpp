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

#include "Human.h"
#include "Item.h"
#include "common.h"
#include "Interface.h"

using namespace std;

int main()
{
	Interface interface1;

	interface1.titleScreen();
	interface1.loading();
	system("cls");
	interface1.intro();

	return 0;
}
/*
TEMPLATE SAVE

Nama Karakter
Level,Job,Gold,Experience,Strength,Endurance,Agility,Dexterity
Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor
#Nama Item1,Strength,Endurance,Agility,Dexterity,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Restriction,Eguipped,Bought
#Nama Item2,Strength,Endurance,Agility,Dexterity,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Restriction,Eguipped,Bought
#Nama Item3,Strength,Endurance,Agility,Dexterity,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Restriction,Eguipped,Bought
#Nama Item4,Strength,Endurance,Agility,Dexterity,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Restriction,Eguipped,Bought
#Nama Item5,Strength,Endurance,Agility,Dexterity,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Restriction,Eguipped,Bought
#Nama Item6,Strength,Endurance,Agility,Dexterity,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Restriction,Eguipped,Bought
#Nama Item7,Strength,Endurance,Agility,Dexterity,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Restriction,Eguipped,Bought
#Nama Item8,Strength,Endurance,Agility,Dexterity,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Restriction,Eguipped,Bought
#Nama Item9,Strength,Endurance,Agility,Dexterity,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Restriction,Eguipped,Bought
@Nama Monster1,Gold,Experience,Level,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Offense,Deffense
@Nama Monster2,Gold,Experience,Level,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Offense,Deffense
@Nama Monster3,Gold,Experience,Level,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Offense,Deffense
@Nama Monster4,Gold,Experience,Level,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Offense,Deffense
@Nama Monster5,Gold,Experience,Level,Damage,Chance to Hit,Evade,Speed,Max Health,Max Stamina,Armor,Offense,Deffense

*/