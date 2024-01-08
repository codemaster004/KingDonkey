//
// Created by Filip Dabkowski on 19/12/2023.
//

#ifndef KINGDONKEY_PLAYERVIEWMODEL_H
#define KINGDONKEY_PLAYERVIEWMODEL_H

#include "../Model/PlayerModel.h"


class PlayerViewModel {
public:
	/**
	 * @brief Handles input events for the player.
	 *
	 * This function is responsible for processing SDL input events and updating the player's position
	 * and keyboard state accordingly.
	 *
	 * @param event The SDL_Event representing the input event.
	 * @param player The PlayerModel object.
	 */
	static void handleInput(SDL_Event event, PlayerModel *player);

	/**
	 * @brief Process the player's input to control their movement and actions.
	 *
	 * This function takes in a PlayerModel object and updates its Position, Collision, and Animation components based
	 * on the player's input from the Keyboard component. The function checks for specific key presses to determine
	 * the player's actions.
	 *
	 * @param player The PlayerModel object representing the player.
	 */
	static void processInput(PlayerModel *player);
};


#endif //KINGDONKEY_PLAYERVIEWMODEL_H
