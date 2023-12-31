//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_COLLISIONCOMPONENT_H
#define KINGDONKEY_COLLISIONCOMPONENT_H

#include "SDL.h"

#include "PositionComponent.h"
#include "Component.h"
#include "../../Utilities/Shapes/Shape.h"


enum CollisionEntityLabel {
	Collision_Default,
	Collision_Floor,
	Collision_Wall,
	Collision_Border,
	Collision_Ladder,
	Collision_Barrel,
	Collision_Player,
};

class CollisionComponent : public Component {
private:
	PositionComponent *position{};

	int width = 0;
	int height = 0;

	CollisionEntityLabel entityLabel;

	void updatePos();

	Shape collisionBox;

public:

	SDL_Rect box{};

	CollisionComponent() {
		entityLabel = Collision_Default;
	};

	CollisionComponent(int w, int h) : width(w), height(h) {
		entityLabel = Collision_Default;
		box.w = width;
		box.h = height;
	}

	CollisionComponent(CollisionEntityLabel label) : entityLabel(label) {};

	CollisionComponent(int w, int h, CollisionEntityLabel label)
		: width(w), height(h), entityLabel(label) {}

	void init() override;

	void update() override;

	void draw() override;

	Shape *getCollisionBox();

};


#endif //KINGDONKEY_COLLISIONCOMPONENT_H
