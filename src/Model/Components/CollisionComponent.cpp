//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "CollisionComponent.h"

#include "../../Game.h"

void CollisionComponent::init() {
	position = entity->getComponent<PositionComponent>();
	if (!(width || height)) {
		box.w = width = position->w() * position->s();
		box.h = height = position->h() * position->s();
	}
	updatePos();
}

void CollisionComponent::update() {
	updatePos();
}

void CollisionComponent::updatePos() {
	box.x = position->x() + position->w() * position->s() / 2 - width / 2;
	box.y = position->y() + position->h() * position->s() / 2 - height / 2;
}

void CollisionComponent::draw() {
	SDL_RenderDrawRect(Game::renderer, &box);
}
