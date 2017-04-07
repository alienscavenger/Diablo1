/** You can copy paste this file, from beginning to the end (using ctrl+a ctrl+c) 
* @author Nikolas Stark
*/
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <vector>

// ================== global constant ==================
#define BUFFER_SIZE 255 // berapa besar character penampung sementara untuk string

/** Console class is an encapsulation of Console device that you use to make program.
* This class contains everything about console functions you need to create animation, colorful text, delay, print, input etc.
*/
#include <windows.h>

class Console {

private:
	static char buff[BUFFER_SIZE]; // used as temporary internal buffer
	static double freq; // frequency of this processor in megahertz
	Console() { }// private constructor = cannot be instantiated

	
	/** Helper function, no need to know */
	static void resetDefaultCharacterSet() {
		SetConsoleOutputCP(437);
		SetConsoleCP(437);
	}

	static CONSOLE_SCREEN_BUFFER_INFO getScreenBufferInfo() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO p;
		GetConsoleScreenBufferInfo(hConsole,&p);		
		return p;
	}

public:
	static const int COLOR_GRAY;
	static const int COLOR_WHITE;
	static const int COLOR_RED;
	static const int COLOR_GREEN;
	static const int COLOR_BLUE;
	static const int COLOR_MAGENTA;
	static const int COLOR_YELLOW;
	static const int COLOR_CYAN;

	static const int CONSOLE_WIDTH;
	static const int CONSOLE_HEIGHT;
	
	/** Initializes console, must be called immediately at the first statement in void main(). */
	static void initialize() { 
		// get the PC frequency
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		long long int PC_FREQ = Frequency.QuadPart;
		freq = PC_FREQ / 1000.0; // in megahertz

		Console::resetDefaultCharacterSet();
		Console::resetColor();		
		
	}

	/** Delay for x milisecond. Will block the process until the specified milisecond elapsed. */
	static void delay(double milisecond) {   
		LARGE_INTEGER StartingTime, EndingTime;
			
		double t = 0;
		while (t < milisecond) {

			QueryPerformanceCounter(&StartingTime);

			for (int loop=0;loop<1000; loop++);

			QueryPerformanceCounter(&EndingTime);
			t+= (EndingTime.QuadPart - StartingTime.QuadPart) / freq;	
		}
	}

	/** Resets the color to white */
	static void resetColor() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, Console::COLOR_WHITE);	
	}

	/** Sets the color to specific Console color provided (see Console color list).
	* Will affect further print out color (Console::printf, Console::println and Console::printd).
	*/
	static void setColor(int color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);	
	}

	/** Changes the current console cursor to coordinate x,y.
	 * Upper left coordinate (x,y) is (0,0). 
	 * WARNING: do not set x and y outside the boundary of console!
	 * @param x the new x coordinate of cursor
	 * @param y the new y coordinate of cursor
	 */
	static void setCursorPos(int x, int y) {

		COORD c;
		c.X = x; c.Y = y;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole,c);
		
	}

	/** Gets the x coordinate where the cursor is currently at. */
	static int getCursorX() {
		CONSOLE_SCREEN_BUFFER_INFO p = getScreenBufferInfo();
		return p.dwCursorPosition.X;
	}

	/** Gets the y coordinate where the cursor is currently at. */
	static int getCursorY() {
		CONSOLE_SCREEN_BUFFER_INFO p = getScreenBufferInfo();
		return p.dwCursorPosition.Y;
	}

	/** Gets the console width */
	static int getScreenWidth() {
		CONSOLE_SCREEN_BUFFER_INFO p = getScreenBufferInfo();
		return p.dwMaximumWindowSize.X;
	}
	
	/** Gets the console width */
	static int getScreenHeight() {
		CONSOLE_SCREEN_BUFFER_INFO p = getScreenBufferInfo();
		return p.dwMaximumWindowSize.Y;
	}

	/** Changes the console's title. */
	static void setTitle(const char *str) {
		SetConsoleTitle(str);
	}

	/** Displays or hiddens the visibility of console cursor. */
	static void setCursorVisibility(bool visible) {
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = visible ? TRUE:FALSE;
		SetConsoleCursorInfo(consoleHandle, &info);
	}

	/**Halts console to wait for further keyboard input and prints "Press any key to continue..." */
	static void pause() {
		system("pause");
	}

	/** Clears console screen. */
	static void clear() {
		system("cls");
	}

	/** Clear input buffer, similar to fflush(stdin). */
	static void flushInput() {
		HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
		FlushConsoleInputBuffer(hConsole);
	}

	/** Mencek apakah keyboard key tertentu ditekan. Hanya sanggup mendeteksi satu tombol saja. 
	@param keycodes array dari nilai dari KeyEvent.wVirtualKeyCode yang diinginkan (misal esc adalah VK_ESCAPE), masukkan -1 untuk semua tombol (any key), null = any key
	@param length panjang array keycodes
	@return keycode dari key yang ditekan atau -1 jika tidak ada
	*/
	static int getKeyPressed() {
		INPUT_RECORD eventBuffer[100];
		DWORD numEvents = 0;
		DWORD numEventsRead = 0;
		HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
		GetNumberOfConsoleInputEvents(hConsole,&numEvents);
		if (numEvents != 0) { // if there is at least one event
			ReadConsoleInput(hConsole, eventBuffer, numEvents, &numEventsRead); // read those events
			for (DWORD i = 0; i < numEventsRead; i++) { // cycle through input event
				// Check the event type: was it a key?
				if (eventBuffer[i].EventType == KEY_EVENT) {
					return eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
					/*
					if (keycode == 0) return true;
					// it is a key event, take its keycode
					int inputKeyCode = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
					Console::setCursorPos(1,1);
					Console::printf("%3d\n",inputKeyCode);
					if (keycode == inputKeyCode) return true;					*/
				}
			}
		}
		return -1;
	}

	/** Returns whether there is at least one hit from keyboard. */
	static bool isAnyKeyPressed() {
		return getKeyPressed() != -1;
	}

	/** Prints to the console similar as using C printf() function.
	* This is a replacement for printf().
	*/
	static int printf(const char *format,...) {
	
		va_list v;
		va_start(v,format);
		vsprintf_s(buff,BUFFER_SIZE,format,v);
		va_end(v);

		int len = strlen(buff);
		DWORD out;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		WriteConsole(hConsole,buff,len,&out,NULL);

		return len;
	}

	/** Just print the string to console and add newline after that */
	static void println(const char *str) {
		strcpy_s(buff,BUFFER_SIZE,str);
		strcat_s(buff,BUFFER_SIZE,"\n\r\0");

		int len = strlen(buff);
		DWORD out;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		WriteConsole(hConsole,buff,len,&out,NULL);

	}

	static void println() {
		Console::println("");
	}

	/**
	Mengubah string input menjadi integer, 
	fungsi ini lebih baik daripada atoi karena 
	apabila input invalid (huruf misalnya) maka atoi mengembalikan 0,
	sehingga kita tidak tahu apakah user input 0 atau invalid,
	sedangkan fungsi ini mengembalikan false.
	@param strIn string input yang ingin dijadikan integer
	@param intOut integer output jika sukses
	@return false jika gagal, true jika sukses
	*/
	static bool toInt(const char *strIn, int *intOut) {
		const char *p = strIn;
		if (intOut == NULL || strIn == NULL) return false;
	
		if (*p == '+' || *p == '-') p++; // jika tanda +/- maka skip char ini	
		if (*p == '\0') return false; // jika tidak ada apa2 maka gagal konversi ke int
		// loop hingga akhir pastikan hanya angka
		while (*p != '\0') {
			if (!isdigit(*p)) return false; // jika ada yang bukan angka langsung keluar		
			p++;
		}
	
		// isi intOut
		*intOut = (int)strtol(strIn,NULL,10);
	
		return true;
	}


	/**
	Meminta input sebuah character, fungsi ini dipastikan mengembalikan 
	salah satu karakter dari allowedCharList. 
	Buffer stdin di flush setelah fungsi ini dipanggil.
	@param strPrompt tulisan yang akan ditampilkan sebelum input
	@param allowedCharList list character yang diijinkan
	@return sebuah character dari allowedCharList
	*/
	static char askChar(const char *strPrompt, const char *allowedCharList) {
		while (true) {
			if (strPrompt != NULL) Console::printf("%s",strPrompt);
			int c = getc(stdin);
			fflush(stdin);
			for (int i=0; i<strlen(allowedCharList); i++) {
				if (c == allowedCharList[i]) {
					return (char)c;
				}
			}
		}
	}

	/** Menanyakan pertanyaan Y/N kepada user
	@return true jika user menjawab 'Y' dan false jika 'N' */
	static bool confirm(const char *prompt) {
		char buff[BUFFER_SIZE];
		sprintf_s(buff,BUFFER_SIZE,"%s [Y/N]? ",prompt);
		char c = askChar(buff,"YyNn");
		if (c == 'Y' || c == 'y') return true;
		return false;
	}

	/**
	Mendapatkan input int dari user antara minRange hingga maxRange.
	Hasil output integer pada return function dipastikan valid dan sesuai range.
	@param strPrompt tulisan yang akan ditampilkan sebelum input
	@param strInvalid tulisan yang muncul ketika user salah memasukkan input
	@param minRange batas min value yang diinginkan (harus <= maxRange)
	@param maxRange batas max value yang diinginkan
	@return value int yang diinput user dan sudah divalidasi
	*/
	static int askInt(const char *strPrompt, const char *strInvalid, int minRange, int maxRange) {
		int result;
		char strTemp[15];
		bool pass;
		if (minRange > maxRange) return maxRange;
		// ulangi terus hingga inputan benar
		while (true) { 
			if (strPrompt != NULL) Console::printf("%s [%d to %d]: ",strPrompt,minRange,maxRange);
			Console::nextString(stdin,strTemp,15);
			pass = Console::toInt(strTemp,&result);
			if (pass && (result >= minRange && result <= maxRange)){
				return result; // keluar ketika sudah menerima angka int yg valid
			}else {
				if (strInvalid != NULL) Console::printf("%s\n",strInvalid); 
			}
		}
	}

	/**
	Mendapatkan input string dari user. Sama seperti gets(str)
	@param strPrompt a string to print to user before inputting
	@return sebuah string dalam bentuk array of char yang menjadi input dari user
	*/
	static int askString(char *strOut) {
		int len = 0;
		while (len <= 0) {
			len = Console::nextString(stdin,strOut,BUFFER_SIZE);
		}
		return len;
	}
	
	/** 
	Mendapatkan input string berikutnya dari stdin hingga \n (enter) 
	dan memasukkan ke dalam string result
	character '\n' di akhir akan dihapus
	@param fp FILE pointer input stream yang akan dibaca (bisa diisi stdin)
	@param result penampung string untuk inputan 
	@param buffSize besar char buffer dari penampung result
	@return panjang char yang didapat, max buffSize-1 char */
	static int nextString(FILE *fp, char *result, int buffSize) {
		int len;
		// pastikan result tidak NULL
		if (result == NULL) return 0;

		// baca input dari stdin hingga \n atau \0 (yg mana duluan)
		if (fgets (result, buffSize, fp) == NULL) return 0;
    
		// pastikan buffer >= 2
		if (buffSize < 2) return 0; 
        
		// hitung panjang yang didapat
		len = strlen(result);

		// jika dapat \n di akhir string
		if (result[len-1] == '\n') { 
 			result[len-1] = '\0'; // hapus \n di akhir
			len--; // kurangi len dg 1 krn \n dihapus
		}
    
		// jika input lebih besar dari buffSize-1, buang char kelebihannya hingga \n atau EOF
		if (len == buffSize-1) {    	
    		int ch;
    		while (((ch = getchar()) != '\n') && (ch != '\0') && (ch != EOF)) ;        
		}
	
		// kembalikan jumlah char yang dibaca (selain \n)
		return len;	
	}
};

char Console::buff[BUFFER_SIZE];
const int Console::COLOR_GRAY = 8;
const int Console::COLOR_WHITE = 15;
const int Console::COLOR_RED = 12;
const int Console::COLOR_GREEN = 10;
const int Console::COLOR_BLUE = 9;
const int Console::COLOR_MAGENTA = 13;
const int Console::COLOR_YELLOW = 14;
const int Console::COLOR_CYAN = 11;

double Console::freq = 1.0;


#endif