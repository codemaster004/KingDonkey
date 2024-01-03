//
// Created by Filip Dabkowski on 19/12/2023.
//

#ifndef KINGDONKEY_PHYSICS_H
#define KINGDONKEY_PHYSICS_H

#include "EntityComponent.h"
#include "Position.h"


class Physics : public EntityComponent{
private:
	bool applyGravity;

	Position *position = nullptr;

public:
	Physics() {
		applyGravity = true;
	}

	explicit Physics(bool gravity) : applyGravity(gravity) {}

	void init() override;

	void update() override;

	void setGravity(bool newValue);

	bool getGravity() const;
};


#endif //KINGDONKEY_PHYSICS_H
