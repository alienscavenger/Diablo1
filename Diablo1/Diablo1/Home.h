#pragma once

#ifndef HOME_H
#define HOME_H

#include "Interface.h"
#include "common.h"

class Home
{
private:

	static void changeRed() { Console::setColor(Console::COLOR_RED); }

	static void changeGreen() { Console::setColor(Console::COLOR_GREEN); }

	static void resetColor() { Console::resetColor(); }

	static void setPos(int x, int y) { Console::setCursorPos(x, y); }

	// -------------------------------- HOME FUNCTION ----------------------------------------------------
	struct ComparePrice { // comparator sort buat harga (ascending)
		bool operator()(Item* struct1, Item* struct2) {
			return (struct1->getPrice() < struct2->getPrice());
		}
	};
	struct CompareName { // comparator sort buat name (ascending)
		bool operator()(Item* struct1, Item* struct2) {
			return (struct1->getName() < struct2->getName());
		}
	};
	struct CompareArmor { // comparator sort buat armor (ascending)
		bool operator()(Item* struct1, Item* struct2) {
			return (struct1->getArmor() < struct2->getArmor());
		}
	};
	struct CompareDamage { // comparator sort buat armor (ascending)
		bool operator()(Item* struct1, Item* struct2) {
			return (struct1->getDamage() < struct2->getDamage());
		}
	};
	// -------------------------------------------------------------------------------------------------

public:

	static void printDiff(int doWhat, Human*& karakter, vector<Item*>temporary, int equipIndex, int itemIndex)
	{
		/*
		doWhat 0 = reset (gk kasih liatin difference nya)
		doWhat 1 = diff when equip
		doWhat 2 = diff when unequip
		*/
		Item x;
		Item* xP = NULL;
		if (!temporary.empty())
		{
			x = *temporary[itemIndex]; // local variable Item
			xP = &x;
		}

		Human compare = *karakter; // local variable Human
		if (doWhat == 0)
		{
			resetColor();
			for (int i = 0; i < 4; i++)
			{
				setPos(15, 8 + i);
				printf("       ");
			}
			setPos(41, 8);
			printf("       ");
			for (int i = 0; i < 2; i++)
			{
				setPos(42, 9 + i);
				printf("       ");
			}
			for (int i = 0; i < 4; i++)
			{
				setPos(41, 11 + i);
				printf("       ");
			}
		}
		else
		{
			if (doWhat == 1)
			{
				Item* temp = NULL;
				if (compare.getEquipStatus(equipIndex)) // kalau lagi ada yang di-equip, maka harus di-unequip dulu
				{
					temp = karakter->getEquipment(equipIndex); // buat ntar di-reequip. Soalnya, pas unequip item,bakal di setEquip ke 0
					if (temp == temporary[itemIndex])return; // kalau yang di-compare sama dengan yang sedang di-equip
					compare.unequipItem(equipIndex); // kalau sudah ada yg di-equip, maka unequip itu (secara implicit, manggil setEquip di item itu)

				}
				compare.equipItem(equipIndex, xP); // equip yang baru
				if (temp != NULL)temp->setEquip(1); // di-set ke equipped lagi item yang lama (urutannya jgn dibalik sama setEquip yang di atas, karena bisa jadi item lama = item baru)
			}
			else if (doWhat == 2)
			{
				if (compare.getEquipStatus(equipIndex)) // kalau lagi ada yang di-equip
				{
					Item* temp = karakter->getEquipment(equipIndex);
					compare.unequipItem(equipIndex);
					temp->setEquip(1); // set equipped untuk karakter utama;
				}
				else return;
			}

			int str = compare.getStrength() - karakter->getStrength();
			int end = compare.getEndurance() - karakter->getEndurance();
			int agi = compare.getAgility() - karakter->getAgility();
			int dex = compare.getDexterity() - karakter->getDexterity();
			int dmg = (int)(compare.getDamage() - karakter->getDamage());
			int cth = (int)(floor(compare.getChanceToHit() - karakter->getChanceToHit()));
			int eva = (int)(floor(compare.getEvade() - karakter->getEvade()));
			int spd = (int)(floor(compare.getSpeed() - karakter->getSpeed()));
			int hp = (int)(floor(compare.getMaxHealth() - karakter->getMaxHealth()));
			int sta = (int)(floor(compare.getMaxStamina() - karakter->getMaxStamina()));
			int amr = compare.getArmor() - karakter->getArmor();

			resetColor();
			if (str < 0)
			{
				setPos(12, 8);
				printf("%3d ", karakter->getStrength());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", str);
				resetColor();
				printf(")");
			}
			else if (str > 0)
			{
				setPos(12, 8);
				printf("%3d ", karakter->getStrength());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", str);
				resetColor();
				printf(")");

			}
			if (end < 0)
			{
				setPos(12, 9);
				printf("%3d ", karakter->getEndurance());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", end);
				resetColor();
				printf(")");
			}
			else if (end > 0)
			{
				setPos(12, 9);
				printf("%3d ", karakter->getEndurance());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", end);
				resetColor();
				printf(")");
			}
			if (agi < 0)
			{
				setPos(12, 10);
				printf("%3d ", karakter->getAgility());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", agi);
				resetColor();
				printf(")");
			}
			else if (agi > 0)
			{
				setPos(12, 10);
				printf("%3d ", karakter->getAgility());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", agi);
				resetColor();
				printf(")");
			}
			if (dex < 0)
			{
				setPos(12, 11);
				printf("%3d ", karakter->getDexterity());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", dex);
				resetColor();
				printf(")");
			}
			else if (dex > 0)
			{
				setPos(12, 11);
				printf("%3d ", karakter->getDexterity());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", dex);
				resetColor();
				printf(")");
			}
			if (dmg < 0)
			{
				setPos(38, 8);
				printf("%3.0f ", karakter->getDamage());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", dmg);
				resetColor();
				printf(")");
			}
			else if (dmg > 0)
			{
				setPos(38, 8);
				printf("%3.0f ", karakter->getDamage());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", dmg);
				resetColor();
				printf(")");
			}
			if (cth < 0)
			{
				setPos(38, 9);
				printf("%3.0f%% ", karakter->getChanceToHit());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", cth);
				resetColor();
				printf(")");
			}
			else if (cth > 0)
			{
				setPos(38, 9);
				printf("%3.0f%% ", karakter->getChanceToHit());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", cth);
				resetColor();
				printf(")");
			}
			if (eva < 0)
			{
				setPos(38, 10);
				printf("%3.0f%% ", karakter->getEvade());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", eva);
				resetColor();
				printf(")");
			}
			else if (eva > 0)
			{
				setPos(38, 10);
				printf("%3.0f%% ", karakter->getEvade());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", eva);
				resetColor();
				printf(")");
			}
			if (spd < 0)
			{
				setPos(38, 11);
				printf("%3.0f ", karakter->getSpeed());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", spd);
				resetColor();
				printf(")");
			}
			else if (spd > 0)
			{
				setPos(38, 11);
				printf("%3.0f ", karakter->getSpeed());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", eva);
				resetColor();
				printf(")");
			}
			if (hp < 0)
			{
				setPos(37, 12);
				printf("%4.0f ", karakter->getMaxHealth());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", hp);
				resetColor();
				printf(")");
			}
			else if (hp > 0)
			{
				setPos(37, 12);
				printf("%4.0f ", karakter->getMaxHealth());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", hp);
				resetColor();
				printf(")");
			}
			if (sta < 0)
			{
				setPos(37, 13);
				printf("%4.0f ", karakter->getMaxStamina());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", sta);
				resetColor();
				printf(")");
			}
			else if (sta > 0)
			{
				setPos(37, 13);
				printf("%4.0f ", karakter->getMaxStamina());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", sta);
				resetColor();
				printf(")");
			}
			if (amr < 0)
			{
				setPos(38, 14);
				printf("%3d ", karakter->getArmor());
				resetColor();
				printf("(");
				changeRed();
				printf("%d", amr);
				resetColor();
				printf(")");
			}
			else if (amr > 0)
			{
				setPos(38, 14);
				printf("%3d ", karakter->getArmor());
				resetColor();
				printf("(");
				changeGreen();
				printf("+%d", amr);
				resetColor();
				printf(")");
			}
			Console::setCursorPos(0, 18);
			// di bawah ini buat debug
			/*printf("(str=%d,end=%d,agi=%d,dex=%d,dmg=%d,cth=%d,eva=%d,spd=%d,hp=%d,sta=%d,amr=%d)", str, end, agi, dex, dmg, cth, eva, spd, hp, sta, amr);
			printf("(\nstr=%d,end=%d,agi=%d,dex=%d,dmg=%.0f,cth=%.0f,eva=%.0f,spd=%.0f,hp=%.0f,sta=%.0f,amr=%d)",
			compare.getStrength(), compare.getEndurance(), compare.getAgility(), compare.getDexterity(), compare.getDamage(), compare.getChanceToHit(),
			compare.getEvade(), compare.getSpeed(), compare.getMaxHealth(), compare.getMaxStamina(), compare.getArmor());*/
		}
	}

