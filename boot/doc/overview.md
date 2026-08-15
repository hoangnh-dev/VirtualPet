<hr>
<h1 align="center">VirtualPet System Overview</h1>
<hr>

Welcome to the VirtualPet documentation! This document provides an overview of all screens and software modules.
---

## 1. Screens
- **Splash Screen:** Show logo and load database (if any)
- **Naming Screen:** Set name
- **Home Screen:** 80% of the game takes place here (poop, food, sleep, clean)
- **Menu Screen:** Select action (eating, sleeping, cleaning, training). Also the place to save game
- **Training Screen:** Like a mini-game where you can play and power up your pet
- **Status Screen:** Place where you can see your pet's info
## 2. Game/pet - All things for pet
- **pet:** Contain pet status info (like hunger, health, emotions)
- **pet frames:** Contain sprite frames of the pet
- **pet profile:** Contain pet profile info
- **pet manager:** Aggregate info from pet and pet profile to save into EEPROM
## 3. Game/home action - All actions will show in home screen
- **food:** show food when pet eats
- **poop:** show poop
- **clean:** show cleaning animation when pet poops
## 4. Game/train action - All actions will show in train screen
- **fire ball:** show animation for pet attack (UI only)
- **required box:** main gameplay of train screen

## Other: files like common or config that store data types, frames and shared libraries
