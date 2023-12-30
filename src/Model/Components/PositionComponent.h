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

	PositionComponent(float x, float y) {
		setPos(x, y);
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

	Vector2D *getPos();

	float x() { return pos->x(); }

	void x(float newX) { pos->x(newX); }

	float y() { return pos->y(); }

	void y(float newY) { pos->y(newY); }

	[[nodiscard]] int w() const { return width; }

	[[nodiscard]] int h() const { return height; }

	[[nodiscard]] float s() const { return scale; }

	void free() {}

};


#endif //KINGDONKEY_POSITIONCOMPONENT_H
