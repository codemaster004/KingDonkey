//
// Created by Filip Dabkowski on 18/12/2023.
//

#ifndef KINGDONKEY_ANIMATIONCOMPONENT_H
#define KINGDONKEY_ANIMATIONCOMPONENT_H

#include "Component.h"
#include "TextureComponent.h"


enum AnimationState {
	MovingLeft,
	MovingRight,
	StandingStill,
};

class AnimationComponent : public Component {
private:
	TextureComponent *textures = nullptr;

	int changeThreshold;
	int updateCount = 0;

	int numberOfSteps;
	int stepCount = 0;

	AnimationState state = StandingStill;

public:

	AnimationComponent() {
		changeThreshold = 1;
		numberOfSteps = 1;
	}

	explicit AnimationComponent(int steps) : numberOfSteps(steps) {
		changeThreshold = 1;
	}

	AnimationComponent(int changeEvery, int steps) : changeThreshold(changeEvery), numberOfSteps(steps) {}

	void init() override;

	void update() override;

	void setAnimationState(AnimationState newState);
};


#endif //KINGDONKEY_ANIMATIONCOMPONENT_H
