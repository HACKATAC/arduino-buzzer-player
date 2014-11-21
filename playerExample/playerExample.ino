#include "songs.h"
#include <string.h>
#include "Player.h"

//Defining constants
#define START_STOP_PIN 2
#define NEXT_SONG_PIN 3
#define BUZE_PIN A2
#define DELAY_ON_STOP 500
#define TIME_ON_STATE_CHANGE 1000
#define SWITCH_CHANGE LOW
#define UPDATE_SONG_NAME 1

#define DELAY_BETWEEN_SONGS 2000

//Array of songs
//Be free of add or remove songs
long *songs[] =
	{  starWars, simpsons, indiana, knighRider, misionImp, topGun, bond,
};//smbDeath, smbWater, smbUnderground };

Player player((long**)&songs, sizeof(songs)/sizeof(long*),BUZE_PIN);


void setup()
{
	Serial.begin(9600);
}


void loop() {
	Serial.println("Loop");
	player.loop();
	long millisSeconds = millis();
	if(player.getMilliNextSong() - millisSeconds > 0){
		delay(player.getMilliNextSong()-millis());
	}
}
