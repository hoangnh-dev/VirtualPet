#include "pet_manager.h"
#include "eeprom.h"
#include "app_eeprom.h"

#define PET_EEPROM_MAGIC_NUMBER    (0x5A5A5A5A)
#define EEPROM_PET_SAVE_ADDR       (EEPROM_START_ADDR)
#define PET_SAVE_CHECKSUM_SIZE     (sizeof(uint32_t) + sizeof(pet_profile_t) + sizeof(pet_save_t))

static uint8_t pet_eeprom_checksum(uint8_t *data, uint32_t size) {
    uint8_t check_sum = 0;

    for (uint32_t i = 0; i < size; i++) {
        check_sum += data[i];
    }

    return check_sum;
}

void pet_eeprom_update_checksum(uint32_t *magic_number, uint8_t *check_sum, uint32_t check_sum_size) {
    *magic_number = PET_EEPROM_MAGIC_NUMBER;
    *check_sum    = pet_eeprom_checksum((uint8_t *)magic_number, check_sum_size);
}

bool pet_eeprom_is_valid(uint32_t *magic_number, uint8_t check_sum, uint32_t check_sum_size) {
    return (*magic_number == PET_EEPROM_MAGIC_NUMBER) && 
           (check_sum == pet_eeprom_checksum((uint8_t *)magic_number, check_sum_size));
}

bool pet_manager_save_game() {
    vp_game_eeprom_t packet;
    packet.data_profile = profile;
    packet.data_pet.type = pet.type;
    packet.data_pet.satiety = pet.satiety;
    packet.data_pet.health = pet.health;
    packet.data_pet.poop = pet.poop;
    packet.data_pet.time = pet.time;

    pet_eeprom_update_checksum(&packet.magic_number, &packet.check_sum, PET_SAVE_CHECKSUM_SIZE);
    return eeprom_write(EEPROM_PET_SAVE_ADDR, (uint8_t *)&packet, sizeof(packet)) == EEPROM_DRIVER_OK;
}

bool pet_manager_load_game() {
    vp_game_eeprom_t packet;

    if (eeprom_read(EEPROM_PET_SAVE_ADDR, (uint8_t *)&packet, sizeof(packet)) != EEPROM_DRIVER_OK) {
        return false;
    }

    if (!pet_eeprom_is_valid(&packet.magic_number, packet.check_sum, PET_SAVE_CHECKSUM_SIZE)) {
        return false;
    }

    profile = packet.data_profile;
    pet.type = packet.data_pet.type;
    pet.satiety = packet.data_pet.satiety;
    pet.health = packet.data_pet.health;
    pet.poop  = packet.data_pet.poop;
    pet.time = packet.data_pet.time;
    is_setup = true;
    return true;
}