#include "Shape.h"
#include "../../ViewModel/CollisionViewModel.h"

#include "cmath"
#include "../DataStructures/ListSet.h"


//Shape::Shape() {
//	origin = Vector2D(0, 0);
//}

void Shape::addCorner(float x, float y) {
	vertices.push(Vector2D((float) x, (float) y));
}

size_t Shape::nEdges() {
	size_t edges = vertices.getSize();
	return edges <= 1 ? 0 : edges - 1;
}

void Shape::initRect(float x, float y, float w, float h) {
	updateOrigin(x, y);
	addCorner(0, 0);
	addCorner(0, h);
	addCorner(w, h);
	addCorner(w, 0);
}

void Shape::updateOrigin(float newX, float newY) {
	origin.x(newX);
	origin.y(newY);
}

void Shape::calculateNormalAxes(ListSet<Vector2D> &buffer) {
	size_t nVertices = vertices.getSize();

	for (int i = 0; i < nVertices; i++) {
		Vector2D vector1 = vertices.get(i);
		Vector2D vector2 = vertices.get((i + 1) % nVertices);

		Vector2D edgeVector = vector2 - vector1;
		Vector2D normalVector(-edgeVector.y(), edgeVector.x());

		float magnitude = sqrt(normalVector.x() * normalVector.x() + normalVector.y() * normalVector.y());
		normalVector.scalarMultiply(1 / magnitude);

		buffer.append(normalVector);
	}
}

void Shape::projectOntoAxis(Vector2D axis, ProjectionRange *shadow) {
	shadow->min = Vector2D::dotProduct(vertices.get(0) + origin, axis);
	shadow->max = shadow->min;

	for (int i = 1; i < nEdges(); i++) {
		float projection = Vector2D::dotProduct(vertices.get(i) + origin, axis);

		if (projection < shadow->min)
			shadow->min = projection;
		if (projection > shadow->max)
			shadow->max = projection;
	}
}

Vector2D *Shape::getOrigin() {
	return &origin;
}
