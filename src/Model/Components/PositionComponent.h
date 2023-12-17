//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_POSITIONCOMPONENT_H
#define KINGDONKEY_POSITIONCOMPONENT_H

#include "Component.h"
#include "../../Utilities/MathVector.h"


class PositionComponent : public Component {
private:
	Vector2D pos;
	Vector2D speed;

	int width;
	int height;

public:

	PositionComponent() {
		pos = Vector2D();
		speed = Vector2D();
		height = width = 32;
	};

	explicit PositionComponent(float v) {
		pos = Vector2D(v, v);
		speed = Vector2D();
		height = width = 32;
	};

	PositionComponent(float x, float y) {
		pos = Vector2D(x, y);
		speed = Vector2D();
		height = width = 32;
	};

	PositionComponent(float x, float y, int w, int h) {
		pos = Vector2D(x, y);
		speed = Vector2D();
		width = w;
		height = h;
	};

	void update() override {
		pos.add(speed);
	}

	void setSpeed(float speedX, float speedY) {
		speed.x(speedX);
		speed.y(speedY);
	}

	Vector2D &getSpeed() {
		return this->speed;
	}

	int x() { return (int) (pos.x()); }

	int y() { return (int) (pos.y()); }

	[[nodiscard]] int w() const { return width; }

	[[nodiscard]] int h() const { return height; }

	void free() {
		pos.free();
		speed.free();
	}

};


#endif //KINGDONKEY_POSITIONCOMPONENT_H
