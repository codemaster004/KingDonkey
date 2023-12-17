//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "../../sdl/include/SDL.h"

#include "TextureComponent.h"
#include "PositionComponent.h"
#include "../../Game.h"


void TextureComponent::init() {
	srcRect.x = srcRect.y = 0;
	destRect.x = destRect.y = 0;
	srcRect.h = srcRect.w = 90;
	destRect.h = destRect.w = 90;
}

void TextureComponent::update() {
	auto *position = entity->getComponent<PositionComponent>();
	destRect.x = (int)(position->x());
	destRect.y = (int)(position->y());
}

void TextureComponent::draw() {
	TextureManager::drawTexture(texture, &srcRect, &destRect);
}

void TextureComponent::setTexture(const char *fileName) {
	texture = TextureManager::loadTexture(fileName);
}
