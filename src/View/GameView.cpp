//
// Created by Filip Dabkowski on 15/12/2023.
//

#include "cstring"
#include "cstdio"

#include "../../sdl/include/SDL.h"

#include "GameView.h"
#include "../Config/GameConfig.h"


GameView::GameView(SDL_Renderer *ren) {
	renderer = ren;
	charTexture = TextureManager::loadTexture("Assets/cs8x8.bmp", renderer);
}

void GameView::update(double delta) {
	frameCount++;
	fpsTimer += delta;

	if (fpsTimer > 0.5) {
		currentFps = frameCount * 2;
		frameCount = 0;
		fpsTimer -= 0.5;
	}
}

void GameView::render() {
	SDL_Rect infoRect = {4, 4, SCREEN_WIDTH - 8, 36};

	SDL_SetRenderDrawColor(renderer, 0, 0, 111, 255);
	SDL_RenderFillRect(renderer, &infoRect);

	snprintf(text, 128, "Current fps value: %.1lf", currentFps);
	renderText(text , SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 10);

//	snprintf(text, 128, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
//	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);
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

		SDL_RenderCopy(renderer, charTexture, &src, &dest);

		startX += 8;
		string++;
	}
}
