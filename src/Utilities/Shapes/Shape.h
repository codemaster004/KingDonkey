//
// Created by Filip Dabkowski on 29/12/2023.
//

#ifndef KINGDONKEY_SHAPE_H
#define KINGDONKEY_SHAPE_H

#include "../DataStructures/DataStore.h"
#include "../MathVector.h"
#include "../DataStructures/ListSet.h"

struct ProjectionRange;

class Shape {
private:
	Vector2D origin;
	DataStore<Vector2D> vertices;

public:
	Shape() = default;

	void addCorner(float x, float y);

	size_t nEdges();

	void initRect(float x, float y, float w, float h);

	void updateOrigin(float newX, float newY);

	Vector2D *getOrigin();

	void calculateNormalAxes(ListSet<Vector2D> &buffer);

	void projectOntoAxis(Vector2D axis, ProjectionRange *shadow);
};


#endif //KINGDONKEY_SHAPE_H
