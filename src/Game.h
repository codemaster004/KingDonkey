//
// Created by Filip Dabkowski on 14/12/2023.
//

#ifndef KINGDONKEY_GAME_H
#define KINGDONKEY_GAME_H

#include "SDL.h"
#include "Config/GameConfig.h"
#include "Model/GameObject.h"
#include "Model/PlayerModel.h"
#include "View/GameView.h"
#include "Model/EntityManager/Manager.h"


class Game {
private:
	Config config;

	SDL_Window *window;

	SDL_Event event;

	/* Important Variables */

	bool isRunning; ///< For main game loop

	Uint32 frameTime = 0;        ///< How long the previous frame took
	double delta, worldTime = 0; ///< Timer for in game passage of time

	/* Models */

	GameView *gameView;
	GameObject *eti;
	PlayerModel *player;

	Manager manager;

	/* Methods */

	void handleEvents();

	void update();

	void renderFrame();

	unsigned int getTicks();

public:
	Game() = default;

	static SDL_Renderer *renderer;

	bool initialize(const char *title, int width, int height);

	void run();

	void clean();

	~Game() = default;
};


#endif //KINGDONKEY_GAME_H
