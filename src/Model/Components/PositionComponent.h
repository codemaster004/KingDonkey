//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_POSITIONCOMPONENT_H
#define KINGDONKEY_POSITIONCOMPONENT_H

#include "Component.h"

class PositionComponent : public Component {
private:
	int xPos;
	int yPos;

public:

	void init() override {
		xPos = 0;
		yPos = 0;
	}

	void update() override {
		xPos++;
		yPos++;
	}
};


#endif //KINGDONKEY_POSITIONCOMPONENT_H
