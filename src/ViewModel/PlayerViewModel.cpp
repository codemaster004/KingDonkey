//
// Created by Filip Dabkowski on 19/12/2023.
//

#include "PlayerViewModel.h"
#include "../Game.h"


void PlayerViewModel::handleInput(SDL_Event event, PlayerModel *player) {
	auto position = player->getComponent<Position>();
	auto keyboard = player->getComponent<Keyboard>();

	int key = event.key.keysym.sym;
	switch (event.type) {
		case SDL_KEYDOWN:
			if (key == SDLK_SPACE) {
				keyboard->keyPressed(Keyboard::KeySpace);
			} else if (key == SDLK_UP) {
				keyboard->keyPressed(Keyboard::ArrUp);
			} else if (key == SDLK_DOWN) {
				keyboard->keyPressed(Keyboard::ArrDown);
			} else if (key == SDLK_RIGHT) {
				keyboard->keyPressed(Keyboard::ArrRight);
			} else if (key == SDLK_LEFT) {
				keyboard->keyPressed(Keyboard::ArrLeft);
			}
			break;
		case SDL_KEYUP:
			if (key == SDLK_SPACE) {
				keyboard->keyLifted(Keyboard::KeySpace);
			} else if (key == SDLK_LEFT || key == SDLK_RIGHT) {
				keyboard->keyLifted(Keyboard::ArrRight);
				keyboard->keyLifted(Keyboard::ArrLeft);
			} else if (key == SDLK_DOWN || key == SDLK_UP) {
				keyboard->keyLifted(Keyboard::ArrUp);
				keyboard->keyLifted(Keyboard::ArrDown);
				position->getSpeed()->setY(0);
			}
			break;
		default:
			break;
	}
}


void PlayerViewModel::processInput(PlayerModel *player) {
	auto *position = player->getComponent<Position>();
	auto *collision = player->getComponent<Collision>();
	auto *animation = player->getComponent<Animation>();

	auto keyboard = player->getComponent<Keyboard>();

	// If the Space key is pressed and the player is colliding with the ground but not a ladder,
	// the player's vertical speed is set to the jump speed specified in the Game configuration.
	if (keyboard->getKey(Keyboard::KeySpace)) {
		if (collision->getCollision(Collision::Ground) && !collision->getCollision(Collision::Ladder)) {
			position->setSpeedY(Game::config.playerConfig.jumpSpeed);
		}
	}

	// If the right or  arrow key is pressed, the player's horizontal speed is set to the walking speed,
	// the Animation component is set to the MovingRight|MovingLeft state.
	if (keyboard->getKey(Keyboard::ArrRight)) {
		position->setSpeedX(Game::config.playerConfig.walkingSpeed);
		animation->setState(Animation::MovingRight);
	} else if (keyboard->getKey(Keyboard::ArrLeft)) {
		position->setSpeedX(-Game::config.playerConfig.walkingSpeed);
		animation->setState(Animation::MovingLeft);
	} else { // If neither the right nor left arrow key is pressed, the player's horizontal speed is set to 0.
		position->getSpeed()->setX(0);
	}

	// If the arrow key is pressed, the player's and player is on the ladder set the speed to walking speed.
	// Down arrow key is handled similarly however it can not be pressed when player is at the bottom of a ladder.
	if (keyboard->getKey(Keyboard::ArrUp) && collision->getCollision(Collision::Ladder)) {
		position->setSpeedY(-Game::config.playerConfig.walkingSpeed);
	} else if (keyboard->getKey(Keyboard::ArrDown) && collision->getCollision(Collision::Ladder) &&
			   !collision->getCollision(Collision::LadderBottom)) {
		position->setSpeedY(Game::config.playerConfig.walkingSpeed);
	}
}
