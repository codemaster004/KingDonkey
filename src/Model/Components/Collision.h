//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_COLLISION_H
#define KINGDONKEY_COLLISION_H

#include "SDL.h"

#include "Position.h"
#include "EntityComponent.h"
#include "../../Utilities/Shapes/Shape.h"
#include "../../Utilities/DataStructures/BitDict.h"


enum CollisionLabel {
	Collision_Default,
	Collision_Block,
	Collision_Ground,
	Collision_Border,
	Collision_Ladder,
	Collision_LadderTop,
	Collision_LadderBottom,
	Collision_Barrel,
	Collision_Player,
};


class Collision : public EntityComponent {
private:
	Position *position{};

	int width = 0;
	int height = 0;

	Shape collisionBox;

	BitDict collidingWith = BitDict();

	/**
	 * Updates the position of the collision box based on the entity's current position and scale.
	 */
	void updatePos();

public:

	CollisionLabel entityLabel;

	SDL_Rect box{};


	Collision() {
		entityLabel = Collision_Default;
	};


	Collision(int w, int h) : width(w), height(h) {
		entityLabel = Collision_Default;
		box.w = width;
		box.h = height;
	}


	explicit Collision(CollisionLabel label) : entityLabel(label) {};


	Collision(int w, int h, CollisionLabel label)
		: width(w), height(h), entityLabel(label) {
		box.w = width;
		box.h = height;
	}


	/**
	 * Initializes the collision component of an entity, setting up its bounding box.
	 */
	void init() override;

	/**
	 * Updates the collision component, typically called each frame.
	 */
	void update() override;

	/**
	 * Renders the collision box for debugging purposes.
	 */
	void draw() override;

	/**
	 * Handles collisions based on entity labels.
	 *
	 * @param main The main entity involved in the collision.
	 * @param with The entity that the main entity has collided with.
	 * @param mtv The minimum translation vector to resolve the collision.
	 */
	static void handleCollisionsForLabels(Collision *main, Collision *with, Vector2 mtv);

	/**
	 * Sets the collision flag for a specific label.
	 *
	 * @param label The label of the entity that this entity collided with.
	 */
	void setCollision(CollisionLabel label);

	/**
	 * Checks if there is a collision with a specific label.
	 *
	 * @param label The label to check for collision.
	 * @return bool True if colliding with the specified label, false otherwise.
	 */
	bool getCollision(CollisionLabel label);

	/**
	 * Removes a collision flag for a specific label.
	 *
	 * @param label The label of the entity to remove the collision with.
	 */
	void removeCollision(CollisionLabel label);

	/**
	 * Resets all collision flags, typically called at the start of each frame.
	 */
	void resetCollisions();

	/**
	 * Responds to a player entity colliding with a floor entity.
	 *
	 * @param main The player entity.
	 * @param mtv The minimum translation vector to resolve the collision.
	 */
	static void respondPlayerToFloor(Collision *main, Collision *with, Vector2 mtv);

	/**
	 * Responds to a player entity colliding with a ladder entity.
	 *
	 * @param main The player entity.
	 * @param with The ladder entity.
	 */
	static void respondPlayerToLadder(Collision *main, Collision *with);

	/**
	 * Returns the collision box of the entity.
	 * @return Shape* Pointer to the collision box.
	 */
	Shape *getCollisionBox();

};


#endif //KINGDONKEY_COLLISION_H
