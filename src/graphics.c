// graphics.c
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

void close_graphics(void)
{
	CloseWindow();
}

void begin_graphics_drawing(void)
{
	BeginDrawing();
}

void end_graphics_drawing(void)
{
	EndDrawing();
}

void clear_graphics(const Color color)
{
	ClearBackground(color);
}

void draw_graphics_object(const object_t* obj)
{
	const Color color = obj->color;
	if(!obj->registered) return;
	
	Vector2 pos = obj->pos;

	switch(obj->obj_type) {
	case SHAPE_CIRCLE:
		DrawCircleV(pos, obj->size_x/2.0f, color);
		break;
	case SHAPE_SQUARE:
		DrawRectangleV(
			(Vector2){pos.x - obj->size_x/2, pos.y - obj->size_y/2},
			(Vector2){obj->size_x, obj->size_y}, color);
		break;
	case SHAPE_RECTANGLE:
		DrawRectangleV(
			(Vector2){pos.x - obj->size_x/2, pos.y - obj->size_y/2},
			(Vector2){obj->size_x, obj->size_y}, color);
		break;
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
	DrawText("G: Random gravity", 10, 110, 20, BLACK);
	DrawText("C: Clear screen", 10, 135, 20, BLACK);
	DrawText("RCLICK: Push object", 10, 160, 20, BLACK);
	DrawText("LCLICK: Add object", 10, 185, 20, BLACK);
	DrawText("1: Spawn Circle", 10, 210, 20, BLACK);
	DrawText("2: Spawn Square", 10, 235, 20, BLACK);
	DrawText("3: Spawn Rectangle", 10, 260, 20, BLACK);
}

bool should_close_graphics(void)
{
	return WindowShouldClose();
}
