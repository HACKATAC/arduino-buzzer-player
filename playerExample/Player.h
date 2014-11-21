#include "Arduino.h"

#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_MAX_NAME_SIZE 25

#define TIME_BETWEEN_SONGS 4000

typedef enum {
	RUN = 1,
	STOP = 0
} Player_state;

typedef enum {
	NORMAL = 1,
	RANDOM = 2
} Player_behaviour;


class Player{

	public:
		Player(long** songs, int numberOfSongs,int buzePin);
		char* getName();
		void loop();
		void nextSong();
		void setPlayerBehaviour(Player_behaviour player_behaviour);
		void setPlayerState(Player_state player_state);
		void setSongsList(long** songs, int numberOfSongs);
		unsigned long getMilliNextSong();
	private:
		void loadSong();
		void updateSongName();
		int randomValue(int maxValue);

	private:
		//Delay until next note
		unsigned long nextNoteMilli;
	public:
		//int time between songs
		unsigned long timeBetweenSongs;
		//buze pin
		int buzePin;
		//Number of songs
		int numberOfSongs;
		//List of all songs
		long** songs;
		//Name of the actual song
		char actualSongName[PLAYER_MAX_NAME_SIZE];
		//The state of the player
		Player_state player_state;
		//The behaviour of the player
		Player_behaviour player_behaviour;

		//ActualSong (pointing to the actual note)
		long *actualMusic;

		int actualSong;

		short repeat;
};


#endif