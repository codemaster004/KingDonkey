//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "MathVector.h"


float Vector2::dot(Vector2 vec1, Vector2 vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y;
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
	// Multiply each dimension with the scalar.
	result.x *= scalar;
	result.y *= scalar;

	return result; // Return the vector.
}


Vector2 Vector2::operator*(float scalar) {
	Vector2 result = *this;
	return result.scalarMultiply(scalar);
}


void Vector2::operator*=(float scalar) {
	*this = this->scalarMultiply(scalar);
}


Vector2 &Vector2::add(const Vector2 &vec) {
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}


Vector2 &Vector2::subtract(const Vector2 &vec) {
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}


Vector2 &Vector2::multiply(const Vector2 &vec) {
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}


Vector2 &Vector2::divide(const Vector2 &vec) {
	this->x /= vec.x;
	this->y /= vec.y;
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


bool Vector2::operator==(const Vector2 &vec) const {
	return x == vec.x && y == vec.y;
}


bool Vector2::operator!=(const Vector2 &vec) const {
	return !(*this == vec);
}


bool Vector2::operator<(const Vector2 &vec) {
	return dot(*this, *this) < dot(vec, vec);
}


bool Vector2::operator>(const Vector2 &vec) {
	return dot(*this, *this) > dot(vec, vec);
}
