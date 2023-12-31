//
// Created by Filip Dabkowski on 15/12/2023.
//

#ifndef KINGDONKEY_UTILITY_H
#define KINGDONKEY_UTILITY_H


int max(int a, int b);

unsigned int max(unsigned int a, unsigned int b);

float max(float a, float b);

int min(int a, int b);

unsigned int min(unsigned int a, unsigned int b);

float min(float a, float b);

void delay(unsigned int microS);

char *joinStrings(const char *string1, size_t len1, const char *string2, size_t len2);

char *joinStrings(const char *string1, const char *string2);

float toSeconds(unsigned int gameTime);

unsigned int toMicroSeconds(float worldTime);

unsigned int toMicroSeconds(unsigned int gameTime);

unsigned int toGameTime(float worldTime);

unsigned int fromSDLTimeToGameTime(unsigned int SDLTime);

#endif //KINGDONKEY_UTILITY_H
