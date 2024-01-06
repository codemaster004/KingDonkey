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

	if (shapeName == Rectangle) {
		collisionBox.initRect(0, 0, (float) (box.w), (float) (box.h));
	} else if (shapeName == Triangle) {
		collisionBox.initTrig(0, 0, (float) (box.w), (float) (box.h));
	}
	updatePos();
}


void Collision::update() {
	updatePos();
}


void Collision::updatePos() {
	// Calculate new position for the collision box.
	box.x = position->x() + position->w() * position->s() / 2 - width / 2;
	box.y = position->y() + position->h() * position->s() / 2 - height / 2;
	collisionBox.setOrigin(
		position->x() + position->w() * position->s() / 2 - width / 2,
		position->y() + position->h() * position->s() / 2 - height / 2);
}


void Collision::draw() {
	// Uncomment to render collision box for floors.
//	return;
	if (shapeName == Rectangle) {
//		SDL_RenderDrawRect(Game::renderer, &box);
	} else if (shapeName == Triangle) {
		Vector2 *origin = collisionBox.getOrigin();
		for (int i = 0; i < 3; ++i) {
			SDL_RenderDrawLine(
				Game::renderer,
				(int) (origin->getX() + collisionBox.getCorner(i).getX()),
				(int) (origin->getY() + collisionBox.getCorner(i).getY()),
				(int) (origin->getX() + collisionBox.getCorner(i + 1 % 3).getX()),
				(int) (origin->getY() + collisionBox.getCorner(i + 1 % 3).getY())
			);
		}
	}
}


Shape *Collision::getCollisionBox() {
	return &this->collisionBox;
}


void Collision::handleCollisionsForLabels(Collision *main, Collision *with, Vector2 mtv) {
	main->setCollision(with->entityLabel);

	// Handle collision based on entity types.
	if (main->entityLabel == Collision_Player && with->entityLabel == Collision_Block) {
		Collision::respondPlayerToFloor(main, with, mtv);
	} else if (main->entityLabel == Collision_Player && with->entityLabel == Collision_Ladder) {
		Collision::respondPlayerToLadder(main, with);
	}
}


void Collision::respondPlayerToFloor(Collision *main, Collision *with, Vector2 mtv) {
	auto position = main->entity->getComponent<Position>();

	// Player can be on the ladder and go thought Floors.
	// However, only if he is not at the beginning of the ladder
	if (main->getCollision(Collision_Ladder) && !main->getCollision(Collision_LadderBottom)) {
		if (position->getSpeed()->getX() != 0) {
			position->getSpeed()->setX(0);
		}
		return;
	}

	mtv *= (1 / Game::delta);

	// This prevents gaining speed when glitching through a wall/floor
	// this bug is caused by calculating translation vector based on only smallest overlap on any axes
	if (mtv.dot(*position->getSpeed()) > 0 &&
		position->getSpeed()->magnitude2() > mtv.magnitude2()) {
		return;
	}

	// Resolve collision with Floor by moving player
	*position->getSpeed() += mtv;
}


void Collision::respondPlayerToLadder(Collision *main, Collision *with) {
	auto keyboard = main->entity->getComponent<Keyboard>();
	auto position = main->entity->getComponent<Position>();

	// Entity is on a ladder now, if he is moving vertically
	if (position->getSpeed()->getY() != 0) {
		// but Arrow keys for Up or Down movement are not pressed
		if (!(keyboard->getKey(Keyboard::ArrDown) || keyboard->getKey(Keyboard::ArrUp))) {
			position->getSpeed()->setY(0);
		}
	}

	Vector2 shiftVec = Vector2(0, (float) (main->box.h)); // Shift the entity down by its height
	// Simulate the entity moving down. if it was at the bottom this would resolve the collision.
	*main->getCollisionBox()->getOrigin() += shiftVec;

	// The flag for collision with ladder was already set.
	// Now check if the player is at the bottom of a ladder, meaning he can not go further down.
	Vector2 checkVec = CollisionViewModel::calculateCollisionSAT(main->getCollisionBox(), with->getCollisionBox());
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
