//
// Created by Filip Dabkowski on 14/12/2023.
//

#ifndef KINGDONKEY_GAME_H
#define KINGDONKEY_GAME_H

#include "../../sdl/include/SDL.h"
#include "Config/GameConfig.h"
#include "Model/GameObject.h"


class Game {
private:
	Config config;

	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Event event;

	/* Important Variables */

	bool isRunning; ///< For main game loop

	Uint32 frameTime = 0;        ///< How long the previous frame took
	double delta, worldTime = 0; ///< Timer for in game passage of time

	/* Models */

	GameObject* eti;

	/* Methods */

	void handleEvents();

	void update();
	void renderFrame();

public:
	Game() = default;
	~Game() = default;

	bool initialize(const char *title, int width, int height);

	void run();

	void clean();
};


#endif //KINGDONKEY_GAME_H