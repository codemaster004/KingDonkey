//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_PLAYERMODEL_H
#define KINGDONKEY_PLAYERMODEL_H

#include "EntityManager/Entity.h"
#include "Components/PositionComponent.h"


class PlayerModel : public Entity {

public:
	PlayerModel() {
		addComponent<PositionComponent>();
	}
};


#endif //KINGDONKEY_PLAYERMODEL_H