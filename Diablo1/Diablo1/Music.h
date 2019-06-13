#pragma once

#ifndef MUSIC_H
#define MUSIC_H

// Please note that this header perhaps is going to be migrated to Interface.h

#pragma comment( lib, "Winmm.lib" ) //this is in Windows.h but still have to be declared. Don't know why :(
#include <Windows.h>
#include <mmsystem.h>
//gonna need this for .mp3 and .WAV files

using namespace std;

class Music {
	//MP3
	//---------------------------------------------------------------------------------------
	//mciSendString("open \"audio\\audio1.mp3\" type mpegvideo alias musik", NULL, 0, NULL);	to open the path to the music file
	//---------------------------------------------------------------------------------------
	//mciSendString("play musik", NULL, 0, NULL);			plays in the background then stop if finished
	//mciSendString("play musik repeat", NULL, 0, NULL);	plays int the background then repeat itself

	//WAV
	//---------------------------------------------------------------------------------------
	//PlaySound("audio/audio1.wav", NULL,SND_ASYNC);	open and play
	//OR we can use sndPlaySound("namaFile.wav", SND_FILENAME); without handle to output
	//---------------------------------------------------------------------------------------
	//SND_ASYNC plays in the background of the program
	//SND_SYNC plays sequential until the sound finished then the program continue

	//mp3 will be used mainly as background ambient music
	//there is a chance we will use wav files as sound effect

	//============================================================================================================

	//karena gw pakai alias nya sama buat semua place BGM jadi kalau play lagi, programnya akan nunggu lagu yang pertama selesai dulu. Solusinya adalah kita stop sendiri
	static void stopBackgroundMusic() {
		mciSendString("close musik", NULL, 0, 0);
	}

	static bool mute;
	static int save;

	static void playMusic(string name, string alias="musik") {
		string file = "open \"audio\\" + name + "\" type mpegvideo alias " + alias.c_str();
		mciSendString(file.c_str(), NULL, 0, NULL);
	}

public:
	static const int TOGGLE = 0;
	static const int MUTE = -1;
	static const int UNMUTE = -2;

	static const int TOWN = 1;
	static const int CAVE = 2;
	static const int BATTLE = 3;
	static const int VICTORY = 4;
	static const int LOSE = 5;
	static const int INTRO = 6;
	static const int OUTRO = 7;

	static const int HIT = 1;
	static const int CRIT = 2;
	static const int SKILL = 3;

	static void playBackgroundMusic(int bgm) {
		stopBackgroundMusic();
		if (bgm == 999) return;
		//open file according to the place
		//untuk sementara alias BGM = "musik"

		if (bgm == TOGGLE) // toggle mute dan unmute
		{
			if (!mute) // kalau sebelumnya tidak di-mute
			{
				// maka mute
				mute = true;
				playSoundEffect(MUTE);
				return;
			}
			else if (mute)
			{
				mute = false;
				playSoundEffect(UNMUTE);
				bgm = save;
			}
		}
		save = bgm;
		if (mute) return;
		switch (bgm) {
		case TOWN:	//town
			playMusic("town1.mp3");
			break;
		case CAVE:	//cave
			playMusic("cave1.mp3");
			break;
		case BATTLE:	//battle
			playMusic("battle1.mp3");
			break;
		case VICTORY:	//victory
			playMusic("victory.mp3");
			break;
		case LOSE:	//lose
			playMusic("gameover.mp3");
			break;
		case INTRO:	//title screen sampai story
			playMusic("intro.mp3");
			break;
		case OUTRO:
			playMusic("outro.mp3");
			break;
		}
		//Play
		mciSendString("play musik repeat", NULL, 0, NULL);
	}

	static void playSoundEffect(int action) {
		mciSendString("close efek", NULL, 0, 0);
		switch (action) {
		case UNMUTE: // unmute
			playMusic("unmute.mp3","efek");
			break;
		case MUTE: // mute
			playMusic("mute.mp3","efek");
			break;
		case HIT:	//normal hit in battle
			playMusic("hit2.wav","efek"); //NOTICE : gw samain akhirnya karena suaranya kecil
			break;
		case CRIT:	//critical hit in battle
			playMusic("hit2.wav","efek"); // SAMA AJA, LUL
			break;
		case SKILL:	//skill
			playMusic("skill.wav","efek");
			break;
		}

		//play
		mciSendString("play efek", NULL, 0, NULL);
	}
};

bool Music::mute = false;
int Music::save = INTRO;

#endif // !MUSIC.H
