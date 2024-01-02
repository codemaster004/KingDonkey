//
// Created by Filip Dabkowski on 15/12/2023.
//

#ifndef KINGDONKEY_UTILITY_H
#define KINGDONKEY_UTILITY_H


int max(int a, int b);

uint64_t max(uint64_t a, uint64_t b);

float max(float a, float b);

int min(int a, int b);

uint64_t min(uint64_t a, uint64_t b);

float min(float a, float b);

void delay(uint64_t microS);

char *joinStrings(const char *string1, size_t len1, const char *string2, size_t len2);

char *joinStrings(const char *string1, const char *string2);

float toSeconds(uint64_t gameTime);

uint64_t toMicroSeconds(float worldTime);

uint64_t toMicroSeconds(uint64_t gameTime);

uint64_t toGameTime(float worldTime);

uint64_t fromSDLToGameTime(uint64_t SDLTime);

float fromSDLToWorldTime(uint64_t SDLTime);

#endif //KINGDONKEY_UTILITY_H
