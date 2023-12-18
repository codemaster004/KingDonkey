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

class CollisionComponent : public Component {
private:
	PositionComponent *position{};

	int width = 0;
	int height = 0;

	CollisionBoxType type;

	void updatePos();

public:

	SDL_Rect box{};

	CollisionComponent() {
		type = Box;
	};

	explicit CollisionComponent(CollisionBoxType type) {
		this->type = type;
	};

	void init() override;

	void update() override;

};


#endif //KINGDONKEY_COLLISIONCOMPONENT_H
