CFLAGS		+= -I./sources/app/game
CPPFLAGS	+= -I./sources/app/game
CFLAGS		+= -I./sources/app/game/pet
CPPFLAGS	+= -I./sources/app/game/pet
CFLAGS		+= -I./sources/app/game/home_action
CPPFLAGS	+= -I./sources/app/game/home_action
CFLAGS		+= -I./sources/app/game/training_action
CPPFLAGS	+= -I./sources/app/game/training_action


VPATH += sources/app/game
VPATH += sources/app/game/pet
VPATH += sources/app/game/home_action
VPATH += sources/app/game/training_action

# CPP source files
SOURCES_CPP += sources/app/game/pet/pet.cpp
SOURCES_CPP += sources/app/game/pet/pet_frames.cpp
SOURCES_CPP += sources/app/game/pet/pet_profile.cpp
SOURCES_CPP += sources/app/game/pet/pet_manager.cpp
SOURCES_CPP += sources/app/game/home_action/food.cpp
SOURCES_CPP += sources/app/game/home_action/poop.cpp
SOURCES_CPP += sources/app/game/home_action/clean.cpp
SOURCES_CPP += sources/app/game/training_action/required_box.cpp
SOURCES_CPP += sources/app/game/training_action/fire_ball.cpp
