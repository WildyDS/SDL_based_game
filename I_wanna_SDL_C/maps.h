//
//  maps.h
//  I_wanna_SDL_C
//
//  Created by Александр on 29.09.14.
//  Copyright (c) 2014 NARO. All rights reserved.
//

#ifndef __I_wanna_SDL_C__maps__
#define __I_wanna_SDL_C__maps__

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_main.h" 

int find_map_coord(int, int);

typedef enum{
    bt_empty,
    bt_wall,
    bt_water,
    bt_hero
}block_type;

typedef struct {
    SDL_Rect rect;
    block_type type;
    int map_id;
} brick_info;

extern const char *back_map;
extern const char *back_map2;

#endif /* defined(__I_wanna_SDL_C__maps__) */
