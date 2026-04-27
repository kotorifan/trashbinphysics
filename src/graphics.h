/**
  * @file graphics.h
  * @brief Header file for graphics.c
  * @date 2026-04-28
*/
#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "common.h"

#include <raylib.h>
#include <stdint.h>

void init_graphics(uint32_t x, uint32_t y, const char* title);
void draw_graphics_object(const object_t* obj);
void draw_graphics_objects(const object_t* world, uint32_t count);
void draw_graphics_info(uint32_t objs);
bool should_close_graphics(void);
#endif // GRAPHICS_H
