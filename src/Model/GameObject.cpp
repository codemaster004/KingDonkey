//
// Created by Filip Dabkowski on 15/12/2023.
//

#include "GameObject.h"
#include "../View/TextureManager.h"

GameObject::GameObject(const char *textureFile, SDL_Renderer *ren, int x, int y) {
	renderer = ren;
	objTexture = TextureManager::loadTexture(textureFile, renderer);

	xPos = x;
	yPos = y;
}

void GameObject::update() {

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 90;
	srcRect.h = 90;

	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void GameObject::render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}
