//
// Created by Filip Dabkowski on 14/12/2023.
//

#include "cstdio"

#include "Game.h"
#include "Utilities/Utility.h"
#include "Model/PlayerModel.h"
#include "ViewModel/CollisionViewModel.h"


SDL_Renderer *Game::renderer = nullptr;

bool Game::initialize(const char *title, int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("Initialization Error accrued!");
		return false;
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
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
		// TODO: Player input handler
	}
}

void Game::run() {
	isRunning = true;

	Uint32 frameStart;

	gameView = new GameView();
	eti = new GameObject("eti.bmp", SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2);

	auto *player = manager.addEntity<PlayerModel>();
	Entity *wall = manager.addEntity();
	wall->addComponent<PositionComponent>(0, 0, SCREEN_WIDTH, 40);
	wall->addComponent<CollisionComponent>();

	while (isRunning) {
		frameStart = getTicks();
		worldTime += toSeconds(frameTime);
//		delta = toSeconds(frameTime);
		delta = toSeconds(max(frameTime, config.idealFrameTime));

		// keyboard & window events
		handleEvents();

		update();
		int8_t collided = CollisionViewModel::collisionBoxToBox(
			player->getComponent<CollisionComponent>()->box,
			wall->getComponent<CollisionComponent>()->box
		);
		if (collided >= 0) {
			printf("Hello World");
		}

		renderFrame();

		frameTime = getTicks() - frameStart;
		if (config.idealFrameTime > frameTime) {
			delay(toMicroSeconds(config.idealFrameTime - frameTime));
		}
	}
}

void Game::update() {
	gameView->update(delta);
	eti->update(delta);
	manager.update();
}

void Game::renderFrame() {
	// Clear the renderer what was left from last frame
	SDL_RenderClear(renderer);

	// Space for actual rendering of the game
	gameView->render();
	eti->render();
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
