//
// Created by Filip Dabkowski on 18/12/2023.
//

#ifndef KINGDONKEY_ANIMATION_H
#define KINGDONKEY_ANIMATION_H

#include "EntityComponent.h"
#include "Texture.h"


enum AnimationState {
	MovingLeft,
	MovingRight,
	StandingStill,
};

class Animation : public EntityComponent {
private:
	Texture *textures = nullptr;

	int changeThreshold;
	int updateCount = 0;

	int numberOfSteps;
	int stepCount = 0;

	AnimationState state = StandingStill;

public:

	Animation() {
		changeThreshold = 1;
		numberOfSteps = 1;
	}

	explicit Animation(int steps) : numberOfSteps(steps) {
		changeThreshold = 1;
	}

	Animation(int changeEvery, int steps) : changeThreshold(changeEvery), numberOfSteps(steps) {}

	void init() override;

	void update() override;

	void setAnimationState(AnimationState newState);
};


#endif //KINGDONKEY_ANIMATION_H
