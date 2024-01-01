//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "CollisionComponent.h"

#include "../../Game.h"


void CollisionComponent::init() {
	position = entity->getComponent<PositionComponent>();
	if (!(width || height)) {
		box.w = width = position->w() * position->s();
		box.h = height = position->h() * position->s();
	}
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


void CollisionComponent::handleCollisionsForLabels(CollisionEntityLabel label, Vector2D &mtv) {
	if (mtv.magnitude2() == 0)
		return;

	if (entityLabel == Collision_Player) {
		if (label == Collision_Border || label == Collision_Floor) {
			return;
		} else if (label == Collision_Ladder) {
			setCollision(Collision_Ladder);
			mtv = {0, 0};
		}
	}
}


void CollisionComponent::setCollision(CollisionEntityLabel label) {
	collidingWith.set((int) (label));
}


bool CollisionComponent::getCollision(CollisionEntityLabel label) {
	return collidingWith.get((int) (label));
}
