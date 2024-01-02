//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_COLLISIONCOMPONENT_H
#define KINGDONKEY_COLLISIONCOMPONENT_H

#include "SDL.h"

#include "PositionComponent.h"
#include "Component.h"
#include "../../Utilities/Shapes/Shape.h"
#include "../../Utilities/DataStructures/BitDict.h"


enum CollisionLabel {
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

	void updatePos();

	Shape collisionBox;

	BitDict collidingWith = BitDict();

public:

	CollisionLabel entityLabel;

	SDL_Rect box{};

	CollisionComponent() {
		entityLabel = Collision_Default;
	};

	CollisionComponent(int w, int h) : width(w), height(h) {
		entityLabel = Collision_Default;
		box.w = width;
		box.h = height;
	}

	explicit CollisionComponent(CollisionLabel label) : entityLabel(label) {};

	CollisionComponent(int w, int h, CollisionLabel label)
		: width(w), height(h), entityLabel(label) {
		box.w = width;
		box.h = height;
	}

	void init() override;

	void update() override;

	void draw() override;

	void setCollision(CollisionLabel label);

	bool getCollision(CollisionLabel label);

	void resetCollisions();

	void handleCollisionsForLabels(CollisionLabel label, Vector2D &mtv);

	Shape *getCollisionBox();

};


#endif //KINGDONKEY_COLLISIONCOMPONENT_H
