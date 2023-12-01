#include "camera.h"

#include "common.h"
#include "input.h"
#include "log.h"

#include <math.h>
#include <stdlib.h>

#include <SDL2/SDL_scancode.h>
#include <cglm/cglm.h>

#define INITAL_YAW -90.0f
#define INITAL_PITCH 0.0f
#define DEFAULT_MOVE_SPEED 0.2f
#define DEFAULT_SENS 0.1f

enum coord_subscript {
	COORD_X = 0,
	COORD_Y = 1,
	COORD_Z = 2
};

struct camera {
	vec3 pos;
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 world_up;
	mat4 view;
	float yaw;
	float pitch;
	float move_speed;
	float sens;
};

static void update_cam_vectors(struct camera *cam)
{
	cam->front[COORD_X] = cosf(glm_rad(cam->yaw))
		* cosf(glm_rad(cam->pitch));
	cam->front[COORD_Y] = sinf(glm_rad(cam->pitch));
	cam->front[COORD_Z] = sinf(glm_rad(cam->yaw))
		* cosf(glm_rad(cam->pitch));
	glm_vec3_normalize(cam->front);
	glm_vec3_crossn(cam->front, cam->world_up, cam->right);
	glm_vec3_crossn(cam->right, cam->front, cam->up);
}

static void handle_rotation(struct camera *cam)
{
	int32_t mx, my;

	input_get_relative_mouse_position(&mx, &my);
	cam->yaw = fmodf((cam->yaw + ((float)(mx) * DEFAULT_SENS)), 360.0f);
	cam->pitch -= ((float)(my) * DEFAULT_SENS);
        if (cam->pitch > 89.0f) {
		cam->pitch = 89.0f;
        }
        if (cam->pitch < -89.0f) {
                cam->pitch = -89.0f;
        }
	// cam->pitch = fminf(cam->pitch, fmax(89.0f, -89.0f));
	update_cam_vectors(cam);
}

static void handle_movement(struct camera *cam)
{
	vec3 tmp;

	if (input_is_keybind_pressed(KEYBIND_LEFT)) {
		glm_vec3_scale(cam->right, DEFAULT_MOVE_SPEED, tmp);
		glm_vec3_sub(cam->pos, tmp, cam->pos);
	}
	if (input_is_keybind_pressed(KEYBIND_RIGHT)) {
		glm_vec3_scale(cam->right, DEFAULT_MOVE_SPEED, tmp);
		glm_vec3_add(cam->pos, tmp, cam->pos);
	}
	if (input_is_keybind_pressed(KEYBIND_FORWARD)) {
		glm_vec3_scale(cam->front, DEFAULT_MOVE_SPEED, tmp);
		glm_vec3_add(cam->pos, tmp, cam->pos);
	}
	if (input_is_keybind_pressed(KEYBIND_BACKWARD)) {
		glm_vec3_scale(cam->front, DEFAULT_MOVE_SPEED, tmp);
		glm_vec3_sub(cam->pos, tmp, cam->pos);
	}
	if (input_is_keybind_pressed(KEYBIND_JUMP)) {
		glm_vec3_scale(cam->world_up, DEFAULT_MOVE_SPEED, tmp);
		glm_vec3_add(cam->pos, tmp, cam->pos);
	}
	if (input_is_keybind_pressed(KEYBIND_CROUCH)) {
		glm_vec3_scale(cam->world_up, DEFAULT_MOVE_SPEED, tmp);
		glm_vec3_sub(cam->pos, tmp, cam->pos);
	}
}

struct camera *camera_create(void)
{
	struct camera *cam;

	cam = malloc(sizeof(struct camera));
	if (!cam) {
		return NULL;
	}
	cam->pos[COORD_X] = 0.0f;
	cam->pos[COORD_Y] = 0.0f;
	cam->pos[COORD_Z] = 0.0f;
	cam->front[COORD_X] = 0.0f;
	cam->front[COORD_Y] = 0.0f;
	cam->front[COORD_Z] = 0.0f;
	cam->up[COORD_X] = 0.0f;
	cam->up[COORD_Y] = 1.0f;
	cam->up[COORD_Z] = 0.0f;
	cam->world_up[COORD_X] = 0.0f;
	cam->world_up[COORD_Y] = 1.0f;
	cam->world_up[COORD_Z] = 0.0f;
	cam->yaw = INITAL_YAW;
	cam->pitch = INITAL_PITCH;
	cam->move_speed = DEFAULT_MOVE_SPEED;
	cam->sens = DEFAULT_SENS;
	update_cam_vectors(cam);
	return cam;
}

void camera_destroy(struct camera *cam)
{
	free(cam);
}

// FIXME: Add delta-time arg variable to decouple movement from frame-rate.
void camera_update(struct camera *cam)
{
	if (!cam) {
		return;
	}
	handle_rotation(cam);
	handle_movement(cam);
}

void camera_calc_view_matrix(struct camera *cam, float view_out[4][4])
{
	vec3 center;

	if (!cam) {
		return;
	}
	glm_vec3_add(cam->pos, cam->front, center);
	glm_lookat(cam->pos, center, cam->up, view_out);
}

void camera_get_position(struct camera *cam, vec2 pos_out)
{
	pos_out[0] = cam->pos[0];
	pos_out[1] = cam->pos[2];
}
