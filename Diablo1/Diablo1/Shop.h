#pragma once

#ifndef SHOP_H
#define SHOP_H

#include "common.h"
#include "Interface.h"

class Shop
{
private:
	// -------------------------------- SHOP FUNCTION ----------------------------------------------------
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

	static void shopMenu(vector<Item>& vShop, Human*& karakter)
	{
		int filterType = 0; // awalnya gk di-filter
		int sortType = 0; // awalnya gk di-sort
		int delayFlag = 1;
		int pickMenu = 0; // awalnya pilihan menu di yang pertama
		size_t nonBoughtSize = 0; // banyak item di shop yang blom dibeli
		bool yourClassOnly = false;
		/*
		pickMenu:
		0 = Sort Items
		1 = Buy Item
		2 = (insert job name here) class only: ON/OFF
		3 = Exit
		*/

		while (1) // print/update terus selama belum beli/exit dan masih filter/sort
		{
			system("cls");

			vector<Item*> temporary; // nampung semua item di vShop yang belum dibeli
			temporary.reserve(Item::MAX_ITEM);
			size_t shopSize = vShop.size(); // berapa item di vShop

			temporary.clear(); // clear dulu

							   // -------------- masukin data item ke temporary vector ---------------------
			if (filterType > 0) // kalau di-filter
			{
				if (yourClassOnly)
				{
					int myJob = karakter->getJob();
					for (int i = 0; i < shopSize; i++)
					{
						if ((vShop[i].getRestriction() == myJob || vShop[i].getRestriction() == 0) && !(vShop[i].getBought()) && vShop[i].getType() == filterType) temporary.push_back(&vShop[i]);
					}
				}
				else
				{
					for (int i = 0; i < shopSize; i++)
					{
						if (!(vShop[i].getBought()) && vShop[i].getType() == filterType) temporary.push_back(&vShop[i]);
					}
				}
			}
			else // kalau gk di-filter
			{
				if (yourClassOnly)
				{
					int myJob = karakter->getJob();
					for (int i = 0; i < shopSize; i++) // ini buat baca di vShop, yang mana yang belum dibeli. (yang belum dibeli doang yang bakal di-push_back)
					{
						if ((vShop[i].getRestriction() == myJob || vShop[i].getRestriction() == 0) && !(vShop[i].getBought())) temporary.push_back(&vShop[i]);
					}
				}
				else
				{
					for (int i = 0; i < shopSize; i++) // ini buat baca di vShop, yang mana yang belum dibeli. (yang belum dibeli doang yang bakal di-push_back)
					{
						if (!(vShop[i].getBought())) temporary.push_back(&vShop[i]);
					}
				}
				nonBoughtSize = temporary.size(); // update banyak item yang blom dibeli di shop
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
			Console::setColor(206); // BRIGHT RED BACKGROUND, WITH YELLOW TEXT
			Console::setCursorPos(35, 0);
			printf(" - TRISTAM SHOP - \n\n");
			Console::resetColor();
			printf(" =======================================================================================\n");
			printf(" %3s | %18s | %5s  | %-28s | %10s | %6s\n", "No.", "ITEM NAME", "PRICE", "ITEM EFFECTS", "RESTRICTION", "TYPE");
			printf(" =======================================================================================\n");

			if (temporary.size() == 0)
			{
				if (nonBoughtSize > 0)
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
					}
					type += ">";
					Console::setColor(color);
					printf("%s", type.c_str());
					Console::resetColor();
					printf(" //\n\n");
				}
				else printf("\n                              // EMPTY SHOP //\n\n"); // kalau inventory kosong
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

				printf(" %2d. | %18s | %6d | %-28s | %11s | %6s\n", i, (*iter)->getName().c_str(), (*iter)->getPrice(), (*iter)->getEffect().c_str(), restriction.c_str(), type.c_str());
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
			case 0:
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

			cout << " ========= Shop Menu ========\n\n";
			cout << " Your Gold: ";
			Console::setColor(Console::COLOR_YELLOW);
			cout << karakter->getGold() << " G\n\n";
			Console::setColor(Console::COLOR_WHITE);

			Console::setCursorVisibility(false);
			int flag = 0;
			bool printFlag = true;
			//pickMenu = 0;

			int currY = Console::getCursorY();
			bool sortA = false; // saat di menu pilihan sort, click 'a'
			bool sortD = false; // saat di menu pilihan sort, click 'd' (SEBENERNYA GK PERLU, TAPI GPP, BUAT KONSISTENSI)
			delayFlag = 0;
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
					cout << "BUY ITEM";

					Console::setColor(Console::COLOR_WHITE);
					printf("\n ");
					if (pickMenu == 2) Console::setColor(79);
					else Console::setColor(Console::COLOR_WHITE);
					string job;
					switch (karakter->getJob())
					{
					case Human::Assassin: job = "ASSASSIN"; break;
					case Human::Paladin: job = "PALADIN"; break;
					case Human::Barbarian: job = "BARBARIAN"; break;
					}
					cout << job << " COMPATIBLE ONLY: ";
					Console::setColor(Console::COLOR_YELLOW);
					if (pickMenu == 2) Console::setColor(78);
					if (yourClassOnly) printf("YES");
					else printf("NO");

					Console::setColor(Console::COLOR_WHITE);
					printf("\n ");
					if (pickMenu == 3) Console::setColor(79);
					else Console::setColor(Console::COLOR_WHITE);
					cout << "BACK";

					Console::setColor(Console::COLOR_WHITE);
					printFlag = false;
				}
				char buff = Console::getKeyPressed();
				if (buff != -1)
				{
					if (delayFlag)
					{
						if (buff == 'M' || buff == 'm')
						{
							Music::playBackgroundMusic(-1);
						}
						if (buff == VK_UP || buff == 0x57) // 0x57 == 'w'
						{
							pickMenu = (pickMenu - 1 + 4) % 4;
							printFlag = true;
						}
						else if (buff == VK_DOWN || buff == 0x53) // 0x53 == 's'
						{
							pickMenu = (pickMenu + 1) % 4;
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
			} // end while dalem

			if (flag == 1)
			{
				continue; // (teken tab) filter ulang
			}

			int index;
			size_t temporarySize = temporary.size();
			bool buy = false;
			switch (pickMenu)
			{
			case 0: // sort item by...
			{
				int maks;
				if (filterType == 0) maks = 3;
				else maks = 4;
				if (sortA) sortType = (sortType - 1 + maks) % maks;
				else sortType = (sortType + 1) % maks;
				continue; // continue while luar
			}
			break;
			case 1: // buy item
			{
				if (temporary.size() > 0)
				{
					Console::setCursorVisibility(true);
					printf("\n\n");
					printf(" Input item number to buy ( 0 = cancel) [ 0 to %u ]: ", (unsigned int)temporarySize);
					index = Interface::getInt(0, temporarySize);

					if (index == 0)
					{
						delayFlag = 1;
						continue;
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
					printf("\n It will cost you ");
					Console::setColor(Console::COLOR_YELLOW);
					printf("%d G\n\n", temporary[index - 1]->getPrice());
					Console::setColor(Console::COLOR_WHITE);

					Console::setCursorVisibility(false);
					if (temporary[index - 1]->getPrice() > karakter->getGold())
					{
						Console::setColor(Console::COLOR_RED);
						printf(" You don't have that much gold!\n");
						Console::setColor(Interface::COLOR_GREY);
						printf(" (press enter to continue)");
						Interface::pressEnterPlease();
						Console::resetColor();
					}
					else
					{
						if ((temporary[index - 1]->getRestriction() > 0) && (temporary[index - 1]->getRestriction() != karakter->getJob()))
						{
							Console::setColor(Console::COLOR_MAGENTA);
							printf(" WARNING: THE ITEM HAS RESTRICTION <");
							switch (temporary[index - 1]->getRestriction())
							{
							case Human::Assassin:
								Console::setColor(Console::COLOR_RED);
								printf("ASSASSIN");
								break;
							case Human::Paladin:
								Console::setColor(Console::COLOR_GREEN);
								printf("PALADIN");
								break;
							case Human::Barbarian:
								Console::setColor(Console::COLOR_YELLOW);
								printf("BARBARIAN");
								break;
							}
							Console::setColor(Console::COLOR_MAGENTA);
							printf("> ONLY!\n");
						}
						Console::setColor(Console::COLOR_WHITE);
						printf(" Are you sure you want to buy it?\n ");
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
										Music::playBackgroundMusic(-1);
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
										if (pickWhat == 0) buy = true;
										break;
									}
									bufferDelay = 0;
								}
								else bufferDelay++;
							}
						} // end while
					}

					if (buy)
					{
						karakter->buyItem(temporary[index - 1]); // beli Itemnya
						karakter->setGold(-1 * (temporary[index - 1]->getPrice())); // kurangin gold sebanyak harga item nya
						Console::setColor(Console::COLOR_GREEN);
						printf("\n\n You have successfuly bought the item!\n");

						Console::setColor(Interface::COLOR_GREY);
						printf("\n (Press enter to continue)");
						Interface::pressEnterPlease();
						Console::setColor(Console::COLOR_WHITE);
						continue;
					}
				}
				else // kalau gk ada item di shop
				{
					Console::setColor(Console::COLOR_RED);
					printf("\n\n No Item detected!");
					Interface::delaySec(700);
					Console::resetColor();
					continue;
				}
			}
			break;
			case 2:
				// toggle your class only
				if (yourClassOnly) yourClassOnly = false;
				else yourClassOnly = true;
				break;
			case 3: // exit
				return;
			} // end switch


		} // end while luar
	}

};

#endif