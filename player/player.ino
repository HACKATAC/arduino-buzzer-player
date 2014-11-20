#include "songs.h"
#include <string.h>


//Defining constants
#define START_STOP_PIN 2
#define NEXT_SONG_PIN 3
#define BUZE_PIN A2
#define DELAY_ON_STOP 500
#define TIME_ON_STATE_CHANGE 1000
#define SWITCH_CHANGE LOW
#define UPDATE_SONG_NAME 1
#define MAX_NAME_SIZE 25
#define DELAY_BETWEEN_SONGS 2000


//Defining types

//Program state
typedef enum {
	RUN = 1,
	STOP = 0
} Player_state;

typedef enum {
	NORMAL = 1,
	RANDOM = 2
} Player_behaviour;

//Attributes

//ActualSong (pointing to the actual note)
long *actualMusic;

//Last update (Player_state) change
//Wait a few time between changes in order
//to avoid the noisy in the circuit
unsigned long lastChangeStateMilli;

//Last song change
//Wait a few time between changes in order
//to avoid the noisy in the circuit
unsigned long lastChangeSongMilli;

//Array of songs
//Be free of add or remove songs
//Be sure
long *songs[] =
	{ starWars, simpsons, indiana, knighRider, misionImp, topGun, bond,
smbDeath, smbWater, smbUnderground };

//The number of songs sizeof(songs)/sizeof(long*)
unsigned long numberOfSongs;

//The number of the actualSong
int actualSong = 0;

//The state of the player, by default STOP.
Player_state player_state = RUN;

//The max song name's length
char actualSongName[MAX_NAME_SIZE];

//The next song behaviour
Player_behaviour player_behaviour = NORMAL;

// functions signature

/**
 *
 *setup method, set up the arduino pins and load the first song. 
 */
void setup(void);

/**
 * Play the actual note. If the song doesn't have
 * more notes return 0, else 1.
 *
 * buzze current note and do the delay
 *
 */
int playActualNote(void);

/**
 * Load the song polonged
 * by songs[actualSong % numberOfSongs]
 * And updates the song name
 * The max song's length is defined by MAX_NAME_SIZE 
 */
void loadSong(void);

/**
 * Play the actual note. If the song has'nt more notes
 * load the next song.
 *
 * listen for stop/start and nextSong events
 *
 */
void loop(void);

/**
 * Polong to the next song
 * If the list is ended
 * polong to the first. You
 * can change this behaviohur
 * and add shuffle or whatever
 * you want. Just make sure that
 * actualSong is in the bounds of the array
 * of songs
 */
void nextSong(void);

/**
 * Updates the actual song's name
 *
 */
void updateSongName();

/**
 * Do a delay of millis
 *
 */
void doDelay(int value);

/**
 * Returns a random long
 * between 0 and max
 *
 */
int randomValue(int maxValue);



//FUNCTIONS BODY

int randomValue(int maxValue)
{
	return millis() % maxValue;
}

void doDelay(int value)
{
	delay(value);
}


void setup()
{
	numberOfSongs = sizeof(songs) / sizeof(long *);
	pinMode(START_STOP_PIN, INPUT);
	pinMode(NEXT_SONG_PIN, INPUT);
	pinMode(BUZE_PIN, OUTPUT);
	lastChangeStateMilli = millis();
	lastChangeSongMilli = millis();
	randomSeed(analogRead(3));
	loadSong();
}

int playActualNote()
{
	long actualNote = *actualMusic;
	if (actualNote != 0) {
		actualMusic++;
		long note = ((actualNote >> 16) & 0xFFFF);
		long duration = (actualNote & 0xFFFF);
		if (note != 0) {
			tone(BUZE_PIN, note, duration);
			doDelay(duration - 1);
		} else {
			doDelay(duration);
		}
		return 1;
	}
	return 0;
}


void loadSong()
{
	actualMusic = songs[actualSong % numberOfSongs];
	if (*actualMusic == 0) {
		actualMusic++;
		while (*actualMusic != 0) {
			actualMusic++;
		}
		actualMusic++;
	}
	updateSongName();
}

void updateSongName()
{
	long *song = songs[actualSong % numberOfSongs];
	if (*song == 0) {
		song++;					//Pointing the first number
		int sizeName = 0;
		while (*song != 0 && sizeName < MAX_NAME_SIZE) {
			long actualChunck = *song;
			long i;
			for (i = 0; i < 4 && sizeName < MAX_NAME_SIZE; i++) {
				const char actualChar = (char) actualChunck % 0xFF;
				actualSongName[sizeName++] = actualChar;
				actualChunck = actualChunck >> 8;
			}
			song++;
		}
		for (; sizeName < MAX_NAME_SIZE; sizeName++) {
			actualSongName[sizeName] = '\0';
		}
	}
}

void loop()
{
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
	if (player_state == RUN) {
		int state = playActualNote();
		if (state == 0) {
			nextSong();
		}
	} else {
		doDelay(DELAY_ON_STOP);
	}

}

void nextSong()
{
	if (player_behaviour == RANDOM) {
		actualSong = randomValue(numberOfSongs);
	} else {
		actualSong++;
	}
	doDelay(DELAY_BETWEEN_SONGS);
	loadSong();
}
