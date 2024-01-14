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
	PlayerModel();
};


#endif //KINGDONKEY_PLAYERMODEL_H
