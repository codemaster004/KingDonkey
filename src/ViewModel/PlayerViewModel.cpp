//
// Created by Filip Dabkowski on 19/12/2023.
//

#include "PlayerViewModel.h"
#include "../Game.h"
#include "../Model/Components/Keyboard.h"

/**
 * @brief Handles input events for the player.
 *
 * This function is responsible for processing SDL input events and updating the player's position
 * and keyboard state accordingly.
 *
 * @param event The SDL_Event representing the input event.
 * @param player The PlayerModel object.
 */
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


/**
 * @brief Process the player's input to control their movement and actions.
 *
 * This function takes in a PlayerModel object and updates its Position, Collision, and Animation components based
 * on the player's input from the Keyboard component. The function checks for specific key presses to determine
 * the player's actions.
 *
 * @param player The PlayerModel object representing the player.
 */
void PlayerViewModel::processInput(PlayerModel *player) {
	auto *position = player->getComponent<Position>();
	auto *collision = player->getComponent<Collision>();
	auto *animation = player->getComponent<Animation>();

	auto keyboard = player->getComponent<Keyboard>();

	// If the Space key is pressed and the player is colliding with the ground but not a ladder,
	// the player's vertical speed is set to the jump speed specified in the Game configuration.
	if (keyboard->getKey(Keyboard::KeySpace)) {
		if (collision->getCollision(Collision::Ground) && !collision->getCollision(Collision::Ladder)) {
			position->setSpeedY(Game::config.jumpSpeed);
		}
	}

	// If the right arrow key is pressed, the player's horizontal speed is set to the walking speed specified in the
	// Game configuration, and the Animation component is set to the MovingRight state.
	// the same is checked for left arrow key.
	if (keyboard->getKey(Keyboard::ArrRight)) {
		position->setSpeedX(Game::config.walkingSpeed);
		animation->setAnimationState(MovingRight);
	} else if (keyboard->getKey(Keyboard::ArrLeft)) {
		position->setSpeedX(-Game::config.walkingSpeed);
		animation->setAnimationState(MovingLeft);
	} else { // If neither the right nor left arrow key is pressed, the player's horizontal speed is set to 0.
		position->getSpeed()->setX(0);
	}

	// If the arrow key is pressed, the player's and player is on the ladder set the speed to walking speed.
	// Down arrow key is handled similarly however it can not be pressed when player is at the bottom of a ladder.
	if (keyboard->getKey(Keyboard::ArrUp) && collision->getCollision(Collision::Ladder)) {
		position->setSpeedY(-Game::config.walkingSpeed);
	} else if (keyboard->getKey(Keyboard::ArrDown) && collision->getCollision(Collision::Ladder) &&
			   !collision->getCollision(Collision::LadderBottom)) {
		position->setSpeedY(Game::config.walkingSpeed);
	}
}
