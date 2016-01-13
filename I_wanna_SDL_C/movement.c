//
//  movement.c
//  I_wanna_SDL_C
//
//  Created by Александр on 21.10.14.
//  Copyright (c) 2014 NARO. All rights reserved.
//

#include "movement.h"

/*
if (k_lt){
    hero.direction = 2;
    if (hero.coord_x>0){
        if (blocks_back_map[hero.map_up_left].type != bt_wall && blocks_back_map[hero.map_dn_left].type != bt_wall && (blocks_back_map[find_map_coord(hero.coord_x, hero.coord_y+BRICK_INT_SIZE_ON_BOARD-1)].type != bt_wall)){
            if (dx>-2){
                dx-=MOVE_SPEED_ON_BOARD;
            }
            if (dx<0) {
                go_x+=dx;
                if (go_x < -1){
                    hero.coord_x+=go_x;
                    //go_x=0;
                }
            }
            hero.map_up_left=find_map_coord(hero.coord_x, hero.coord_y);
            hero.map_dn_left=find_map_coord(hero.coord_x, hero.coord_y+HERO_SIZE_ON_BOARD-1);
            while (blocks_back_map[hero.map_up_left].type == bt_wall || blocks_back_map[hero.map_dn_left].type == bt_wall || (blocks_back_map[find_map_coord(hero.coord_x, hero.coord_y+BRICK_INT_SIZE_ON_BOARD-1)].type == bt_wall)){
                hero.coord_x++;
                hero.map_up_left=find_map_coord(hero.coord_x, hero.coord_y);
                hero.map_dn_left=find_map_coord(hero.coord_x, hero.coord_y+HERO_SIZE_ON_BOARD-1);
            }
            go_x=0;
        }
        
    }
    else{
        hero.coord_x+=(WIDTH_ON_BOARD-HERO_SIZE_ON_BOARD);
        current_screen = 0;
        switch_screen=1;
    }
}
*/
