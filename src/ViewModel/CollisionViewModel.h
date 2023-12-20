//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_COLLISIONVIEWMODEL_H
#define KINGDONKEY_COLLISIONVIEWMODEL_H

#include "SDL.h"
#include "../Model/EntityManager/Entity.h"
#include "../Model/EntityManager/Manager.h"


enum Direction {
	None,
	Horizontal,
	Vertical,
	Undetermined,
};

struct CollisionResult {
	int x;
	int y;
	int w;
	int h;
	Direction d;
};


class CollisionViewModel {
public:
	static CollisionResult collisionBoxToBox(SDL_Rect box1, SDL_Rect box2);

	static void handleCollision(Entity *entity, Manager *manager);

	static CollisionResult checkCollisions(Entity *entity, Manager *manager);
};


#endif //KINGDONKEY_COLLISIONVIEWMODEL_H
