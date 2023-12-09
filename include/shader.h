#ifndef SHADER_H
#define SHADER_H

enum shader_uniform_type {
	SHADER_UNIFORM_TYPE_MAT4 = 0,
	SHADER_UNIFORM_TYPE_VEC4,
	SHADER_UNIFORM_TYPE_VEC3,
	SHADER_UNIFORM_TYPE_VEC2,
	SHADER_UNIFORM_TYPE_IVEC2,
	NUM_SHADER_UNIFORM_TYPES
};

unsigned int shader_build(const char *vsrc, const char *fsrc);
void shader_use(unsigned int sh);
void shader_set_uniform(unsigned int sh, const char *name, const void *val,
		enum shader_uniform_type type);

#endif
