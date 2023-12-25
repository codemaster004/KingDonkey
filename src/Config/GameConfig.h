//
// Created by Filip Dabkowski on 14/12/2023.
//

#ifndef KINGDONKEY_GAMECONFIG_H
#define KINGDONKEY_GAMECONFIG_H

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

const unsigned int NSMultiplier = 1000000;
const unsigned int MSMultiplier = 1000;
const unsigned int gameTimeMultiplier = 1000000;
const double worldTimeMultiplier = 1.0 / gameTimeMultiplier;
const unsigned int SDLTimeMultiplier = gameTimeMultiplier / MSMultiplier;

class Config {
public:
	const int FPS = 120; ///< Expected number of Frames [1/second]

	// use 1_000_000 for conversion from seconds to micro.
	const unsigned int idealFrameTime = (int)(gameTimeMultiplier / FPS); ///< Expected time of one Frame [microsecond]

	const char *baseAssetsDir = "Assets/";

	const float gravity = 1000;

	const float jumpSpeed = -300;

	const float walkingSpeed = 190;
};

#endif //KINGDONKEY_GAMECONFIG_H
