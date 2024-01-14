//
// Created by Filip Dabkowski on 14/12/2023.
//

#ifndef KINGDONKEY_GAMECONFIG_H
#define KINGDONKEY_GAMECONFIG_H

#include "cstdint"


#define SCREEN_WIDTH 896
#define SCREEN_HEIGHT 608

#define TILE_SIZE 32
#define COLLIDER_HEIGHT 10
#define COLLIDER_WIDTH 10
#define LADDER_WIDTH 20

const uint64_t USMultiplier = (int) (1e6);
const uint64_t MSMultiplier = 1000;
const uint64_t gameTimeMultiplier = (int) (1e6);
const float worldTimeMultiplier = 1.0 / gameTimeMultiplier;
const uint64_t SDLTimeMultiplier = gameTimeMultiplier / MSMultiplier;


class PlayerConfig {
public:
	const int startX = 160; // Starting X position of the player [px]
	const int startY = 200; // Starting Y position of the player [px]

	const float jumpSpeed = -300; ///< Speed of player when jump is triggered [px/seconds]
	const float walkingSpeed = 190; ///< Player speed when moving along X-Axis [px/seconds]

	// Other player-specific configurations can be added here
};

class Config {
public:
	const int FPS = 60; ///< Expected number of Frames [1/second]

	// use 1_000_000 for conversion from seconds to micro.
	const uint64_t idealFrameTime = (int) (gameTimeMultiplier / FPS); ///< Expected time of one Frame [microsecond]

	const char* baseAssetsDir = "Assets/"; ///< path to base of folder for storing in game assets.

	const float gravity = 1000; ///< Gravity speed [px/seconds^2]

	// Instance of PlayerConfig
	PlayerConfig playerConfig;
};


#endif //KINGDONKEY_GAMECONFIG_H
