//
// Created by Filip Dabkowski on 18/12/2023.
//

#include "Animation.h"
#include "../../Game.h"


void Animation::init() {
	textures = entity->getComponent<Texture>();
}

void Animation::update() {
	updateCount++;
	if (updateCount >= changeThreshold) {
		stepCount++;
		updateCount = 0;
	}
	if (stepCount >= numberOfSteps) {
		stepCount = 0;
	}
	textures->moveSourceTo(stepCount, 0);
	textures->setFlip(state == MovingRight);
}

void Animation::setAnimationState(AnimationState newState) {
	state = newState;
}
