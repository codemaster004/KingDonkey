//
// Created by Filip Dabkowski on 19/12/2023.
//

#ifndef KINGDONKEY_PHYSICSCOMPONENT_H
#define KINGDONKEY_PHYSICSCOMPONENT_H

#include "Component.h"
#include "PositionComponent.h"


class PhysicsComponent : public Component{
private:
	bool applyGravity;

	PositionComponent *position = nullptr;

public:
	PhysicsComponent() {
		applyGravity = true;
	}

	explicit PhysicsComponent(bool gravity) : applyGravity(gravity) {}

	void init() override;

	void update() override;

	void setGravity(bool newValue);

	bool getGravity();
};


#endif //KINGDONKEY_PHYSICSCOMPONENT_H
