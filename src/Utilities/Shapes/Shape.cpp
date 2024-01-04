#include "Shape.h"
#include "../../ViewModel/CollisionViewModel.h"

#include "cmath"


void Shape::addCorner(float x, float y) {
	vertices.push(Vector2D((float) x, (float) y)); // Add new corner vector (x, y) to the shape.
}


size_t Shape::nEdges() {
	// Getting the count of vertices in the shape.
	size_t verticesCount = vertices.getSize();

	// Return 0 if the shape does not have any points or is a single point.
	return verticesCount <= 1 ? 0 : verticesCount - 1;
}


void Shape::initRect(float x, float y, float w, float h) {
	// All corners are relative to the origin to optimise movement in a space.
	setOrigin(x, y);

	// Adding corners to the rectangle.
	// The order matters for creating the shape edges.
	addCorner(0, 0); // Top-left
	addCorner(0, h); // Bottom-left
	addCorner(w, h); // Bottom-right
	addCorner(w, 0); // Top-right
}


Vector2D *Shape::getOrigin() {
	return &origin; // return the pointer to the origin vector
}


void Shape::setOrigin(float newX, float newY) {
	// Set new values for the origin.
	origin.setX(newX);
	origin.setY(newY);
}


void Shape::calculateNormalAxes(ListSet<Vector2D> &buffer) {
	// Loop through each vertex.
	size_t nVertices = vertices.getSize();
	for (int i = 0; i < nVertices; i++) {
		// Get the current vertex and the next one.
		Vector2D vector1 = vertices.get(i);
		Vector2D vector2 = vertices.get((i + 1) % nVertices);

		Vector2D edgeVector = vector2 - vector1; // Calculate the edge vector.

		// Calculate the normal vector by rotating the edge vector 90 degrees counter-clockwise.
		Vector2D normalVector(-edgeVector.getY(), edgeVector.getX());

		// Normalize the obtained normal vector
		float magnitude = sqrt(normalVector.magnitude2());
		normalVector = normalVector.scalarMultiply(1 / magnitude);

		buffer.append(normalVector); // Add to the Set
	}
}


void Shape::projectOntoAxis(Vector2D axis, ProjectionRange *shadow) {
	// Initializing the min and max of the shadow with project of the first vertex onto the axis.
	shadow->min = Vector2D::dot(vertices.get(0) + origin, axis);
	shadow->max = shadow->min;

	// Now, iterate through the rest of the vertices.
	for (int i = 1; i < nEdges(); i++) {
		// Project the current vertex onto the axis.
		float projection = Vector2D::dot(vertices.get(i) + origin, axis);

		// If this projection is less than the current min, update the min.
		if (projection < shadow->min)
			shadow->min = projection;
		// If it is more than the current max, update the max.
		if (projection > shadow->max)
			shadow->max = projection;
	}
}
