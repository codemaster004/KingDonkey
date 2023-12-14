//
// Created by Filip Dabkowski on 14/12/2023.
//

#include "cstdio"

#include "Game.h"
#include "View/TextureManager.h"

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

	SDL_Texture *charset;
	TextureManager::loadTexture("Assets/cs8x8.bmp", renderer);

	while (isRunning) {
		frameStart = SDL_GetTicks();
		delta = frameTime * 0.001; // conversion from milliseconds to seconds.
		worldTime += delta;

		// keyboard & window events
		handleEvents();

		renderFrame();

		frameTime = SDL_GetTicks() - frameStart;
		if (config.frameDelay > frameTime) {
			SDL_Delay(config.frameDelay - frameTime);
		}
	}
}

void Game::update() {

}

void Game::renderFrame() {
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
