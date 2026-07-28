#include "pet_frames.h"
#include "pet_config.h"
#include "screens_bitmap.h"

const pet_frame_t egg_frames[2] = {
    { EGG_X, EGG_Y, EGG_W, EGG_MAX_H, bitmap_egg_1 },
    { EGG_X, EGG_MAX_Y, EGG_W, EGG_H, bitmap_egg_2 },
};
const pet_frame_t egg_hatch_frame = {
    EGG_MAX_X, EGG_Y, EGG_MAX_W, 54, bitmap_egg_3
};
const pet_frame_t child_frames[2] = {
    { Child_X, Child_Y, Child_W, Child_H, bitmap_child_1 },
    { Child_X, Child_MAX_Y, Child_W, Child_MIN_H, bitmap_child_2 },
};
const pet_frame_t child_eat_frames[2] = {
    { Child_X, Child_Y, Child_W, Child_H, bitmap_child_eat_1},
    { Child_X, Child_MIN_Y, Child_W, Child_MAX_H, bitmap_child_eat_2},
};
const pet_frame_t child_dislike_frames[2] = {
    { Child_X, Child_Y, Child_W, Child_H, bitmap_child_dislike_1 },
    { Child_X, Child_Y, Child_W, Child_H, bitmap_child_dislike_2 },
};
const pet_frame_t child_happy_frames[2] = {
    { Child_X, Child_Y, Child_W, Child_H, bitmap_child_1 },
    { Child_X, Child_Y, Child_W, Child_H, bitmap_child_happy_1 },
};
