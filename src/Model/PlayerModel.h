//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_PLAYERMODEL_H
#define KINGDONKEY_PLAYERMODEL_H

#include "EntityManager/Entity.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Components/Collision.h"
#include "Components/Animation.h"
#include "Components/Physics.h"
#include "Components/Keyboard.h"


class PlayerModel : public Entity {

public:
	PlayerModel() {
		float scale = 2;
		addComponent<Position>(100, 250, 28, 28, scale);
		addComponent<Texture>("Warden.bmp");
		addComponent<Animation>(16, 8);
		addComponent<Collision>(30 * scale, 26 * scale, Collision_Player);
		addComponent<Physics>(true);
		addComponent<Keyboard>();
	}
};


#endif //KINGDONKEY_PLAYERMODEL_H
