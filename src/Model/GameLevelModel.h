//
// Created by Filip Dabkowski on 20/12/2023.
//

#ifndef KINGDONKEY_GAMELEVELMODEL_H
#define KINGDONKEY_GAMELEVELMODEL_H

#include "EntityManager/Manager.h"
#include "Components/CollisionComponent.h"

class GameLevelModel {
private:

	void initGameBorders();

	void addCollideableObject(int posX, int posY, int width, int height, CollisionEntityLabel label);

public:
	Manager objects = Manager();

	GameLevelModel() {
		initGameBorders();
	}

	void createLvl1();

};


#endif //KINGDONKEY_GAMELEVELMODEL_H
