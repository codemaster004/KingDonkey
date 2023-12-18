//
// Created by Filip Dabkowski on 18/12/2023.
//

#ifndef KINGDONKEY_ANIMATIONCOMPONENT_H
#define KINGDONKEY_ANIMATIONCOMPONENT_H

#include "Component.h"
#include "TextureComponent.h"


class AnimationComponent : public Component {
private:
	TextureComponent *textures = nullptr;

	int changeThreshold;
	int updateCount;
	int numberOfSteps;
	int stepCount;

public:

	AnimationComponent() {
		changeThreshold = 1;
		numberOfSteps = 1;
		updateCount = 0;
		stepCount = 0;
	}

	explicit AnimationComponent(int steps) : numberOfSteps(steps) {
		changeThreshold = 1;
		updateCount = 0;
		stepCount = 0;
	}

	AnimationComponent(int changeEvery, int steps) : changeThreshold(changeEvery), numberOfSteps(steps) {
		updateCount = 0;
		stepCount = 0;
	}

	void init() override;

	void update() override;
};


#endif //KINGDONKEY_ANIMATIONCOMPONENT_H
