#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/types.h>

struct camera {
	vec3 pos;
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 world_up;
	float yaw;
	float pitch;
	float move_speed;
	float sens;
};

void camera_init(struct camera *cam);
void camera_update(struct camera *cam);
void camera_calc_view_matrix(struct camera *cam, mat4 view_out);

#endif
