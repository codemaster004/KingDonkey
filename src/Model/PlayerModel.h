//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_PLAYERMODEL_H
#define KINGDONKEY_PLAYERMODEL_H

#include "EntityManager/Entity.h"
#include "Components/PositionComponent.h"
#include "Components/TextureComponent.h"
#include "Components/CollisionComponent.h"


class PlayerModel : public Entity {

public:
	PlayerModel() {
		addComponent<PositionComponent>(100, 250, 90, 90);
		this->getComponent<PositionComponent>()->setSpeed(0.5, -0.5);

		addComponent<TextureComponent>("eti.bmp");
		addComponent<CollisionComponent>();
	}
};


#endif //KINGDONKEY_PLAYERMODEL_H
