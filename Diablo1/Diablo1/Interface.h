#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <cstdio>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "common.h"
#include "Music.h"

// forward declaration to fix circular dependency
class Shop;
class Introduction;
class NewGame;
class Home;

using namespace std;

class Interface //untuk load screen, dll
{
private:

public:
	static int const COLOR_GREY = 7;

	static Shop& shop;
	static Introduction& introduction;
	static NewGame& newGame;
	static Home& home;
	
	static void delaySec(int sec)
	{
		int i = sec;
		char buff;
		int delay = 0;
		while (i > 0)
		{
			buff = Console::getKeyPressed(); // supaya saat delay, apapun yang ditekan bakal kebuang
			if (buff != -1)
			{
				if (delay)
				{
					if (buff == 'm' || buff == 'M')
					{
						Music::playBackgroundMusic(Music::TOGGLE); // MUTE UNMUTE
						delay = 0;
					}
				}
				else delay = 1;
			}
			i--;
			Console::delay(1);
		}
	}

	static void ErrorMsg(string headerName,int line, int SaveErrorCount)
	{
		system("cls");
		Console::setCursorPos(0, 0);
		printf("ERROR ERROR ERROR ERROR ERROR\n");
		printf("Header: %s\n", headerName.c_str());
		printf("Line: %d\n", line);
		if (SaveErrorCount != -1)
		{
			printf("SAVE ERROR: READ ITERATION NUMBER %d\n", SaveErrorCount);
		}
		pressEnterPlease();
		return;
	}

	static int getInt(int min, int max)
	{
		Console::setCursorVisibility(true);
		int x = Console::getCursorX()+1;
		int y = Console::getCursorY(); 

		stringstream output;
		int output_int;
		string out;
		char buff;
		Console::setCursorPos(x, y);
		while (1)
		{
			buff = _getch();
			if (buff == 'm' || buff == 'M') Music::playBackgroundMusic(Music::TOGGLE); // mute
			if (buff == VK_RETURN)
			{
				if (out.size() > 0)
				{
					out.push_back('\n');
					break;
				}
				else continue;
			}
			if (buff == VK_BACK)
			{
				if (out.size() > 0) // backspace kalau di dalem string out ada isinya
				{
					out.pop_back();
					printf("\b \b");
				}
				continue;
			}
			//if (buff == VK_ESCAPE) continue;
			if (buff >= '0' && buff <= '9')
			{
				out.push_back(buff);
				printf("%c", buff);
			}
		}
		output << out;
		output >> output_int;

		while(output.fail() || output_int<min || output_int>max)
		{
			// flush
			{
				output.clear();
				output.ignore(10000000, '\n');
				output.sync();
				output.clear();
				int counter = (int)out.size();
				for (int i = 0; i < counter; i++) printf("\b \b");
				out.clear();
				Console::setCursorPos(x, y);
				Console::setColor(Console::COLOR_RED);
				printf("INVALID INPUT!");
				Interface::delaySec(500);
				Console::setCursorPos(x, y);
				printf("               ");
				Console::resetColor();
			}
			Console::setCursorPos(x, y);
			// ulang lagi
			while (1)
			{
				buff = _getch();
				if (buff == VK_RETURN)
				{
					if (out.size() > 0)
					{
						out.push_back('\n');
						break;
					}
					else continue;
				}
				if (buff == VK_BACK)
				{
					if (out.size() > 0) // backspace kalau di dalem string out ada isinya
					{
						out.pop_back();
						printf("\b \b");
					}
					continue;
				}
				if (buff == VK_ESCAPE) continue; // (buff==VK_ESCAPE) gk berfungsi gtau kenapa
				if (buff>='0' && buff<='9')
				{
					out.push_back(buff);
					printf("%c", buff);
				}
			}
			output << out;
			output >> output_int;
		}

		Console::setCursorVisibility(false);
		return output_int;
	}

	static void pressEnterPlease()
	{
		while (1)
		{
			char x = _getch(); // tidak ngebaca key release (hanya key press), tapi getKeyPressed iya
			if (x == 'M' || x == 'm')
			{
				Music::playBackgroundMusic(Music::TOGGLE);
			}
			if (x == VK_RETURN)
			{
				int sampah;
				while (true)
				{
					sampah = Console::getKeyPressed(); // harus pake ini, supaya getKeyPressed lainnya nggak ada masalah
					if (sampah == VK_RETURN) {
						//printf(" <-");
						//Interface::delaySec(50);
						break;
					}
				}
				break;
			}
			printf("\b"); // backspace
		}
	}

	static void flush()
	{
		cin.clear();
		cin.ignore(10000000, '\n');
	}

	static void setWindowSize(int width, int height)
	{
		HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console, &r); //stores the console's current dimensions

		MoveWindow(console, r.left, r.top, width, height, TRUE);
	}

	static void setDefaultFont(int font)
	{
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0; // Width of each character in the font
		cfi.dwFontSize.Y = font; // Height
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	}

	Interface() { // constructor
		Console::initialize();
		Console::setCursorVisibility(false);
	}


}; // END CLASS

#endif