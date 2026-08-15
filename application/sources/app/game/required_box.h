#ifndef REQUIRED_BOX_H
#define REQUIRED_BOX_H

#include <stdbool.h>
#include <stdint.h>
#include "common.h"
#include "screens_bitmap.h"
#include "screens_bitmap.h"

extern required_box_t box;

void box_update(void);
void box_check_time(void);
#endif