//
// Created by Filip Dabkowski on 14/01/2024.
//

#include "PlayerModel.h"
#include "../Game.h"

PlayerModel::PlayerModel() {
	float scale = 1.5;

	addComponent<Position>(Game::config.playerConfig.startX, Game::config.playerConfig.startY, 28, 28, scale);
	addComponent<Texture>("Warden.bmp");
	addComponent<Animation>(8, 0.2);
	addComponent<Collision>(8 * scale, 26 * scale, Collision::Player);
	addComponent<Physics>(true);
	addComponent<Keyboard>();
}