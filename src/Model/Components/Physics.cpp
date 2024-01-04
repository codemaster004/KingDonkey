//
// Created by Filip Dabkowski on 19/12/2023.
//

#include "Physics.h"
#include "../../Game.h"


void Physics::init() {
	position = entity->getComponent<Position>();
}

void Physics::update() {
	if (applyGravity) {
		position->getSpeed()->add(Vector2(0, (float) (Game::config.gravity * Game::delta)));
	}
}

void Physics::setGravity(bool newValue) {
	applyGravity = newValue;
}

bool Physics::getGravity() const {
	return applyGravity;
}
