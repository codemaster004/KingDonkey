//
// Created by Filip Dabkowski on 19/12/2023.
//

#include "PlayerViewModel.h"
#include "../Game.h"

void PlayerViewModel::handleInput(SDL_Event event, PlayerModel *player) {
	auto *position = player->getComponent<PositionComponent>();
	auto *physics = player->getComponent<PhysicsComponent>();

	int key = event.key.keysym.sym;
	switch (event.type) {
		case SDL_KEYDOWN:
			if (key == SDLK_SPACE) {
				if (!physics->getGravity()) {
					physics->setGravity(true);
					position->setSpeedY(Game::config.jumpSpeed);
				}
			}
			if (key == SDLK_UP) {

			}
			if (key == SDLK_DOWN) {

			}
			if (key == SDLK_RIGHT) {
				position->setSpeedX(Game::config.walkingSpeed);
			}
			if (key == SDLK_LEFT) {
				position->setSpeedX(-Game::config.walkingSpeed);
			}
			break;
		case SDL_KEYUP:
			if (key == SDLK_LEFT || key == SDLK_RIGHT) {
				position->getSpeed()->multiply(Vector2D(0, 1));
			}
		default:
			break;
	}
}
