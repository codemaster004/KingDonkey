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

	PositionComponent() {
		xPos = 0;
		yPos = 0;
	};

	PositionComponent(int x, int y) : xPos(x), yPos(y) {}

	void update() override {
		xPos++;
		yPos++;
	}

	int x() { return xPos ;}
	int y() { return yPos ;}

};


#endif //KINGDONKEY_POSITIONCOMPONENT_H
