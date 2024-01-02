//
// Created by Filip Dabkowski on 15/12/2023.
//

#include "unistd.h"
#include "cstring"

#include "Utility.h"
#include "../Config/GameConfig.h"

uint64_t max(uint64_t a, uint64_t b) {
	return a > b ? a : b;
}

uint64_t min(uint64_t a, uint64_t b) {
	return a < b ? a : b;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

float max(float a, float b) {
	return a > b ? a : b;
}

float min(float a, float b) {
	return a < b ? a : b;
}


char *joinStrings(const char *string1, size_t len1, const char *string2, size_t len2) {
	char *fullString = new char[len1 + len2 + 1];
	fullString[len1 + len2] = '\0';

	for (int i = 0; i < len1; ++i) {
		fullString[i] = string1[i];
	}
	for (int i = 0; i < len2; ++i) {
		fullString[len1 + i] = string2[i];
	}
	return fullString;
}

char *joinStrings(const char *string1, const char *string2) {
	size_t len1 = strlen(string1);
	size_t len2 = strlen(string2);
	return joinStrings(string1, len1, string2, len2);
}

void delay(uint64_t microS) {
	usleep(microS);
}

float toSeconds(uint64_t gameTime) {
	return (float) (gameTime) * worldTimeMultiplier;
}

uint64_t toMicroSeconds(float worldTime) {
	return (unsigned int) (worldTime * gameTimeMultiplier);
}

uint64_t toMicroSeconds(uint64_t gameTime) {
	return (unsigned int) (gameTime * (gameTimeMultiplier / NSMultiplier));
}

uint64_t toGameTime(float worldTime) {
	return (unsigned int) (worldTime * gameTimeMultiplier);
}

uint64_t fromSDLToGameTime(uint64_t SDLTime) {
	return SDLTime * SDLTimeMultiplier;
}

float fromSDLToWorldTime(uint64_t SDLTime) {
	return (float) (SDLTime) * SDLTimeMultiplier * worldTimeMultiplier;
}