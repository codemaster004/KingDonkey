//
// Created by Filip Dabkowski on 20/12/2023.
//

#include "GameLevelModel.h"
#include "../Game.h"


void GameLevelModel::initGameBorders() {
	// Top Border
	addCollideableObject(0, 0, SCREEN_WIDTH, 40, Border);
	// Bottom Border
	addCollideableObject(0, SCREEN_HEIGHT, SCREEN_WIDTH, 10, Border);
	// Right Border
	addCollideableObject(SCREEN_WIDTH, 0, 10, SCREEN_HEIGHT, Border);
	// Left Border
	addCollideableObject(-10, 0, 10, SCREEN_HEIGHT, Border);
}

void GameLevelModel::addCollideableObject(int posX, int posY, int width, int height, CollisionEntityLabel label) {
	Entity *temp = objects.addEntity();
	temp->addComponent<PositionComponent>(posX, posY, width, height);
	temp->addComponent<CollisionComponent>(label);
}

void GameLevelModel::createLvl1() {
//	mapBackground = TextureManager::loadTexture("Background/Background-0006.bmp");

	addCollideableObject(96, 704, 769, 20, Floor);
	addCollideableObject(200, 554, 30, 150, Ladder);
}
