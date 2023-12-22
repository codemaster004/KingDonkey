//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_POSITIONCOMPONENT_H
#define KINGDONKEY_POSITIONCOMPONENT_H

#include "Component.h"
#include "../../Utilities/MathVector.h"


class PositionComponent : public Component {
private:
	Vector2D *pos = new Vector2D();
	Vector2D *speed = new Vector2D();

	float scale;
	int width;
	int height;

public:

	PositionComponent() {
		height = width = 32;
		scale = 1;
	};

	explicit PositionComponent(float v) {
		setPos(v, v);
		height = width = 32;
		scale = 1;
	};

	PositionComponent(float x, float y) {
		height = width = 32;
		scale = 1;
	};

	PositionComponent(float x, float y, int w, int h) {
		setPos(x, y);
		width = w;
		height = h;
		scale = 1;
	};

	PositionComponent(float x, float y, int w, int h, float s) {
		setPos(x, y);
		width = w;
		height = h;
		scale = s;
	};

	void update() override;

	void setSpeed(float speedX, float speedY);

	void setPos(float posX, float posY);

	void setSpeedX(float speedX);

	void setSpeedY(float speedY);

	Vector2D *getSpeed();

	int x() { return (int) (pos->x()); }

	void x(float newX) { pos->x(newX); }

	int y() { return (int) (pos->y()); }

	void y(float newY) { pos->y(newY); }

	[[nodiscard]] int w() const { return width; }

	[[nodiscard]] int h() const { return height; }

	[[nodiscard]] float s() const { return scale; }

	void free() {
		pos->free();
		delete pos;

		speed->free();
		delete speed;
	}

};


#endif //KINGDONKEY_POSITIONCOMPONENT_H
