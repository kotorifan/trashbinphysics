// graphics.h
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <raylib.h>
#include <stdint.h>
#include "common.h"

void init_graphics(uint32_t x, uint32_t y, const char* title);
void close_graphics(void)
void begin_graphics_drawing(void);
void end_graphics_drawing(void);
void clear_graphics(const Color color);
void draw_graphics_object(const object_t* obj, Color color);
void draw_graphics_objects(const object_t* world, uint32_t count, Color color);
void draw_graphics_info(uint32_t fps, uint32_t objs, uint32_t max_objs);
bool should_close_graphics(void);
#endif // GRAPHICS_H
