//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "MathVector.h"


bool MathVector::checkDims(const MathVector &vec1, const MathVector &vec2) {
	return vec1.dimensions == vec2.dimensions;
}

MathVector &MathVector::add(const MathVector &vec) {
	if (checkDims(*this, vec))
		for (int i = 0; i < dimensions; ++i)
			this->vector[i] += vec.vector[i];

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
