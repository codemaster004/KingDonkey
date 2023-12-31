//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_COLLISIONVIEWMODEL_H
#define KINGDONKEY_COLLISIONVIEWMODEL_H

#include "../Model/EntityManager/Entity.h"
#include "../Model/EntityManager/Manager.h"
#include "../Utilities/Shapes/Shape.h"


/// A structure representing the result of a collision detection.
/// It holds a Vector2D for the movement vector and a boolean flag indicating if a collision has occurred.
struct CollisionResult {
	Vector2D mtv; ///< Minimal Translation Vector to resolve collision.
	bool colliding; ///< A flag indicating whether a collision has occurred.
};

/// A structure to represent a range of projection in a 1D plane.
/// It consists of two floats representing the minimum and maximum values of a projection range.
typedef struct ProjectionRange {
	float min; ///< The minimum value.
	float max; ///< The maximum value.
} ProjectionRange;


class CollisionViewModel {
private:

	/**
	 * @brief Checks whether the entity with a conservative down-shift is colliding with another entity.
	 *
	 * @details Performs a collision check using the `evaluateCollisionWithEntities` function.
	 * If the entity is not colliding with any other entities, the gravity flag of the PhysicsComponent is set to true.
	 *
	 * @param entity The entity for which the on-ground check is performed.
	 * @param manager The manager that contains the entities.
	 */
	void handleOnGroundCheck(Entity *entity, Manager *manager);

	/**
	 * @brief Handles the collision for a given entity.
	 *
	 * * @details This function updates the position and speed of the entity based on the collision result. It also disables gravity for the entity.
	 *
	 * @param entity The entity for which to handle collision.
	 * @param checkResult The collision result containing the movement vector and collision flag.
	 */
	void handleCollisionForEntity(Entity *entity, Vector2D mtv);

	/**
	 * @brief Calculates the collision result for an entity with other entities in the manager.
	 *
	 * @details This function checks for collision between the main shape of the entity and the shapes of other entities.
	 *
	 * @param entity The entity to check for collision.
	 * @param manager The manager containing the entities.
	 * @return CollisionResult The collision result, including the final movement and a flag indicating if collision occurred.
	 */
	CollisionResult evaluateCollisionWithEntities(Entity *entity, Manager *manager);

public:

	/**
	 * @brief Calculates the minimum translation vector for collision between two shapes.
	 *
	 * @details Given two shapes, this function calculates the minimum translation vector (MTV) to resolve the collision.
	 * To check for collisions a SAT method is used, compering shadows of shapes on axis.
	 * The MTV is a vector that needs to be applied to one of the shapes to move them apart and resolve the collision.
	 * If there is no collision, it returns a zero vector.
	 *
	 * @param shape1 The first shape involved in the collision.
	 * @param shape2 The second shape involved in the collision.
	 * @return The minimum translation vector (MTV) to resolve the collision.
	 */
	static Vector2D collisionShapeToShape(Shape *shape1, Shape *shape2);

	/**
	 * @brief Handles the collision for an entity.
	 *
	 * @details This function handles the collision for an entity by checking for collision with other entities in the manager.
	 * If a collision occurs, it updates the position and speed of the entity, and disables gravity.
	 *
	 * @param entity The entity to handle collision for.
	 * @param manager The manager containing the entities.
	 */
	void handleCollision(Entity *entity, Manager *manager);

	/**
	 * @brief Calculates the overlap between two projection ranges.
	 *
	 * @param shadow1 The first projection range.
	 * @param shadow2 The second projection range.
	 * @return The overlap between the two projection ranges.
	 */
	static float checkForOverlap(ProjectionRange shadow1, ProjectionRange shadow2);
};


#endif //KINGDONKEY_COLLISIONVIEWMODEL_H
