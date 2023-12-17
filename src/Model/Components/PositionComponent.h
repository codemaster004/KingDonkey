//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_POSITIONCOMPONENT_H
#define KINGDONKEY_POSITIONCOMPONENT_H

#include "Component.h"
#include "../../Utilities/MathVector.h"

class PositionComponent : public Component {
private:
	Vector2D vec;

public:

	PositionComponent() {
		vec = Vector2D();
	};

	explicit PositionComponent(float v) {
		vec = Vector2D(v, v);
	};

	PositionComponent(float x, float y) {
		vec = Vector2D(x, y);
	};

	void update() override {
		vec.add(Vector2D(1, -0.5));
	}

	float x() { return vec.x(); }

	float y() { return vec.y(); }

	void free() {
		vec.free();
	}

};


#endif //KINGDONKEY_POSITIONCOMPONENT_H
