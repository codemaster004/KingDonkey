//
// Created by Filip Dabkowski on 03/01/2024.
//

#ifndef KINGDONKEY_KEYBOARD_H
#define KINGDONKEY_KEYBOARD_H

#include "EntityComponent.h"
#include "../../Utilities/DataStructures/BitDict.h"


class Keyboard : public EntityComponent {
private:
	BitDict keysPressed = BitDict();
public:
	enum Keys {
		ArrUp,
		ArrDown,
		ArrLeft,
		ArrRight,
		KeySpace,
	};

	Keyboard() = default;

	~Keyboard() override = default;

	void keyPressed(Keys key);

	bool getKey(Keys key);

	void keyLifted(Keys key);
};


#endif //KINGDONKEY_KEYBOARD_H
