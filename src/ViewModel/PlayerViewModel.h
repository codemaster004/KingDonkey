//
// Created by Filip Dabkowski on 19/12/2023.
//

#ifndef KINGDONKEY_PLAYERVIEWMODEL_H
#define KINGDONKEY_PLAYERVIEWMODEL_H

#include "../Model/PlayerModel.h"


class PlayerViewModel {
public:
	static void handleInput(SDL_Event event, PlayerModel *player);

	static void processInput(PlayerModel *player);
};


#endif //KINGDONKEY_PLAYERVIEWMODEL_H
