//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "MathVector.h"


void MathVector::init() {
	vector = new float[dimensions];
	for (int i = 0; i < dimensions; ++i) {
		vector[i] = 0;
	}
}

bool MathVector::checkDims(const MathVector &vec1, const MathVector &vec2) {
	return vec1.dimensions == vec2.dimensions;
}

MathVector &MathVector::add(const MathVector &vec, float multiplier) {
	if (checkDims(*this, vec))
		for (int i = 0; i < dimensions; ++i)
			this->vector[i] += vec.vector[i] * multiplier;

	return *this;
}

MathVector &MathVector::subtract(const MathVector &vec) {
	if (checkDims(*this, vec))
		for (int i = 0; i < dimensions; ++i)
			this->vector[i] -= vec.vector[i];

	return *this;
}

MathVector &MathVector::multiply(const MathVector &vec) {
	if (checkDims(*this, vec))
		for (int i = 0; i < dimensions; ++i)
			this->vector[i] *= vec.vector[i];

	return *this;
}

MathVector &MathVector::divide(const MathVector &vec) {
	if (checkDims(*this, vec))
		for (int i = 0; i < dimensions; ++i)
			this->vector[i] /= vec.vector[i];

	return *this;
}

MathVector &MathVector::flip() {
	float temp;
	for (int i = 0; i < dimensions/2; ++i) {
		temp = vector[i];
		vector[i] = vector[dimensions - i - 1];
		vector[dimensions - i - 1] = temp;
	}
	return *this;
}
