#include "pet.h"

#define EGG_HATCH_TIME (8)

pet_t pet;

void pet_setup(){
    pet.type = PET_TYPE_EGG;
    pet.x = Egg_X;
    pet.y = Egg_Y;
    pet.w = Egg_W;
    pet.h = Egg_H;
    pet.bitmap = bitmap_egg_1;
    pet.animation_check = 0;
    pet.action = PET_ACTION_NONE; 
}
void pet_update_bitmap(){
    switch (pet.type) {
        case PET_TYPE_EGG:
            if(pet.animation_check){
                pet.bitmap = bitmap_egg_1;
            }else {
                pet.bitmap = bitmap_egg_2;
            }
        break;
        default:
            if(pet.animation_check){
                pet.bitmap = bitmap_child_1;
            }else {
                pet.bitmap = bitmap_child_2;
            }
        break;
    }
}
void pet_animation_update(){
    pet.animation_check = !pet.animation_check;
    pet_update_bitmap();
}

void pet_evolve(){
    if (pet.type >= PET_TYPE_ADULT) return;
    
    pet.type = static_cast<pet_type_t>(pet.type + 1);;
    pet.action = PET_ACTION_NONE;
    pet.animation_check = 0;
    pet.x = Egg_X;
    pet.w = Egg_W;
    pet_update_bitmap();
}

void pet_update()
{
    switch (pet.action) {
        case PET_ACTION_NONE: 
            pet_animation_update();
        break;
        case PET_ACTION_HATCH: 
            pet.x = Egg_MAX_X;
            pet.w = Egg_MAX_W;
            pet.bitmap = bitmap_egg_3;
            pet.action = PET_ACTION_TRAN;
        break;
        case PET_ACTION_TRAN:
            pet_evolve();
        break;
        default:
        break;
    }
    
}
void pet_time(){
    pet.lifetime ++;
    if(pet.type == PET_TYPE_EGG && pet.lifetime >= EGG_HATCH_TIME){
        pet.action = PET_ACTION_HATCH;
    }
}
