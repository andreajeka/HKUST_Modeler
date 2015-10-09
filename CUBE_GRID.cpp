//////////////////////////////////////////////////////////////////////////////////////////
//	CUBE_GRID.cpp
//	function definitions for grid of cubes for "marching cubes" algorithm
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	

#include <windows.h>
#include <GL/gl.h>
#include <iostream>
#include "CUBE_GRID.h"

bool CUBE_GRID::CreateMemory()
{
	vertices = new CUBE_GRID_VERTEX[(maxGridSize + 1)*(maxGridSize + 1)*(maxGridSize + 1)];
	if (!vertices)
	{
		printf("Unable to allocate memory for %d Grid Vertices", numVertices);
		return false;
	}

	cubes = new CUBE_GRID_CUBE[maxGridSize*maxGridSize*maxGridSize];
	if (!cubes)
	{
		printf("Unable to allocate memory for %d Grid Cubes", numCubes);
		return false;
	}

	return true;
}


bool CUBE_GRID::Init(int gridSize)
{

	//VERTICES
	numVertices = (gridSize + 1)*(gridSize + 1)*(gridSize + 1);

	int currentVertex = 0;
	// using grid size = 20 in 10 x 10 cube
	float dimension = 10.0f;
	float offset = 5.0f;

	for (int i = 0; i<gridSize + 1; i++)
	{
		for (int j = 0; j<gridSize + 1; j++)
		{
			for (int k = 0; k<gridSize + 1; k++)
			{
				vertices[currentVertex].position =
					Vec3f((i*dimension) / (gridSize)-offset, (j*dimension) / (gridSize)-offset, (k*dimension) / (gridSize)-offset);

				currentVertex++;
			}
		}
	}

	//CUBES
	numCubes = (gridSize)*(gridSize)*(gridSize);

	int currentCube = 0;

	for (int i = 0; i<gridSize; i++)
	{
		for (int j = 0; j<gridSize; j++)
		{
			for (int k = 0; k<gridSize; k++)
			{
				cubes[currentCube].vertices[0] = &vertices[(i*(gridSize + 1) + j)*(gridSize + 1) + k];
				cubes[currentCube].vertices[1] = &vertices[(i*(gridSize + 1) + j)*(gridSize + 1) + k + 1];
				cubes[currentCube].vertices[2] = &vertices[(i*(gridSize + 1) + (j + 1))*(gridSize + 1) + k + 1];
				cubes[currentCube].vertices[3] = &vertices[(i*(gridSize + 1) + (j + 1))*(gridSize + 1) + k];
				cubes[currentCube].vertices[4] = &vertices[((i + 1)*(gridSize + 1) + j)*(gridSize + 1) + k];
				cubes[currentCube].vertices[5] = &vertices[((i + 1)*(gridSize + 1) + j)*(gridSize + 1) + k + 1];
				cubes[currentCube].vertices[6] = &vertices[((i + 1)*(gridSize + 1) + (j + 1))*(gridSize + 1) + k + 1];
				cubes[currentCube].vertices[7] = &vertices[((i + 1)*(gridSize + 1) + (j + 1))*(gridSize + 1) + k];

				currentCube++;
			}
		}
	}

	return true;
}

void CUBE_GRID::DrawSurface(float threshold)
{
	numFacesDrawn = 0;

	static SURFACE_VERTEX edgeVertices[12];

	glBegin(GL_TRIANGLES);
	{
		//loop through cubes
		for (int i = 0; i<numCubes; i++)
		{
			//calculate which vertices are inside the surface
			unsigned char cubeIndex = 0;

			if (cubes[i].vertices[0]->value < threshold)
				cubeIndex |= 1;
			if (cubes[i].vertices[1]->value < threshold)
				cubeIndex |= 2;
			if (cubes[i].vertices[2]->value < threshold)
				cubeIndex |= 4;
			if (cubes[i].vertices[3]->value < threshold)
				cubeIndex |= 8;
			if (cubes[i].vertices[4]->value < threshold)
				cubeIndex |= 16;
			if (cubes[i].vertices[5]->value < threshold)
				cubeIndex |= 32;
			if (cubes[i].vertices[6]->value < threshold)
				cubeIndex |= 64;
			if (cubes[i].vertices[7]->value < threshold)
				cubeIndex |= 128;

			//look this value up in the edge table to see which edges to interpolate along
			int usedEdges = edgeTable[cubeIndex];

			//if the cube is entirely within/outside surface, no faces			
			if (usedEdges == 0 || usedEdges == 255)
				continue;

			//update these edges
			for (int currentEdge = 0; currentEdge<12; currentEdge++)
			{
				if (usedEdges & 1 << currentEdge)
				{
					CUBE_GRID_VERTEX * v1 = cubes[i].vertices[verticesAtEndsOfEdges[currentEdge * 2]];
					CUBE_GRID_VERTEX * v2 = cubes[i].vertices[verticesAtEndsOfEdges[currentEdge * 2 + 1]];

					float delta = (threshold - v1->value) / (v2->value - v1->value);
					//edgeVertices[currentEdge].position=v1->position + delta*(v2->position - v1->position);
					edgeVertices[currentEdge].position[0] = v1->position[0] + delta*(v2->position[0] - v1->position[0]);
					edgeVertices[currentEdge].position[1] = v1->position[1] + delta*(v2->position[1] - v1->position[1]);
					edgeVertices[currentEdge].position[2] = v1->position[2] + delta*(v2->position[2] - v1->position[2]);
					//edgeVertices[currentEdge].normal=v1->normal + delta*(v2->normal - v1->normal);
					edgeVertices[currentEdge].normal[0] = v1->normal[0] + delta*(v2->normal[0] - v1->normal[0]);
					edgeVertices[currentEdge].normal[1] = v1->normal[1] + delta*(v2->normal[1] - v1->normal[1]);
					edgeVertices[currentEdge].normal[2] = v1->normal[2] + delta*(v2->normal[2] - v1->normal[2]);
				}
			}

			//send the vertices
			for (int k = 0; triTable[cubeIndex][k] != -1; k += 3)
			{
				glNormal3fv(edgeVertices[triTable[cubeIndex][k + 0]].normal.getPointer());
				glVertex3fv(edgeVertices[triTable[cubeIndex][k + 0]].position.getPointer());

				glNormal3fv(edgeVertices[triTable[cubeIndex][k + 2]].normal.getPointer());
				glVertex3fv(edgeVertices[triTable[cubeIndex][k + 2]].position.getPointer());

				glNormal3fv(edgeVertices[triTable[cubeIndex][k + 1]].normal.getPointer());
				glVertex3fv(edgeVertices[triTable[cubeIndex][k + 1]].position.getPointer());

				numFacesDrawn++;
			}
		}
	}
	glEnd();
}

void CUBE_GRID::FreeMemory()
{
	if (vertices)
		delete[] vertices;
	vertices = NULL;
	numVertices = 0;

	if (cubes)
		delete[] cubes;
	cubes = NULL;
	numCubes = 0;
}