//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "Collision.h"

#include "../../Game.h"


void Collision::init() {
	position = entity->getComponent<Position>();
	// If width and height are not initialized, calculate them based on the entity's position and scale.
	if (width == 0)
		box.w = width = position->w() * position->s();
	if (height == 0)
		box.h = height = position->h() * position->s();

	collisionBox.initRect(0, 0, (float) (box.w), (float) (box.h));
	updatePos();
}


void Collision::update() {
	updatePos();
}


void Collision::updatePos() {
	// Calculate new position for the collision box.
	box.x = position->x() + position->w() * position->s() / 2 - width / 2;
	box.y = position->y() + position->h() * position->s() / 2 - height / 2;
	collisionBox.setOrigin(box.x, box.y);
}


void Collision::draw() {
	// Uncomment to render collision box for floors.
	SDL_RenderDrawRect(Game::renderer, &box);
}


Shape *Collision::getCollisionBox() {
	return &this->collisionBox;
}


void Collision::handleCollisionsForLabels(Collision *main, Collision *with, Vector2D mtv) {
	main->setCollision(with->entityLabel);

	// Handle collision based on entity types.
	if (main->entityLabel == Collision_Player && with->entityLabel == Collision_Block) {
		Collision::respondPlayerToFloor(main, with, mtv);
	} else if (main->entityLabel == Collision_Player && with->entityLabel == Collision_Ladder) {
		Collision::respondPlayerToLadder(main, with);
	}
}


void Collision::respondPlayerToFloor(Collision *main, Collision *with, Vector2D mtv) {
	// Player can be on the ladder and go thought Floors.
	// However, only if he is not at the beginning of the ladder
	if (main->getCollision(Collision_Ladder) && !main->getCollision(Collision_LadderBottom))
		return;
	printf("Collision Floor:\n  move: %f\n  playerY: %f\n  speed: %f\n\n", mtv.getY(), main->getCollisionBox()
		->getOrigin()->getY(), main->entity->getComponent<Position>()->getSpeed()->getY());

	auto position = main->entity->getComponent<Position>();
	// Resolve collision with Floor by moving player
	*position->getPos() += mtv;
	main->updatePos();

	// reset speed vectors to prevent further collisions in the same axis.
	if (mtv.getX() != 0)
		position->getSpeed()->setX(0);
	if (mtv.getY() != 0)
		position->getSpeed()->setY(0);

	Vector2D collisionRes = CollisionViewModel::calculateCollisionSAT(main->getCollisionBox(), with->getCollisionBox());
	if (collisionRes.magnitude2() == 0) {
		main->removeCollision(Collision_Block);
	}
}


void Collision::respondPlayerToLadder(Collision *main, Collision *with) {
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


void Collision::setCollision(CollisionLabel label) {
	collidingWith.set((int) (label));
}


bool Collision::getCollision(CollisionLabel label) {
	return collidingWith.get((int) (label));
}


void Collision::removeCollision(CollisionLabel label) {
	collidingWith.remove(label);
}


void Collision::resetCollisions() {
	collidingWith.reset();
}
