//
// Created by Filip Dabkowski on 15/12/2023.
//

#ifndef KINGDONKEY_GAMEVIEW_H
#define KINGDONKEY_GAMEVIEW_H

#include "TextureManager.h"
#include "../Model/EntityManager/Manager.h"
#include "../Config/GameConfig.h"
#include "../Model/Components/Collision.h"
#include "../Model/GameLevelModel.h"
#include "../Utilities/Timer.h"


class GameView {
private:
	char text[128]{};

	int frameCount = 0;
	double fpsTimer = 0;
	double currentFps = 0;

	Timer* timer = nullptr;

	SDL_Texture* charTexture;

	void renderText(char* string, int startX, int topY) const;

public:

	GameLevelModel* levelModel = nullptr;

	GameView() = default;

	explicit GameView(Timer* timer) : timer(timer) {
		charTexture = TextureManager::loadTexture("cs8x8.bmp", true);
	}


	void init();

	void setLevelMode(GameLevelModel* newModel);

	void update();

	void render() const;

};


#endif //KINGDONKEY_GAMEVIEW_H
