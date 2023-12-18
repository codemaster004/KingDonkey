//
// Created by Filip Dabkowski on 18/12/2023.
//

#include "AnimationComponent.h"
#include "../../Game.h"


void AnimationComponent::init() {
	textures = entity->getComponent<TextureComponent>();
}

void AnimationComponent::update() {
	updateCount++;
	if (updateCount >= changeThreshold) {
		stepCount++;
		updateCount = 0;
	}
	if (stepCount >= numberOfSteps) {
		stepCount = 0;
	}
	textures->moveSourceTo(stepCount, 0);
}
