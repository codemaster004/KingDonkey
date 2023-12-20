//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "CollisionViewModel.h"
#include "../Game.h"
#include "../Utilities/Utility.h"


CollisionResult CollisionViewModel::collisionBoxToBox(SDL_Rect box1, SDL_Rect box2) {
	CollisionResult res = {0, 0, 0, 0, None};
	res.x = max(0, min(box1.x + box1.w, box2.x + box2.w) - max(box1.x, box2.x));
	res.y = max(0, min(box1.y + box1.h, box2.y + box2.h) - max(box1.y, box2.y));

	if (!(res.x > 0 && res.y > 0))
		return res;

	if (res.x > res.y) {
		res.d = Horizontal;
	} else if (res.y > res.x) {
		res.d = Vertical;
	} else {
		res.d = Undetermined;
	}

	return res;
}

CollisionResult CollisionViewModel::checkCollisions(Entity *entity, Manager *manager) {
	SDL_Rect mainBox = entity->getComponent<CollisionComponent>()->box;
	SDL_Rect tempBox;

	auto *position = entity->getComponent<PositionComponent>();
	Vector2D *speed = position->getSpeed();

	CollisionResult result = {0, 0, 0, 0, None};

	size_t count = manager->getEntityCount();
	for (int i = 0; i < count; ++i) {
		Entity *temp = manager->getEntity(i);

		if (temp->hasComponent<CollisionComponent>()) {
			tempBox = temp->getComponent<CollisionComponent>()->box;
			CollisionResult collided = CollisionViewModel::collisionBoxToBox(
				mainBox,
				tempBox
			);

			if (collided.d != None) {
				if (collided.d == Vertical) {
					result.w = 1;
					result.x += collided.x * (speed->x() >= 0 ? -1 : 1);
				} else if (collided.d == Horizontal) {
					result.h = 1;
					result.y += collided.y * (speed->y() > 0 ? 1 : -1);
				}
			} else if (mainBox.y + mainBox.h == tempBox.y) {
				result.h = 1;
			}  else if (mainBox.x + mainBox.w == tempBox.x) {
				result.w = 1;
			}
		}
	}

	if (result.w && result.x) {
		position->x(position->x() + result.x);
		speed->x(0);
	}
	if (result.h && result.y) {
		position->y(position->y() + result.y);
		speed->y(0);
	}

	return result;
}

void CollisionViewModel::handleCollision(Entity *entity, Manager *manager) {

	CollisionResult colliding = CollisionViewModel::checkCollisions(entity, manager);
	entity->getComponent<PhysicsComponent>()->setGravity(!(colliding.h));


}
