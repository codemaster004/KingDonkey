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

	int scale;
	int width;
	int height;

public:

	PositionComponent() {
		pos = new Vector2D();
		speed = new Vector2D();
		height = width = 32;
		scale = 1;
	};

	explicit PositionComponent(float v) {
		pos = new Vector2D(v, v);
		speed = new Vector2D();
		height = width = 32;
		scale = 1;
	};

	PositionComponent(float x, float y) {
		pos = new Vector2D(x, y);
		speed = new Vector2D();
		height = width = 32;
		scale = 1;
	};

	PositionComponent(float x, float y, int w, int h) {
		pos = new Vector2D(x, y);
		speed = new Vector2D();
		width = w;
		height = h;
		scale = 1;
	};

	PositionComponent(float x, float y, int w, int h, int s) {
		pos = new Vector2D(x, y);
		speed = new Vector2D();
		width = w;
		height = h;
		scale = s;
	};

	void update() override {
		pos->add(*speed);
	}

	void setSpeed(float speedX, float speedY) {
		speed->x(speedX);
		speed->y(speedY);
	}

	void setSpeedX(float speedX) {
		speed->x(speedX);
	}

	void setSpeedY(float speedY) {
		speed->y(speedY);
	}

	Vector2D *getSpeed() {
		return this->speed;
	}

	int x() { return (int) (pos->x()); }

	void x(float newX) { pos->x(newX); }

	int y() { return (int) (pos->y()); }

	void y(float newY) { pos->y(newY); }

	[[nodiscard]] int w() const { return width; }

	[[nodiscard]] int h() const { return height; }

	[[nodiscard]] int s() const { return scale; }

	void free() {
		pos->free();
		delete[] pos;

		speed->free();
		delete[] speed;
	}

};


#endif //KINGDONKEY_POSITIONCOMPONENT_H
