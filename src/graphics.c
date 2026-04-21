// graphics.c
#include <raylib.h>
#include <stdint.h>
#include "graphics.h"
#include "math.h"

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

void draw_graphics_object(const object_t* obj, Color color)
{
	if(!obj->registered) return;
	
	Vector2 pos = obj->pos;

	switch(obj->type) {
	case OBJECT_CIRCLE:
		DrawCircleV(pos, obj->size_x, color);
		break;
	case OBJECT_SQUARE:
		DrawRectangleV(
			(Vector2){pos.x - obj->size_x/2, pos.y - obj->size_y/2},
			(Vector2){obj->size_x, obj->size_y}, color);
		break;
	case OBJECT_RECTANGLE:
		DrawRectangleV(
			(Vector2){pos.x - obj->size_x/2, pos.y - obj->size_y/2},
			(Vector2){obj->size_x, obj->size_y}, color);
		break;
	}

}

void draw_graphics_objects(const object_t* world, uint32_t count, Color color)
{
	
}


void draw_graphics_info(uint32_t fps, uint32_t objs, uint32_t max_objs);
bool should_close_graphics(void);
