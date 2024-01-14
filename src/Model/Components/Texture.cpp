//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "Texture.h"
#include "../../Game.h"


void Texture::init() {
	position = entity->getComponent<Position>();

	srcRect.x = srcRect.y = 0;
	destRect.x = position->x();
	destRect.y = position->y();

	srcRect.w = position->w();
	srcRect.h = position->h();
	destRect.w = (int) ((float)(srcRect.w) * position->s());
	destRect.h = (int)((float)(srcRect.h) * position->s());
}

void Texture::update() {
	destRect.x = position->x();
	destRect.y = position->y();
}

void Texture::draw() {
	TextureManager::drawTexture(texture, &srcRect, &destRect, flip);
}

void Texture::setTexture(const char *fileName, bool removeBackground) {
	texture = TextureManager::loadTexture(fileName, removeBackground);
}

void Texture::moveSourceTo(int x, int y) {
	srcRect.x = x * srcRect.w;
	srcRect.y = y * srcRect.h;
}

void Texture::setFlip(bool newValue) {
	flip = newValue;
}
