#include "songs.h"
#include <string.h>

#if  __GNUC__
#if  __x86_64__
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#endif
#endif

#define START_STOP_PIN 2
#define NEXT_SONG_PIN 3
#define BUZE_PIN A1
#define DELAY_ON_STOP 500
#define TIME_ON_STATE_CHANGE 1000
#define SWITCH_CHANGE LOW
#define UPDATE_SONG_NAME 1
#define MAX_NAME_SIZE 25
//Defining types

typedef enum {
	RUN = 1,
	STOP = 0
} Player_state;


//Attributes

int *actualMusic;
int length;
int state;
int lastChangeStateMilli;
int lastChangeSongMilli;
int *songs[] =
	{ starWars, simpsons, indiana, knighRider, misionImp, topGun, bond };

int numberOfSongs = 7;
int actualSong = 0;
Player_state player_state = STOP;
char actualSongName[MAX_NAME_SIZE];


// functions signature
void setup(void);
int playActualNote(void);
void loadSong(void);
void loop(void);
void nextSong(void);
void updateSongName();


void setup()
{
#if ! __GNUC__
#if ! __x86_64__
	pinMode(START_STOP_PIN, INPUT);
	pinMode(NEXT_SONG_PIN, INPUT);
	pinMode(BUZE_PIN, INPUT);
	lastChangeStateMilli = millis();
	lastChangeSongMilli = millis();
#endif
#endif
loadSong();
}

int playActualNote()
{
	int actualNote = *actualMusic;
	if (actualNote != 0) {
		int tone = ((actualNote >> 16) & 0xFFFF);
		int duration = (actualNote & 0xFFFF);
		if (tone != 0) {
#if ! __GNUC__
#if ! __x86_64__
			tone(BUZE_PIN, tone);
#endif
#endif
		}
#if ! __GNUC__
#if ! __x86_64__
		delay(duration);
#endif
#else
		printf("tone : %d, duration : %d \n", tone, duration);
#endif
		actualMusic++;
		return 1;
	}
	return 0;
}


void loadSong()
{
	actualMusic = songs[actualSong % numberOfSongs];
	if(*actualMusic == 0) {
		actualMusic++;
		while(*actualMusic != 0) {
			actualMusic++;
		}
		actualMusic++;
	}
	updateSongName();
}

void updateSongName() {	
	int* song = songs[actualSong % numberOfSongs];
	if(*song == 0) {
		song++;//Pointing to the first number
		int sizeName = 0;
		int size = 0;
		while(*song != 0) {
			int actualChunck = *song;
			int i;
			for(i = 0; i < 4; i++) {
				const char actualChar = (char) actualChunck % 0xFF;
				actualSongName[size++] = actualChar;
				actualChunck = actualChunck >> 8;	
			}
			song++;
		}
		for(; size < MAX_NAME_SIZE; size++) {
			actualSongName[size] = '\0';
		}
	}
}

void loop()
{
#if ! __GNUC__
#if ! __x86_64__
	if (digitalRead(START_STOP_PIN) == SWITCH_CHANGE
		&& (millis() - lastChangeStateMilli) > TIME_ON_STATE_CHANGE) {
		if (player_state == RUN) {
			player_state = STOP;
		} else {
			player_state = RUN;
		}
		lastChangeStateMilli = millis();
	}

	if (digitalRead(NEXT_SONG_PIN) == SWITCH_CHANGE
		&& (millis() - lastChangeSongMilli) > TIME_ON_STATE_CHANGE) {
		nextSong();
		lastChangeSongMilli = millis();
	}
#endif
#endif
	if (player_state == RUN) {
		int state = playActualNote();
		if (state == 0) {
			nextSong();
		}
	} else {
#if ! __GNUC__
#if ! __x86_64__
		delay(DELAY_ON_STOP);
#endif
#endif
	}

}

void nextSong()
{
	actualSong++;
	loadSong();

}

#if  __GNUC__
#if  __x86_64__
int main(int argc, char **argv)
{
	setup();
	player_state = RUN;
	while (1) {
		loop();
	}
}
#endif
#endif
