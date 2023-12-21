//
// Created by Filip Dabkowski on 20/12/2023.
//

#include "GameLevelModel.h"
#include "../Game.h"


void GameLevelModel::initGameBorders() {
	addCollideableObject(0, SCREEN_HEIGHT, SCREEN_WIDTH, 10, Border);
	addCollideableObject(SCREEN_WIDTH, 0, 1, SCREEN_HEIGHT, Border);
	addCollideableObject(0, 0, SCREEN_WIDTH, 40, Border);
	addCollideableObject(0, 0, 1, SCREEN_HEIGHT, Border);
}

void GameLevelModel::addCollideableObject(int posX, int posY, int width, int height, CollisionEntityLabel label) {
	Entity *temp = objects.addEntity();
	temp->addComponent<PositionComponent>(posX, posY, width, height);
	temp->addComponent<CollisionComponent>(Box, label);
}

void GameLevelModel::createLvl1() {
	addCollideableObject(100, 380, 100, 30, Floor);
	addCollideableObject(400, 380, 80, 30, Floor);
	addCollideableObject(150, 280, 400, 30, Floor);
	addCollideableObject(350, 160, 150, 30, Floor);
}
