//
// Created by Filip Dabkowski on 02/01/2024.
//

#include "SDL.h"

#include "Timer.h"


uint64_t Timer::mark() {
	uint64_t now = getCurrentTime();
	duration = now - prevMark;
	worldTime += toSeconds(duration);
	prevMark = now;
	return duration;
}


float Timer::getTotalTime() const {
	return worldTime;
}


uint64_t Timer::getCurrentTime() {
	return fromSDLToGameTime(SDL_GetTicks());
}

void Timer::reset() {
	worldTime = 0;
	duration = 0;
}
