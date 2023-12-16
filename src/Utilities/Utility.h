//
// Created by Filip Dabkowski on 15/12/2023.
//

#ifndef KINGDONKEY_UTILITY_H
#define KINGDONKEY_UTILITY_H

#include "../Config/GameConfig.h"

unsigned int max(unsigned int a, unsigned int b);

void delay(unsigned int microS);

double toSeconds(unsigned int gameTime);

unsigned int toMicroSeconds(double worldTime);

unsigned int toMicroSeconds(unsigned int gameTime);

unsigned int toGameTime(double worldTime);

unsigned int fromSDLTimeToGameTime(unsigned int SDLTime);

#endif //KINGDONKEY_UTILITY_H
