//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "CollisionComponent.h"

#include "../../Game.h"

void CollisionComponent::init() {
	position = entity->getComponent<PositionComponent>();
	box.w = width = position->w();
	box.h = height = position->h();
	updatePos();
}

void CollisionComponent::update() {
	updatePos();
}

void CollisionComponent::updatePos() {
	box.x = position->x();
	box.y = position->y();
}
