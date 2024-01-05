//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_COLLISIONVIEWMODEL_H
#define KINGDONKEY_COLLISIONVIEWMODEL_H

#include "../Model/EntityManager/Entity.h"
#include "../Model/EntityManager/Manager.h"
#include "../Utilities/Shapes/Shape.h"
#include "../Model/Components/Collision.h"


class CollisionViewModel {
private:

	Entity *currentEntity = nullptr;
	Manager *entityManager = nullptr;

	/**
	 * @brief Determines if the current entity is on the ground and adjusts its gravity component.
	 */
	void checkIfOnGround();

	/**
	 * @brief Responds to the entity's collision with the ground.
	 *
	 * @details Simple callback function for `checkIfOnGround`.
	 * This function is called only when, during ground check, a collision with Floor is detected.
	 *
	 * @param mainComponent The main entity's collision component.
	 */
	static void respondToGroundCollision(Collision *main, Collision *, Vector2);

	/**
	 * Evaluates collisions with entities of a specific type (label).
	 *
	 * @param filterLabel The label to filter entities for collision checks.
	 * @param handleCollisionFunction Function pointer to handle specific collisions.
	 */
	void evaluateCollisions(CollisionLabel filterLabel,
							void (*collisionCallback)(Collision *main, Collision *with, Vector2));

	/**
	 * @brief Adjusts the rotation of a vector based on the given axes.
	 *
	 * @details If the magnitude of the axis is not zero, it rotates the vector to have the same rotation as the axes.
	 * The resulting vector is returned. If the axis is 0, input vec will be returned.
	 *
	 * @param vec The vector to adjust the rotation of.
	 * @param axes The axes to adjust the rotation on.
	 * @return The adjusted vector.
	 */
	static Vector2 alignWithVelocity(Vector2 vec, Vector2 axes);

	static void adjustMvtDirection(Shape *shape1, Shape *shape2, Vector2 &currentMvt);

public:

	/**
	 * @brief Calculates the minimum translation vector for collision between two shapes.
	 *
	 * @details Given two shapes, this function calculates the minimum translation vector (MTV) to resolve the collision.
	 * To check for collisions a SAT method is used, compering shadows of shapes on axis.
	 * The MTV is a vector that needs to be applied to one of the shapes to move them apart and resolve the collision.
	 * As the sign of vector is not determined, proper rotation should be applied based on speed or position of objects.
	 * If there is no collision, it returns a zero vector.
	 *
	 * @param shape1 The first shape involved in the collision.
	 * @param shape2 The second shape involved in the collision.
	 * @return The value of translation vector (MTV) to resolve the collision.
	 */
	static Vector2 calculateCollisionSAT(Shape *shape1, Shape *shape2);

	/**
	 * @brief Handles the collision detection and response for a given entity.
	 *
	 * @details Perform all collision checks for given entities inside of the manager,
	 * in case of collision resolve with default handler inside the component.
	 * Also check if entity is on the ground and turn gravity accordingly with respect to ladders.
	 *
	 * @param entity The entity whose collisions are to be evaluated.
	 * @param manager The manager handling all entities, used to access other entities for collision checks.
	 */
	void handleCollision(Entity *entity, Manager *manager);

	/**
	 * @brief Calculates the overlap between two projection ranges.
	 *
	 * @param shadow1 The first projection range.
	 * @param shadow2 The second projection range.
	 * @return The overlap between the two projection ranges.
	 */
	static float checkForOverlap(Range shadow1, Range shadow2);
};


#endif //KINGDONKEY_COLLISIONVIEWMODEL_H

/*
 * 1 [x]. Define Collision Shapes
 * 		- Add function to approximate to rectangle (on initialization preferably or on corner add)
 * 2 [ ]. Spatial Partitioning
 * 4 [ ]. Collision Detection Algorithms
 * 		- Approximate using AABB then SAT for accurate result
 * 5 [ ]. Broad Phase and Narrow Phase
 * 6 [ ]. Collision Response
 * 7 [ ]. Optimization
 * 8 [ ]. Integration with Game Physics
 * 9 [ ]. Event Handling System
 * 10 [ ]. Debugging and Visualization Tools
 * 11 [ ]. Documentation and Comments
 */
