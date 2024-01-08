//
// Created by Filip Dabkowski on 18/12/2023.
//

#ifndef KINGDONKEY_ANIMATION_H
#define KINGDONKEY_ANIMATION_H

#include "EntityComponent.h"
#include "Texture.h"


/**
 * @class Animation
 * @brief This class provides functionalities for Entity animations in the game.
 *
 * Class inherits from the EntityComponent. It gives the ability to change
 * animations state, initialize and update animations.
 *
 * @constructor Animation(int steps)
 * @param steps Specifies the number of animation frames and defaults changeThreshold to 1s
 *
 * @constructor Animation(int steps, float changeEvery)
 * @param steps Specifies the number of animation frames.
 * @param changeEvery Specifies the duration of one frame.
 */
class Animation : public EntityComponent {
public:

	enum AnimationState {
		MovingLeft,
		MovingRight,
		StandingStill,
	};

	Animation() {
		numberOfFrames = 1;
		changeThreshold = 1;
	}

	explicit Animation(int steps) : numberOfFrames(steps) {
		changeThreshold = 1;
	}

	Animation(int steps, float changeEvery) : numberOfFrames(steps), changeThreshold(changeEvery) {}

	void init() override;

	void update() override;

	void setState(AnimationState newState);
private:
	Texture *textures = nullptr; ///< Texture Component

	float changeThreshold; ///< Change animation frame every N seconds.
	float timePassed = 0; ///< Keep score of how much time passed in game to change frames accordingly.

	int numberOfFrames; ///< Number of frames an animation has.
	int frameIndex = 0; ///< Index of animations frame that needs to be show now.

	AnimationState state = StandingStill; ///< Allow to show more than one different animation, specify which one.
};


#endif //KINGDONKEY_ANIMATION_H
