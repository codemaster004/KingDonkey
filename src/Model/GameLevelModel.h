//
// Created by Filip Dabkowski on 20/12/2023.
//

#ifndef KINGDONKEY_GAMELEVELMODEL_H
#define KINGDONKEY_GAMELEVELMODEL_H

#include "EntityManager/Manager.h"
#include "Components/Collision.h"

class GameLevelModel {
private:

	SDL_Texture *mapBackground = nullptr;

	void initGameBorders();

	void addCollideableObject(int posX, int posY, int width, int height, CollisionLabel label);

public:
	Manager objects = Manager();

	GameLevelModel() {
		initGameBorders();
	}

	void createLvl1();

	SDL_Texture *getMapBgc() {
		return mapBackground;
	}

};


#endif //KINGDONKEY_GAMELEVELMODEL_H
