//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_MATHVECTOR_H
#define KINGDONKEY_MATHVECTOR_H

#include "cstddef"

class MathVector {
protected:
	float *vector;
	size_t dimensions;

public:

	explicit MathVector(size_t size) : dimensions(size) {
		vector = new float[dimensions];
		for (int i = 0; i < dimensions; ++i) {
			vector[i] = 0;
		}
	}

	static bool checkDims(const MathVector &vec1, const MathVector &vec2);

	MathVector & add(const MathVector &vec);

	MathVector &subtract(const MathVector &vec);

	MathVector &multiply(const MathVector &vec);

	MathVector &divide(const MathVector &vec);

	// TODO: general getters & setters

	void free() {
		delete[] vector;
	}

	~MathVector() = default;

public:
	MathVector() = default;
};

class Vector2D : public MathVector {
public:
	Vector2D() : MathVector(2) {}

	Vector2D(float x, float y) : MathVector(2) {
		vector[0] = x;
		vector[1] = y;
	}

	float x() {
		return vector[0];
	}

	void x(float value) {
		vector[0] = value;
	}

	float y() {
		return vector[1];
	}

	void y(float value) {
		vector[1] = value;
	}

	~Vector2D() = default;

};


#endif //KINGDONKEY_MATHVECTOR_H
