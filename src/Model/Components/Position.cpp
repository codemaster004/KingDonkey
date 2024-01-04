//
// Created by Filip Dabkowski on 16/12/2023.
//

#include "Position.h"
#include "../../Game.h"

void Position::update()  {
	pos->add(speed->scalarMultiply(Game::delta));
}

void Position::setSpeed(float speedX, float speedY) {
	speed->setX(speedX);
	speed->setY(speedY);
}

void Position::setSpeedX(float speedX) {
	speed->setX(speedX);
}

void Position::setSpeedY(float speedY) {
	speed->setY(speedY);
}

Vector2 *Position::getSpeed() {
	return this->speed;
}

void Position::setPos(float posX, float posY) {
	pos->setX(posX);
	pos->setY(posY);
}

Vector2 *Position::getPos() {
	return this->pos;
}
