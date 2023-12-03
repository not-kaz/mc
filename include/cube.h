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
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f, 0.0f, -0.5f,
	//left
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	//right
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, 0.5f, 0.0f, -0.5f,
	//top
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f, 0.0f, -0.5f,
	//bottom
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f, 0.0f, -0.5f
};

unsigned int cube_elements[] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// back
	6, 5, 4,
	4, 7, 6,
	// left
	10, 9, 8,
	8, 11, 10,
	// right
	12, 13, 14,
	14, 15, 12,
	// top
	16, 17, 18,
	18, 19, 16,
	// bottom
	22, 21, 20,
	20, 23, 22
};

#endif
