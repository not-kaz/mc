#include "shader.h"

#include "log.h"
#include "str.h"

#include <stdlib.h>

#include <glad/gl.h>

#define MSG_MAX_LEN 1024

/* TODO: Change shader code to work as a hash map containing all shaders.  *
 *  	 Assign names to shaders and use those to access them when needed. */

/* TODO: Implement missing error handling in compile_shader(). */

static unsigned int compile_shader(const char *fp, GLenum type)
{
	int res;
	unsigned int sh;
	char *src;
	const char *tmp[1]; // Required for glShaderSource().
	char msg[MSG_MAX_LEN];

	src = str_read_file(fp);
	if (!src) {
		DIE("Failed to read shader source file. '%s'", fp);
	}
	tmp[0] = src;
	sh = glCreateShader(type);
	glShaderSource(sh, 1, tmp, NULL);
	glCompileShader(sh);
	free(src);
	glGetShaderiv(sh, GL_COMPILE_STATUS, &res);
	if (!res) {
		glGetShaderInfoLog(sh, MSG_MAX_LEN, NULL, msg);
		DIE("Shader compliation failed: %s", msg);
	}
	return sh;
}

unsigned int shader_build(const char *vsrc, const char *fsrc)
{
	unsigned int sp, vs, fs;
	int res;
	char msg[MSG_MAX_LEN];

	sp = glCreateProgram();
	vs = compile_shader(vsrc, GL_VERTEX_SHADER);
	fs = compile_shader(fsrc, GL_FRAGMENT_SHADER);
	// REVIEW: What does attaching and linking shaders actually do?
	glAttachShader(sp, vs);
	glAttachShader(sp, fs);
	glLinkProgram(sp);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glGetProgramiv(sp, GL_LINK_STATUS, &res);
	if (!res) {
		glGetProgramInfoLog(sp, MSG_MAX_LEN, NULL, msg);
		DIE("Shader linking failed: %s", msg);
	}
	return sp;
}

void shader_use(unsigned int sh)
{
	glUseProgram(sh);
}

void shader_set_uniform(unsigned int sh, const char *name, const float *val,
		enum shader_uniform_type type)
{
	int loc;

	loc = glGetUniformLocation(sh, name);
	switch (type) {
	case SHADER_UNIFORM_TYPE_MAT4:
		glUniformMatrix4fv(loc, 1, GL_FALSE, val);
		break;
	case SHADER_UNIFORM_TYPE_VEC4:
		glUniform4fv(loc, 1, val);
		break;
	case SHADER_UNIFORM_TYPE_VEC2:
		glUniform2fv(loc, 1, val);
		break;
	default:
		break;
	}
}
