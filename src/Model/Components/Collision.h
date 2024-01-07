//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_COLLISION_H
#define KINGDONKEY_COLLISION_H

#include "SDL.h"

#include "Position.h"
#include "EntityComponent.h"
#include "../../Utilities/Shapes/Shape.h"
#include "../../Utilities/DataStructures/BitSet.h"


enum CollisionShape {
	Rectangle,
	Triangle,
};


class Collision : public EntityComponent {
private:
	Position* position{};

	int width = 0;
	int height = 0;

	Shape collisionBox;
	CollisionShape shapeName;

	BitSet collidingWith = BitSet();

	/**
	 * Updates the position of the collision box based on the entity's current position and scale.
	 */
	void updatePos();

public:

	enum Label {
		Default, Block, Ground, Border,
		Ladder, LadderTop, LadderBottom,
		Barrel,
		Player,
	};


	Label entityLabel;

	SDL_Rect box{};


	Collision() {
		entityLabel = Default;
		shapeName = Rectangle;
	};

	Collision(int w, int h) : width(w), height(h) {
		entityLabel = Default;
		shapeName = Rectangle;
		box.w = width;
		box.h = height;
	}


	explicit Collision(Label label) : entityLabel(label) {
		shapeName = Rectangle;
	};

	Collision(Label label, CollisionShape shape) : entityLabel(label), shapeName(shape) {};

	Collision(int w, int h, Label label)
		: width(w), height(h), entityLabel(label) {
		shapeName = Rectangle;
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
	static void handleCollisionsForLabels(Collision* main, Collision* with, Vector2 mtv);

	/**
	 * Sets the collision flag for a specific Label.
	 *
	 * @param label The Label of the entity that this entity collided with.
	 */
	void setCollision(Label label);

	/**
	 * Checks if there is a collision with a specific Label.
	 *
	 * @param label The Label to check for collision.
	 * @return bool True if colliding with the specified Label, false otherwise.
	 */
	bool getCollision(Label label);

	/**
	 * Removes a collision flag for a specific Label.
	 *
	 * @param label The Label of the entity to remove the collision with.
	 */
	void removeCollision(Label label);

	/**
	 * Resets all collision flags, typically called at the start of each frame.
	 */
	void resetCollisions();

	/**
	 * Responds to a player entity colliding with a floor entity.
	 *
	 * @param player The player entity.
	 * @param mtv The minimum translation vector to resolve the collision.
	 */
	static void respondPlayerToFloor(Collision* player, Vector2 mtv);

	/**
	 * Responds to a player entity colliding with a ladder entity.
	 *
	 * @param player The player entity.
	 * @param ladder The ladder entity.
	 */
	static void respondPlayerToLadder(Collision* player, Collision* ladder, Vector2 mtv);

	/**
	 * Returns the collision box of the entity.
	 * @return Shape* Pointer to the collision box.
	 */
	Shape* getCollisionBox();

};


#endif //KINGDONKEY_COLLISION_H
