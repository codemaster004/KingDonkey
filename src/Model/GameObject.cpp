//
// Created by Filip Dabkowski on 15/12/2023.
//

#include "cmath"
#include "GameObject.h"
#include "../View/TextureManager.h"
#include "../Config/GameConfig.h"

GameObject::GameObject(const char *textureFile, SDL_Renderer *ren, int x, int y) {
	renderer = ren;
	objTexture = TextureManager::loadTexture(textureFile, renderer);

	xPos = x;
	yPos = y;
}

void GameObject::update(double delta) {

	distance += 1 * delta;

	xPos = SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3;
	yPos = SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = srcRect.h = 90;

	destRect.x = xPos - srcRect.w / 2;
	destRect.y = yPos - srcRect.h / 2;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void GameObject::render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}
