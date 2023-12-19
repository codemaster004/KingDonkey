//
// Created by Filip Dabkowski on 19/12/2023.
//

#ifndef KINGDONKEY_PLAYERVIEWMODEL_H
#define KINGDONKEY_PLAYERVIEWMODEL_H

#include "../Model/PlayerModel.h"


class PlayerViewModel {
public:
	static void handleInput(SDL_Event event, PlayerModel *player) {
		PositionComponent *position = player->getComponent<PositionComponent>();
		position->getSpeed()->multiply(Vector2D(0, 1));
		switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_SPACE) {
					player->getComponent<PhysicsComponent>()->setGravity(true);
					position->setSpeedY(-5); // TODO: WHY
				}
				if (event.key.keysym.sym == SDLK_UP) {

				}
				if (event.key.keysym.sym == SDLK_DOWN) {

				}
				if (event.key.keysym.sym == SDLK_RIGHT) {
					position->getSpeed()->add(Vector2D(1, 0));
				}
				if (event.key.keysym.sym == SDLK_LEFT) {
					position->getSpeed()->add(Vector2D(-1, 0));
				}
				break;
			default:
				break;
		}
	}
};


#endif //KINGDONKEY_PLAYERVIEWMODEL_H
