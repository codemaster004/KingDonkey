//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "CollisionViewModel.h"
#include "../Game.h"
#include "../Utilities/Utility.h"

#include "cmath"


void CollisionViewModel::handleCollision(Entity *entity, Manager *manager) {
	// Reset all collision flags for given entity, prepare them to be set later.
	entity->getComponent<CollisionComponent>()->resetCollisions();

	// Evaluate collisions for the given entity with all other entities in the scene.
	CollisionResult res = evaluateCollisionWithEntities(entity, manager);

	// If a collision has occurred, handle the collision for the entity.
	if (res.colliding) {
		handleCollisionForEntity(entity, res.mtv);
		return; // collision was detected no need to check for ground beneath.
	}

	// Perform the OnGround check for the entity. As when an Entity is considered to be "onGround".
	// It isn't touching ground just floating 0 pixel above it.
	handleOnGroundCheck(entity, manager);
}


void CollisionViewModel::handleCollisionForEntity(Entity *entity, Vector2D mtv) {
	// Retrieving the PositionComponent from the entity.
	auto position = entity->getComponent<PositionComponent>();

	// Updating the entity's position by adding the minimum translation vector (mtv).
	// This adjusts the entity's position to resolve the collision.
	*position->getPos() -= mtv;

	// Modifying the speed of the entity to halt any vertical motion.
	if (mtv.y() != 0)
		*position->getSpeed() *= Vector2D(1, 0);
	if (mtv.x() != 0)
		*position->getSpeed() *= Vector2D(0, 1);

	// Turning off gravity for the entity
	// since collision has been handled, we assume the entity has "landed" and does not need to fall any further.
	entity->getComponent<PhysicsComponent>()->setGravity(false);
}


void CollisionViewModel::handleOnGroundCheck(Entity *entity, Manager *manager) {
	// Retrieving necessary component from the entity.
	auto collision = entity->getComponent<CollisionComponent>();
	auto gravity = entity->getComponent<PhysicsComponent>();
	auto position = entity->getComponent<PositionComponent>();

	// Declare vector to shift entity by to check for collision with ground
	auto shiftVec = Vector2D(0, 1);
	// Shifting the entity down by one unit along the y-axis (Simulate falling in vertical direction).
	*collision->getCollisionBox()->getOrigin() += shiftVec;
	*position->getSpeed() += shiftVec;

	// Now check for collision at shifted position.
	CollisionResult onGroundRes = CollisionViewModel::evaluateCollisionWithEntities(entity, manager);

	// Shifting the entity back up by one unit (to its original position).
	*collision->getCollisionBox()->getOrigin() -= shiftVec;
	*position->getSpeed() -= shiftVec;

	// If there's a collision, it means the entity is "onGround", and we switch off its gravity.
	// If none, it means the entity is airborne, and we apply gravity to it.
	gravity->setGravity(!onGroundRes.colliding);
}


CollisionResult CollisionViewModel::evaluateCollisionWithEntities(Entity *entity, Manager *manager) {
	// Retrieve collision component of the main entity.
	auto collision = entity->getComponent<CollisionComponent>();
	Shape *mainShape = collision->getCollisionBox(); // Main collision box for collision detection
	// Entity speed is used to determine the correct axes to resolve collision
	Vector2D *speed = entity->getComponent<PositionComponent>()->getSpeed();
	Vector2D finalMovement = {0, 0}; // This will be returned as Translation Vector, default is (0, 0)

	// Iterate over Entities inside of manager.
	size_t count = manager->getEntityCount();
	for (size_t i = 0; i < count; ++i) {
		Entity *tempEntity = manager->getEntity(i);

		// Checking if the checking entity can be collided with.
		if (tempEntity->hasComponent<CollisionComponent>()) {
			// If yes, fetching the component
			auto tempCollision = tempEntity->getComponent<CollisionComponent>();
			Shape *tempShape = tempCollision->getCollisionBox();
			// Calculate the MTV to resolve collision.
			Vector2D mtv = collisionShapeToShape(mainShape, tempShape); // returns absolute form
			// Collision for different entities can be handled separately depending on unique label.
			collision->handleCollisionsForLabels(tempCollision->entityLabel, mtv);
			// Try adjusting the rotation to be the same as speed vector.
			mtv = adjustRotation(mtv, *speed);
			// Reverse the rotation to undo part of the movement.
			finalMovement += mtv;
		}
	}

	return {
		finalMovement,
		finalMovement.magnitude2() > 0.001
	};
}


Vector2D CollisionViewModel::collisionShapeToShape(Shape *shape1, Shape *shape2) {
	// A set of vectors representing the axes of the two shapes
	ListSet<Vector2D> axes;

	// Calculating the normal axes for both shapes
	shape1->calculateNormalAxes(axes);
	shape2->calculateNormalAxes(axes);

	float minOverlap = 0.0; // Initially overlap is 0 (no overlap).

	// The axis corresponding to the minimum translated vector (MTV)
	Vector2D mtvAxis = Vector2D();

	// Checking each axis for overlap
	for (Vector2D axis: axes) {
		ProjectionRange projection1{};
		ProjectionRange projection2{};

		// Projecting "shadows" of both shapes onto the current axis
		shape1->projectOntoAxis(axis, &projection1);
		shape2->projectOntoAxis(axis, &projection2);

		// Checking for overlap of the projections
		float overlap = round(checkForOverlap(projection1, projection2));

		// If there's no overlap, we found a separating axis
		// This means that the shapes are not colliding
		if (overlap == 0.0)
			return {0, 0};

		// update overlap since we are interested in the smallest one.
		if (overlap < minOverlap || minOverlap == 0.0) {
			minOverlap = overlap;
			mtvAxis = axis;
		}
	}

	// Calculating minimum translated vector (MTV) to push object out of collision
	Vector2D mtv = mtvAxis.scalarMultiply(minOverlap);
	return mtv.abs(); // return the absolute vector to resolve collision
}


float CollisionViewModel::checkForOverlap(ProjectionRange shadow1, ProjectionRange shadow2) {
	// The amount of overlap is calculated as the length of the intersection of two ranges.
	return max(0.0, min(shadow1.max, shadow2.max) - max(shadow1.min, shadow2.min));
}


Vector2D CollisionViewModel::adjustRotation(Vector2D vec, Vector2D axes) {
	// Warning very stupid solution
	if (axes.magnitude2() == 0)
		return vec;

	// check if X has wrong sign
	if (axes.x() < 0) {
		vec *= Vector2D(-1, 1);
	}
	// check if X is not included in the axes
	if (axes.x() == 0)
		vec *= Vector2D(0, 1);
	// check if Y has wrong sign
	if (axes.y() < 0) {
		vec *= Vector2D(1, -1);
	}
	// check if Y is not included in the axes
	if (axes.y() == 0)
		vec *= Vector2D(1, 0);

	return vec; // Return the adjusted vector.
}
