//
// Created by Filip Dabkowski on 18/12/2023.
//

#ifndef KINGDONKEY_ANIMATIONCOMPONENT_H
#define KINGDONKEY_ANIMATIONCOMPONENT_H

#include "Component.h"


class AnimationComponent : public Component {
	int changeThreshold;
	int updateCount;
	int numberOfSteps;
	int stepCount;

	AnimationComponent() {
		changeThreshold = 1;
		numberOfSteps = 1;
		updateCount = 0;
		stepCount = 0;
	}

	AnimationComponent(int changeEvery, int steps) : changeThreshold(changeEvery), numberOfSteps(steps) {
		updateCount = 0;
		stepCount = 0;
	}

	void update() override {
		updateCount++;
		if (updateCount >= changeThreshold) {
			numberOfSteps++;
			updateCount = 0;
		}
		if (stepCount >= numberOfSteps) {
			stepCount = 0;
		}
	}
};


#endif //KINGDONKEY_ANIMATIONCOMPONENT_H
