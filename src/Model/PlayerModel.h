//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_PLAYERMODEL_H
#define KINGDONKEY_PLAYERMODEL_H

#include "EntityManager/Entity.h"
#include "Components/PositionComponent.h"
#include "Components/TextureComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/PhysicsComponent.h"


class PlayerModel : public Entity {

public:
	PlayerModel() {
		int scale = 2;
		addComponent<PositionComponent>(100, 250, 28, 28, scale);
//		this->getComponent<PositionComponent>()->setSpeed(0.5, -0.5);
		addComponent<TextureComponent>("Warden.bmp");
		addComponent<AnimationComponent>(16, 8);
		addComponent<CollisionComponent>(21 * scale, 28 * scale);
		addComponent<PhysicsComponent>(true);
	}
};


#endif //KINGDONKEY_PLAYERMODEL_H
