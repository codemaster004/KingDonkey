//
// Created by Filip Dabkowski on 20/12/2023.
//

#include "GameLevelModel.h"
#include "../Game.h"


void GameLevelModel::initGameBorders() {
	// Top Collision_Border
	addCollideableObject(0, 0, SCREEN_WIDTH, 40, Collision_Border);
	// Bottom Collision_Border
	addCollideableObject(0, SCREEN_HEIGHT, SCREEN_WIDTH, 10, Collision_Border);
	// Right Collision_Border
	addCollideableObject(SCREEN_WIDTH, 0, 10, SCREEN_HEIGHT, Collision_Border);
	// Left Collision_Border
	addCollideableObject(-10, 0, 10, SCREEN_HEIGHT, Collision_Border);
}

void GameLevelModel::addCollideableObject(int posX, int posY, int width, int height, CollisionEntityLabel label) {
	Entity *temp = objects.addEntity();
	temp->addComponent<PositionComponent>(posX, posY, width, height);
	temp->addComponent<CollisionComponent>(label);
}

void GameLevelModel::createLvl1() {
//	mapBackground = TextureManager::loadTexture("Background/Background-0006.bmp");

	addCollideableObject(96, 690, 169, 20, Collision_Floor);
	addCollideableObject(300, 554, 30, 150, Collision_Ladder);
}
