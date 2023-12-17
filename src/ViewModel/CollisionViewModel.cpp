//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "CollisionViewModel.h"

int8_t CollisionViewModel::collisionBoxToBox(SDL_Rect box1, SDL_Rect box2) {
	if (box1.x + box1.w >= box2.x && box1.y + box1.h >= box2.y) return 1;
	if (box1.x <= box2.x + box2.w && box1.y <= box2.y + box2.h) return 0;
	return -1;
}
