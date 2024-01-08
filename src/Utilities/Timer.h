//
// Created by Filip Dabkowski on 02/01/2024.
//

#ifndef KINGDONKEY_TIMER_H
#define KINGDONKEY_TIMER_H

#include "Utility.h"

#include "cstdint"

/**
 * @class Timer, in game module for measuring time,
 *
 * @brief This class is meant to resemble functionalities of real life stoppers/timers.
 */
class Timer {
private:
	uint64_t duration = 0; ///< Store duration of last check in between marks.
	uint64_t prevMark = 0; ///< Previously marked ticks from game start
	float worldTime = 0; ///< Timer for in game passage of time
public:

	/**
	 * @brief Calculates the time elapsed since the previous mark and updates the duration.
	 *
	 * This function calculates the duration of time elapsed since the previous mark and updates the duration variable.
	 * It also updates the worldTime variable by converting the duration to seconds.
	 * Finally, it updates the prevMark variable with the current time.
	 *
	 * @return The duration of time elapsed since the previous mark.
	 */
	uint64_t mark();

	/**
	 * @brief Retrieves the total time elapsed since the Timer was created or last reset.
	 *
	 * @return The total time elapsed since the Timer was created or last reset.
	 */
	[[nodiscard]] float getTotalTime() const;

	/**
	 * @brief Get the current time in game time.
	 *
	 * This function returns the current time in game time by converting the
	 * SDL ticks to game time using the fromSDLToGameTime function.
	 *
	 * @return The current time in game time.
	 */
	static uint64_t getCurrentTime();

	/**
	* @brief Resets the timer by setting the worldTime and duration to zero.
	*
	* This function sets the worldTime and duration variables of the Timer instance to zero,
	* effectively resetting the timer to its initial state.
	*/
	void reset();
};


#endif //KINGDONKEY_TIMER_H
