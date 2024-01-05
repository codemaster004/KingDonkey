//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_MATHVECTOR_H
#define KINGDONKEY_MATHVECTOR_H

#include "cstddef"


/**
 * @class Vector2
 * @brief Represents a 2D vector
 *
 * @details Class is used to hold coordinates of various elements in the game,
 * in order to simplify mathematical operation on them.
 */
class Vector2 {
private:
	float x = 0, y = 0; ///< table with coordinates for each dimension

public:

	Vector2() = default;


	/**
	 * @brief Constructor for the Vector2 class.
	 *
	 * @param x The x coordinate of the vector.
	 * @param y The y coordinate of the vector.
	 */
	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
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
	inline static float dot(Vector2 vec1, Vector2 vec2);

	float dot(Vector2 vec);

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
	[[nodiscard]] Vector2 scalarMultiply(float scalar);

	Vector2 operator*(float scalar);

	void operator*=(float scalar);


	/// + Add operations
	Vector2 &add(const Vector2 &vec);

	Vector2 operator+(const Vector2 &vec);

	void operator+=(const Vector2 &vec);

	/// - Subtract operation
	Vector2 &subtract(const Vector2 &vec);

	Vector2 operator-(const Vector2 &vec);

	void operator-=(const Vector2 &vec);

	/// * Multiply operation
	Vector2 &multiply(const Vector2 &vec);

	Vector2 operator*(const Vector2 &vec);

	void operator*=(const Vector2 &vec);

	/// / Divide operation
	Vector2 &divide(const Vector2 &vec);

	Vector2 operator/(const Vector2 &vec);

	void operator/=(const Vector2 &vec);

	/// == Equality check
	bool operator==(const Vector2 &vec) const;

	bool operator!=(const Vector2 &vec) const;

	/// < is Less than
	bool operator<(const Vector2 &vec);

	/// > is More than
	bool operator>(const Vector2 &vec);


	[[nodiscard]]
	float getX() const {
		return x;
	}


	void setX(float value) {
		x = value;
	}


	[[nodiscard]]
	float getY() const {
		return y;
	}


	void setY(float value) {
		y = value;
	}


	~Vector2() = default;

};


#endif //KINGDONKEY_MATHVECTOR_H