	static void equipmentMenu(Human*& karakter, vector<Item*>temporary, bool& active, int& state, int& filterType, bool& print, int& stillUnequiping, int which)
	{
		// int which -> CUMAN BUAT DEBUG
		Console::resetColor();
		Console::setCursorPos(50, 2);
		printf("============== Character Equipment ==============");

		if (print) // kalau print doang
		{
			int color[7];
			for (int i = 0; i < 7; i++) color[i] = Console::COLOR_WHITE;
			color[state] = 94; // highlight ungu-pink, text kuning
			char*text[7] = { " ","Head","Left Arm","Right Arm","Hands","Torso","Legs" };
			for (int i = 1; i < 7; i++)
			{
				Console::setColor(color[i]);
				Console::setCursorPos(51, 3 + i);

				if (karakter->getEquipStatus(i)) printf("%-9s: %s (%s)", text[i], karakter->getEquipment(i)->getName().c_str(), karakter->getEquipment(i)->getEffect().c_str());
				else printf("%-9s: (empty)", text[i]);
			}
			Console::resetColor();

			Console::setCursorPos(50, 11);
			printf("=================================================");

			return;
		}
		else
		{
			if (active) // lagi milih apa yang mau di-equip
			{
				Console::setCursorPos(50, 12);
				Console::setColor(Console::COLOR_GRAY);
				printf("(Preview when equipping/swapping item can be seen");
				Console::setCursorPos(50, 13);
				printf("On the left, with the difference inside the brackets)");
				Console::resetColor();
				Console::setCursorPos(50, 14);
				printf("===== Equipment Menu =====");
				Console::setCursorPos(50, 16);
				size_t maxItem = temporary.size();
				if (maxItem > 0)
				{
					int equipThis = 1;
					while (1)
					{
						Console::setCursorPos(50, 15);
						Console::setColor(79);
						printf("Select item to equip below (ESC to cancel) (ENTER to choose)");
						Console::resetColor();
						///Console::setCursorVisibility(true);
						///equipThis = Interface::getInt(0,maxItem);
						equipThis = compareEquipment(filterType, karakter, temporary, 1, equipThis - 1); // -1 karena masalah indexingnya. Coba ganti ke 0 biar ngerti
																										 ///Console::setCursorVisibility(false);

						Console::setCursorPos(50, 17);
						if (equipThis == -1)
						{
							active = false;
							filterType = 0;
							stillUnequiping = state - 1;
							state = 0;
							print = true;
							return;
						}
						if (temporary[equipThis - 1]->getEquipped())
						{
							Console::setCursorPos(90, 23 + equipThis - 1);
							printf("YOU ARE CURRENTLY EQUIPPING THIS!");
							Console::setCursorPos(90, 23 + equipThis);
							Console::setColor(Console::COLOR_GRAY);
							printf("(Press enter to continue)");
							Interface::pressEnterPlease();
							Console::resetColor();
							Console::setCursorPos(90, 23 + equipThis - 1);
							printf("                                  ");
							Console::setCursorPos(90, 23 + equipThis);
							printf("                         ");
							continue;
						}
						else if (temporary[equipThis - 1]->getRestriction() > 0 && temporary[equipThis - 1]->getRestriction() != karakter->getJob())
						{
							Console::setCursorPos(90, 23 + equipThis - 1);
							printf("YOU CANNOT EQUIP THIS! (see Restriction)");
							Console::setCursorPos(90, 23 + equipThis);
							Console::setColor(Console::COLOR_GRAY);
							printf("(Press enter to continue)");
							Interface::pressEnterPlease();
							Console::resetColor();
							Console::setCursorPos(90, 23 + equipThis - 1);
							printf("                                        ");
							Console::setCursorPos(90, 23 + equipThis);
							printf("                         ");
							continue;
						}
						else
						{
							printDiff(1, karakter, temporary, state, equipThis - 1);
							Console::setCursorPos(90, 23 + equipThis - 1);
							printf("Are you sure you want to equip");
							Console::setCursorPos(90, 23 + equipThis);
							Console::setColor(Console::COLOR_CYAN);
							printf("*%s*", temporary[equipThis - 1]->getName().c_str());
							Console::resetColor();
							Console::printf(" ?");
							int pickWhat = 0;
							int bufferDelay = 0;
							bool flagPrint = true;
							int currY = Console::getCursorY();
							int currX = Console::getCursorX();
							bool equip = false;
							while (1)
							{
								if (flagPrint)
								{
									Console::setCursorPos(currX, currY);
									if (pickWhat == 0)
									{
										Console::setColor(79);
										printf("<YES>");
										Console::setColor(Console::COLOR_WHITE);
										printf(" NO ");
									}
									else
									{
										Console::setColor(Console::COLOR_WHITE);
										printf(" YES ");
										Console::setColor(79);
										printf("<NO>");
										Console::setColor(Console::COLOR_WHITE);
									}
									flagPrint = false;
								}
								int buff = Console::getKeyPressed();
								if (buff != -1)
								{
									if (bufferDelay)
									{
										if (buff == 'M' || buff == 'm')
										{
											Music::playBackgroundMusic(Music::TOGGLE);
										}
										if (buff == VK_LEFT || buff == 0x41) // 41 == 'a'
										{
											pickWhat = (pickWhat - 1 + 2) % 2;
											flagPrint = true;
										}
										else if (buff == VK_RIGHT || buff == 0x44) // 0x44 == 'd'
										{
											pickWhat = (pickWhat + 1) % 2;
											flagPrint = true;
										}
										else if (buff == VK_RETURN)
										{
											if (pickWhat == 0) equip = true;
											break;
										}
										bufferDelay = 0;
									}
									else bufferDelay++;
								}
							} // end while
							if (equip)
							{
								stillUnequiping = state-1;
								if (state == 2 && temporary[equipThis - 1]->getType() == 5 && !(karakter->getEquipStatus(3))) // kalau sedang equip weapon di left hand, tapi tangan kanan masih kosong
								{
									// prioritaskan tangan kanan
									Console::setColor(Console::COLOR_CYAN);
									Console::setCursorPos(90, 23 + equipThis + 2);
									printf("RIGHT HAND IS EMPTY!");
									Console::setCursorPos(90, 23 + equipThis + 3);
									printf("EQUIPPING IN RIGHT HAND...");
									state = 3;
									Console::setCursorPos(90, 23 + equipThis + 4);
									Console::setColor(Console::COLOR_GRAY);
									printf("(Press enter to continue)");
									Interface::pressEnterPlease();
									Console::resetColor();
								}
								else if (karakter->getEquipStatus(state))
								{
									karakter->unequipItem(state);
								}
								karakter->equipItem(state, temporary[equipThis - 1]);
								active = false;
								state = 0;
								filterType = 0;
								print = true;
								break;
							}
							else
							{
								Console::setCursorPos(90, 23 + equipThis - 1);
								printf("                                    ");
								Console::setCursorPos(90, 23 + equipThis);
								printf("                                    ");
								printDiff(0, karakter, temporary, 0, 0);
								Console::resetColor();
								Console::setCursorPos(91, 16);
								printf("                      ");
								Console::setCursorPos(50, 17);
								printf("                                                      ");
								Console::setCursorPos(currX, currY);
								printf("          ");
								continue;
							}
						} // end else
					} // end while
				}
				else
				{
					Console::setColor(79);
					printf("NO ITEM WITH THE TYPE: ");
					Console::resetColor();
					printf(" ");
					int color;
					string type = "<";
					switch (filterType)
					{
					case Human::Helmet: type += "HELMET"; color = Console::COLOR_BLUE; break;
					case Human::Gloves: type += "GLOVES"; color = Console::COLOR_CYAN; break;
					case Human::Armor: type += "ARMOR"; color = Console::COLOR_GREEN; break;
					case Human::Boots: type += "BOOTS"; color = Console::COLOR_MAGENTA; break;
					case Human::Weapon: type += "WEAPON"; color = Console::COLOR_RED; break;
					case Human::WeaponAndShield: type += "WEAPON/SHIELD"; color = Console::COLOR_YELLOW; break;
					}
					type += ">";
					Console::setColor(color);
					printf("%s", type.c_str());

					Console::setCursorPos(50, 18);
					Console::setColor(Console::COLOR_GRAY);
					printf("(press enter to continue)");
					Interface::pressEnterPlease();
					stillUnequiping = state - 1;
					active = false;
					state = 0;
					filterType = 0;
					print = true;
				}
				return;
			}
			else
			{
				Console::setCursorPos(15, 1);
				Console::setColor(Console::COLOR_GRAY);
				printf("(Unequip Preview)");

				//Human preview = *karakter; // copy stats karakter ke temporary Objek

				Console::setCursorPos(50, 12);
				Console::setColor(Console::COLOR_GRAY);
				printf("(Choose the equipment slot above to CHANGE EQUIPMENT,");
				Console::setCursorPos(50, 13);
				printf("WSAD to pick, BACKSPACE to UNEQUIP item, ESC to go back.)");
				Console::resetColor();
				Console::setCursorPos(50, 14);
				printf("===== Equipment Menu =====");

				bool printFlag = true;
				int pickMenu = stillUnequiping<6 ? stillUnequiping : 6; // kalau pickMenu berada di 'back', tidak akan men-skip ke unequip
				stillUnequiping = 6;
				/*
				menu 0-5 = equipment slot
				menu 6 = back
				*/
				int delayFlag = 0;
				while (1)
				{
					if (printFlag)
					{
						printDiff(0, karakter, temporary, 0, 0);//reset yang sebelumnya ada aja)
						printDiff(2, karakter, temporary, pickMenu + 1, 0);//print perbedaannya
						int color[7];
						for (int i = 0; i < 7; i++) color[i] = Console::COLOR_WHITE;
						color[pickMenu] = 79; // highlight merah, text putih
						char*text[6] = { "Head","Left Arm","Right Arm","Hands","Torso","Legs" };
						for (int i = 0; i < 6; i++)
						{
							Console::setColor(color[i]);
							Console::setCursorPos(51, 4 + i);

							if (karakter->getEquipStatus(i + 1)) printf("%-9s: %s (%s)", text[i], karakter->getEquipment(i + 1)->getName().c_str(), karakter->getEquipment(i + 1)->getEffect().c_str());
							else printf("%-9s: (empty)", text[i]);
						}
						Console::setCursorPos(50, 15);
						Console::setColor(color[6]);
						printf("Back");

						Console::resetColor();

						printFlag = false;
					}
					char buff = Console::getKeyPressed();
					if (buff != -1)
					{
						if (delayFlag) // supaya key release tidak kebaca
						{
							if (buff == 'M' || buff == 'm')
							{
								Music::playBackgroundMusic(Music::TOGGLE);
							}
							if (buff == VK_UP || buff == 0x57) // 0x57 == 'w'
							{
								pickMenu = (pickMenu - 1 + 7) % 7;
								printFlag = true;
							}
							else if (buff == VK_DOWN || buff == 0x53) // 0x53 == 's'
							{
								pickMenu = (pickMenu + 1) % 7;
								printFlag = true;
							}
							else if (buff == VK_BACK)
							{
								if (pickMenu < 6 && karakter->getEquipStatus(pickMenu + 1)) // kalau menu bukan di 'back', dan ada yang sedang di-equip
								{
									//unequip
									karakter->unequipItem(pickMenu + 1);
									stillUnequiping = pickMenu;
									print = true;
									break;
								}
							}
							else if (buff == VK_ESCAPE)
							{
								break;
							}
							else if (buff == VK_RETURN)
							{
								bool balik = false;
								switch (pickMenu)
								{
								case 0: // Human::Head - 1
									filterType = Human::Helmet;
									break;
								case 1: // Human::LeftArm - 1
									filterType = -1; // weapon dan shield (5 dan 6)
									break;
								case 2: // Human::RightArm - 1
									filterType = Human::Weapon;
									break;
								case 3: // Human::Hands - 1
									filterType = Human::Gloves;
									break;
								case 4: // Human::Torso - 1
									filterType = Human::Armor;
									break;
								case 5: // Human::Legs - 1
									filterType = Human::Boots;
									break;
								case 6:
									balik = true;
									break;
								}
								if (balik)break;
								active = true;
								state = pickMenu + 1;
								break;
							}
							int sampah = Console::getKeyPressed();
							delayFlag = 0;
						}
						else delayFlag++;
					}
				} // end while
				printDiff(0, karakter, temporary, 0, 0);//reset yang sebelumnya ada aja)

			} // end else kalau gk active
		} // end else luar
	}

