//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_POSITIONCOMPONENT_H
#define KINGDONKEY_POSITIONCOMPONENT_H

#include "Component.h"
#include "../../Utilities/MathVector.h"


class PositionComponent : public Component {
private:
	Vector2D *pos = nullptr;
	Vector2D *speed = nullptr;

	int width;
	int height;

public:

	PositionComponent() {
		pos = new Vector2D();
		speed = new Vector2D();
		height = width = 32;
	};

	explicit PositionComponent(float v) {
		pos = new Vector2D(v, v);
		speed = new Vector2D();
		height = width = 32;
	};

	PositionComponent(float x, float y) {
		pos = new Vector2D(x, y);
		speed = new Vector2D();
		height = width = 32;
	};

	PositionComponent(float x, float y, int w, int h) {
		pos = new Vector2D(x, y);
		speed = new Vector2D();
		width = w;
		height = h;
	};

	void update() override {
		pos->add(*speed);
	}

	void setSpeed(float speedX, float speedY) {
		speed->x(speedX);
		speed->y(speedY);
	}

	Vector2D *getSpeed() {
		return this->speed;
	}

	int x() { return (int) (pos->x()); }

	int y() { return (int) (pos->y()); }

	[[nodiscard]] int w() const { return width; }

	[[nodiscard]] int h() const { return height; }

	void free() {
		pos->free();
		delete[] pos;

		speed->free();
		delete[] speed;
	}

};


#endif //KINGDONKEY_POSITIONCOMPONENT_H
