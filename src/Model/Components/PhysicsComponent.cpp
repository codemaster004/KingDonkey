//
// Created by Filip Dabkowski on 19/12/2023.
//

#include "PhysicsComponent.h"
#include "../../Game.h"

void PhysicsComponent::init() {
	position = entity->getComponent<PositionComponent>();
}

void PhysicsComponent::update() {
	if (applyGravity) {
		position->getSpeed()->add(Vector2D(0, 0.1));
	} else {
		position->getSpeed()->y(0);
	}
}

void PhysicsComponent::setGravity(bool newValue) {
	applyGravity = newValue;
}
