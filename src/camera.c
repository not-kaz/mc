#include "camera.h"

#include "input.h"

#include <math.h>
#include <stdlib.h>

#include <SDL2/SDL_scancode.h>
#include <cglm/cglm.h>

#define INITAL_YAW -90.0f
#define INITAL_PITCH 0.0f
#define DEFAULT_MOVE_SPEED 0.01f
#define DEFAULT_SENS 0.1f

enum COORD_SUBSCRIPT {
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

struct camera *camera_create(void)
{
	struct camera *cam;

	cam = malloc(sizeof(struct camera));
	if (!cam) {
		return NULL;
	}
	cam->pos[COORD_X] = 0.0f;
	cam->pos[COORD_Y] = 0.0f;
	cam->pos[COORD_Z] = 5.0f;
	cam->front[COORD_X] = 0.0f;
	cam->front[COORD_Y] = 0.0f;
	cam->front[COORD_Z] = -1.0f;
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

// HACKME: I do not like how we pass key states into camera to handle move here.
// FIXME: Add delta-time arg variable to decouple movement from frame-rate.
void camera_update(struct camera *cam, const uint8_t *key_states)
{
	if (key_states[SDL_SCANCODE_A]) {
		cam->pos[COORD_X] -= cam->move_speed;\
	}
	if (key_states[SDL_SCANCODE_D]) {
		cam->pos[COORD_X] += cam->move_speed;
	}
	if (key_states[SDL_SCANCODE_W]) {
		cam->pos[COORD_Z] -= cam->move_speed;
	}
	if (key_states[SDL_SCANCODE_S]) {
		cam->pos[COORD_Z] += cam->move_speed;
	}
	if (key_states[SDL_SCANCODE_SPACE]) {
		cam->pos[COORD_Y] += cam->move_speed;
	}
	if (key_states[SDL_SCANCODE_LCTRL]) {
		cam->pos[COORD_Y] -= cam->move_speed;
	}
	// If we don't constrain the yaw to only use values between 0-360
	// we would lose floating precission with very high values, hence
	// the movement would look like big "steps" instead a smooth one!
	// Yaw = std::fmod((Yaw + xoffset), (GLfloat)360.0f);
}

void camera_calc_view_matrix(struct camera *cam, float view_out[4][4])
{
	vec3 center;

	glm_vec3_add(cam->pos, cam->front, center);
	glm_lookat(cam->pos, center, cam->up, view_out);
}
