//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_COLLISIONVIEWMODEL_H
#define KINGDONKEY_COLLISIONVIEWMODEL_H

#include "../../sdl/include/SDL.h"


class CollisionViewModel {
public:
	static int8_t collisionBoxToBox(SDL_Rect box1, SDL_Rect box2);
};


#endif //KINGDONKEY_COLLISIONVIEWMODEL_H
