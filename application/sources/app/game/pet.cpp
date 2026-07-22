#include "pet.h"

#define EGG_HATCH_TIME (8)

egg_state_t egg_state;
pet_t pet;

void pet_setup(){
    pet.type = PET_TYPE_EGG;
    pet.x = Egg_X;
    pet.y = Egg_Y;
    pet.w = Egg_W;
    pet.h = Egg_H;
    egg_state = EGG_STATE_IDLE;
    pet.bitmap = bitmap_egg_1;
}
void pet_update_egg(){
    pet.x = Egg_X;
    pet.w = Egg_W;
    switch (egg_state) {
        case EGG_STATE_BOUNCE:
        pet.bitmap = bitmap_egg_2;
        egg_state = EGG_STATE_IDLE;
        break;
        case EGG_STATE_IDLE: 
        pet.bitmap = bitmap_egg_1;
        egg_state = EGG_STATE_BOUNCE;
        break;
        case EGG_STATE_HATCH: 
        pet.x = Egg_MAX_X;
        pet.w = Egg_MAX_W;
        pet.bitmap = bitmap_egg_3;
        break;
        default:
        break;
    }
}

void pet_update()
{
    switch (pet.type) {
        case PET_TYPE_EGG: 
        pet_update_egg();
        break;
        default:
        break;
    }
    
}
void pet_time(){
    pet.lifetime ++;
    if(pet.type != EGG_STATE_HATCH && pet.lifetime >= EGG_HATCH_TIME){
        egg_state = EGG_STATE_HATCH;
    }
}

