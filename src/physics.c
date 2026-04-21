// physics.c
#include <raylib.h>
#include <time.h>
#include "physics.h"
#include "common.h"


void init_physics(object_t* world, uint32_t max_objs)
{
	for(uint32_t iter = 0; iter < max_objs; iter++) {
		world[iter].registered = false;
		world[iter].grabbed = false;
	}
}

void update_physics(object_t* world, uint32_t objs_count, float gravity, float dt)
{
	const uint32_t screen_width = GetScreenWidth();
	const uint32_t screen_height = GetScreenHeight();
	if(dt > 0.033f) dt = 0.033f;
	
	for(uint32_t iter = 0; iter < objs_count; iter++)
	{
		object_t* obj = &world[iter];
		if(!obj->grabbed && obj->registered) {
			obj->pos.x += obj->vel.x * dt;
			obj->pos.y += obj->vel.y * dt;

			float half_width = obj->size_x/2.0f;
			float half_height = obj->size_y/2.0f;

			if((obj->pos.x + half_width >= screen_width)) {
				obj->pos.x = screen_width - half_width;
				obj->vel.x = -obj->vel.x * obj->elast;

			} else if((obj->pos.x - half_width) <= 0) {
				obj->pos.x = half_width;
				obj->vel.x = -obj->vel.x * obj->elast;

			} else if((obj->pos.y + half_height) >= screen_height) {
				obj->pos.y = screen_height - half_height;
				obj->vel.y = -obj->vel.y * obj->elast;

			} else if((obj->pos.y - half_height) <= 0) {
				obj->pos.y = half_height;
				obj->vel.y = -obj->vel.y * obj->elast;

			}

			obj->vel.x = obj->vel.x * obj->frict;
			obj->vel.y = obj->vel.y * obj->frict * gravity * dt; 
		}
		
		if(obj->grabbed) {
			Vector2 cursor_pos = GetMousePosition();
			obj->pos = cursor_pos;
			obj->vel = (Vector2){0, 0};
		}
	}
}
