//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "CollisionViewModel.h"
#include "../Game.h"


// todo: better docS
void CollisionViewModel::handleCollision(Entity *entity, Manager *manager) {
	currentEntity = entity;
	entityManager = manager;

	auto collision = entity->getComponent<CollisionComponent>();

	// Reset all collision flags for given entity, prepare them to be set later.
	collision->resetCollisions();

	// Evaluating collisions with different entity types using specific labels.
	evaluateCollisions(Collision_Ladder, CollisionComponent::handleCollisionsForLabels);
	evaluateCollisions(Collision_Floor, CollisionComponent::handleCollisionsForLabels);

	// Checks if the entity is on the ground to adjust its gravity accordingly.
	checkIfOnGround();
}


void CollisionViewModel::checkIfOnGround() {
	auto collisionComponent = currentEntity->getComponent<CollisionComponent>();
	// By default, if the Entity is not on a ladder set gravity to true
	currentEntity->getComponent<PhysicsComponent>()->setGravity(!collisionComponent->getCollision(Collision_Ladder));

	Vector2D shiftDown = Vector2D(0, 1); // Vector to shift the entity down by 1 unit.
	// Shift the entity down to simulate a fall for collision detection.
	*collisionComponent->getCollisionBox()->getOrigin() += shiftDown;

	// Check for collision after shifting.
	evaluateCollisions(Collision_Floor, respondToGroundCollision);

	// Revert the entity to its original position.
	*collisionComponent->getCollisionBox()->getOrigin() -= shiftDown;
}


void CollisionViewModel::respondToGroundCollision(CollisionComponent *mainComponent, CollisionComponent *, Vector2D) {
	// Entity is considered to be "on Ground" there for we can turn of the gravity for this entity.
	mainComponent->entity->getComponent<PhysicsComponent>()->setGravity(false);
}


void CollisionViewModel::evaluateCollisions(
	CollisionLabel filterLabel,
	void (*handleCollisionFunction)(CollisionComponent *main, CollisionComponent *with, Vector2D)) {

	auto collisionComponent = currentEntity->getComponent<CollisionComponent>();
	Shape *mainCollisionBox = collisionComponent->getCollisionBox();
	// Later used to determine proper alignment for resolving collision vector
	Vector2D *entitySpeed = currentEntity->getComponent<PositionComponent>()->getSpeed();

	// Loop through all entities managed by the manager.
	size_t entityCount = entityManager->getEntityCount();
	for (size_t i = 0; i < entityCount; ++i) {
		Entity *tempEntity = entityManager->getEntity(i);

		// Check if the temporary entity is valid for collision.
		if (tempEntity->hasComponent<CollisionComponent>()) {
			auto tempCollisionComponent = tempEntity->getComponent<CollisionComponent>();

			if (tempCollisionComponent->entityLabel != filterLabel)
				continue; // Filtering by type

			Shape *tempCollisionBox = tempCollisionComponent->getCollisionBox();
			// Calculate the Minimum Translation Vector (MTV) for collision resolution.
			Vector2D mtv = calculateCollisionSAT(mainCollisionBox, tempCollisionBox);
			if (mtv.magnitude2() == 0)
				continue; // No collision was detected.

			// Adjust the MTV based on the entity's speed.
			mtv = alignWithVelocity(mtv, *entitySpeed);
			// Handle the collision based on specific entity labels.
			handleCollisionFunction(collisionComponent, tempCollisionComponent, mtv);
		}
	}
}


Vector2D CollisionViewModel::calculateCollisionSAT(Shape *shape1, Shape *shape2) {
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
	return mtv; // return the vector to resolve collision
}


float CollisionViewModel::checkForOverlap(ProjectionRange shadow1, ProjectionRange shadow2) {
	// The amount of overlap is calculated as the length of the intersection of two ranges.
	return max(0.0, min(shadow1.max, shadow2.max) - max(shadow1.min, shadow2.min));
}


Vector2D CollisionViewModel::alignWithVelocity(Vector2D vec, Vector2D axes) {
	if (axes.magnitude2() == 0)
		return vec;

	// vector to resolve collision should point opposite direction than speed vector
	// there for a dot product should be negative, if it is not we need to reverse it.
	if (Vector2D::dot(vec, axes) > 0) {
		vec *= Vector2D(-1, -1);
	}

	return vec; // Return the adjusted vector.
}
