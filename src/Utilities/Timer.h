//
// Created by Filip Dabkowski on 02/01/2024.
//

#ifndef KINGDONKEY_TIMER_H
#define KINGDONKEY_TIMER_H

#include "Utility.h"

#include "cstdint"


class Timer {
private:
	uint64_t duration;
	uint64_t prevMark = 0; ///< previously marked ticks from game start
	float worldTime = 0; ///< Timer for in game passage of time
public:

	uint64_t mark();

	[[nodiscard]]
	float getTotalTime() const;

	static uint64_t getCurrentTime();

	void reset();
};


#endif //KINGDONKEY_TIMER_H
