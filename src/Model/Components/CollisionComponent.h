//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_COLLISIONCOMPONENT_H
#define KINGDONKEY_COLLISIONCOMPONENT_H

#include "SDL.h"

#include "PositionComponent.h"
#include "Component.h"


enum CollisionBoxType {
	Box,
};

enum CollisionEntityLabel {
	Floor,
	Wall,
	Ladder,
	Barrel,
	Player,
};

class CollisionComponent : public Component {
private:
	PositionComponent *position{};

	int width = 0;
	int height = 0;

	CollisionBoxType boxType;
	CollisionEntityLabel entityLabel;

	void updatePos();

public:

	SDL_Rect box{};

	CollisionComponent() {
		boxType = Box;
		entityLabel = Floor;
	};

	CollisionComponent(int w, int h) : width(w), height(h) {
		boxType = Box;
		entityLabel = Floor;
		box.w = width;
		box.h = height;
	}

	CollisionComponent(CollisionBoxType type, CollisionEntityLabel label) : boxType(type), entityLabel(label) {};

	CollisionComponent(int w, int h, CollisionBoxType type, CollisionEntityLabel label)
		: width(w), height(h), boxType(type), entityLabel(label) {}

	void init() override;

	void update() override;

	void draw() override;

};


#endif //KINGDONKEY_COLLISIONCOMPONENT_H
