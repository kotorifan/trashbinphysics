/**
 *   @file physics.h
 *   @brief All things related to physics
 *   @date 2026-04-27
 */
#include <raylib.h>
#include <raymath.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "physics.h"
#include "common.h"

/**
   @brief iterate through all objects and check whether they are grabbed or registered
*/
void init_physics(object_t* world, uint32_t max_objs)
{
	for(u32 iter = 0; iter < max_objs; iter++) {
		world[iter].registered = false;
		world[iter].grabbed = false;
	}
}

/**
   @brief uses the SAT to check whether a collision between two objects is happening
*/
bool check_collision(object_t* obj1, object_t* obj2)
{
	for(u32 shape = 0; shape < 2; shape++) {
		object_t* obj = (shape == 0) ? obj1 : obj2;
		
		for(u32 iter = 0; iter < obj->vertex_n; iter++) {
			Vector2 edge = obj->edges[iter];
			// perpendicular axis
			Vector2 axis = Vector2Normalize((Vector2){-edge.y, edge.x});
		 
			float a_min = INFINITY, b_min = INFINITY;
			float a_max = -INFINITY, b_max = -INFINITY;
			  
			for(u32 iter2 = 0; iter2 < obj1->vertex_n; iter2++) {
				float p = Vector2DotProduct(obj1->vertices[iter2], axis);
				a_min = fminf(a_min, p);
				a_max = fmaxf(a_max, p);
			}
			
			for(u32 iter2 = 0; iter2 < obj2->vertex_n; iter2++) {
				float p = Vector2DotProduct(obj2->vertices[iter2], axis);
				b_min = fminf(b_min, p);
				b_max = fmaxf(b_max, p);
			}

			if(a_max < b_min || b_max < a_min) return false;
		}
	}
	return true;
}

void resolve_collision(object_t* obj1, object_t* obj2, Vector2 normal)
{
	Vector2 rel_vel = Vector2Subtract(obj1->vel, obj2->vel);
	float vel_along = Vector2DotProduct(rel_vel, normal);
	if(vel_along > 0) return;
}


void update_physics(object_t* world, u32 objs_count, float gravity, float dt)
{
	const u32 screen_width = GetScreenWidth();
	const u32 screen_height = GetScreenHeight();
	for(u32 iter = 0; iter < objs_count; iter++) {
		object_t* obj = &world[iter];
		
		// Clamp objects to the window boundaries if they move outside
		obj->pos.x = Clamp(obj->pos.x, 0.0f, (float)screen_width);
		obj->pos.y = Clamp(obj->pos.y, 0.0f, (float)screen_height);
		
		obj->vel.x += gravity * dt;
		obj->pos = Vector2Add(obj->pos, Vector2Scale(obj->vel, dt));
		for(u32 iter2 = 0; iter2 < objs_count; iter2++) {
			object_t* obj_a = &world[iter];
			object_t* obj_b = &world[iter++];
			if(check_collision(obj_a, obj_b)) {
				
			}
		}
	}
}
