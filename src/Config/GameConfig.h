//
// Created by Filip Dabkowski on 14/12/2023.
//

#ifndef KINGDONKEY_GAMECONFIG_H
#define KINGDONKEY_GAMECONFIG_H

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

const uint64_t NSMultiplier = 1000000;
const uint64_t MSMultiplier = 1000;
const uint64_t gameTimeMultiplier = 1000000;
const float worldTimeMultiplier = 1.0 / gameTimeMultiplier;
const uint64_t SDLTimeMultiplier = gameTimeMultiplier / MSMultiplier;

class Config {
public:
	const int FPS = 60; ///< Expected number of Frames [1/second]

	// use 1_000_000 for conversion from seconds to micro.
	const uint64_t idealFrameTime = (int)(gameTimeMultiplier / FPS); ///< Expected time of one Frame [microsecond]

	const char *baseAssetsDir = "Assets/"; ///< path to base of folder for storing in game assets.

	const float gravity = 1000; ///< Gravity speed [px/seconds^2]

	const float jumpSpeed = -300; ///< Speed of player when jump is triggered [px/seconds]

	const float walkingSpeed = 190; ///< Player speed when moving along X-Axis [px/seconds]
};

#endif //KINGDONKEY_GAMECONFIG_H
