#include "Metaball.h"

MetaBalls::MetaBalls() {
	gridSize = 20;
	threshold = 0.35f;
	numMetaballs = 12;
}

void MetaBalls::setUpGrid() {
	//set up grid
	cubeGrid.CreateMemory();
	cubeGrid.Init(gridSize);
}

void MetaBalls::setUpMetaballs() {
	//set up front metaballs
	metaballs[0].Init(Vec3f(0.3f, 0.4f, 0.4f), 0.05f);
	metaballs[1].Init(Vec3f(0.3f, -0.3f, 0.4f), 0.05f);
	metaballs[2].Init(Vec3f(0.3f, -1.0f, 0.0f), 0.05f);

	metaballs[3].Init(Vec3f(-0.3f, 0.4f, 0.4f), 0.05f);
	metaballs[4].Init(Vec3f(-0.3f, -0.3f, 0.4f), 0.05f);
	metaballs[5].Init(Vec3f(-0.3f, -1.0f, 0.0f), 0.05f);

	//set up back metaballs
	metaballs[6].Init(Vec3f(0.3f, 0.4f, -0.4f), 0.05f);
	metaballs[7].Init(Vec3f(0.3f, -0.3f, -0.4f), 0.05f);
	metaballs[8].Init(Vec3f(0.3f, -1.0f, -0.0f), 0.05f);

	metaballs[9].Init(Vec3f(-0.3f, 0.4f, -0.4f), 0.05f);
	metaballs[10].Init(Vec3f(-0.3f, -0.3f, -0.4f), 0.05f);
	metaballs[11].Init(Vec3f(-0.3f, -1.0f, -0.0f), 0.05f);
}

void MetaBalls::evalScalarField() {
	//clear the field
	for (int i = 0; i<cubeGrid.numVertices; i++) {
		cubeGrid.vertices[i].value = 0.0f;
		cubeGrid.vertices[i].normal.zeroElements();
	}

	//evaluate the scalar field at each point
	Vec3f ballToPoint;
	float squaredRadius;
	Vec3f ballPosition;
	float normalScale;
	for (int i = 0; i<numMetaballs; i++) {
		squaredRadius = metaballs[i].squaredRadius;
		ballPosition = metaballs[i].position;

		for (int j = 0; j<cubeGrid.numVertices; j++) {
			ballToPoint[0] = cubeGrid.vertices[j].position[0] - ballPosition[0];
			ballToPoint[1] = cubeGrid.vertices[j].position[1] - ballPosition[1];
			ballToPoint[2] = cubeGrid.vertices[j].position[2] - ballPosition[2];

			float squaredDistance = ballToPoint[0] * ballToPoint[0] + ballToPoint[1] * ballToPoint[1] + ballToPoint[2] * ballToPoint[2];

			if (squaredDistance == 0.0f)
				squaredDistance = 0.0001f;

			//value = r^2/d^2
			cubeGrid.vertices[j].value += squaredRadius / squaredDistance;

			//normal = (r^2 * v)/d^4
			normalScale = squaredRadius / (squaredDistance*squaredDistance);

			cubeGrid.vertices[j].normal[0] += ballToPoint[0] * normalScale;
			cubeGrid.vertices[j].normal[1] += ballToPoint[1] * normalScale;
			cubeGrid.vertices[j].normal[2] += ballToPoint[2] * normalScale;
		}
	}
}


void MetaBalls::draw() {
	cubeGrid.DrawSurface(threshold);
}
