//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_POSITION_H
#define KINGDONKEY_POSITION_H

#include "EntityComponent.h"
#include "../../Utilities/MathVector.h"


class Position : public EntityComponent {
private:
	Vector2 *pos = new Vector2();
	Vector2 *speed = new Vector2();

	float scale;
	int width;
	int height;

public:

	Position() {
		height = width = 32;
		scale = 1;
	};


	Position(float x, float y) {
		setPos(x, y);
		height = width = 32;
		scale = 1;
	};


	Position(float x, float y, int w, int h) {
		setPos(x, y);
		width = w;
		height = h;
		scale = 1;
	};


	Position(float x, float y, int w, int h, float s) {
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

	Vector2 *getSpeed();

	Vector2 *getPos();


	float x() { return pos->getX(); }


	void x(float newX) { pos->setX(newX); }


	float y() { return pos->getY(); }


	void y(float newY) { pos->setY(newY); }


	[[nodiscard]] float w() const { return (float) (width); }


	[[nodiscard]] float h() const { return (float) (height); }


	[[nodiscard]] float s() const { return scale; }


	void free() {}

};


#endif //KINGDONKEY_POSITION_H
