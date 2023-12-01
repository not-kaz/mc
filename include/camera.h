#ifndef CAMERA_H
#define CAMERA_H

#include "types.h"

#include <cglm/types.h>

struct camera *camera_create(void);
void camera_destroy(struct camera *cam);
void camera_update(struct camera *cam);
void camera_calc_view_matrix(struct camera *cam, float view_out[4][4]);
void camera_get_position(struct camera *cam, vec2 pos_out);

#endif
