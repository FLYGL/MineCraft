#pragma once

float billinearInterpolation(float bottomLeft, float topLeft, float bottomRight, float topRight,
	float xMin, float xMax,
	float zMin, float zMax,
	float xToCalc, float zToCalc);