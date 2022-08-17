#include "GeneralMaths.h"
float billinearInterpolation(float bottomLeft, float topLeft, float bottomRight, float topRight,
	float xMin, float xMax,
	float zMin, float zMax,
	float x, float z)
{
	float width = xMax - xMin;
	float height = zMax - zMin;
	float xDistanceToMaxValue = xMax - x;
	float zDistanceToMaxValue = zMax - z;
	float xDistanceToMinValue = x - xMin;
	float zDistanceToMinValue = z - zMin;

	return 1.f / (width * height) *
		(
			bottomLeft * xDistanceToMaxValue * zDistanceToMaxValue +
			bottomRight * xDistanceToMinValue * zDistanceToMaxValue +
			topLeft * xDistanceToMaxValue * zDistanceToMinValue +
			topRight * xDistanceToMinValue * zDistanceToMinValue
			);
}