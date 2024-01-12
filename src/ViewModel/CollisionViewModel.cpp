//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "CollisionViewModel.h"
#include "../Game.h"


void CollisionViewModel::handleCollision(Entity *entity, Manager *manager) {
	currentEntity = entity;
	entityManager = manager;

	auto collision = entity->getComponent<Collision>();
	auto position = entity->getComponent<Position>();

	// Evaluating collisions with different entity types using specific labels.
	collision->removeCollision(Collision::Ladder);
	collision->removeCollision(Collision::LadderBottom);
	collision->removeCollision(Collision::LadderTop);
	evaluateCollisions(Collision::Ladder, Collision::handleCollisionsForLabels);

	Vector2 speedTranslation = *position->getSpeed() * Game::delta;
	*collision->getCollisionBox()->getOrigin() += speedTranslation;

	collision->removeCollision(Collision::Block);
	evaluateCollisions(Collision::Block, Collision::handleCollisionsForLabels);

	*collision->getCollisionBox()->getOrigin() -= speedTranslation;

	// Checks if the entity is on the ground to adjust its gravity accordingly.
	checkIfOnGround();
}


void CollisionViewModel::checkIfOnGround() {
	auto collision = currentEntity->getComponent<Collision>();

	// By default, if the Entity is not on a ladder set gravity to true
	currentEntity->getComponent<Physics>()->setGravity(!collision->getCollision(Collision::Ladder));

	Vector2 shiftDown = Vector2(0, 1); // Vector to shift the entity down by 1 unit.
	// Shift the entity down to simulate a fall for collision detection.
	*collision->getCollisionBox()->getOrigin() += shiftDown;

	// Check for collision after shifting.
	collision->removeCollision(Collision::Ground);
	evaluateCollisions(Collision::Block, respondToGroundCollision);

	// Revert the entity to its original position.
	*collision->getCollisionBox()->getOrigin() -= shiftDown;
}


void CollisionViewModel::respondToGroundCollision(Collision *mainComponent, Collision *, Vector2) {
	// Entity is considered to be "on Ground" when after the shifted collision is inside the floor and is not moving up.
	if (mainComponent->entity->getComponent<Position>()->getSpeed()->getY() >= 0)
		mainComponent->setCollision(Collision::Ground);
}


void CollisionViewModel::evaluateCollisions(Collision::Label filterLabel,
											void (*collisionCallback)(Collision *main, Collision *with, Vector2)) {
	auto collision = currentEntity->getComponent<Collision>();
	Shape *mainCollisionBox = collision->getCollisionBox();
	// Later used to determine proper alignment for resolving collision vector

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

			// Handle the collision based on specific entity labels.
			collisionCallback(collision, tempCollisionComponent, mtv);
		}
	}
}


void CollisionViewModel::adjustMvtDirection(Shape *shape1, Shape *shape2, Vector2 &currentMvt) {
	// Retrieve Center points of the shape
	Vector2 centroid1 = shape1->getCentroid();
	Vector2 centroid2 = shape2->getCentroid();

	// Create a vector from shape1 to shape2
	Vector2 direction = centroid2 - centroid1;

	// Check if the MTV needs to be reversed
	if (currentMvt.dot(direction) > 0) {
		currentMvt *= -1;
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
		Range projection1{};
		Range projection2{};

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
	adjustMvtDirection(shape1, shape2, mtv);

	return mtv; // return the vector to resolve collision
}


float CollisionViewModel::checkForOverlap(Range shadow1, Range shadow2) {
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
