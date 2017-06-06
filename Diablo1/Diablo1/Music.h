#pragma once

#ifndef MUSIC_H
#define MUSIC_H

// Please note that this header perhaps is going to be migrated to Interface.h

#pragma comment( lib, "Winmm.lib" ) //this is in Windows.h but still have to be declared. Don't know why :(
#include <Windows.h>
#include <mmsystem.h>
//gonna need this for .mp3 and .WAV files

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

public:

	static void playBackgroundMusic(int bgm) {
		stopBackgroundMusic();
		//open file according to the place
		//untuk sementara alias BGM = "musik"
		switch (bgm) {
		case 1:	//town
			mciSendString("open \"audio\\town1.mp3\" type mpegvideo alias musik", NULL, 0, NULL);
			break;
		case 2:	//cave
			mciSendString("open \"audio\\cave1.mp3\" type mpegvideo alias musik", NULL, 0, NULL);
			break;
		case 3:	//battle
			mciSendString("open \"audio\\battle1.mp3\" type mpegvideo alias musik", NULL, 0, NULL);
			break;
		case 4:	//victory
			mciSendString("open \"audio\\victory.mp3\" type mpegvideo alias musik", NULL, 0, NULL);
			break;
		case 5:	//lose
			mciSendString("open \"audio\\gameover.mp3\" type mpegvideo alias musik", NULL, 0, NULL);
			break;
		case 6:	//title screen sampai story
			mciSendString("open \"audio\\intro.mp3\" type mpegvideo alias musik", NULL, 0, NULL);
			break;
		}
		//Play
		mciSendString("play musik repeat", NULL, 0, NULL);
	}

	static void playSoundEffect(int action) {
		mciSendString("close efek", NULL, 0, 0);
		switch (action) {
		case 1:	//normal hit in battle
			mciSendString("open \"audio\\hit2.wav\" type mpegvideo alias efek", NULL, 0, NULL);
			break;
		case 2:	//critical hit in battle
			mciSendString("open \"audio\\hit2.wav\" type mpegvideo alias efek", NULL, 0, NULL); // SAMA AJA, LUL
			break;
		}



		//play
		mciSendString("play efek", NULL, 0, NULL);
	}
};






#endif // !MUSIC.H
