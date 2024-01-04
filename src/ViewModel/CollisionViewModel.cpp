//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "CollisionViewModel.h"
#include "../Game.h"


void CollisionViewModel::handleCollision(Entity *entity, Manager *manager) {
	currentEntity = entity;
	entityManager = manager;

	auto collision = entity->getComponent<Collision>();

	// Reset all collision flags for given entity, prepare them to be set later.
	collision->resetCollisions();

	// Evaluating collisions with different entity types using specific labels.
	evaluateCollisions(Collision_Ladder, Collision::handleCollisionsForLabels);
	evaluateCollisions(Collision_Block, Collision::handleCollisionsForLabels);

	// Checks if the entity is on the ground to adjust its gravity accordingly.
	checkIfOnGround();
}


void CollisionViewModel::checkIfOnGround() {
	auto collision = currentEntity->getComponent<Collision>();
	// If Entity is colliding with floor he is colliding with something (floor or celling).
	// Entity is considered to be "onGround" only when not colliding with anything and one pixel above Floor.
	if (collision->getCollision(Collision_Block))
		return;
	// By default, if the Entity is not on a ladder set gravity to true
	currentEntity->getComponent<Physics>()->setGravity(!collision->getCollision(Collision_Ladder));

	// If the entity is moving in Vertical direction it can not be "standing" "onGround"
	if (currentEntity->getComponent<Position>()->getSpeed()->getY() != 0)
		return;

	Vector2 shiftDown = Vector2(0, 1); // Vector to shift the entity down by 1 unit.
	// Shift the entity down to simulate a fall for collision detection.
	*collision->getCollisionBox()->getOrigin() += shiftDown;

	// Check for collision after shifting.
	evaluateCollisions(Collision_Block, respondToGroundCollision);

	// Revert the entity to its original position.
	*collision->getCollisionBox()->getOrigin() -= shiftDown;
}


void CollisionViewModel::respondToGroundCollision(Collision *mainComponent, Collision *, Vector2) {
	// Entity is considered to be "on Ground" there for we can turn of the gravity for this entity.
	mainComponent->entity->getComponent<Physics>()->setGravity(false);
	mainComponent->setCollision(Collision_Ground);
}


void CollisionViewModel::evaluateCollisions(CollisionLabel filterLabel,
											void (*collisionCallback)(Collision *main, Collision *with, Vector2)) {
	auto collisionComponent = currentEntity->getComponent<Collision>();
	Shape *mainCollisionBox = collisionComponent->getCollisionBox();
	// Later used to determine proper alignment for resolving collision vector
	Vector2 *entitySpeed = currentEntity->getComponent<Position>()->getSpeed();

	// Loop through all entities managed by the manager.
	size_t entityCount = entityManager->getEntityCount();
	for (size_t i = 0; i < entityCount; ++i) {
		Entity *tempEntity = entityManager->getEntity(i);

		// Check if the temporary entity is valid for collision.
		if (tempEntity->hasComponent<Collision>()) {
			auto tempCollisionComponent = tempEntity->getComponent<Collision>();

			if (tempCollisionComponent->entityLabel != filterLabel)
				continue; // Filtering by type

			Shape *tempCollisionBox = tempCollisionComponent->getCollisionBox();
			// Calculate the Minimum Translation Vector (MTV) for collision resolution.
			Vector2 mtv = calculateCollisionSAT(mainCollisionBox, tempCollisionBox);
			if (mtv.magnitude2() == 0)
				continue; // No collision was detected.

			// Adjust the MTV based on the entity's speed.
			mtv = alignWithVelocity(mtv, *entitySpeed);
			// Handle the collision based on specific entity labels.
			collisionCallback(collisionComponent, tempCollisionComponent, mtv);
		}
	}
}


Vector2 CollisionViewModel::calculateCollisionSAT(Shape *shape1, Shape *shape2) {
	// A set of vectors representing the axes of the two shapes
	ListSet<Vector2> axes;

	// Calculating the normal axes for both shapes
	shape1->calculateNormalAxes(axes);
	shape2->calculateNormalAxes(axes);

	float minOverlap = 0.0; // Initially overlap is 0 (no overlap).

	// The axis corresponding to the minimum translated vector (MTV)
	Vector2 mtvAxis = Vector2();

	// Checking each axis for overlap
	for (Vector2 axis: axes) {
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
	Vector2 mtv = mtvAxis * minOverlap;
	return mtv; // return the vector to resolve collision
}


float CollisionViewModel::checkForOverlap(ProjectionRange shadow1, ProjectionRange shadow2) {
	// The amount of overlap is calculated as the length of the intersection of two ranges.
	return max(0.0, min(shadow1.max, shadow2.max) - max(shadow1.min, shadow2.min));
}


Vector2 CollisionViewModel::alignWithVelocity(Vector2 vec, Vector2 axes) {
	if (axes.magnitude2() == 0)
		return vec;

	// vector to resolve collision should point opposite direction than speed vector
	// there for a dot product should be negative, if it is not we need to reverse it.
	if (vec.dot(axes) > 0) {
		vec *= -1;
	}

	return vec; // Return the adjusted vector.
}
