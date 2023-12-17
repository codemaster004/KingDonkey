//
// Created by Filip Dabkowski on 15/12/2023.
//

#include "unistd.h"
#include "cstring"

#include "Utility.h"

unsigned int max(unsigned int a, unsigned int b) {
	return a > b ? a : b;
}

char *joinStrings(const char *string1, size_t len1, const char *string2, size_t len2) {
	char *fullString = new char [len1 + len2 + 1];
	fullString[len1 + len2] = '\0';

	for (int i = 0; i < len1; ++i) {
		fullString[i] = string1[i];
	}
	for (int i = 0; i < len2; ++i) {
		fullString[len1 + i] = string2[i];
	}
	return fullString;
}

char *joinStrings(const char*string1, const char *string2) {
	size_t len1 = strlen(string1);
	size_t len2 = strlen(string2);
	return joinStrings(string1, len1, string2, len2);
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
	return (unsigned int) (gameTime * (gameTimeMultiplier / NSMultiplier));
}

unsigned int toGameTime(double worldTime) {
	return (unsigned int) (worldTime * gameTimeMultiplier);
}

unsigned int fromSDLTimeToGameTime(unsigned int SDLTime) {
	return SDLTime * SDLTimeMultiplier;
}