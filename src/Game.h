//
// Created by Filip Dabkowski on 14/12/2023.
//

#ifndef KINGDONKEY_GAME_H
#define KINGDONKEY_GAME_H

#include "SDL.h"
#include "Config/GameConfig.h"
#include "Model/PlayerModel.h"
#include "View/GameView.h"
#include "Model/EntityManager/Manager.h"
#include "ViewModel/CollisionViewModel.h"
#include "Utilities/Timer.h"


class Game {
private:
	SDL_Window *window;
	SDL_Event event;

	/* Important Variables */

	bool isRunning; ///< For main game loop

	Uint32 frameTime = 0; ///< How long the previous frame took

	/* Models */

	GameView gameView;
	GameLevelModel *gameLevel = nullptr;

	CollisionViewModel collisionViewModel;
	PlayerModel *player;
	Manager manager = Manager();
	Timer timer = Timer();

	/* Methods */

	void handleEvents();

	void update();

	void renderFrame();

	static void sleep(uint64_t frameDuration);

public:
	Game() = default;

	static float delta;
	static Config config;
	static SDL_Renderer *renderer;

	bool initialize(const char *title, int width, int height);

	void run();

	void gameMechanics();

	void clean();

	~Game() = default;
};


#endif //KINGDONKEY_GAME_H
