//
// Created by Filip Dabkowski on 03/01/2024.
//

#include "Keyboard.h"


void Keyboard::keyPressed(Keyboard::Keys key) {
	keysPressed.set((int) (key));
}


void Keyboard::keyLifted(Keyboard::Keys key) {
	keysPressed.remove((int) (key));
}


bool Keyboard::getKey(Keys key) {
	return keysPressed.get((int) (key));
}
