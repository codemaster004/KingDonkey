//
// Created by Filip Dabkowski on 29/12/2023.
//
#include "Shape.h"

#include "cmath"


void Shape::addCorner(float x, float y) {
	vertices.push(Vector2((float) x, (float) y)); // Add new corner vector (x, y) to the shape.
	updateBox(x, y);
	updateCenter(x, y);
}


size_t Shape::nEdges() {
	// Getting the count of vertices in the shape.
	size_t verticesCount = vertices.getSize();

	// Return 0 if the shape does not have any points or is a single point.
	return verticesCount <= 1 ? 0 : verticesCount;
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


void Shape::initTrig(float x, float y, float w, float h) {
	setOrigin(x, y);

	addCorner(0, 0);
	addCorner(w, 0);
	addCorner(0, h);
}


Vector2 *Shape::getOrigin() {
	return &origin; // return the pointer to the origin vector
}


void Shape::setOrigin(float newX, float newY) {
	// Set new values for the origin.
	origin.setX(newX);
	origin.setY(newY);
}


void Shape::calculateNormalAxes(ListSet<Vector2> &buffer) {
	// Loop through each vertex.
	size_t nVertices = vertices.getSize();
	for (int i = 0; i < nVertices; i++) {
		// Get the current vertex and the next one.
		Vector2 vector1 = vertices.get(i);
		Vector2 vector2 = vertices.get((i + 1) % nVertices);

		Vector2 edgeVector = vector2 - vector1; // Calculate the edge vector.

		// Calculate the normal vector by rotating the edge vector 90 degrees counter-clockwise.
		Vector2 normalVector(-edgeVector.getY(), edgeVector.getX());

		// Normalize the obtained normal vector
		float magnitude = sqrt(normalVector.magnitude2());
		normalVector = normalVector.scalarMultiply(1 / magnitude);

		buffer.append(normalVector); // Add to the Set
	}
}


void Shape::projectOntoAxis(Vector2 axis, Range *shadow) {
	// Initializing the min and max of the shadow with project of the first vertex onto the axis.
	shadow->min = Vector2::dot(vertices.get(0) + origin, axis);
	shadow->max = shadow->min;

	// Now, iterate through the rest of the vertices.
	for (int i = 1; i < nEdges(); i++) {
		// Project the current vertex onto the axis.
		float projection = Vector2::dot(vertices.get(i) + origin, axis);

		// If this projection is less than the current min, update the min.
		if (projection < shadow->min)
			shadow->min = projection;
		// If it is more than the current max, update the max.
		if (projection > shadow->max)
			shadow->max = projection;
	}
}


Vector2 Shape::getCorner(int index) {
	return vertices.get(index);
}


void Shape::updateRange(Range &range, float newValue) {
	if (newValue < range.min) {
		range.min = newValue;
	} else if (newValue > range.max) {
		range.max = newValue;
	}
}


void Shape::updateBox(float newX, float newY) {
	// Update ranges check for value
	updateRange(rangeBox.xAxis, newX + origin.getX());
	updateRange(rangeBox.yAxis, newY + origin.getY());

	// Update for potentially new X and new width
	boundingBox.x = rangeBox.xAxis.min;
	boundingBox.w = rangeBox.xAxis.max - rangeBox.xAxis.min;

	// Update for potentially new Y and new height
	boundingBox.y = rangeBox.yAxis.min;
	boundingBox.h = rangeBox.yAxis.max - rangeBox.yAxis.min;
}


void Shape::updateCenter(float newX, float newY) {
	if (vertices.getSize() == 1) {
		centroid.setX(newX);
		centroid.setY(newY);
		return;
	}

	float avg;
	auto size = (float) (vertices.getSize());

	// Calculate nre Average for X cord
	avg = (centroid.getX() * size - 1 + newX) / size;
	centroid.setX(avg);

	// Calculate nre Average for Y cord
	avg = (centroid.getY() * size - 1 + newY) / size;
	centroid.setY(avg);
}


Vector2 Shape::getCentroid() {
	return centroid + origin;
}