	static int compareEquipment(int currFilterType, Human*& karakter, vector<Item*>temporary, int type, int curr) // type 0 = cek doang, type 1 = equip, curr = i saat equip (balik ke pilihan sebelumnya)
	{
		Console::setCursorPos(18, 17);
		Console::setColor(Console::COLOR_GREEN);
		if (type == 1)
		{
			Console::setColor(Console::COLOR_RED);
			printf("        <CHOOSE THE ITEM TO BE EQUIPPED>");
		}
		else printf("<COMPARE CURRENTLY EQUIPPED WITH THE SELECTED ITEM>");

		Console::setCursorPos(28, 18);
		if ((currFilterType == Human::Weapon || currFilterType == 0) && type == 0) Console::setCursorPos(16, 18); // kalau lagi filter weapon
		Console::setColor(Console::COLOR_GREEN);
		printf("<tab> ");

		Console::resetColor();
		printf("<Camera: ");

		Console::setColor(Console::COLOR_YELLOW);
		printf("DYNAMIC");

		Console::resetColor();
		printf(">  ");

		if ((currFilterType == Human::Weapon || currFilterType == 0) && type == 0) // kalau lagi filter weapon
		{
			Console::resetColor();
			printf("<Compare with");

			Console::setColor(Console::COLOR_YELLOW);
			printf(" LEFT HAND>");

			Console::setColor(Console::COLOR_GREEN);
			printf(" <space>     ");
		}
		else
		{
			printf("                ");
		}


		Console::setCursorPos(0, 23);
		Console::resetColor();
		size_t size = temporary.size();
		int printDelay = 0;
		bool printFlag = true;
		int leftHand = 1;
		int i = 0;
		if (type == 1)
		{
			if (currFilterType == Human::Weapon) leftHand = 0;
			else if (currFilterType == Human::WeaponAndShield) leftHand = 1;
			i = curr;
			// reset warna sebelumnya ke putih/highlight merah dulu
			{
				if (temporary[i]->getEquipped())Console::setColor(79);
				else Console::resetColor();
				Console::setCursorPos(0, 23 + i);

				int res = temporary[i]->getRestriction();
				string restriction;
				if (res == 0) restriction = "-";
				else if (res == Human::Assassin) restriction = "Assassin";
				else if (res == Human::Paladin) restriction = "Paladin";
				else if (res == Human::Barbarian) restriction = "Barbarian";

				string type;
				int tmp = temporary[i]->getType();
				switch (tmp)
				{
				case Human::Helmet: type = "Helmet"; break;
				case Human::Gloves: type = "Gloves"; break;
				case Human::Armor: type = "Armor"; break;
				case Human::Boots: type = "Boots"; break;
				case Human::Weapon: type = "Weapon"; break;
				case Human::Shield: type = "Shield"; break;
				}
				printf(" %2d. | %18s | %6d | %-28s | %11s | %6s\n", i + 1, temporary[i]->getName().c_str(), temporary[i]->getPrice(),
					temporary[i]->getEffect().c_str(), restriction.c_str(), type.c_str());
			}
		}
		int fixedCamera = 0;
		while (1)
		{
			if (printFlag)
			{
				Console::setCursorPos(0, 23 + i);

				int res = temporary[i]->getRestriction();
				string restriction;
				if (res == 0) restriction = "-";
				else if (res == 1) restriction = "Assassin";
				else if (res == 2) restriction = "Paladin";
				else if (res == 3) restriction = "Barbarian";

				string type_;
				int tmp = temporary[i]->getType();
				switch (tmp)
				{
				case Human::Helmet: type_ = "Helmet"; break;
				case Human::Gloves: type_ = "Gloves"; break;
				case Human::Armor: type_ = "Armor"; break;
				case Human::Boots: type_ = "Boots"; break;
				case Human::Weapon: type_ = "Weapon"; break;
				case Human::Shield: type_ = "Shield"; break;
				}

				if (temporary[i]->getEquipped())Console::setColor(94);
				else Console::setColor(78);

				printf(" %2d. | %18s | %6d | %-28s | %11s | %6s\n", i + 1, temporary[i]->getName().c_str(), temporary[i]->getPrice(),
					temporary[i]->getEffect().c_str(), restriction.c_str(), type_.c_str());

				int index;
				switch (temporary[i]->getType())
				{
				case Human::Helmet:
					index = Human::Head;
					break;
				case Human::Gloves:
					index = Human::Hands;
					break;
				case Human::Armor:
					index = Human::Torso;
					break;
				case Human::Boots:
					index = Human::Legs;
					break;
				case Human::Weapon:
				{
					//// kalau tangan kiri kosong atau tangan kiri ada shield, cek tangan kanan

					//if (!(karakter->getEquipStatus(2)) || (karakter->getEquipment(2)->getType()==2)) { index = 3; }
					//else
					//{
					//	// kalau kiri kanan weapon
					//	if (leftHand)index = 2;
					//	else index = 3;
					//}
					if (leftHand) index = Human::LeftArm;
					else index = Human::RightArm;
					break;
				}
				break;
				case Human::Shield:
					index = Human::LeftArm;
					break;
				}
				printDiff(0, karakter, temporary, 0, 0);
				if ((type == 0 && (currFilterType == Human::Weapon || currFilterType == 0 || (temporary[i]->getType() != Human::Weapon && !temporary[i]->getEquipped())))
					||
					(type == 1)) printDiff(1, karakter, temporary, index, i);
				if (fixedCamera)Console::setCursorPos(0, 0); // supaya gk loncat" cameranya
				else Console::setCursorPos(0, 25 + i);
				printFlag = false;
			}
			char buff = Console::getKeyPressed();
			if (buff != -1)
			{
				if (printDelay)
				{
					if (buff == 'M' || buff == 'm')
					{
						Music::playBackgroundMusic(Music::TOGGLE);
					}
					if (buff == VK_UP || buff == 0x57) // 0x57 == 'w'
					{
						// reset warna sebelumnya ke putih/highlight merah dulu
						{
							if (temporary[i]->getEquipped())Console::setColor(79);
							else Console::resetColor();
							Console::setCursorPos(0, 23 + i);

							int res = temporary[i]->getRestriction();
							string restriction;
							if (res == 0) restriction = "-";
							else if (res == Human::Assassin) restriction = "Assassin";
							else if (res == Human::Paladin) restriction = "Paladin";
							else if (res == Human::Barbarian) restriction = "Barbarian";

							string type;
							int tmp = temporary[i]->getType();
							switch (tmp)
							{
							case Human::Helmet: type = "Helmet"; break;
							case Human::Gloves: type = "Gloves"; break;
							case Human::Armor: type = "Armor"; break;
							case Human::Boots: type = "Boots"; break;
							case Human::Weapon: type = "Weapon"; break;
							case Human::Shield: type = "Shield"; break;
							}
							printf(" %2d. | %18s | %6d | %-28s | %11s | %6s\n", i + 1, temporary[i]->getName().c_str(), temporary[i]->getPrice(),
								temporary[i]->getEffect().c_str(), restriction.c_str(), type.c_str());
						}
						i = (i - 1 + (int)size) % (int)size;
						printFlag = true;
					}
					else if (buff == VK_DOWN || buff == 0x53) // 0x53 == 's'
					{
						// reset warna sebelumnya ke putih/highlight dulu
						{
							if (temporary[i]->getEquipped())Console::setColor(79);
							else Console::resetColor();
							Console::setCursorPos(0, 23 + i);

							int res = temporary[i]->getRestriction();
							string restriction;
							if (res == 0) restriction = "-";
							else if (res == 1) restriction = "Assassin";
							else if (res == 2) restriction = "Paladin";
							else if (res == 3) restriction = "Barbarian";

							string type;
							int tmp = temporary[i]->getType();
							switch (tmp)
							{
							case Human::Helmet: type = "Helmet"; break;
							case Human::Gloves: type = "Gloves"; break;
							case Human::Armor: type = "Armor"; break;
							case Human::Boots: type = "Boots"; break;
							case Human::Weapon: type = "Weapon"; break;
							case Human::Shield: type = "Shield"; break;
							}
							printf(" %2d. | %18s | %6d | %-28s | %11s | %6s\n", i + 1, temporary[i]->getName().c_str(), temporary[i]->getPrice(),
								temporary[i]->getEffect().c_str(), restriction.c_str(), type.c_str());
						}
						i = (i + 1) % size;
						printFlag = true;
					}
					else if (buff == VK_TAB)
					{
						fixedCamera = (fixedCamera + 1) % 2; // toggle fixed camera
						if (fixedCamera)Console::setCursorPos(0, 0); // supaya gk loncat" cameranya
						else Console::setCursorPos(0, 23 + i);
						{
							Console::setCursorPos(28, 18);
							if ((currFilterType == Human::Weapon || currFilterType == 0) && type != 1) Console::setCursorPos(16, 18); // kalau lagi filter weapon
							Console::setColor(Console::COLOR_GREEN);
							printf("<tab> ");
							Console::resetColor();
							if (fixedCamera)
							{
								printf("<Camera: ");
								Console::setColor(Console::COLOR_YELLOW);
								printf("FIXED");
								Console::resetColor();
							}
							else
							{
								printf("<Camera: ");
								Console::setColor(Console::COLOR_YELLOW);
								printf("DYNAMIC");
							}

							Console::resetColor();
							printf(">  ");

							if ((currFilterType == Human::Weapon || currFilterType == 0) && type != 1) // kalau lagi filter weapon
							{
								if (leftHand)
								{
									Console::resetColor();
									printf("<Compare with");

									Console::setColor(Console::COLOR_YELLOW);
									printf(" LEFT HAND>");

									Console::setColor(Console::COLOR_GREEN);
									printf("<space>      ");
								}
								else
								{
									Console::resetColor();
									printf("<Compare with");

									Console::setColor(Console::COLOR_YELLOW);
									printf(" RIGHT HAND>");

									Console::setColor(Console::COLOR_GREEN);
									printf("<space>     ");
								}
							}
							else
							{
								printf("                ");
							}
						}
					}
					else if (buff == VK_SPACE && ((currFilterType == Human::Weapon || currFilterType == 0) && type != 1))
					{
						leftHand = (leftHand + 1) % 2;
						{
							Console::setCursorPos(28, 18);
							if ((currFilterType == Human::Weapon || currFilterType == 0) && type != 1) Console::setCursorPos(16, 18); // kalau lagi filter weapon
							Console::setColor(Console::COLOR_GREEN);
							printf("<tab> ");
							Console::resetColor();
							if (fixedCamera)
							{
								printf("<Camera: ");
								Console::setColor(Console::COLOR_YELLOW);
								printf("FIXED");
								Console::resetColor();
							}
							else
							{
								printf("<Camera: ");
								Console::setColor(Console::COLOR_YELLOW);
								printf("DYNAMIC");
							}

							Console::resetColor();
							printf(">  ");

							if ((currFilterType == Human::Weapon || currFilterType == 0) && type != 1) // kalau lagi filter weapon
							{
								if (leftHand)
								{
									Console::resetColor();
									printf("<Compare with");

									Console::setColor(Console::COLOR_YELLOW);
									printf(" LEFT HAND>");

									Console::setColor(Console::COLOR_GREEN);
									printf("<space>      ");
								}
								else
								{
									Console::resetColor();
									printf("<Compare with");

									Console::setColor(Console::COLOR_YELLOW);
									printf(" RIGHT HAND>");

									Console::setColor(Console::COLOR_GREEN);
									printf("<space>     ");
								}
							}
							else
							{
								printf("                ");
							}
						}
						printFlag = true;
					}
					else if (buff == VK_RETURN && type == 1)
					{
						Console::resetColor();
						return i + 1;
					}
					else if (buff == VK_ESCAPE)
					{
						if (type == 1)
						{
							Console::resetColor();
							return -1;
						}
						break;
					}
					printDelay = 0;
				}
				else printDelay++;
			}
		}
		Console::resetColor();
		return 0;
	}

