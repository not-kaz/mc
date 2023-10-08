#include "camera.h"

#include <math.h>

#include <cglm/cglm.h>

#define GLM_X 0
#define GLM_Y 1
#define GLM_Z 2
#define INITAL_YAW -90.0f
#define INITAL_PITCH 0.0f
#define DEFAULT_MOVE_SPEED 2.5f
#define DEFAULT_SENS 0.1f

enum 	 {
	COORD_X = 0,
	COORD_Y = 1,
	COORD_Z = 2
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

void camera_init(struct camera *cam)
{
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
}

void camera_update(struct camera *cam)
{
	cam->pos[COORD_Z] += 0.01f;
	// If we don't constrain the yaw to only use values between 0-360
	// we would lose floating precission with very high values, hence
	// the movement would look like big "steps" instead a smooth one!
	// Yaw = std::fmod((Yaw + xoffset), (GLfloat)360.0f);
}

void camera_calc_view_matrix(struct camera *cam, mat4 view_out)
{
	vec3 center;

	glm_vec3_add(cam->pos, cam->front, center);
	glm_lookat(cam->pos, center, cam->up, view_out);
}
