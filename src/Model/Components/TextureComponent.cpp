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

	destRect.w = srcRect.w = position->w();
	destRect.h = srcRect.h = position->h();

}

void TextureComponent::update() {
	destRect.x = position->x();
	destRect.y = position->y();
}

void TextureComponent::draw() {
	TextureManager::drawTexture(texture, &srcRect, &destRect);
}

void TextureComponent::setTexture(const char *fileName) {
	texture = TextureManager::loadTexture(fileName);
}
