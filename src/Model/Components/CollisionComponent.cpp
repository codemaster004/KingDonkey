//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "CollisionComponent.h"

#include "../../Game.h"


void CollisionComponent::init() {
	position = entity->getComponent<PositionComponent>();
	// If width and height are not initialized, calculate them based on the entity's position and scale.
	if (width == 0)
		box.w = width = position->w() * position->s();
	if (height == 0)
		box.h = height = position->h() * position->s();

	collisionBox.initRect(0, 0, (float) (box.w), (float) (box.h));
	updatePos();
}


void CollisionComponent::update() {
	updatePos();
}


void CollisionComponent::updatePos() {
	// Calculate new position for the collision box.
	box.x = position->x() + position->w() * position->s() / 2 - width / 2;
	box.y = position->y() + position->h() * position->s() / 2 - height / 2;
	collisionBox.setOrigin(box.x, box.y);
}


void CollisionComponent::draw() {
	// Uncomment to render collision box for floors.
	SDL_RenderDrawRect(Game::renderer, &box);
}


Shape *CollisionComponent::getCollisionBox() {
	return &this->collisionBox;
}


void CollisionComponent::handleCollisionsForLabels(CollisionComponent *main, CollisionComponent *with, Vector2D mtv) {
	main->setCollision(with->entityLabel);

	// Handle collision based on entity types.
	if (main->entityLabel == Collision_Player && with->entityLabel == Collision_Floor) {
		CollisionComponent::respondPlayerToFloor(main, mtv);
	} else if (main->entityLabel == Collision_Player && with->entityLabel == Collision_Ladder) {
		CollisionComponent::respondPlayerToLadder(main, with);
	}
}


void CollisionComponent::respondPlayerToFloor(CollisionComponent *main, Vector2D mtv) {
	// Player can be on the ladder and go thought Floors.
	// However, only if he is not at the beginning of the ladder
	if (main->getCollision(Collision_Ladder) && !main->getCollision(Collision_LadderBottom))
		return;

	auto position = main->entity->getComponent<PositionComponent>();
	// Resolve collision with Floor by moving player
	*position->getPos() += mtv;
	// reset speed vectors to prevent further collisions in the same axis.
	if (mtv.y() != 0)
		*position->getSpeed() *= Vector2D(1, 0);
	if (mtv.x() != 0)
		*position->getSpeed() *= Vector2D(0, 1);
}


void CollisionComponent::respondPlayerToLadder(CollisionComponent *main, CollisionComponent *with) {
	// The flag for collision with ladder was already set.
	// Now check if the player is at the bottom of a ladder, meaning he can not go further down.

	// Vector to shift the entity down by its height
	Vector2D shiftVec = Vector2D(0, (float) (main->box.h));
	// Simulate the entity moving down. if it was at the bottom this would resolve the collision.
	*main->getCollisionBox()->getOrigin() += shiftVec;

	Vector2D checkVec = CollisionViewModel::calculateCollisionSAT(main->getCollisionBox(), with->getCollisionBox());
	// Shift the entity back to original state.
	*main->getCollisionBox()->getOrigin() -= shiftVec;

	// If the collision did not happen this indicates we are at the bottom of the ladder.
	if (checkVec.magnitude2() == 0)
		main->setCollision(Collision_LadderBottom);
}


void CollisionComponent::setCollision(CollisionLabel label) {
	collidingWith.set((int) (label));
}


bool CollisionComponent::getCollision(CollisionLabel label) {
	return collidingWith.get((int) (label));
}


void CollisionComponent::removeCollision(CollisionLabel label) {
	collidingWith.remove(label);
}


void CollisionComponent::resetCollisions() {
	collidingWith.reset();
}
