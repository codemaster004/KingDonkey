//
// Created by Filip Dabkowski on 19/12/2023.
//

#include "PlayerViewModel.h"

void PlayerViewModel::handleInput(SDL_Event event, PlayerModel *player)  {
	auto *position = player->getComponent<PositionComponent>();
	int key = event.key.keysym.sym;
	switch (event.type) {
		case SDL_KEYDOWN:
			if (key == SDLK_SPACE) {
				player->getComponent<PhysicsComponent>()->setGravity(true);
				position->setSpeedY(-5); // TODO: WHY
			}
			if (key == SDLK_UP) {

			}
			if (key == SDLK_DOWN) {

			}
			if (key == SDLK_RIGHT) {
				position->setSpeedX(1);
			}
			if (key == SDLK_LEFT) {
				position->setSpeedX(-1);
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
