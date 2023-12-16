//
// Created by Filip Dabkowski on 14/12/2023.
//

#ifndef KINGDONKEY_GAMECONFIG_H
#define KINGDONKEY_GAMECONFIG_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Config {
public:
	const int FPS = 512;
	const double frameDelay = 1000.0 / FPS; // use 1000 for conversion from seconds to milli.

};

#endif //KINGDONKEY_GAMECONFIG_H
