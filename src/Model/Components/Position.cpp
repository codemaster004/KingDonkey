//
// Created by Filip Dabkowski on 16/12/2023.
//

#include "Position.h"
#include "../../Game.h"

void Position::update()  {
	pos->add(speed->scalarMultiply(Game::delta));
}

void Position::setSpeed(float speedX, float speedY) {
	speed->x(speedX);
	speed->y(speedY);
}

void Position::setSpeedX(float speedX) {
	speed->x(speedX);
}

void Position::setSpeedY(float speedY) {
	speed->y(speedY);
}

Vector2D *Position::getSpeed() {
	return this->speed;
}

void Position::setPos(float posX, float posY) {
	pos->x(posX);
	pos->y(posY);
}

Vector2D *Position::getPos() {
	return this->pos;
}
