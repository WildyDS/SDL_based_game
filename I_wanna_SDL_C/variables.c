//
//  variables.c
//  I_wanna_SDL_C
//
//  Created by Александр on 01.10.14.
//  Copyright (c) 2014 NARO. All rights reserved.
//

#include "variables.h"

double    JUMP_POWA_ON_BOARD = HEIGHT_ON_BOARD*0.01;
double GRAVITY_POWA_ON_BOARD = HEIGHT_ON_BOARD*0.02/3;
double   MOVE_SPEED_ON_BOARD = HEIGHT_ON_BOARD*0.01/6;


int      HERO_SIZE_ON_BOARD = 2*HEIGHT_ON_BOARD/map_h;
int BRICK_INT_SIZE_ON_BOARD = HEIGHT_ON_BOARD/map_h;
int  BRICK_SIZE_ON_BOARD = HEIGHT_ON_BOARD/map_h;

int      HERO_SIZE_ON_SCREEN= 2*WINDOW_HEIGHT/map_h;
int BRICK_INT_SIZE_ON_SCREEN = WINDOW_HEIGHT/map_h;
int  BRICK_SIZE_ON_SCREEN = WINDOW_HEIGHT/map_h;