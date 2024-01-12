//
// Created by Filip Dabkowski on 14/12/2023.
//

#ifndef KINGDONKEY_GAME_H
#define KINGDONKEY_GAME_H

#include "SDL.h"
#include "Config/GameConfig.h"
#include "Model/PlayerModel.h"
#include "View/GameView.h"
#include "Model/EntityManager/Manager.h"
#include "ViewModel/CollisionViewModel.h"
#include "Utilities/Timer.h"


class Game {
private:
	/* Fields */

	SDL_Window *window; ///< Application window for showing content
	SDL_Event event; ///< Event that occurred by pressing or lifting some key

	bool isRunning; ///< For main game loop.

	Uint32 frameTime = 0; ///< How long the previous frame took.

	/* Models */

	GameView gameView; ///< Object responsible for rendering game level and game information on screen.
	GameLevelModel *gameLevel = nullptr; ///< Model of the in game level (map)

	CollisionViewModel collisionViewModel; ///< Module responsible for checking collision in game.
	Timer timer = Timer(); ///< Time module for measuring time in game.

	Manager manager = Manager(); ///< Entity Storage responsible for preforming updates and renders.
	PlayerModel *player; ///< Player Entity.

	/* Methods */

	/**
	 * @brief Handles the events in the game loop.
	 *
	 * It polls events from SDL and processes them accordingly.
	 * The function checks for SDL_QUIT event to stop the game loop.
	 * It also handles the system quit case by checking for ESCAPE key press.
	 * Additionally, it calls the handleInput function from PlayerViewModel to handle player input events.
	 */
	void handleEvents();

	/**
	 * @brief Updates the game.
	 *
	 * This method is responsible for updating the game's state.
	 * It calls the update() method of the game view and the manager.
	 */
	void update();

	/**
	 * @brief Renders a frame of the game.
	 *
	 * This function is responsible for clearing the renderer, rendering the game view,
	 * rendering the manager, and presenting everything on the screen.
	 */
	void renderFrame();

	/**
	 * @brief Suspends the execution of the game for a specific duration.
	 *
	 * This function calculates the time difference between the ideal frame duration and the
	 * actual frame duration. If the actual frame duration is shorter than the ideal frame duration,
	 * the function delays the execution by the difference between the two durations.
	 *
	 * @param frameDuration The duration of the frame in microseconds.
	 */
	static void capFPS(uint64_t frameDuration);

	void gameSetUp();

public:
	/* Public Fields */

	static float delta; ///< Part of a second that frame took.
	static Config config; ///< Game config for storing constants.
	static SDL_Renderer *renderer; ///< Main renderer for showing on screen.

	Game() = default;

	~Game() = default;

	/**
	 * @brief Initializes the Game object.
	 *
	 * This method initializes the SDL library, creates a window and a renderer, and sets the initial render draw color.
	 *
	 * @param title The title of the window.
	 * @param width The width of the window.
	 * @param height The height of the window.
	 * @return True if the initialization is successful, otherwise false.
	 */
	bool initialize(const char *title, int width, int height);

	/**
	 * @brief Runs the game loop.
	 *
	 * This function runs the game loop, handling events, updating the game state, and rendering
	 * the frame. The loop continues until the game is no longer running.
	 */
	void run();

	/**
	 * @brief Executes the game mechanics.
	 *
	 * This method handles the collision between the player and the game objects.
	 * It calls the `handleCollision` method of the `collisionViewModel` object, passing
	 * the `player` and the pointer to the `objects` field of the `gameView.levelModel` object.
	 */
	void gameMechanics();

	/**
	 * @brief Clean up the resources used by the game.
	 *
	 * This function destroys the SDL window and renderer, and quits the SDL library.
	 */
	void clean();
};


#endif //KINGDONKEY_GAME_H
