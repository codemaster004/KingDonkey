//
// Created by Filip Dabkowski on 19/12/2023.
//

#include "PlayerViewModel.h"
#include "../Game.h"
#include "../Model/Components/Keyboard.h"

void PlayerViewModel::handleInput(SDL_Event event, PlayerModel *player) {
	auto *position = player->getComponent<Position>();
	auto *physics = player->getComponent<Physics>();
	auto *animation = player->getComponent<Animation>();
	auto *collision = player->getComponent<Collision>();
	auto keyboard = player->getComponent<Keyboard>();

	int key = event.key.keysym.sym;
	switch (event.type) {
		case SDL_KEYDOWN:
			if (key == SDLK_SPACE) {
				keyboard->keyPressed(Keyboard::KeySpace);
//				if (!physics->getGravity() && !collision->getCollision(Collision_Ladder)) {
//					physics->setGravity(true);
//					position->setSpeedY(Game::config.jumpSpeed);
//				}
			} else if (key == SDLK_UP) {
				if (collision->getCollision(Collision_Ladder)) {
					position->setSpeedY(-Game::config.walkingSpeed);
				}
			} else if (key == SDLK_DOWN) {
				if (collision->getCollision(Collision_Ladder) && !collision->getCollision(Collision_LadderBottom)) {
					position->setSpeedY(Game::config.walkingSpeed);
				}
			} else if (key == SDLK_RIGHT) {
				position->setSpeedX(Game::config.walkingSpeed);
				animation->setAnimationState(MovingRight);
			} else if (key == SDLK_LEFT) {
				position->setSpeedX(-Game::config.walkingSpeed);
				animation->setAnimationState(MovingLeft);
			}
			break;
		case SDL_KEYUP:
			if (key == SDLK_SPACE) {
				keyboard->keyLifted(Keyboard::KeySpace);
			} else if (key == SDLK_LEFT || key == SDLK_RIGHT) {
				position->getSpeed()->setX(0);
			} else if (key == SDLK_DOWN || key == SDLK_UP) {
				position->getSpeed()->setY(0);
			}
			break;
		default:
			break;
	}
}


void PlayerViewModel::processInput(PlayerModel *player) {
	auto *physics = player->getComponent<Physics>();
	auto *position = player->getComponent<Position>();
	auto *collision = player->getComponent<Collision>();

	auto keyboard = player->getComponent<Keyboard>();
	if (keyboard->getKey(Keyboard::KeySpace)) {
		if (collision->getCollision(Collision_Ground) && !collision->getCollision(Collision_Ladder)) {
			position->setSpeedY(Game::config.jumpSpeed);
		}
	}
}
