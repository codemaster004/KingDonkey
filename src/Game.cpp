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
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("Initialization Error accrued!");
		return false;
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
	if (window == nullptr) {
		printf("Could not create Renderer!");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr) {
		printf("Could not create Renderer!");
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

	return true;
}

void Game::handleEvents() {
	while (SDL_PollEvent(&event)) {
		// handle system quit case
		switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
		}
		PlayerViewModel::handleInput(event, player);
	}
}

void Game::run() {
	isRunning = true;

	Uint32 frameStart;

	gameView = GameView();

	gameLevel = new GameLevelModel();
	gameView.setLevelMode(gameLevel);
	gameView.levelModel->createLvl1();

//	eti = new GameObject("eti.bmp", SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2);
	player = (PlayerModel *)(manager.addEntity<PlayerModel>());

//	Vector2D changeVec = Vector2D(1.01, -1.01);

	while (isRunning) {
		frameStart = getTicks();
		worldTime += toSeconds(frameTime);

//		delta = toSeconds(frameTime);
//		delta = toSeconds(config.idealFrameTime);
		delta = toSeconds(max(frameTime, config.idealFrameTime));

		// keyboard & window events
		handleEvents();

		gameMechanics();

		update();

		renderFrame();

		frameTime = getTicks() - frameStart;
		if (config.idealFrameTime > frameTime) {
			delay(toMicroSeconds(config.idealFrameTime - frameTime));
		}
	}
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

	SDL_SetRenderDrawColor(renderer, 30, 30, 110, 255);
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

unsigned int Game::getTicks() {
	return fromSDLTimeToGameTime(SDL_GetTicks());
}
