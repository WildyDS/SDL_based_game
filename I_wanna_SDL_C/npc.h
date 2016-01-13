//
//  npc.h
//  I_wanna_SDL_C
//
//  Created by Александр on 04.09.14.
//  Copyright (c) 2014 NARO. All rights reserved.
//

#ifndef I_wanna_SDL_C_npc_h
#define I_wanna_SDL_C_npc_h

#include "SDL2/SDL.h"
#include "SDL2/SDL_main.h"

int create_npc_array(int count);

typedef struct {
    SDL_Rect rect;  //прямоугольник, в котором текстура персонажа и его координаты на экране
    int map_up_left;     //"координата" левого верхнего угла на карте
    int map_up_right;
    int map_dn_left;
    int map_dn_right;
    double coord_x; //координаты x
    double coord_y; //и y
    double v_x;     //скорость по x
    double v_y;     //скорость по y
    double dx;      //изменение скорости по x
    double dy;      //изменение скорости по y
    char direction; //направление (куда персонаж смотрит: 1 == вправо, 2 == влево)
} npc;


#endif
