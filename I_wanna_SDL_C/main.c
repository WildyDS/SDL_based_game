//
//  main.c
//  I_wanna_SDL_C
//
//  Created by Александр on 31.10.13.
//  Copyright (c) 2013 NARO. All rights reserved.
//

//#include "main.h"
#include "time.h"
#include "heroes.h"
#include "maps.h"
#include "physics.h"
#include "variables.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

int find_map_coord (int, int);

int current_screen = 0;

int main(int argc, const char * argv[]){
    
    int FPS;
    int frame_cap = 1;
    Uint32 start_clock;
    Uint32 delta_clock;
    
    start_clock = SDL_GetTicks();

    
    int jump = 200;
    int on_floor = 0;
    int switch_screen = 0;
    int quit = 0;
    
    character hero;
    {
        hero.coord_x =  WIDTH_ON_BOARD / 2 - HERO_SIZE_ON_BOARD / 2;
        hero.coord_y = HEIGHT_ON_BOARD / 2 - HERO_SIZE_ON_BOARD / 2;
        hero.rect.w = HERO_SIZE_ON_SCREEN;
        hero.rect.h = HERO_SIZE_ON_SCREEN;
      
    }
    
    //для определения столкновений
    /*
    int m = 1;

    double shape_size_part = SHAPE_INT_SIZE;
    if (SHAPE_INT_SIZE>BRICK_INT_SIZE){
        m = SHAPE_INT_SIZE/BRICK_INT_SIZE;
        shape_size_part = SHAPE_INT_SIZE/m;
    }
    */

    SDL_Window *window = NULL;
    SDL_Renderer *MainRenderer = NULL;
    
    
    
    SDL_Texture **textures;
    textures=(SDL_Texture**)malloc(TEX_COUNT*sizeof(SDL_Texture*));
    
    //SDL_Texture *bulletTex;
    SDL_Texture *bgTex = NULL;
    SDL_Texture *spriteTex = NULL;
    SDL_Surface *bitmapSurface = NULL;
    
    SDL_Rect brick;
        brick.x = 0;
        brick.y = 0;
        brick.w = BRICK_INT_SIZE_ON_SCREEN;
        brick.h = BRICK_INT_SIZE_ON_SCREEN;
    

    
    //Изменения скорости и скорость в определенном направлении
    double dx = 0;
    double dy = 0;
    double go_x = 0;
    double go_y = 0;
    int k_up, k_dn, k_lt, k_rt, shootDir, shoot;
        k_up = 0; k_dn = 0; k_lt = 0; k_rt = 0;
    SDL_Init(SDL_INIT_VIDEO);
    
    // Create an application window with the following settings:
    window = SDL_CreateWindow(
                              "I am The Window. Press 'Esc' to exit.",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH,
                              WINDOW_HEIGHT,
                              0
                              );
    
    // Check that the window was successfully made
    if (window == NULL) {
        // In the event that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    // The window is open: enter program loop (see SDL_PollEvent)
    
    
    MainRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    const char *tex_names[]={
        NULL,
        "../../images/brick.bmp",
        "../../images/water.bmp"
    };
    
    textures[0]=NULL;
    for (int i=1; i<TEX_COUNT; i++) {
        //тексутра кирпичей
        bitmapSurface = SDL_LoadBMP(tex_names[i]); //Полный путь до текстуры фона
        if ( bitmapSurface == NULL){
            printf("SDL_LoadBMP failed: %s\n", SDL_GetError());
        }
        textures[i] = SDL_CreateTextureFromSurface(MainRenderer, bitmapSurface);
        SDL_FreeSurface(bitmapSurface);
    }

    bitmapSurface = SDL_LoadBMP("../../images/bg.bmp"); //Полный путь до текстуры фона
    if ( bitmapSurface== NULL){
        printf("SDL_LoadBMP failed: %s\n", SDL_GetError());
    }
     //Загружаю текстуру фона  в главный рендерер.
    bgTex = SDL_CreateTextureFromSurface(MainRenderer, bitmapSurface);
    SDL_FreeSurface(bitmapSurface);
    //Загружаю текстуру героя в главный рендерер. Будет здорово сделать функцию.
    //это игрок
    bitmapSurface = SDL_LoadBMP("../../images/blue_face.bmp"); //Полный путь до текстуры игрока
    if ( bitmapSurface== NULL){
        printf("SDL_LoadBMP failed: %s\n", SDL_GetError());
    }
    
    
    spriteTex = SDL_CreateTextureFromSurface(MainRenderer, bitmapSurface);
    
    //bulletTex = SDL_CreateTextureFromSurface(MainRenderer, bitmapSurface);
    
    SDL_FreeSurface(bitmapSurface);

    
    
do {
    //выделение памяти для указателей на элементы карту по-старому
    /*
     brick_info *blocks_back_map;
     blocks_back_map = (brick_info*)malloc(map_full_h*map_full_w*sizeof(brick_info));
     */
    //и по-новому
    
    brick_info *blocks_back_map = malloc(map_h*map_w*sizeof(*blocks_back_map));
    const char **maps_array = malloc(2*sizeof(back_map));
    maps_array[0] = back_map;
    maps_array[1] = back_map2;
    
//**************************************************************************
    //начало обновления состояния игры
    
    for (int i=0;i<map_h*map_w;i++){
        blocks_back_map[i].map_id=i;
        switch (maps_array[current_screen][i]) {
            case '*':
                blocks_back_map[i].type=bt_wall;
                break;
            case ' ':
                blocks_back_map[i].type=bt_empty;
                break;
            case '~':
                blocks_back_map[i].type=bt_water;
                break;
            case '!':
                blocks_back_map[i].type=bt_hero;
                break;
            default:
                break;
        }
        blocks_back_map[i].rect.x=(i%map_w)*(int)floor(BRICK_INT_SIZE_ON_SCREEN);
        blocks_back_map[i].rect.y=((i/map_w)%map_h)*(int)floor(BRICK_INT_SIZE_ON_SCREEN);
        blocks_back_map[i].rect.w=(int)floor(BRICK_INT_SIZE_ON_SCREEN);
        blocks_back_map[i].rect.h=(int)floor(BRICK_INT_SIZE_ON_SCREEN);
    }
    
    for (int i=0;i<map_h*map_w;i++)
        if (blocks_back_map[i].type==bt_hero){
            hero.coord_x=blocks_back_map[i].rect.x;
            hero.coord_y=blocks_back_map[i].rect.y;
        }
    
    
    while (!switch_screen)
    {
        hero.map_up_left=find_map_coord(hero.coord_x, hero.coord_y);
        hero.map_up_right=find_map_coord(hero.coord_x+HERO_SIZE_ON_BOARD-1, hero.coord_y);
        hero.map_dn_left=find_map_coord(hero.coord_x, hero.coord_y+HERO_SIZE_ON_BOARD-1);
        hero.map_dn_right=find_map_coord(hero.coord_x+HERO_SIZE_ON_BOARD-1, hero.coord_y+HERO_SIZE_ON_BOARD-1);
        
        
        
        //гравитация
        
        if (blocks_back_map[find_map_coord(hero.coord_x, hero.coord_y+HERO_SIZE_ON_BOARD)].type != bt_wall && blocks_back_map[find_map_coord(hero.coord_x+HERO_SIZE_ON_BOARD-1, hero.coord_y+HERO_SIZE_ON_BOARD)].type != bt_wall && (blocks_back_map[find_map_coord(hero.coord_x+BRICK_INT_SIZE_ON_BOARD-1, hero.coord_y+HERO_SIZE_ON_BOARD)].type != bt_wall))
            on_floor=0;
        
        /*
        if (blocks_back_map[hero.map_dn_left+ map_w].type == bt_wall )
            on_floor=1;
        */
        else
            on_floor=1;
        if (!on_floor){
            if (dy>=0)
                dy-=GRAVITY_POWA_ON_BOARD;
            
            go_y+=dy;
            if (go_y <= -1){
                //hero.coord_y++;
                hero.coord_y-=go_y; //переделать, может выкинуть нафиг
                go_y = 0;
            }
            
            hero.map_dn_left=find_map_coord(hero.coord_x, hero.coord_y);
            hero.map_dn_right=find_map_coord(hero.coord_x+HERO_SIZE_ON_BOARD-1, hero.coord_y);
            /*if ((blocks_back_map[hero.map_up_left].type == bt_wall) || (blocks_back_map[hero.map_up_right].type == bt_wall) || (blocks_back_map[find_map_coord(hero.coord_x+BRICK_SIZE-1, hero.coord_y+SHAPE_SIZE-1)].type == bt_wall)){
             hero.coord_y--;
             }*/
            while (blocks_back_map[find_map_coord(hero.coord_x, hero.coord_y+HERO_SIZE_ON_BOARD-1)].type == bt_wall && blocks_back_map[find_map_coord(hero.coord_x+HERO_SIZE_ON_BOARD-1, hero.coord_y+HERO_SIZE_ON_BOARD-1)].type == bt_wall && (blocks_back_map[find_map_coord(hero.coord_x+BRICK_INT_SIZE_ON_BOARD-1, hero.coord_y+HERO_SIZE_ON_BOARD-1)].type == bt_wall)){
                hero.coord_y--;
            }
            
            
            //}
            
            
        } else {
            on_floor = 1;
        }
        
        //конец гравитации
        
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // handle your event here
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                {
                    case SDLK_SPACE:
                        shoot = 1;
                        break;
                    case SDLK_ESCAPE:
                        switch_screen=1;
                        quit=1;
                        //goto quit;
                    case SDLK_UP:
                        k_up = 1;
                        shootDir = 1;
                        break;
                    case SDLK_DOWN:
                        k_dn = 1;
                        shootDir = 3;
                        break;
                    case SDLK_LEFT:
                        k_lt = 1;
                        shootDir = 4;
                        break;
                    case SDLK_RIGHT:
                        k_rt = 1;
                        shootDir = 2;
                        break;
                    default:
                        break;
                }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                {
                    case SDLK_SPACE:
                        shoot = 0;
                        break;
                    case SDLK_UP:
                        k_up = 0;
                        dy=0;
                        break;
                    case SDLK_DOWN:
                        k_dn = 0;
                        dy=0;
                        break;
                    case SDLK_LEFT:
                        k_lt = 0;
                        dx=0;
                        break;
                    case SDLK_RIGHT:
                        k_rt = 0;
                        dx=0;
                        break;
                    default:
                        break;
                }
                    break;
                default:
                    break;
            }
        }
        if (k_up){
            
            if (jump>0) {
                jump-=1.4*JUMP_POWA_ON_BOARD;
                on_floor=0;
                if ((blocks_back_map[hero.map_up_left].type != bt_wall) && (blocks_back_map[hero.map_up_right].type != bt_wall) && (blocks_back_map[find_map_coord(hero.coord_x+BRICK_INT_SIZE_ON_BOARD-1, hero.coord_y)].type != bt_wall)){
                    if (hero.coord_y>0){
                        
                        if (dy<0.2) {
                            dy+=JUMP_POWA_ON_BOARD;
                        }
                        
                        go_y+=dy;
                        if (go_y >= 1){
                            
                            hero.coord_y-=go_y;
                            hero.map_up_left=find_map_coord(hero.coord_x, hero.coord_y);
                            hero.map_up_right=find_map_coord(hero.coord_x+HERO_SIZE_ON_BOARD-1, hero.coord_y);
                            if ((blocks_back_map[hero.map_up_left].type == bt_wall) || (blocks_back_map[hero.map_up_right].type == bt_wall) || (blocks_back_map[find_map_coord(hero.coord_x+BRICK_INT_SIZE_ON_BOARD-1, hero.coord_y)].type == bt_wall)){
                                hero.coord_y+=go_y;
                            }
                            go_y = 0;
                        }
                    }
                }
            }
        } else {
            if (on_floor)
                jump = 40*JUMP_POWA_ON_BOARD;
        }
        
        if (k_dn){
            if (blocks_back_map[hero.map_dn_left].type != bt_wall && blocks_back_map[hero.map_dn_right].type != bt_wall){
                if (hero.coord_y<HEIGHT_ON_BOARD-HERO_SIZE_ON_BOARD){
                    if (dy>-2)
                        dy-=MOVE_SPEED_ON_BOARD;
                    
                    if (dy<0) {
                        go_y-=dy;
                        if (go_y <= -1){
                            hero.coord_y+=go_y;
                            go_y = 0;
                        }
                    }
                    
                    
                    hero.map_dn_left=find_map_coord(hero.coord_x, hero.coord_y+HERO_SIZE_ON_BOARD-1);
                    hero.map_dn_right=find_map_coord(hero.coord_x+HERO_SIZE_ON_BOARD-1, hero.coord_y+HERO_SIZE_ON_BOARD-1);
                    if (blocks_back_map[hero.map_dn_left].type == bt_wall || blocks_back_map[hero.map_dn_right].type == bt_wall)
                        hero.coord_y--;
                    
                    go_y = 0;
                }
            }
        }
        if (k_rt){
            hero.direction = 1;
            if (hero.coord_x+HERO_SIZE_ON_BOARD<WIDTH_ON_BOARD){
                if (blocks_back_map[hero.map_up_right].type != bt_wall && blocks_back_map[hero.map_dn_right].type != bt_wall && (blocks_back_map[find_map_coord(hero.coord_x+HERO_SIZE_ON_BOARD-1, hero.coord_y+BRICK_INT_SIZE_ON_BOARD-1)].type != bt_wall)){
                    if (dx<2)
                        dx+=MOVE_SPEED_ON_BOARD;
                    if (dx>0) {
                        go_x+=dx;
                        if (go_x > 1){
                            hero.coord_x+=go_x;
                            //go_x = 0;
                        }
                    }
                    hero.map_up_right=find_map_coord(hero.coord_x+HERO_SIZE_ON_BOARD-1, hero.coord_y);
                    hero.map_dn_right=find_map_coord(hero.coord_x+HERO_SIZE_ON_BOARD-1, hero.coord_y+HERO_SIZE_ON_BOARD-1);
                    
                    while ((blocks_back_map[hero.map_up_right].type == bt_wall) || (blocks_back_map[hero.map_dn_right].type == bt_wall) || (blocks_back_map[find_map_coord(hero.coord_x+HERO_SIZE_ON_BOARD-1, hero.coord_y+BRICK_INT_SIZE_ON_BOARD-1)].type == bt_wall)){
                        hero.coord_x-=go_x;
                        hero.map_up_right=find_map_coord(hero.coord_x+HERO_SIZE_ON_BOARD-1, hero.coord_y);
                        hero.map_dn_right=find_map_coord(hero.coord_x+HERO_SIZE_ON_BOARD-1, hero.coord_y+HERO_SIZE_ON_BOARD-1);
                    }
                    
                    go_x = 0;
                }
            }
            else{
                hero.coord_x-=(WIDTH_ON_BOARD-HERO_SIZE_ON_BOARD);
                current_screen = 1;
                switch_screen = 1;
            }
        }
        //влево работает правильно.
        //сделать функцию движения и подстроить ее под все стороны
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
        
        if (shoot) {
            
        }
        
        
        
        //координаты игрока в пространстве
        hero.rect.x=hero.coord_x/WIDTH_ON_BOARD*WINDOW_WIDTH;
        hero.rect.y=hero.coord_y/HEIGHT_ON_BOARD*WINDOW_HEIGHT;
        
        
    //конец обновления состояния игры
//**************************************************************************
//**************************************************************************
        
        //вывод на экран
        
        SDL_RenderClear(MainRenderer);
        SDL_RenderCopy(MainRenderer, bgTex, NULL, NULL);
        for (int i=0;i<map_h*map_w;i++){
            //if (i%map_screen_w==0){
            //    i+=map_screen_w;
            //}
            if (blocks_back_map[i].type!=bt_hero) {
                SDL_RenderCopy(MainRenderer, textures[blocks_back_map[i].type], NULL, &blocks_back_map[i].rect);
            }
            
        }
        
        //SDL_RenderCopy(MainRenderer, textures[blocks_back_map[i].type], NULL, &blocks_back_map[i].rect)
        
        SDL_RenderCopy(MainRenderer, spriteTex, NULL, &hero.rect);
        
        SDL_RenderPresent(MainRenderer);
        
        //ограничитель фпс
        
        if (frame_cap) {
            delta_clock = SDL_GetTicks() - start_clock;
            start_clock = SDL_GetTicks();
            
            if ( delta_clock != 0 )
                FPS = 1000 / delta_clock;
            //else
            //printf("delta_clock=%i ", delta_clock);
            if (FPS>50)
                SDL_Delay(FPS/50);
            
            /* при делении положительных чисел округляется в меньшую сторону
            printf("%i ",10/7);
            printf("%i ",11/7);
            printf("%i ",12/7);
            printf("%i ",13/7);
            printf("%i ",14/7);
            printf("%i ",15/7);
             
            */
            //printf("%i ",m);
            
            
            //printf("FPS=%i ", FPS);
            //printf("SDL_Delay(50/FPS)=%d ", 50/FPS);
            //printf("delta_clock=%i ", delta_clock);

        }
        /*
         //для проверки утечки памяти, быстрая смена экранов
        if (current_screen) {
            current_screen=0;
        } else current_screen=1;
        switch_screen=1;
         */
    }
    //free(textures);
    //LOL=NULL;
    //assert(blocks_back_map!=NULL);
    free (maps_array);
    free (blocks_back_map);
    switch_screen =0;
} while (!quit);
        //конец вывода на экран
//**************************************************************************
    
quit:
    
    for (int i=1; i<TEX_COUNT; i++) {
        SDL_DestroyTexture(textures[i]);
    }
    free (textures);
    
    
    SDL_DestroyTexture(bgTex);
    SDL_DestroyTexture(spriteTex);
    SDL_DestroyRenderer(MainRenderer);
    // Close and destroy the window
    SDL_DestroyWindow(window);
    
    // Clean up
    SDL_Quit();
    
    return 0;
}
