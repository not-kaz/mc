#ifndef CUBE_H
#define CUBE_H

#define CUBE_NUM_COMPS_PER_VERT 5
#define CUBE_NUM_VERTS_PER_FACE 4
#define CUBE_NUM_COMPS_PER_FACE (CUBE_NUM_COMPS_PER_VERT * CUBE_NUM_VERTS_PER_FACE)

enum cube_face {
	CUBE_FACE_FRONT = 0,
	CUBE_FACE_BACK,
	CUBE_FACE_LEFT,
	CUBE_FACE_RIGHT,
	CUBE_FACE_TOP,
	CUBE_FACE_BOTTOM,
	NUM_CUBE_FACES
};

// TODO: Fix these incorrect vertices, not correctly assigned.
float cube_vertices[] = {
	// front
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	// back
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	//left
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
	//right
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	//top
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	//bottom
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f
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
