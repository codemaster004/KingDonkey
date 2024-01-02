//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "MathVector.h"


float Vector2D::dot(Vector2D vec1, Vector2D vec2) {
	float res = 0;
	for (int i = 0; i < vec1.dimensions; ++i) { // Loop through dimensions
		// Calculate their product and add it to the result.
		res += vec1.vector[i] * vec2.vector[i];
	}

	return res;
}


float Vector2D::magnitude2() {
	// calculate the square magnitude using the dot with itself
	return dot(*this, *this);
}


Vector2D Vector2D::scalarMultiply(float scalar) {
	Vector2D result = *this;
	for (int i = 0; i < dimensions; ++i) // Loop through dimensions
		// Multiply each dimension with the scalar.
		result.vector[i] *= scalar;

	return result; // Return the vector.
}


Vector2D Vector2D::abs() {
	Vector2D result = *this;
	for (int i = 0; i < dimensions; ++i) { // Loop through dimensions
		if (result.vector[i] < 0) {
			// Change the sign of the dimension value to positive
			result.vector[i] = -result.vector[i];
		}
	}

	return result; // Return the new absolute vector
}


Vector2D &Vector2D::add(const Vector2D &vec) {
	for (int i = 0; i < dimensions; ++i)
		this->vector[i] += vec.vector[i];

	return *this;
}


Vector2D &Vector2D::subtract(const Vector2D &vec) {
	for (int i = 0; i < dimensions; ++i)
		this->vector[i] -= vec.vector[i];

	return *this;
}


Vector2D &Vector2D::multiply(const Vector2D &vec) {
	for (int i = 0; i < dimensions; ++i)
		this->vector[i] *= vec.vector[i];

	return *this;
}


Vector2D &Vector2D::divide(const Vector2D &vec) {
	for (int i = 0; i < dimensions; ++i)
		this->vector[i] /= vec.vector[i];

	return *this;
}


Vector2D Vector2D::operator+(const Vector2D &vec) {
	Vector2D result = *this;
	return result.add(vec);
}


void Vector2D::operator+=(const Vector2D &vec) {
	this->add(vec);
}


Vector2D Vector2D::operator-(const Vector2D &vec) {
	Vector2D result = *this;
	return result.subtract(vec);
}


void Vector2D::operator-=(const Vector2D &vec) {
	this->subtract(vec);
}


Vector2D Vector2D::operator*(const Vector2D &vec) {
	Vector2D result = *this;
	return result.multiply(vec);
}


void Vector2D::operator*=(const Vector2D &vec) {
	this->multiply(vec);
}


Vector2D Vector2D::operator/(const Vector2D &vec) {
	Vector2D result = *this;
	return result.divide(vec);
}


void Vector2D::operator/=(const Vector2D &vec) {
	this->divide(vec);
}


bool Vector2D::operator==(const Vector2D &vec) {
	return vector[0] == vec.vector[0] && vector[1] == vec.vector[1];
}


bool Vector2D::operator!=(const Vector2D &vec) {
	return !(*this == vec);
}


bool Vector2D::operator<(const Vector2D &vec) {
	return Vector2D::dot(*this, *this) < Vector2D::dot(vec, vec);
}


bool Vector2D::operator>(const Vector2D &vec) {
	return Vector2D::dot(*this, *this) > Vector2D::dot(vec, vec);
}
