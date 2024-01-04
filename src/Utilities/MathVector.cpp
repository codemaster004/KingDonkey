//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "MathVector.h"


float Vector2::dot(Vector2 vec1, Vector2 vec2) {
	float res = 0;
	for (int i = 0; i < vec1.dimensions; ++i) { // Loop through dimensions
		// Calculate their product and add it to the result.
		res += vec1.vector[i] * vec2.vector[i];
	}

	return res;
}

float Vector2::dot(Vector2 vec) {
	return Vector2::dot(*this, vec);
}


float Vector2::magnitude2() {
	// calculate the square magnitude using the dot with itself
	return dot(*this, *this);
}


Vector2 Vector2::scalarMultiply(float scalar) {
	Vector2 result = *this;
	for (int i = 0; i < dimensions; ++i) // Loop through dimensions
		// Multiply each dimension with the scalar.
		result.vector[i] *= scalar;

	return result; // Return the vector.
}


Vector2 Vector2::operator*(float scalar) {
	Vector2 result = *this;
	return result.scalarMultiply(scalar);
}


void Vector2::operator*=(float scalar) {
	*this = this->scalarMultiply(scalar);
}


Vector2 Vector2::abs() {
	Vector2 result = *this;
	for (int i = 0; i < dimensions; ++i) { // Loop through dimensions
		if (result.vector[i] < 0) {
			// Change the sign of the dimension value to positive
			result.vector[i] = -result.vector[i];
		}
	}

	return result; // Return the new absolute vector
}


Vector2 &Vector2::add(const Vector2 &vec) {
	for (int i = 0; i < dimensions; ++i)
		this->vector[i] += vec.vector[i];

	return *this;
}


Vector2 &Vector2::subtract(const Vector2 &vec) {
	for (int i = 0; i < dimensions; ++i)
		this->vector[i] -= vec.vector[i];

	return *this;
}


Vector2 &Vector2::multiply(const Vector2 &vec) {
	for (int i = 0; i < dimensions; ++i)
		this->vector[i] *= vec.vector[i];

	return *this;
}


Vector2 &Vector2::divide(const Vector2 &vec) {
	for (int i = 0; i < dimensions; ++i)
		this->vector[i] /= vec.vector[i];

	return *this;
}


Vector2 Vector2::operator+(const Vector2 &vec) {
	Vector2 result = *this;
	return result.add(vec);
}


void Vector2::operator+=(const Vector2 &vec) {
	this->add(vec);
}


Vector2 Vector2::operator-(const Vector2 &vec) {
	Vector2 result = *this;
	return result.subtract(vec);
}


void Vector2::operator-=(const Vector2 &vec) {
	this->subtract(vec);
}


Vector2 Vector2::operator*(const Vector2 &vec) {
	Vector2 result = *this;
	return result.multiply(vec);
}


void Vector2::operator*=(const Vector2 &vec) {
	this->multiply(vec);
}


Vector2 Vector2::operator/(const Vector2 &vec) {
	Vector2 result = *this;
	return result.divide(vec);
}


void Vector2::operator/=(const Vector2 &vec) {
	this->divide(vec);
}


bool Vector2::operator==(const Vector2 &vec) {
	return vector[0] == vec.vector[0] && vector[1] == vec.vector[1];
}


bool Vector2::operator!=(const Vector2 &vec) {
	return !(*this == vec);
}


bool Vector2::operator<(const Vector2 &vec) {
	return dot(*this, *this) < dot(vec, vec);
}


bool Vector2::operator>(const Vector2 &vec) {
	return dot(*this, *this) > dot(vec, vec);
}