	static void playerStatus(Human*& karakter, vector<Monster>& vMonster) // print player status
	{
		Console::setCursorPos(0, 2);
		Console::resetColor();
		printf(" =============== Player Status ==============\n\n");
		printf(" Character: '");
		Console::setColor(13); // warna ungu terang
		cout << karakter->getName();
		Console::setColor(Console::COLOR_WHITE);
		printf("' Level %d\n", karakter->getLevel());
		printf(" Class : ");
		switch (karakter->getJob())
		{
		case Human::Assassin:
			Console::setColor(Console::COLOR_RED);
			cout << "Assassin";
			break;
		case Human::Paladin:
			Console::setColor(Console::COLOR_GREEN);
			cout << "Paladin";
			break;
		case Human::Barbarian:
			Console::setColor(Console::COLOR_YELLOW);
			cout << "Barbarian";
			break;
		}
		printf("\n");
		Console::setColor(Console::COLOR_WHITE);
		printf(" Monsters killed : %d", karakter->getMonsterKilled());
		printf("\n\n");
		printf(" %-9s: %3d%7s %-13s: %3.0f\n", "Strength", karakter->getStrength(), " ", "Base Damage", karakter->getDamage());
		printf(" %-9s: %3d%7s %-13s: %3.0f%%\n", "Endurance", karakter->getEndurance(), " ", "Chance to Hit", karakter->getChanceToHit());
		printf(" %-9s: %3d%7s %-13s: %3.0f%%\n", "Agility", karakter->getAgility(), " ", "Evade", karakter->getEvade());
		printf(" %-9s: %3d%7s %-13s: %3.0f\n", "Dexterity", karakter->getDexterity(), " ", "Speed", karakter->getSpeed());
		printf(" %21s %-13s:%4.0f\n", " ", "Max Health", karakter->getMaxHealth());
		stringstream temp;
		temp << karakter->getGold() << " G";
		string gold_string;
		getline(temp, gold_string);
		printf(" %-5s: %-14s %-13s:%4.0f\n", "Gold", gold_string.c_str(), "Max Stamina", karakter->getMaxStamina());
		temp.clear();

		if (karakter->getLevel() < Human::MAX_LEVEL)
		{
			temp << karakter->getExperience() << '/' << karakter->getExpRequirement(karakter->getLevel() + 1);
		}
		else
		{
			temp << "MAX LEVEL!!!";
		}
		string exp_string;
		getline(temp, exp_string);
		printf(" %-5s: %-14s %-13s: %3d\n\n", "Exp", exp_string.c_str(), "Armor", karakter->getArmor());
		printf(" ============================================\n");
	}

