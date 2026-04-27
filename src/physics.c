// physics.c
#include <raylib.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "physics.h"
#include "common.h"

bool check_collision(object_t obj1, object_t obj2)
{
	// perp = perpendicular here
	void* perpendicular_line = NULL;
	Vector2* perp_stack = NULL;
	float dot = 0;
	float a_min, a_max, b_min, b_max;
	
	Vector2 obj1_len = sizeof(obj1->edges)/sizeof(Vector2);
	Vector2 obj2_len = sizeof(obj2->edges)/sizeof(Vector2);
	perp_stack = (Vector2*)malloc((obj1_len + obj2_len) * sizeof(Vector2));
	
	for(u32 iter = 0; iter < obj1_len; iter++) {
		Vector2 perp = {
			.x = -obj1->edges[iter].x,
			.y = obj1->edges[iter].y
		};
		perp_stack[perp_stack_size++] = perp;
	}

	for(u32 iter = 0; iter < obj2_len; iter++) {
		Vector2 perp = {
			.x = -obj2->edges[i].y,
			.y = obj2->edges[i].x
		};
		perp_stack[perp_stack_size++] = perp;
	}

	for(u32 iter = 0; iter < perp_count; iter++) {
		a_min = INFINITY;
		a_max = -INFINITY;
		b_min = INFINITY;
		b_max = -INFINITY;

		for(u32 iter2 = 0; iter2 < obj1_len; iter2++) {
			dot = Vector2DotProduct(obj1.vertices[iter2], perp_stack[iter2]);
			
			if(a_max == NULL || dot < a_min) a_max = dot;
			if(a_min == NULL || dot < a_min) a_min = dot;			
		}
		
		for(u32 iter2 = 0; iter2 < obj2_len; iter2++) {
			dot = Vector2DotProduct(obj2.vertices[iter2], perp_stack[iter2]);
			
			if(b_max == NULL || dot > b_max) b_max = dot;
			if(b_min == NULL || dot < b_min) b_min = dot;
		}
		
		if((a_min < b_max && a_min > b_min) || (b_min < a_max && b_min > a_min)) {
			continue;
		} else {
			return false;
		}
	}
	return true;
}

void resolve_collision(object_t* obj1, object_t* obj2, Vector2 normal)
{
	Vector2 rel_vel = Vector2Subtract(obj1->vel, obj1->vel);
	float vel_along = Vector2DotProduct(rel_vel, normal);
	if(vel_along > 0) return;
}

void init_physics(object_t* world, uint32_t max_objs)
{
	for(u32 iter = 0; iter < max_objs; iter++) {
		world[iter].registered = false;
		world[iter].grabbed = false;
	}
}

void update_physics(object_t* world, u32 objs_count, float gravity, float dt)
{
	const u32 screen_width = GetScreenWidth();
	const u32 screen_height = GetScreenHeight();
	Vector2 walls;
	for(u32 iter = 0; iter < objs_count; iter++) {
		object_t* obj = &world[iter];
		
		// Clamp objects to the window boundaries if they move outside
		obj = { 
			Clamp(obj->pos.x, 0.0f, (float)screen_width),
			Clamp(obj->pos.y, 0.0f, (float)screen_height)
		};
		
		for(u32 iter2 = 0; iter2 < objs_count; iter2++) {
			object_t obj_a = &world[iter];
			object_t obj_b = &world[iter++];
			if(check_collision(obj_a, obj_b)) {
				
			}
		}
	}
}
