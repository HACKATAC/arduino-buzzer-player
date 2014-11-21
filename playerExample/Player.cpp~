#include "Player.h"

Player::Player(long** songs, int numberOfSongs,int buzePin) {
	this->songs = songs;
	this->numberOfSongs = numberOfSongs;
	this->buzePin = buzePin;
	this->loadSong();
	pinMode(buzePin, OUTPUT);
	timeBetweenSongs = TIME_BETWEEN_SONGS;
}
		
char* Player::getName() {
	return this->actualSongName;
}
	
void Player::loop() {
	long actualNote = *actualMusic;
	if(nextNoteMilli - millis() < 4) {
		if (actualNote != 0) {
			actualMusic++;
			long note = ((actualNote >> 16) & 0xFFFF);
			long duration = (actualNote & 0xFFFF);
			if (note != 0) {
				Serial.println(note);
				tone(buzePin, note, duration);
				nextNoteMilli = (duration - 1) + millis();;
			} else {
				nextNoteMilli = (duration) + millis();
			}
		} else {
			nextSong();
			this->nextNoteMilli = millis() +  timeBetweenSongs;
		}
	}
}
	
void Player::loadSong() {
	actualMusic = songs[actualSong % numberOfSongs];
	if (*actualMusic == 0) {
		actualMusic++;
		while (*actualMusic != 0) {
			actualMusic++;
		}
		actualMusic++;
	}
	this->nextNoteMilli=millis();
	updateSongName();
}

void Player::nextSong() {
	if (player_behaviour == RANDOM) {
		actualSong = randomValue(numberOfSongs);
	} else {
		actualSong++;
	}
	loadSong();
}
		
void Player::setPlayerBehaviour(Player_behaviour player_behaviour) {
	this->player_behaviour = player_behaviour;
}
		
void Player::setPlayerState(Player_state player_state) {
	this->player_state = player_state;
}
		
void Player::setSongsList(long** songs, int numberOfSongs) {
	this->songs = songs;
	this->numberOfSongs = numberOfSongs;
}

void Player::updateSongName(){
	long *song = this->songs[this->actualSong % this->numberOfSongs];
	if (*song == 0) {
		song++;					//Pointing the first number
		int sizeName = 0;
		while (*song != 0 && sizeName < PLAYER_MAX_NAME_SIZE) {
			long actualChunck = *song;
			long i;
			for (i = 0; i < 4 && sizeName < PLAYER_MAX_NAME_SIZE; i++) {
				const char actualChar = (char) actualChunck % 0xFF;
				this->actualSongName[sizeName++] = actualChar;
				actualChunck = actualChunck >> 8;
			}
			song++;
		}
		for (; sizeName < PLAYER_MAX_NAME_SIZE; sizeName++) {
			this->actualSongName[sizeName] = '\0';
		}
	}
}

unsigned long Player::getMilliNextSong() {
	return this->nextNoteMilli;
}

int Player::randomValue(int maxValue) {
	return millis() % maxValue;
}
