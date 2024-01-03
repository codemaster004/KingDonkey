//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "CollisionViewModel.h"
#include "../Game.h"


// todo: better docS
void CollisionViewModel::handleCollision(Entity *entity, Manager *manager) {
	checkEntity = entity;
	checkManager = manager;

	auto collision = entity->getComponent<CollisionComponent>();
	// Reset all collision flags for given entity, prepare them to be set later.
	collision->resetCollisions();

	// Loop over all entities and calculate minimal vector to resolve collisions.
//	evaluateCollisionWithEntities(entity, manager, Collision_Default,);
	evaluateCollisionWithEntities(Collision_Ladder, CollisionComponent::handleCollisionsForLabels);
	evaluateCollisionWithEntities(Collision_Floor, CollisionComponent::handleCollisionsForLabels);

	// Perform the OnGround check for the entity. As when an Entity is considered to be "onGround".
	// It isn't touching ground just floating 0 pixel above it.
	handleOnGroundCheck();
}


void CollisionViewModel::handleOnGroundCheck() {
	// Retrieving necessary component from the entity.
	auto collision = checkEntity->getComponent<CollisionComponent>();
	checkEntity->getComponent<PhysicsComponent>()->setGravity(!collision->getCollision(Collision_Ladder));

	// Declare vector to shift entity by to check for collision with ground
	auto shiftVec = Vector2D(0, 1);
	// Shifting the entity down by one unit along the y-axis (Simulate falling in vertical direction).
	*collision->getCollisionBox()->getOrigin() += shiftVec;

	// Now check for collision at shifted position.
//	CollisionResult onGroundRes = CollisionViewModel::evaluateCollisionWithEntities(entity, manager, Collision_Floor);
	evaluateCollisionWithEntities(Collision_Floor, respondToEntityGround);

	// Shifting the entity back up by one unit (to its original position).
	*collision->getCollisionBox()->getOrigin() -= shiftVec;
}


void CollisionViewModel::respondToEntityGround(CollisionComponent *main, CollisionComponent *, Vector2D mvt) {
	auto gravity = main->entity->getComponent<PhysicsComponent>();
	if (mvt.magnitude2() != 0) {
		gravity->setGravity(false);
	}
}


void CollisionViewModel::evaluateCollisionWithEntities(
	CollisionLabel filterLabel,
	void (*handleCollision)(CollisionComponent *main, CollisionComponent *with, Vector2D)) {

	// Retrieve collision component of the main entity.
	auto collision = checkEntity->getComponent<CollisionComponent>();
	Shape *mainShape = collision->getCollisionBox(); // Main collision box for collision detection
	// Entity speed is used to determine the correct axes to resolve collision
	Vector2D *speed = checkEntity->getComponent<PositionComponent>()->getSpeed();

	// Iterate over Entities inside of manager.
	size_t count = checkManager->getEntityCount();
	for (size_t i = 0; i < count; ++i) {
		Entity *tempEntity = checkManager->getEntity(i);

		// Checking if the temp entity can be collided with.
		if (tempEntity->hasComponent<CollisionComponent>()) {
			auto tempCollision = tempEntity->getComponent<CollisionComponent>();
			// Optimisation to be able to check only a certain type of entities
			if (tempCollision->entityLabel != filterLabel)
				continue;

			Shape *tempShape = tempCollision->getCollisionBox();
			// Calculate the MTV to resolve collision.
			Vector2D mtv = collisionShapeToShape(mainShape, tempShape);
			if (mtv.magnitude2() == 0)
				continue;

			// Try adjusting the rotation to be the same as speed vector.
			mtv = adjustRotation(mtv, *speed);
			// Collision for different entities can be handled separately depending on unique label.
			handleCollision(collision, tempCollision, mtv);
		}
	}
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
	return mtv; // return the vector to resolve collision
}


float CollisionViewModel::checkForOverlap(ProjectionRange shadow1, ProjectionRange shadow2) {
	// The amount of overlap is calculated as the length of the intersection of two ranges.
	return max(0.0, min(shadow1.max, shadow2.max) - max(shadow1.min, shadow2.min));
}


Vector2D CollisionViewModel::adjustRotation(Vector2D vec, Vector2D axes) {
	// Warning very stupid solution
	if (axes.magnitude2() == 0)
		return vec;

	// vector to resolve collision should point opposite direction than speed vector
	// there for a dot product should be negative, if it is not we need to reverse it.
	if (Vector2D::dot(vec, axes) > 0) {
		vec *= Vector2D(-1, -1);
	}

	return vec; // Return the adjusted vector.
}
