//
// Created by Filip Dabkowski on 15/12/2023.
//

#ifndef KINGDONKEY_GAMEVIEW_H
#define KINGDONKEY_GAMEVIEW_H

#include "TextureManager.h"
#include "../Model/EntityManager/Manager.h"
#include "../Config/GameConfig.h"
#include "../Model/Components/CollisionComponent.h"


class GameView {
private:
	char text[128]{};

	int frameCount = 0;
	double fpsTimer = 0;
	double currentFps = 0;

	SDL_Texture* charTexture;

	void renderText(char *string, int startX, int topY);

	void initGameBorders() {
		Entity *wall = manager.addEntity();
//		wall->addComponent<PositionComponent>(0, 0, SCREEN_WIDTH, 40);
//		wall->addComponent<CollisionComponent>(Box, Floor);
//		wall = manager.addEntity();
		wall->addComponent<PositionComponent>(0, SCREEN_HEIGHT, SCREEN_WIDTH, 1);
		wall->addComponent<CollisionComponent>(Box, Wall);
		wall = manager.addEntity();
		wall->addComponent<PositionComponent>(SCREEN_WIDTH, 0, 1, SCREEN_HEIGHT);
		wall->addComponent<CollisionComponent>(Box, Floor);
		wall = manager.addEntity();
		wall->addComponent<PositionComponent>(0, 0, 1, SCREEN_HEIGHT);
		wall->addComponent<CollisionComponent>(Box, Wall);
	}

public:
	Manager manager;

	explicit GameView() {
		charTexture = TextureManager::loadTexture("cs8x8.bmp");
		initGameBorders();
	}

	void update(double delta);

	void render();

};


#endif //KINGDONKEY_GAMEVIEW_H
