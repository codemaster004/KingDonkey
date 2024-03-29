//
// Created by Filip Dabkowski on 29/12/2023.
//

#ifndef KINGDONKEY_SHAPE_H
#define KINGDONKEY_SHAPE_H

#include "../DataStructures/DataStore.h"
#include "../DataStructures/Vector.h"
#include "../DataStructures/ListSet.h"
#include "../MathVector.h"

#include "cfloat"


/// A structure to represent a range of projection in a 1D plane.
/// It consists of two floats representing the minimum and maximum values of a projection range.
typedef struct Range {
	float min = FLT_MAX; ///< The minimum value.
	float max = FLT_MIN; ///< The maximum value.
} Range;


typedef struct Range2 {
	Range xAxis; ///< Range of values on X axis
	Range yAxis; ///< Range of values on Y axis
} Range2;

typedef struct Rect {
	float x, y; ///< Origin cords of rectangle corner
	float w, h; ///< width, height of rectangle to create representation in space
} Rect;


class Shape {
private:
	Vector2 origin;
	Vector<Vector2> vertices;

	Range2 rangeBox;
	Rect boundingBox;

	Vector2 centroid;

	static void updateRange(Range &range, float newValue);

	void updateBox(float newX, float newY);

	void updateCenter(float newX, float newY);

public:
	Shape() = default;

	/**
	 * @brief Add a corner to the shape.
	 *
	 * @details This function adds a corner with the given x and y coordinates to the shape.
	 *
	 * @param x The x coordinate of the corner.
	 * @param y The y coordinate of the corner.
	 */
	void addCorner(float x, float y);

	Vector2 getCorner(int index);

	Vector2 getCentroid();

	/**
	 * @brief Calculates the number of edges for the shape.
	 *
	 * @details This function returns the number of edges for the shape, based on the number of vertices.
	 * If the shape has less than 2 vertices, it does not have any edges.
	 *
	 * @return The number of edges in the shape.
	 */
	size_t nEdges();

	/**
	 * @brief Initialize a rectangle shape with the given parameters.
	 *
	 * @details This function updates the origin of the shape and adds four corners
	 * to create a rectangle shape.
	 *
	 * @param x The X coordinate of the origin.
	 * @param y The Y coordinate of the origin.
	 * @param w The width of the rectangle.
	 * @param h The height of the rectangle.
	 */
	void initRect(float x, float y, float w, float h);


	void initTrig(float x, float y, float w, float h);

	/**
	 * @brief Set new value for the origin vector.
	 *
	 * @param newX new value for the x coordinate.
	 * @param newY new value for the Y coordinate.
	 */
	void setOrigin(float newX, float newY);

	/**
	 * @brief Returns a pointer to the origin of the shape.
	 *
	 * @return A pointer to the origin of the shape.
	 */
	Vector2 *getOrigin();

	/**
	 * @brief Calculates the normal axes of the shape and stores them in the given buffer.
	 *
	 * @details The normal axes are the perpendicular vectors to the edges of the shape.
	 * For each edge, it calculates the edge vector and then determines the perpendicular normal vector.
	 * The function then normalizes the normal vector and appends it to the buffer.
	 *
	 * @param buffer The list set to store the calculated normal axes.
	 */
	void calculateNormalAxes(ListSet<Vector2> &buffer);

	/**
	 * @brief Project the shape onto a given axis and calculate the projection range.
	 *
	 * @details Projection is calculated by taking the dot product of each vertex of the shape with the specified axis.
	 * The minimum and maximum values of the projection range are updated based on the calculated projections.
	 *
	 * @param axis The axis onto which the shape is projected.
	 * @param shadow The projection range structure where the minimum and maximum values will be stored.
	 */
	void projectOntoAxis(Vector2 axis, Range *shadow);
};


#endif //KINGDONKEY_SHAPE_H
