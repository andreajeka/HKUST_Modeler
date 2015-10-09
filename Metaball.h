#include "CUBE_GRID.h"
#include "vec.h"

#ifndef _METABALL_H
#define _METABALL_H

class METABALL {
public:
	Vec3f position;
	float squaredRadius;

	void Init(Vec3f newPosition, float newSquaredRadius)
	{
		position = newPosition;
		squaredRadius = newSquaredRadius;
	}
};

class MetaBalls {
public:
	MetaBalls();
	void setUpGrid();
	void setUpMetaballs();
	void evalScalarField();
	void draw();

private:
	int gridSize;
	float threshold;

	CUBE_GRID cubeGrid;

	int numMetaballs;
	METABALL metaballs[12];
};

#endif