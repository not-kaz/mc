#ifndef CUBE_H
#define CUBE_H

#define CUBE_NUM_COMPS_PER_VERT 5
#define CUBE_NUM_VERTS_PER_FACE 4
#define CUBE_NUM_COMPS_PER_FACE (CUBE_NUM_COMPS_PER_VERT * CUBE_NUM_VERTS_PER_FACE)

float cube_vertices[] = {
	// front
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
	// back
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
	//left
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
	//right
	0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	//top
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	//bottom
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f
};

unsigned int cube_indices[] = {
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
