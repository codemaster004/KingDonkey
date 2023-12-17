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
	int width;
	int height;

public:

	PositionComponent() {
		vec = Vector2D();
		height = width = 32;
	};

	explicit PositionComponent(float v) {
		vec = Vector2D(v, v);
		height = width = 32;
	};

	PositionComponent(float x, float y) {
		vec = Vector2D(x, y);
		height = width = 32;
	};

	PositionComponent(float x, float y, int w, int h) {
		vec = Vector2D(x, y);
		width = w;
		height = h;
	};

	void update() override {
		vec.add(Vector2D(1, -0.5));
	}

	int x() { return (int)(vec.x()); }

	int y() { return (int)(vec.y()); }

	[[nodiscard]] int w() const { return width; }

	[[nodiscard]] int h() const { return height; }

	void free() {
		vec.free();
	}

};


#endif //KINGDONKEY_POSITIONCOMPONENT_H
