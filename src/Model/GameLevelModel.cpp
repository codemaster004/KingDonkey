//
// Created by Filip Dabkowski on 20/12/2023.
//

#include "GameLevelModel.h"
#include "../Game.h"


void GameLevelModel::initGameBorders() {
	addCollideableObject(0, SCREEN_HEIGHT, SCREEN_WIDTH, 10, Floor);
	addCollideableObject(SCREEN_WIDTH, 0, 1, SCREEN_HEIGHT, Wall);
	addCollideableObject(0, 0, SCREEN_WIDTH, 40, Floor);
	addCollideableObject(0, 0, 1, SCREEN_HEIGHT, Wall);
}

void GameLevelModel::addCollideableObject(int posX, int posY, int width, int height, CollisionEntityLabel label) {
	Entity *temp = objects.addEntity();
	temp->addComponent<PositionComponent>(posX, posY, width, height);
	temp->addComponent<CollisionComponent>(Box, label);
}
