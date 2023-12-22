//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "SDL.h"

#include "TextureComponent.h"
#include "../../Game.h"


void TextureComponent::init() {
	position = entity->getComponent<PositionComponent>();

	srcRect.x = srcRect.y = 0;
	destRect.x = position->x();
	destRect.y = position->y();

	srcRect.w = position->w();
	srcRect.h = position->h();
	destRect.w = (int) ((float)(srcRect.w) * position->s());
	destRect.h = (int)((float)(srcRect.h) * position->s());
}

void TextureComponent::update() {
	destRect.x = position->x();
	destRect.y = position->y();
}

void TextureComponent::draw() {
	TextureManager::drawTexture(texture, &srcRect, &destRect, flip);
}

void TextureComponent::setTexture(const char *fileName, bool removeBackground) {
	texture = TextureManager::loadTexture(fileName, removeBackground);
}

void TextureComponent::moveSourceTo(int x, int y) {
	srcRect.x = x * srcRect.w;
	srcRect.y = y * srcRect.h;
}

void TextureComponent::setFlip(bool newValue) {
	flip = newValue;
}
