//
// Created by Filip Dabkowski on 18/12/2023.
//

#include "Animation.h"
#include "../../Game.h"


void Animation::init() {
	textures = entity->getComponent<Texture>();
}

void Animation::update() {
	timePassed += Game::delta;
	if (timePassed >= changeThreshold) {
		frameIndex++;
		timePassed -= changeThreshold;
	}
	if (frameIndex >= numberOfFrames) {
		frameIndex = 0;
	}
	textures->moveSourceTo(frameIndex, 0);
	textures->setFlip(state == MovingRight);
}

void Animation::setState(AnimationState newState) {
	state = newState;
}
