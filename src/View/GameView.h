//
// Created by Filip Dabkowski on 15/12/2023.
//

#ifndef KINGDONKEY_GAMEVIEW_H
#define KINGDONKEY_GAMEVIEW_H

#include "TextureManager.h"
#include "../Model/EntityManager/Manager.h"
#include "../Config/GameConfig.h"
#include "../Model/Components/CollisionComponent.h"
#include "../Model/GameLevelModel.h"


class GameView {
private:
	char text[128]{};

	int frameCount = 0;
	double fpsTimer = 0;
	double currentFps = 0;

	SDL_Texture* charTexture;

	void renderText(char *string, int startX, int topY);

public:

	GameLevelModel *levelModel = nullptr;

	GameView() {
		charTexture = TextureManager::loadTexture("cs8x8.bmp");
	}

	void init();

	void setLevelMode(GameLevelModel *newModel);

	void update();

	void render() const;

};


#endif //KINGDONKEY_GAMEVIEW_H
