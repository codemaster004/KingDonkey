//
// Created by Filip Dabkowski on 15/12/2023.
//

#ifndef KINGDONKEY_UTILITY_H
#define KINGDONKEY_UTILITY_H

#include "../Config/GameConfig.h"


int max(int a, int b);

unsigned int max(unsigned int a, unsigned int b);

int min(int a, int b);

unsigned int min(unsigned int a, unsigned int b);

void delay(unsigned int microS);

char *joinStrings(const char *string1, size_t len1, const char *string2, size_t len2);

char *joinStrings(const char *string1, const char *string2);

double toSeconds(unsigned int gameTime);

unsigned int toMicroSeconds(double worldTime);

unsigned int toMicroSeconds(unsigned int gameTime);

unsigned int toGameTime(double worldTime);

unsigned int fromSDLTimeToGameTime(unsigned int SDLTime);

#endif //KINGDONKEY_UTILITY_H
