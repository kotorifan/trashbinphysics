// physics.c
#include <raylib.h>
#include <time.h>
#include "physics.h"
#include "common.h"


void init_physics(object_t* world, uint32_t max_objs)
{
	for(uint32_t iter = 0; iter < max_objs; iter++) world[iter].registered = false;
}

void update_physics(object_t* world, uint32_t objs_count, float gravity, 
					float damping, float dt)
{
	const uint32_t screen_width = GetScreenWidth();
	const uint32_t screen_height = GetScreenHeight();
	for(uint32_t iter = 0; iter < objs_count; iter++)
	{
		object_t* obj = &world[iter];
		if(!obj->grabbed) {
			obj->pos.x += obj->vel.x * dt;
			obj->pos.y += obj->vel.y * dt;

			if((obj->pos.x + obj->size_x >= screen_width)) {
				obj->pos.x = screen_width - obj->size_x;
				obj->vel.x = -obj->vel.x * obj->elast;
			} else if((obj->pos.x - obj->size_x) <= 0) {
				obj->pos.x = obj->radius;
				obj->vel.x = -obj->vel.x * obj->elast;
			} else if((obj->pos.y + obj->size_y) >= screen_height) {
				obj->pos.y = screen_height - obj->size_y;
				obj->vel.y = -obj->vel.y * obj->elast;
			} else if((obj->pos.y - obj->size_y) <= 0) {
				obj->pos.y = obj->size_y;
				obj->vel.y -obj->vel.y * obj->elast;
			}

			obj->vel.x = obj->vel.x * obj->frict;
			obj->vel.y = obj->vel.y * obj->frict * gravity; 
		}
	}

/* void apply_force(object_t* obj, Vector2 force) */
/* { */
/* 	if(obj->registered == true) { */
/* 		obj->force = Vector2Add(body->force, force) */
			
/* 			} */
/* } */

/* void add_object(object_t* world, uint32_t* count, object_type_t type, Vector2 pos) */
/* { */
/* 	world */
/* } */
/* void clear_all_physics(object_t* world, uint32_t* count); */
	void push_pos(object_t* world, uint32_t count, Vector2 pos, float radius, float strength);
