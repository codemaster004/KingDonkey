//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "CollisionComponent.h"

#include "../../Game.h"


void CollisionComponent::init() {
	position = entity->getComponent<PositionComponent>();
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
	box.x = position->x() + position->w() * position->s() / 2 - width / 2;
	box.y = position->y() + position->h() * position->s() / 2 - height / 2;
	collisionBox.setOrigin(
		position->x() + position->w() * position->s() / 2 - width / 2,
		position->y() + position->h() * position->s() / 2 - height / 2
	);
}


void CollisionComponent::draw() {
//	if (entityLabel == Collision_Floor) {
	SDL_RenderDrawRect(Game::renderer, &box);
//	}
}


Shape *CollisionComponent::getCollisionBox() {
	return &this->collisionBox;
}


void CollisionComponent::handleCollisionsForLabels(CollisionComponent *main, CollisionComponent *with, Vector2D mtv) {
	main->setCollision(with->entityLabel);

	if (main->entityLabel == Collision_Player && with->entityLabel == Collision_Floor) {
		CollisionComponent::respondToPlayerFloor(main, mtv);
	} else if (main->entityLabel == Collision_Player && with->entityLabel == Collision_Ladder) {
		CollisionComponent::respondToPlayerLadder(main, with);
	}
}


void CollisionComponent::respondToPlayerFloor(CollisionComponent *main, Vector2D mtv) {
	if (main->getCollision(Collision_Ladder) && !main->getCollision(Collision_LadderBottom))
		return;

	auto position = main->entity->getComponent<PositionComponent>();
	*position->getPos() += mtv;
	if (mtv.y() != 0)
		*position->getSpeed() *= Vector2D(1, 0);
	if (mtv.x() != 0)
		*position->getSpeed() *= Vector2D(0, 1);
}


void CollisionComponent::respondToPlayerLadder(CollisionComponent *main, CollisionComponent *with) {
	Vector2D shiftVec = Vector2D(0, (float) (main->box.h));
	*main->getCollisionBox()->getOrigin() += shiftVec;

	Vector2D checkVec = CollisionViewModel::collisionShapeToShape(main->getCollisionBox(), with->getCollisionBox());

	*main->getCollisionBox()->getOrigin() -= shiftVec;

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
