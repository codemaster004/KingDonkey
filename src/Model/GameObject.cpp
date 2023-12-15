//
// Created by Filip Dabkowski on 15/12/2023.
//

#include "GameObject.h"
#include "../View/TextureManager.h"

GameObject::GameObject(const char *textureFile, SDL_Renderer *ren) {
	renderer = ren;
	objTexture = TextureManager::loadTexture(textureFile, renderer);
}

void GameObject::update() {
	xPos = 0;
	yPos = 0;

	srcRect.w = 90;
	srcRect.h = 90;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void GameObject::render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}
