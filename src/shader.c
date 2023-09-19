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
	const char *src;
	char msg[MSG_MAX_LEN];

	src = str_read_file(fp);
	if (!src) {
		DIE("Failed to read shader source file. '%s'", fp);
	}
	sh = glCreateShader(type);
	glShaderSource(sh, 1, &src, NULL);
	glCompileShader(sh);
	free((char *)(src)); // HACK: Casting to allow freeing a const variable.
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

void shader_set_mat4f(unsigned int sh, const char *name, const float *val)
{
	int loc;

	loc = glGetUniformLocation(sh, name);
	glad_glUniformMatrix4fv(loc, 1, GL_FALSE, val);
}
