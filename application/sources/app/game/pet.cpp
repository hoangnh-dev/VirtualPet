#include "pet.h"




egg_state_t egg_state;
pet_t pet;
void pet_setup(){
    pet.type = PET_TYPE_EGG;
    pet.x = Pet_X;
    pet.y = Egg_MAX_Y;
    pet.w = Pet_W;
    pet.h = Egg_Max_H;
    egg_state = EGG_STATE_IDLE;
    pet.bitmap = bitmap_egg;
}
void pet_update_egg(){
    switch (egg_state) {
        case EGG_STATE_BOUNCE:
        pet.y = Egg_MAX_Y;
        pet.h = Egg_Max_H; 
        pet.bitmap = bitmap_egg;
        egg_state = EGG_STATE_IDLE;
        break;
        case EGG_STATE_IDLE: 
        pet.y = Egg_Y;
        pet.h = Egg_H;
        pet.bitmap = bitmap_egg_2;
        egg_state = EGG_STATE_BOUNCE;
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

