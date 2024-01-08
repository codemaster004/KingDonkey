//
// Created by Filip Dabkowski on 14/12/2023.
//

#include "cstdio"

#include "Game.h"
#include "Utilities/Utility.h"
#include "Model/PlayerModel.h"
#include "ViewModel/CollisionViewModel.h"
#include "ViewModel/PlayerViewModel.h"


SDL_Renderer *Game::renderer = nullptr;

Config Game::config = Config();

float Game::delta = 0;


bool Game::initialize(const char *title, int width, int height) {
	// If SDL did not manage to set itself up.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("Initialization Error accrued!");
		return false;
	}

	// Try creating window.
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
							  SDL_WINDOW_RESIZABLE);
	if (window == nullptr) {
		printf("Could not create Renderer!");
		return false;
	}

	// Try creating renderer for drawing on the actual window.
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr) {
		printf("Could not create Renderer!");
		return false;
	}

	// Set the default drawing color for renderer.
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

	return true;
}


void Game::run() {
	isRunning = true;
	delta = toSeconds(config.idealFrameTime);

	gameLevel = new GameLevelModel();
	gameLevel->createLvl1();

	gameView = GameView();
	gameView.setLevelMode(gameLevel);

	player = (PlayerModel *) (manager.addEntity<PlayerModel>());

	uint64_t duration;
	while (isRunning) {
		timer.mark();

		// keyboard & window events
		handleEvents();

		gameMechanics();

		update();
		renderFrame();

		duration = timer.mark();
		sleep(duration);
	}
}


void Game::handleEvents() {
	while (SDL_PollEvent(&event)) {
		// handle system quit case
		switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					isRunning = false;
				}
				if (event.key.keysym.sym == SDLK_n) {

				}
				break;
			case SDL_QUIT:
				isRunning = false;
				break;
		}
		PlayerViewModel::handleInput(event, player);
	}
	PlayerViewModel::processInput(player);
}


void Game::update() {
	gameView.update();
	manager.update();
}


void Game::gameMechanics() {
	collisionViewModel.handleCollision(player, &gameView.levelModel->objects);
}


void Game::renderFrame() {
	// Clear the renderer what was before from last frame
	SDL_RenderClear(renderer);

	// Space for actual rendering of the game
	gameView.render();

	SDL_SetRenderDrawColor(renderer, 30, 30, 110, 255); // blue for Game Entities
	manager.render();

	// Show on screen everything that is inside the current renderer;
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderPresent(renderer);
}


void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


void Game::sleep(uint64_t frameDuration) {
	// todo: uncomment, only for debug
//	delta = toSeconds(max(frameDuration, config.idealFrameTime));
	delta = toSeconds(config.idealFrameTime);
	if (config.idealFrameTime > frameDuration)
		delay(toMicroSeconds(config.idealFrameTime - frameDuration));
}
