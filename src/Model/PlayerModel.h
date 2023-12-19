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


class PlayerModel : public Entity {

public:
	PlayerModel() {
		addComponent<PositionComponent>(100, 250, 32, 32, 4);
		this->getComponent<PositionComponent>()->setSpeed(0.5, -0.5);
		addComponent<TextureComponent>("SoulKeeper.bmp", true);
		addComponent<AnimationComponent>(12, 12);
		addComponent<CollisionComponent>(96, 96);
	}
};


#endif //KINGDONKEY_PLAYERMODEL_H
