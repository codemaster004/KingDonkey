//
// Created by Filip Dabkowski on 15/12/2023.
//

#include "unistd.h"

#include "Utility.h"

unsigned int max(unsigned int a, unsigned int b) {
	return a > b ? a : b;
}

void delay(unsigned int microS) {
	usleep(microS);
}

double toSeconds(unsigned int gameTime) {
	return gameTime * worldTimeMultiplier;
}

unsigned int toMicroSeconds(double worldTime) {
	return (unsigned int) (worldTime * gameTimeMultiplier);
}

unsigned int toMicroSeconds(unsigned int gameTime) {
	return (unsigned int) (gameTime * gameTimeMultiplier / NSMultiplier);
}

unsigned int toGameTime(double worldTime) {
	return (unsigned int) (worldTime * gameTimeMultiplier);
}

unsigned int fromSDLTimeToGameTime(unsigned int SDLTime) {
	return SDLTime * SDLTimeMultiplier;
}