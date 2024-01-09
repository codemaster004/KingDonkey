//
// Created by Filip Dabkowski on 20/12/2023.
//

#include "GameLevelModel.h"
#include "../Game.h"


void GameLevelModel::initGameBorders() {
	// Top Border
	addCollideableObject(0, 0, SCREEN_WIDTH, 40, Collision::Border, Rectangle);
	// Bottom Border
	//addCollideableObject(0, SCREEN_HEIGHT, SCREEN_WIDTH, 10, Border);
	// Right Border
	//addCollideableObject(SCREEN_WIDTH, 0, 10, SCREEN_HEIGHT, Border);
	// Left Border
	//addCollideableObject(-10, 0, 10, SCREEN_HEIGHT, Border);
}

void GameLevelModel::addCollideableObject(int posX, int posY, int width, int height,
										  Collision::Label label, CollisionShape shape) {
	Entity *temp = objects.addEntity();
	temp->addComponent<Position>(posX, posY, width, height);
	temp->addComponent<Collision>(label, shape);
}

void GameLevelModel::createLvl1() {
//	mapBackground = TextureManager::loadTexture("Background/Background-0006.bmp");

	// Floor 1
	addCollideableObject(96, 704, 350, 21, Collision::Block, Rectangle);
	addCollideableObject(510, 704, 420, 11, Collision::Block, Rectangle);
	addCollideableObject(190, 672, 100, 11, Collision::Block, Rectangle);

	// Floor 2
	addCollideableObject(224, 576, 130, 11, Collision::Block, Rectangle);

	// Triangle for fun
//	addCollideableObject(465, 704, -100, -100, Collision::Block, Triangle);

	// Ladder
	addCollideableObject(208, 575, 16, 93, Collision::Ladder, Rectangle);

	// Wall
	addCollideableObject(90, 500, 10, 300, Collision::Block, Rectangle);
}
