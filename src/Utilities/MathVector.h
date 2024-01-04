//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_MATHVECTOR_H
#define KINGDONKEY_MATHVECTOR_H

#include "cstddef"


/**
 * @class Vector2D
 * @brief Represents a 2D vector
 *
 * @details Class is used to hold coordinates of various elements in the game,
 * in order to simplify mathematical operation on them.
 */
class Vector2D {
private:
	int dimensions = 2; ///< number of dimensions of the vector
	float vector[2] = {0, 0}; ///< table with coordinates for each dimension

public:

	Vector2D() = default;


	/**
	 * @brief Constructor for the Vector2D class.
	 *
	 * @param x The x coordinate of the vector.
	 * @param y The y coordinate of the vector.
	 */
	Vector2D(float x, float y) {
		vector[0] = x;
		vector[1] = y;
	}


	/**
	 * @brief This function calculates and returns the dot product of two given vectors.
	 *
	 * @details The dot product is the result of
	 * multiplication of the corresponding entries in the two input vectors,
	 * summed up for all entries.
	 *
	 * @param vec1 The first vector.
	 * @param vec2 The second vector.
	 * @returns The dot product of the two vectors.
	 */
	static float dot(Vector2D vec1, Vector2D vec2);

	float dot(const Vector2D vec);

	/**
	 * @brief This function calculates and returns the square of the magnitude of the vector.
	 *
	 * @return The square of the magnitude of the vector.
	 */
	float magnitude2();

	/**
	 * @brief Multiplies the vector by a scalar.
	 *
	 * @details Function creates a new vector with the multiplied values and returns it.
	 *
	 * @param scalar The scalar value to multiply the vector by.
	 * @return The resulting vector after scalar multiplication.
	 */
	[[nodiscard ]] Vector2D scalarMultiply(float scalar);

	Vector2D operator*(float scalar);

	void operator*=(float scalar);

	/**
	 * @brief Calculates the absolute value of the vector.
	 *
	 * @details This function creates a new vector with the absolute values of the dimensions
	 * of the original vector and returns it.
	 *
	 * @return The vector with absolute values.
 	 */
	[[nodiscard ]] Vector2D abs();


	/// + Add operations
	Vector2D &add(const Vector2D &vec);

	Vector2D operator+(const Vector2D &vec);

	void operator+=(const Vector2D &vec);

	/// - Subtract operation
	Vector2D &subtract(const Vector2D &vec);

	Vector2D operator-(const Vector2D &vec);

	void operator-=(const Vector2D &vec);

	/// * Multiply operation
	Vector2D &multiply(const Vector2D &vec);

	Vector2D operator*(const Vector2D &vec);

	void operator*=(const Vector2D &vec);

	/// / Divide operation
	Vector2D &divide(const Vector2D &vec);

	Vector2D operator/(const Vector2D &vec);

	void operator/=(const Vector2D &vec);

	/// == Equality check
	bool operator==(const Vector2D &vec);

	bool operator!=(const Vector2D &vec);

	/// < is Less than
	bool operator<(const Vector2D &vec);

	/// > is More than
	bool operator>(const Vector2D &vec);


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