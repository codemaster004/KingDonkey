//
// Created by Filip Dabkowski on 16/12/2023.
//

#include "PositionComponent.h"
#include "../../Game.h"

void PositionComponent::update()  {
	pos->add(speed->scalarMultiply(Game::delta));
}

void PositionComponent::setSpeed(float speedX, float speedY) {
	speed->x(speedX);
	speed->y(speedY);
}

void PositionComponent::setSpeedX(float speedX) {
	speed->x(speedX);
}

void PositionComponent::setSpeedY(float speedY) {
	speed->y(speedY);
}

Vector2D *PositionComponent::getSpeed() {
	return this->speed;
}

void PositionComponent::setPos(float posX, float posY) {
	pos->x(posX);
	pos->y(posY);
}

Vector2D *PositionComponent::getPos() {
	return this->pos;
}
