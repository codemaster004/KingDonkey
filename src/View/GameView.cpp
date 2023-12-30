//
// Created by Filip Dabkowski on 15/12/2023.
//

#include "cstring"
#include "cstdio"

#include "SDL.h"

#include "GameView.h"
#include "../Game.h"


void GameView::init() {

}

void GameView::update() {
	frameCount++;
	fpsTimer += Game::delta;

	if (fpsTimer > 0.5) {
		currentFps = frameCount * 2;
		frameCount = 0;
		fpsTimer -= 0.5;
	}
}

void GameView::render() {
//	SDL_Rect infoRect = {4, 4, SCREEN_WIDTH - 8, 36};

//	SDL_RenderFillRect(Game::renderer, &infoRect);
//
//	snprintf(text, 128, "Current fps value: %.1lf", currentFps);
//	renderText(text , SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 10);

	TextureManager::drawTexture(levelModel->getMapBgc(), nullptr, nullptr);

	SDL_SetRenderDrawColor(Game::renderer, 111, 0, 0, 255);
//	levelModel->objects.render();
//	levelModel->objects.render();
}

void GameView::renderText(char *string, int startX, int topY) {
	int charX, charY;

	SDL_Rect src, dest;

	src.w = 8;
	src.h = 8;
	dest.w = 8;
	dest.h = 8;

	int character;
	while (*string) {
		character = *string & 255;

		charY = (character / 16) * 8;
		charX = (character % 16) * 8;

		src.x = charX;
		src.y = charY;
		dest.x = startX;
		dest.y = topY;

		SDL_RenderCopy(Game::renderer, charTexture, &src, &dest);

		startX += 8;
		string++;
	}
}

void GameView::setLevelMode(GameLevelModel *newModel) {
	levelModel = newModel;
}
