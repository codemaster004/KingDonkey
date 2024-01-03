//
// Created by Filip Dabkowski on 19/12/2023.
//

#include "PlayerViewModel.h"
#include "../Game.h"

void PlayerViewModel::handleInput(SDL_Event event, PlayerModel *player) {
	auto *position = player->getComponent<PositionComponent>();
	auto *physics = player->getComponent<PhysicsComponent>();
	auto *animation = player->getComponent<AnimationComponent>();
	auto *collision = player->getComponent<CollisionComponent>();

	int key = event.key.keysym.sym;
	switch (event.type) {
		case SDL_KEYDOWN:
			if (key == SDLK_SPACE) {
				if (!physics->getGravity() && !collision->getCollision(Collision_Ladder)) {
					physics->setGravity(true);
					position->setSpeedY(Game::config.jumpSpeed);
				}
			}
			if (key == SDLK_UP) {
				if (collision->getCollision(Collision_Ladder)) {
					position->setSpeedY(-Game::config.walkingSpeed);
				}
			}
			if (key == SDLK_DOWN) {
				if (collision->getCollision(Collision_Ladder) && !collision->getCollision(Collision_LadderBottom)) {
					position->setSpeedY(Game::config.walkingSpeed);
				}
			}
			if (key == SDLK_RIGHT) {
				position->setSpeedX(Game::config.walkingSpeed);
				animation->setAnimationState(MovingRight);
			}
			if (key == SDLK_LEFT) {
				position->setSpeedX(-Game::config.walkingSpeed);
				animation->setAnimationState(MovingLeft);
			}
			break;
		case SDL_KEYUP:
			if (key == SDLK_LEFT || key == SDLK_RIGHT) {
				position->getSpeed()->multiply(Vector2D(0, 1));
			}
			if (key == SDLK_DOWN || key == SDLK_UP) {
				position->getSpeed()->multiply(Vector2D(1, 0));
			}
			break;
		default:
			break;
	}
}
