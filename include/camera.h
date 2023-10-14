#ifndef CAMERA_H
#define CAMERA_H

#include "types.h"

struct camera *camera_create(void);
void camera_destroy(struct camera *cam);
void camera_update(struct camera *cam, const uint8_t *keypress);
void camera_calc_view_matrix(struct camera *cam, float view_out[4][4]);

#endif
