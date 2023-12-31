//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "CollisionViewModel.h"
#include "../Game.h"
#include "../Utilities/Utility.h"


void CollisionViewModel::handleCollision(Entity *entity, Manager *manager) {
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
	*position->getPos() += mtv;

	// Modifying the speed of the entity to halt any vertical motion.
	*position->getSpeed() *= Vector2D(1, 0);

	// Turning off gravity for the entity
	// since collision has been handled, we assume the entity has "landed" and does not need to fall any further.
	entity->getComponent<PhysicsComponent>()->setGravity(false);
}


void CollisionViewModel::handleOnGroundCheck(Entity *entity, Manager *manager) {
	// Gabbing the CollisionComponent and PhysicsComponent from the entity.
	auto collision = entity->getComponent<CollisionComponent>();
	auto gravity = entity->getComponent<PhysicsComponent>();

	// Shifting the entity down by one unit along the y-axis (Simulate falling in vertical direction).
	*collision->getCollisionBox()->getOrigin() += Vector2D(0, 1);

	// Now check for collision at shifted position.
	CollisionResult onGroundRes = CollisionViewModel::evaluateCollisionWithEntities(entity, manager);

	// If there's a collision, it means the entity is "onGround", and we switch off its gravity.
	// If none, it means the entity is airborne, and we apply gravity to it.
	gravity->setGravity(!onGroundRes.colliding);

	// Shifting the entity back up by one unit (to its original position).
	*collision->getCollisionBox()->getOrigin() += Vector2D(0, -1);
}


CollisionResult CollisionViewModel::evaluateCollisionWithEntities(Entity *entity, Manager *manager) {
	// Retrieving the collision box of the main entity.
	Shape *mainShape = entity->getComponent<CollisionComponent>()->getCollisionBox();

	Vector2D finalMovement = {0, 0}; // This will be returned as Translation Vector

	// Iterate over Entities inside of manager.
	size_t count = manager->getEntityCount();
	for (size_t i = 0; i < count; ++i) {
		Entity *tempEntity = manager->getEntity(i);

		// Checking if the checking entity can be collided with.
		if (tempEntity->hasComponent<CollisionComponent>()) {
			// If yes, fetching the shape (collision box) of the entity.
			Shape *tempShape = tempEntity->getComponent<CollisionComponent>()->getCollisionBox();
			// Adding the mtv to final vector, in case of need to resolve more than one collision
			finalMovement += collisionShapeToShape(mainShape, tempShape);
		}
	}

	return {
		finalMovement,
		finalMovement != Vector2D(0, 0)
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
		float overlap = checkForOverlap(projection1, projection2);

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
