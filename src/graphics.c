/**
 *   @file graphics.c
 *   @brief All things related to graphics
 *   @date 2026-04-27
 */
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include "graphics.h"
#include "common.h"

void init_graphics(uint32_t x, uint32_t y, const char* title)
{
	InitWindow(x, y, title);
	SetTargetFPS(60);
}

void draw_graphics_object(const object_t* obj)
{
	// shapes smaller than 3 don't make sense
	if(obj->vertex_n < 3) return;

	for(u32 iter = 0; iter < obj->vertex_n; iter++) {
		Vector2 start = obj->vertices[iter];
		Vector2 end = obj->vertices[(iter + 1) % obj->vertex_n];
		DrawLineEx(start, end, obj->line_thickness, obj->color);
	}
}

void draw_graphics_objects(const object_t* world, uint32_t count)
{
	for (uint32_t iter = 0; iter < count; iter++)
	{
		if(world[iter].registered) draw_graphics_object(&world[iter]);
	}
}

void draw_graphics_info(uint32_t objs)
{
	char buffer[128];
	snprintf(buffer, sizeof(buffer), "FPS: %d", GetFPS());
	DrawText(buffer, 10, 10, 20, BLACK);
	snprintf(buffer, sizeof(buffer), "OBJ: %d/%d", objs, MAX_OBJECTS);
    DrawText(buffer, 10, 35, 20, BLACK); 
	DrawText("ESC: Exit", 10, 60, 20, BLACK);
	DrawText("R: Random velocity", 10, 85, 20, BLACK);
	DrawText("G: Anti-Gravity", 10, 110, 20, BLACK);
	DrawText("C: Clear screen", 10, 135, 20, BLACK);
	DrawText("RCLICK: Push object", 10, 160, 20, BLACK);
	DrawText("LCLICK: Add object", 10, 185, 20, BLACK);
}

bool should_close_graphics(void)
{
	return WindowShouldClose();
}
