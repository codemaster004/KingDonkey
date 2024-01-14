//
// Created by Filip Dabkowski on 20/12/2023.
//

#include "GameLevelModel.h"
#include "../Game.h"


void GameLevelModel::initGameBorders() {
	// Top Border
	//addCollideableObject(0, 0, SCREEN_WIDTH, 40, Collision::Border, Rectangle);
	// Bottom Border
	//addCollideableObject(0, SCREEN_HEIGHT, SCREEN_WIDTH, 10, Border);
	// Right Border
	//addCollideableObject(SCREEN_WIDTH, 0, 10, SCREEN_HEIGHT, Border);
	// Left Border
	//addCollideableObject(-10, 0, 10, SCREEN_HEIGHT, Border);
}


void GameLevelModel::addCollideableObject(int posX, int posY, int width, int height,
                                          Collision::Label label, CollisionShape shape) {
	Entity* temp = objects.addEntity();
	temp->addComponent<Position>(posX, posY, width, height);
	temp->addComponent<Collision>(label, shape);
}


void GameLevelModel::createLvl1() {
	mapBackground = TextureManager::loadTexture("TempleLayout.bmp");

	// Main Sides Collider
	addCollideableObject(TILE_SIZE * 2 - COLLIDER_WIDTH, 0, COLLIDER_WIDTH, TILE_SIZE * 18);
	addCollideableObject(TILE_SIZE * 26, 0, COLLIDER_WIDTH, TILE_SIZE * 16);

	// Floor 1
	addCollideableObject(TILE_SIZE * 2, TILE_SIZE * 18, TILE_SIZE * 3, COLLIDER_HEIGHT);
	addCollideableObject(TILE_SIZE * 8, TILE_SIZE * 18, TILE_SIZE * 12, COLLIDER_HEIGHT);

	addCollideableObject(TILE_SIZE * 5, TILE_SIZE * 15, COLLIDER_WIDTH, TILE_SIZE * 3);
	addCollideableObject(TILE_SIZE * 9 - COLLIDER_WIDTH, TILE_SIZE * 15, COLLIDER_WIDTH, TILE_SIZE * 2);
	addCollideableObject(TILE_SIZE * 8 - COLLIDER_WIDTH, TILE_SIZE * 17, COLLIDER_WIDTH, TILE_SIZE);
	addCollideableObject(TILE_SIZE * 20, TILE_SIZE * 16, COLLIDER_WIDTH, TILE_SIZE * 2);

	// Floor 1.5
	addCollideableObject(TILE_SIZE * 5, TILE_SIZE * 15, TILE_SIZE * 4, COLLIDER_HEIGHT);
	addCollideableObject(TILE_SIZE * 11, TILE_SIZE * 15, TILE_SIZE * 7, COLLIDER_HEIGHT);
	addCollideableObject(TILE_SIZE * 20, TILE_SIZE * 16, TILE_SIZE * 6, COLLIDER_HEIGHT);


	// Floor 2
	addCollideableObject(TILE_SIZE * 2, TILE_SIZE * 10, TILE_SIZE * 3, COLLIDER_HEIGHT);
	addCollideableObject(TILE_SIZE * 5, TILE_SIZE * 11, TILE_SIZE * 3, COLLIDER_HEIGHT);
	addCollideableObject(TILE_SIZE * 8 - COLLIDER_WIDTH, TILE_SIZE * 11, COLLIDER_WIDTH, TILE_SIZE * 1.5);
	addCollideableObject(TILE_SIZE * 21, TILE_SIZE * 12, TILE_SIZE * 3, COLLIDER_HEIGHT);

	addCollideableObject(TILE_SIZE * 5, TILE_SIZE * 8, TILE_SIZE * 3, COLLIDER_HEIGHT);
	addCollideableObject(TILE_SIZE * 8, TILE_SIZE * 9, TILE_SIZE * 3, COLLIDER_HEIGHT);
	addCollideableObject(TILE_SIZE * 11 - COLLIDER_WIDTH, TILE_SIZE * 9, COLLIDER_WIDTH, TILE_SIZE * 3);
	addCollideableObject(TILE_SIZE * 13, TILE_SIZE * 10, COLLIDER_WIDTH, TILE_SIZE * 3);
	addCollideableObject(TILE_SIZE * 24 - COLLIDER_WIDTH, TILE_SIZE * 12, COLLIDER_WIDTH, TILE_SIZE * 1.5);

	addCollideableObject(TILE_SIZE * 18, TILE_SIZE * 10, TILE_SIZE, -TILE_SIZE, Collision::Block, Triangle);
	addCollideableObject(TILE_SIZE * 19, TILE_SIZE * 11, TILE_SIZE, -TILE_SIZE, Collision::Block, Triangle);
	addCollideableObject(TILE_SIZE * 20, TILE_SIZE * 12, TILE_SIZE, -TILE_SIZE, Collision::Block, Triangle);

	// Floor 2.5
	addCollideableObject(TILE_SIZE * 13, TILE_SIZE * 10, TILE_SIZE, COLLIDER_HEIGHT);
	addCollideableObject(TILE_SIZE * 14, TILE_SIZE * 9, TILE_SIZE * 4, COLLIDER_HEIGHT);


//	addCollideableObject(96, 704, 350, 21, Collision::Block, Rectangle);
//	addCollideableObject(510, 704, 420, 11, Collision::Block, Rectangle);
//	addCollideableObject(190, 672, 100, 11, Collision::Block, Rectangle);

	// Floor 2
//	addCollideableObject(224, 576, 130, 11, Collision::Block, Rectangle);

	// Triangle for fun
//	addCollideableObject(465, 704, -100, -100, Collision::Block, Triangle);

	// Ladder
//	addCollideableObject(208, 575, 16, 93, Collision::Ladder, Rectangle);

	// Wall
//	addCollideableObject(90, 500, 10, 300, Collision::Block, Rectangle);
}
