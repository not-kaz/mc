#ifndef CUBE_H
#define CUBE_H

// TODO: Fix these incorrect vertices, not correctly assigned.
float cube_vertices[] = {
	// front
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f, 0.0f, -0.5f,
	// back
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f, 0.0f, -0.5f,
	//left
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f, 0.0f, -0.5f,
	//right
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f, 0.0f, -0.5f,
	//top
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f, 0.0f, -0.5f,
	//bottom
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f, 0.0f, -0.5f
};

unsigned int cube_elements[] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// back
	4, 5, 6,
	6, 7, 4,
	// left
	8, 9, 10,
	10, 11, 8,
	// right
	12, 13, 14,
	14, 15, 12,
	// top
	16, 17, 18,
	18, 19, 16,
	// bottom
	20, 21, 22,
	22, 23, 20
};

#endif
