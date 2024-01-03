//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_COLLISIONVIEWMODEL_H
#define KINGDONKEY_COLLISIONVIEWMODEL_H

#include "../Model/EntityManager/Entity.h"
#include "../Model/EntityManager/Manager.h"
#include "../Utilities/Shapes/Shape.h"
#include "../Model/Components/CollisionComponent.h"


/// A structure to represent a range of projection in a 1D plane.
/// It consists of two floats representing the minimum and maximum values of a projection range.
typedef struct ProjectionRange {
	float min; ///< The minimum value.
	float max; ///< The maximum value.
} ProjectionRange;


class CollisionViewModel {
private:

	Entity *checkEntity = nullptr;
	Manager *checkManager = nullptr;

	/**
	 * @brief Checks whether the entity with a conservative down-shift is colliding with another entity.
	 *
	 * @details Performs a collision check using the `evaluateCollisionWithEntities` function.
	 * If the entity is not colliding with any other entities, the gravity flag of the PhysicsComponent is set to true.
	 *
	 * @param entity The entity for which the on-ground check is performed.
	 * @param manager The manager that contains the entities.
	 */
	void handleOnGroundCheck();

	static void respondToEntityGround(CollisionComponent *main, CollisionComponent *, Vector2D mvt);

	/**
	 * @brief Calculates the collision result for an entity with other entities in the manager.
	 *
	 * @details This function checks for collision between the main shape of the entity and the shapes of other entities.
	 *
	 * @param entity The entity to check for collision.
	 * @param manager The manager containing the entities.
	 * @return CollisionResult The collision result, including the final movement and a flag indicating if collision occurred.
	 */
	void evaluateCollisionWithEntities(
		CollisionLabel filterLabel,
		void (*handleCollision)(CollisionComponent *main, CollisionComponent *with, Vector2D));

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
	Vector2D adjustRotation(Vector2D vec, Vector2D axes);

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
