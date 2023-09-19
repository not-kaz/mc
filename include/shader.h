#ifndef SHADER_H
#define SHADER_H

unsigned int shader_build(const char *vsrc, const char *fsrc);
void shader_use(unsigned int sh);
void shader_set_mat4f(unsigned int sh, const char *name, const float *val);

#endif

