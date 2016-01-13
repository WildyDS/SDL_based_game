//
//  variables.h
//  I_wanna_SDL_C
//
//  Created by Александр on 12.08.14.
//  Copyright (c) 2014 NARO. All rights reserved.
//

#ifndef I_wanna_SDL_C_variables_h
#define I_wanna_SDL_C_variables_h

//#ifndef TEX_COUNT
#define TEX_COUNT 3
//#endif


#define FRAMES_PER_SECOND 50


#define map_w 40
#define map_h 30

#define  WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// *_on_board - это значения размеров пространства, по которому можно перемещаться, будет конвертироваться в координаты на экране
#define  WIDTH_ON_BOARD 16000
#define HEIGHT_ON_BOARD 12000

//#define    jump_powa_on_board 120
//#define gravity_powa_on_board 80
//#define   move_speed_on_board 10

// *_on_screen - размеры на экране

extern double    JUMP_POWA_ON_BOARD;// = HEIGHT_ON_BOARD*0.01;
extern double GRAVITY_POWA_ON_BOARD;// = HEIGHT_ON_BOARD*0.02/3;
extern double   MOVE_SPEED_ON_BOARD;// = HEIGHT_ON_BOARD*0.01/6;


extern int      HERO_SIZE_ON_BOARD;// = 2*HEIGHT_ON_BOARD/map_h;
extern int BRICK_INT_SIZE_ON_BOARD;// = HEIGHT_ON_BOARD/map_h;
extern int  BRICK_SIZE_ON_BOARD;// = HEIGHT_ON_BOARD/map_h;

extern int      HERO_SIZE_ON_SCREEN;// = 2*WINDOW_HEIGHT/map_h;
extern int BRICK_INT_SIZE_ON_SCREEN;// = WINDOW_HEIGHT/map_h;
extern int  BRICK_SIZE_ON_SCREEN;// = WINDOW_HEIGHT/map_h;


#endif
