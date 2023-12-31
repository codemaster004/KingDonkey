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
		float scale = 1.8;
		addComponent<PositionComponent>(100, 250, 28, 28, scale);
		addComponent<TextureComponent>("Warden.bmp");
		addComponent<AnimationComponent>(16, 8);
		addComponent<CollisionComponent>(21 * scale, 28 * scale, Collision_Player);
		addComponent<PhysicsComponent>(true);
	}
};


#endif //KINGDONKEY_PLAYERMODEL_H
