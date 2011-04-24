#ifndef COMMON_H
#define COMMON_H

// Dimensions
#define SCREEN_WIDTH 1051.76f
#define SCREEN_HEIGHT 700.f
#define GUI_DIMENSION 1000.f
#define MAP_DIMENSION 1990.f
#define PIXEL_DIMENSION 50
#define PIXEL_LINE_COUNT 40

#define COLLISION_MAP_TYPE unsigned short int

// Collision bits
#define PIECE_NONE 0
#define PIECE_SNAKE_HEAD 1
#define PIECE_SNAKE_BODY 2
#define PIECE_FOOD 4
#define PIECE_WALL 8
#define PIECE_FREE 16

#endif // COMMON_H