	static void homeMenu(vector<Item>& vShop, vector<Monster>& vMonster, Human*& karakter, vector<Item*>& vInventory)
	{
		// 99% COPAS DARI SHOPMENU
		int filterType = 0; // awalnya gk di-filter
		int sortType = 0; // awalnya gk di-sort
		int delayFlag = 0;
		bool equipMenuPrintOnly = true; // true kalau mau print character equipment aja
		bool equipMenuActive = false; // awalnya equipment menu gk active (kalau active, artinya, di dalem loop, akan masuk ke equipment menu, bukan player menu
		int stillUnequiping = 6; // SATU"NYA WORKAROUND SUPAYA BISA CEPET BALIK KE UNEQUIP ITEM
		int equipMenuState = 0; // kalau >0, artinya, equipment menu saat sedang ada di state "pick item to equip". Valuenya adalah index dari eguipment yang sedang dipilih
		int pickMenu = 0; // awalnya pilihan menu di yang pertama
						  /*
						  pickMenu:
						  0 = Sort Items
						  1 = Sell Item
						  2 = My Equipment
						  3 = Compare Equipment
						  4 = Exit
						  */

		while (1) // print/update terus selama belum beli/exit dan masih filter/sort
		{
			system("cls");
			Console::setColor(206); // BRIGHT RED BACKGROUND, WITH YELLOW TEXT
			string houseName= karakter->getName() + "'s House";
			Console::setCursorPos(48-(houseName.length()/2), 0);
			cout << houseName;
			Console::resetColor();

			playerStatus(karakter, vMonster);

			printf("\n");
			size_t inventSize = vInventory.size(); // berapa item di inventory

			vector<Item*> temporary; // nampung semua item di vInventory yang sudah dibeli
			temporary.reserve(Item::MAX_ITEM);
			temporary.clear(); // clear dulu

							   // -------------- masukin data item ke temporary vector ---------------------
			if (filterType == Human::WeaponAndShield) // kalau filternya <Weapon and Shield>
			{
				for (int i = 0; i < inventSize; i++)
				{
					if (vInventory[i]->getType() > 4) temporary.push_back(vInventory[i]); // filter 5 dan 6
				}
			}
			else if (filterType > 0) // kalau di-filter
			{
				for (int i = 0; i < inventSize; i++)
				{
					if (vInventory[i]->getType() == filterType) temporary.push_back(vInventory[i]);
				}
			}
			else // kalau gk di-filter
			{
				for (int i = 0; i < inventSize; i++) // ini buat baca di vShop, yang mana yang belum dibeli. (yang belum dibeli doang yang bakal di-push_back)
				{
					temporary.push_back(vInventory[i]);
				}
			}
			// --------------------------------------------------------------------------

			// --------- sort data vector temporary berdasarkan yg diinginkan -----------
			if (sortType > 0)
			{
				switch (sortType)
				{
				case 1:
					sort(temporary.begin(), temporary.end(), ComparePrice());
					break;
				case 2:
					sort(temporary.begin(), temporary.end(), CompareName());
					break;
				case 3:
					if (filterType == Human::Weapon) // kalau weapon, sort berdasarkan damage
					{
						sort(temporary.begin(), temporary.end(), CompareDamage());
						break;
					}
					else sort(temporary.begin(), temporary.end(), CompareArmor()); // selain itu, sort berdasarkan armor
					break;
				}
			}
			// --------------------------------------------------------------------------


			// --------------------------- print vector temporary -----------------------------------------------------------------------------------------------------
			vector<Item*>::iterator iter; // iterator untuk vector temporary (Item*)
			int i = 1; // variable buat print index vector (tapi ini mulai dari 1, sedangkan vector mulai dari 0)
			printf("\n");
			printf("                                 - My Inventory -\n");
			printf(" =======================================================================================\n");
			printf(" %3s | %18s | %5s  | %-28s | %10s | %6s\n", "No.", "ITEM NAME", "PRICE", "ITEM EFFECTS", "RESTRICTION", "TYPE");
			printf(" =======================================================================================\n");

			if (temporary.size() == 0)
			{
				if (inventSize > 0)
				{
					printf("\n                          // NO ITEM WITH THE TYPE ");
					int color;
					string type = "<";
					switch (filterType)
					{
					case Human::Helmet: type += "HELMET"; color = Console::COLOR_BLUE; break;
					case Human::Gloves: type += "GLOVES"; color = Console::COLOR_CYAN; break;
					case Human::Armor: type += "ARMOR"; color = Console::COLOR_GREEN; break;
					case Human::Boots: type += "BOOTS"; color = Console::COLOR_MAGENTA; break;
					case Human::Weapon: type += "WEAPON"; color = Console::COLOR_RED; break;
					case Human::Shield: type += "SHIELD"; color = Console::COLOR_YELLOW; break;
					case Human::WeaponAndShield: type += "WEAPON OR SHIELD"; color = Console::COLOR_YELLOW; break;
					}
					type += ">";
					Console::setColor(color);
					printf("%s", type.c_str());
					Console::resetColor();
					printf(" //\n\n");
				}
				else printf("\n                              // EMPTY INVENTORY //\n\n"); // kalau inventory kosong
			}

			for (iter = temporary.begin(); iter != temporary.end(); iter++, i++)
			{
				int res = (*iter)->getRestriction();
				string restriction;
				if (res == 0) restriction = "-";
				else if (res == Human::Assassin) restriction = "Assassin";
				else if (res == Human::Paladin) restriction = "Paladin";
				else if (res == Human::Barbarian) restriction = "Barbarian";
				/*
				type 0 = GAADA
				type 1 = helmet
				type 2 = gloves
				type 3 = armor
				type 4 = boots
				type 5 = weapon
				type 6 = shield
				*/
				string type;
				int tmp = (*iter)->getType();
				switch (tmp)
				{
				case Human::Helmet: type = "Helmet"; break;
				case Human::Gloves: type = "Gloves"; break;
				case Human::Armor: type = "Armor"; break;
				case Human::Boots: type = "Boots"; break;
				case Human::Weapon: type = "Weapon"; break;
				case Human::Shield: type = "Shield"; break;
				}

				if ((*iter)->getEquipped())Console::setColor(79); // kalau sudah di-equip, maka ganti warnanya
				else Console::resetColor();

				printf(" %2d. | %18s | %6d | %-28s | %11s | %6s\n", i, (*iter)->getName().c_str(), (*iter)->getPrice(), (*iter)->getEffect().c_str(), restriction.c_str(), type.c_str());
				Console::resetColor();
			}
			printf(" =======================================================================================\n");

			//-----------------------------------------------------------------------------------------------------------------------------------------------------------

			cout << "\n";
			cout << " Filter by : <";
			int color[7]{ Console::COLOR_WHITE,Console::COLOR_WHITE, Console::COLOR_WHITE, Console::COLOR_WHITE, Console::COLOR_WHITE,
				Console::COLOR_WHITE, Console::COLOR_WHITE };
			char* filterText[7] = { "NONE","HELMET","GLOVE","ARMOR","BOOTS","WEAPON","SHIELD" };
			switch (filterType)
			{
			case Human::WeaponAndShield:
				color[5] = Console::COLOR_RED;
				color[6] = Console::COLOR_YELLOW;
				break;
			case 0: // NONE
				color[0] = Console::COLOR_GRAY;
				break;
			case Human::Helmet:
				color[1] = Console::COLOR_BLUE;
				break;
			case Human::Gloves:
				color[2] = Console::COLOR_CYAN;
				break;
			case Human::Armor:
				color[3] = Console::COLOR_GREEN;
				break;
			case Human::Boots:
				color[4] = Console::COLOR_MAGENTA;
				break;
			case Human::Weapon:
				color[5] = Console::COLOR_RED;
				break;
			case Human::Shield:
				color[6] = Console::COLOR_YELLOW;
				break;
			}
			// print filter by apa text
			{
				Console::setColor(color[0]);
				printf("%s", filterText[0]);
				for (int i = 1; i < 7; i++)
				{
					Console::resetColor();
					printf(",");
					Console::setColor(color[i]);
					printf("%s", filterText[i]);
				}
			}
			Console::setColor(Console::COLOR_WHITE);
			cout << ">";
			Console::setColor(Interface::COLOR_GREY);
			cout << " (Press ";
			Console::setColor(Console::COLOR_GREEN);
			cout << "<tab>";
			Console::setColor(Interface::COLOR_GREY);
			cout << " to change filter)\n\n";
			Console::setColor(Console::COLOR_WHITE);



			cout << " ========= Player Menu ========\n\n";
			Console::setColor(Console::COLOR_WHITE);

			Console::setCursorVisibility(false);
			int flag = 0;
			bool printFlag = true;
			pickMenu = 0;
			if (equipMenuActive || stillUnequiping <= 5) pickMenu = -1; // kalau equipMenu lagi active, jgn highlight selection di player menu

			int currY = Console::getCursorY();
			bool sortA = false; // saat di menu pilihan sort, click 'a'
			bool sortD = false; // saat di menu pilihan sort, click 'd' (SEBENERNYA GK PERLU, TAPI GPP, BUAT KONSISTENSI)

								// //////////////////////////////////////////////////////////// lokasi kode ini gk boleh diubah
			equipmentMenu(karakter, temporary, equipMenuActive, equipMenuState, filterType, equipMenuPrintOnly, stillUnequiping, 1); // state 0 kalau mau print doang, state>0 saat ada yang sedang dipilih
			equipMenuPrintOnly = false;
			// ////////////////////////////////////////////////////////////

			while (1)
			{
				if (printFlag)
				{
					Console::setCursorPos(0, currY);

					// 79 = putih dengan highlight merah
					// 78 = kuning dengan highlight merah
					// 14 = kuning

					int color1 = Console::COLOR_WHITE;
					int color2 = 14;
					if (pickMenu == 0)
					{
						color1 = 79;
						color2 = 78;
					}
					Console::setColor(Console::COLOR_WHITE);
					printf(" ");
					Console::setColor(color1);
					cout << "SORT : ";

					if (sortType == 0)
					{
						Console::setColor(color2);
						cout << "<NONE> ";
					}
					else
					{
						Console::setColor(color1);
						cout << "NONE ";
					}
					if (sortType == 1)
					{
						Console::setColor(color2);
						cout << "<PRICE> ";
					}
					else
					{
						Console::setColor(color1);
						cout << "PRICE ";
					}
					if (sortType == 2)
					{
						Console::setColor(color2);
						cout << "<NAME>";
					}
					else
					{
						Console::setColor(color1);
						cout << "NAME";
					}
					if (filterType != 0)
					{
						if (sortType == 3)
						{
							Console::setColor(color2);
							if (filterType == Human::Weapon) cout << " <DAMAGE>";
							else cout << " <ARMOR>";
						}
						else
						{
							Console::setColor(color1);
							if (filterType == Human::Weapon) cout << " DAMAGE";
							else cout << " ARMOR";
						}
					}
					Console::setColor(Console::COLOR_WHITE);
					printf("\n ");
					if (pickMenu == 1) Console::setColor(79);
					else Console::setColor(Console::COLOR_WHITE);
					cout << "SELL ITEM";

					Console::setColor(Console::COLOR_WHITE);
					printf("\n ");
					if (pickMenu == 2) Console::setColor(79);
					else Console::setColor(Console::COLOR_WHITE);
					cout << "MY EQUIPMENT";

					Console::setColor(Console::COLOR_WHITE);
					printf("\n ");
					if (temporary.size() == 0)
					{
						if (pickMenu == 3) Console::setColor(72); // highlight merah, text abu"
						else Console::setColor(Console::COLOR_GRAY);
					}
					else
					{
						if (pickMenu == 3) Console::setColor(79);
						else Console::setColor(Console::COLOR_WHITE);
					}
					cout << "COMPARE EQUIPMENT";

					Console::setColor(Console::COLOR_WHITE);
					printf("\n ");
					if (pickMenu == 4) Console::setColor(79);
					else Console::setColor(Console::COLOR_WHITE);
					cout << "EXIT";

					Console::setColor(Console::COLOR_WHITE);
					printFlag = false;
				}
				char buff = Console::getKeyPressed();
				if (buff != -1)
				{
					if (equipMenuActive || stillUnequiping <= 5)break; // menjaga tidak tombol yang tak sengaja ditekan
					if (delayFlag)
					{
						if (buff == 'M' || buff == 'm')
						{
							Music::playBackgroundMusic(Music::TOGGLE);
						}
						if (buff == VK_UP || buff == 0x57) // 0x57 == 'w'
						{
							pickMenu = (pickMenu - 1 + 5) % 5;
							printFlag = true;
						}
						else if (buff == VK_DOWN || buff == 0x53) // 0x53 == 's'
						{
							pickMenu = (pickMenu + 1) % 5;
							printFlag = true;
						}
						else if (buff == VK_TAB)
						{
							flag = 1;
							filterType = (filterType + 1) % 7;
							sortType = 0;
							delayFlag = 0;
							break;
						}
						else if (buff == VK_RETURN)
						{
							delayFlag = 0;
							break;
						}
						else if (buff == VK_ESCAPE)
						{
							return;
						}
						else if (pickMenu == 0 && (buff == 0x41 || buff == VK_LEFT)) // 'a'
						{
							sortA = true;
							delayFlag = 0;
							break;
						}
						else if (pickMenu == 0 && (buff == 0x44 || buff == VK_RIGHT)) // 'd'
						{
							sortD = true;
							delayFlag = 0;
							break;
						}
						delayFlag = 0;
					}
					else delayFlag++;
				}
				if (equipMenuActive || stillUnequiping <= 5)break; // kalau lagi di equp menu, break aja
			} // end while dalem

			if (equipMenuActive || stillUnequiping <= 5) // kalau lagi active, artinya sedang milih item. kalau stillUnequiping<=5, artinya lagi unequip
			{
				equipmentMenu(karakter, temporary, equipMenuActive, equipMenuState, filterType, equipMenuPrintOnly, stillUnequiping, 2);
				equipMenuPrintOnly = true;
				sortType = 0; // jangan di-sort
				continue;
			}

			if (flag == 1)
			{
				equipMenuPrintOnly = true;
				continue; // (teken tab) filter ulang
			}

			int index;
			size_t temporarySize = temporary.size();
			bool sell = false;
			switch (pickMenu)
			{
			case 0: // sort item by...
			{
				equipMenuPrintOnly = true;
				int maks;
				if (filterType == 0) maks = 3;
				else maks = 4;
				if (sortA) sortType = (sortType - 1 + maks) % maks;
				else sortType = (sortType + 1) % maks;
				continue; // continue while luar
			}
			break;
			case 1: // sell item
			{
				equipMenuPrintOnly = true;
				if (temporary.size() == 0)
				{
					Console::setColor(Console::COLOR_RED);
					printf("\n\n");
					printf(" No Item detected!");
					Interface::delaySec(700);
					continue;
				}
				Console::setCursorVisibility(true);
				printf("\n\n");
				printf(" Input item number to sell ( 0 = cancel) [ 0 to %u ]:", (unsigned int)temporarySize);
				index = Interface::getInt(0, temporarySize);

				if (index == 0)
				{
					delayFlag = 1;
					continue;
				}

				if (temporary[index - 1]->getEquipped())
				{
					Console::setColor(Console::COLOR_RED);
					printf("\n THAT ITEM IS CURRENTLY EQUIPPED!!!\n");
					Console::setColor(Console::COLOR_GRAY);
					printf(" (press enter to continue)");
					Console::resetColor();
					Interface::pressEnterPlease();
					continue; // ulang lagi
				}

				printf("\n ========== Confirmation ==========\n");
				printf(" Item name  : %s\n", temporary[index - 1]->getName().c_str());
				printf(" Item type  : ");

				switch (temporary[index - 1]->getType())
				{
				case Human::Helmet:
					printf("Helmet");
					break;
				case Human::Gloves:
					printf("Gloves");
					break;
				case Human::Armor:
					printf("Armor");
					break;
				case Human::Boots:
					printf("Boots");
					break;
				case Human::Weapon:
					printf("Weapon");
					break;
				case Human::Shield:
					printf("Shield");
					break;
				}

				printf("\n Effects    : %s", temporary[index - 1]->getEffect().c_str());
				printf("\n Restriction: ");

				switch (temporary[index - 1]->getRestriction())
				{
				case 0:
					cout << "-";
					break;
				case Human::Assassin:
					cout << "Assassin";
					break;
				case Human::Paladin:
					cout << "Paladin";
					break;
				case Human::Barbarian:
					cout << "Barbarian";
					break;
				}
				printf("\n ==================================\n");

				Console::setColor(Console::COLOR_WHITE);
				printf("\n You will receive ");
				Console::setColor(Console::COLOR_YELLOW);
				printf("%d G\n\n", (temporary[index - 1]->getPrice()) / 2);
				Console::setColor(Console::COLOR_WHITE);

				Console::setCursorVisibility(false);

				Console::setColor(Console::COLOR_WHITE);
				printf(" Are you sure you want to sell it?\n ");
				int pickWhat = 0;
				int bufferDelay = 0;
				bool flagPrint = true;
				int currY = Console::getCursorY();
				while (1)
				{
					if (flagPrint)
					{
						Console::setCursorPos(0, currY);
						if (pickWhat == 0)
						{
							Console::setColor(79);
							printf("<YES>");
							Console::setColor(Console::COLOR_WHITE);
							printf(" NO ");
						}
						else
						{
							Console::setColor(Console::COLOR_WHITE);
							printf(" YES ");
							Console::setColor(79);
							printf("<NO>");
							Console::setColor(Console::COLOR_WHITE);
						}
						flagPrint = false;
					}
					int buff = Console::getKeyPressed();
					if (buff != -1)
					{
						if (bufferDelay)
						{
							if (buff == 'M' || buff == 'm')
							{
								Music::playBackgroundMusic(Music::TOGGLE);
							}
							if (buff == VK_LEFT || buff == 0x41) // 41 == 'a'
							{
								pickWhat = (pickWhat - 1 + 2) % 2;
								flagPrint = true;
							}
							else if (buff == VK_RIGHT || buff == 0x44) // 0x44 == 'd'
							{
								pickWhat = (pickWhat + 1) % 2;
								flagPrint = true;
							}
							else if (buff == VK_RETURN)
							{
								if (pickWhat == 0) sell = true;
								break;
							}
							bufferDelay = 0;
						}
						else bufferDelay++;
					}
				} // end while

				if (sell)
				{
					karakter->sellItem(temporary[index - 1]); // jual Itemnya
					karakter->setGold((temporary[index - 1]->getPrice()) / 2); // tambah gold sebanyak 50% harga item nya
					Console::setColor(Console::COLOR_GREEN);
					printf("\n\n You have successfuly sold the item!\n");

					Console::setColor(Interface::COLOR_GREY);
					printf("\n (Press enter to continue)");
					Interface::pressEnterPlease();
					Console::setColor(Console::COLOR_WHITE);
					continue;
				}
			}
			break;
			case 2: // eguipment menu
					// PRINT DI SEBELAH KANAN PLAYER STATUS
				equipmentMenu(karakter, temporary, equipMenuActive, equipMenuState, filterType, equipMenuPrintOnly, stillUnequiping, 3); // (state 0, sedang tidak active, tapi akan di-set ke active)
				sortType = 0;
				equipMenuPrintOnly = true;
				break;
			case 3: // compare equipment
				if (temporary.size() == 0)
				{
					Console::setColor(Console::COLOR_RED);
					printf("\n\n No item detected!");
					Console::resetColor();
					Interface::delaySec(700);
				}
				else compareEquipment(filterType, karakter, temporary, 0, 0);
				equipMenuPrintOnly = true;
				continue;
			case 4: // exit
				return;
			} // end switch


		} // end while luar

	}

};

#endif