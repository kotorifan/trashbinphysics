/**
 *   @file physics.h
 *   @brief All things related to physics
 *   @date 2026-04-27
 */
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "common.h"
#include "physics.h"

#define OBJ_MAX_SPEED 300.0f // obviously a float, so beware
#define GROUND_OFFSET 30.0f

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
bool check_collision(object_t* obj1, object_t* obj2, Vector2* out_n, float* out_depth)
{
	float min_overlap = INFINITY;
	Vector2 best_axis = {0};

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
			
			float overlap = fminf(a_max, b_max) - fmaxf(a_min, b_min);
			if(overlap < min_overlap) {
				min_overlap = overlap; 
			    best_axis = axis;
			} 
		}
	}
	Vector2 dir = Vector2Subtract(obj2->pos, obj1->pos);
	if(Vector2DotProduct(dir, best_axis) < 0) {
		best_axis = Vector2Negate(best_axis);
	}
	*out_n = best_axis;
	*out_depth = min_overlap;
	return true;
}

void resolve_collision(object_t* obj1, object_t* obj2, Vector2 normal, float out_depth)
{
	Vector2 rvel = Vector2Subtract(obj1->vel, obj2->vel);
	float vel = Vector2DotProduct(rvel, normal);
	
	// Early exist options for too small values
	if(vel > 0.0f) return; 

	//float e = fminf(obj1->elast, obj2->elast);
	float e = FORCE_RESITUTION_DEFAULT;
    float inv_m1 = 1.0f/obj1->mass;
	float inv_m2 = 1.0f/obj2->mass;
	float j = -(1.0f + e) * vel;
	j /= (inv_m1 + inv_m2);

	// correction
	Vector2 corr = Vector2Scale(normal, out_depth * 0.8f);
	obj1->pos = Vector2Subtract(obj1->pos, Vector2Scale(corr, inv_m1));
	obj2->pos = Vector2Add(obj2->pos, Vector2Scale(corr, inv_m2));
	obj1->vel = Vector2Scale(obj1->vel, FORCE_LINEAR_DAMPING_DEFAULT);
	obj2->vel = Vector2Scale(obj2->vel, FORCE_LINEAR_DAMPING_DEFAULT);
}

void update_shape(object_t* obj)
{
	float c = cosf(obj->angle);
	float s = sinf(obj->angle);

	for(u32 iter = 0; iter < obj->vertex_n; iter++) {
		Vector2 v = obj->local_vertices[iter];
		
		obj->vertices[iter] = (Vector2){ // rotate and translate
			v.x * c - v.y * s + obj->pos.x,
			v.x * s - v.y * c + obj->pos.y
		};
	}
	
	for(u32 iter = 0; iter < obj->vertex_n; iter++) {
		Vector2 a = obj->vertices[iter];
		Vector2 b = obj->vertices[(iter + 1) % obj->vertex_n];
		obj->edges[iter] = Vector2Subtract(b, a);
	}
}


void update_physics(object_t* world, u32 objs_count, float gravity, float dt)
{
	float left = 0.0f;
	float right = (float)GetScreenWidth();
	float top = 0.0f;
	float bottom = (float)GetScreenHeight() - GROUND_OFFSET;
	for(u32 iter = 0; iter < objs_count; iter++) {
		object_t* obj1 = &world[iter];

		// here it's separate if statements because ALL these must be checked, 
		// so else if wouldn't work here
		if (obj1->pos.x < left) { obj1->pos.x = left; obj1->vel.x *= -obj1->elast; }
		if (obj1->pos.x > right) { obj1->pos.x = right; obj1->vel.x *= -obj1->elast; }
		if (obj1->pos.y < top) { obj1->pos.y = top; obj1->vel.y *= -obj1->elast; }
		if (obj1->pos.y > bottom) { obj1->pos.y = bottom; obj1->vel.y *= -obj1->elast; }

		obj1->vel.y += gravity * dt;
		// small global damping to prevent explosive movements
		obj1->vel = Vector2Scale(obj1->vel, FORCE_LINEAR_DAMPING_DEFAULT);
		obj1->vel = Vector2ClampValue(obj1->vel, 0.0f, OBJ_MAX_SPEED);
		obj1->pos = Vector2Add(obj1->pos, Vector2Scale(obj1->vel, dt));

		update_shape(obj1);
		
		for(u32 iter2 = iter + 1; iter2 < objs_count; iter2++) {
			object_t* obj2 = &world[iter2];
			Vector2 normal;
			float out_depth;
			if(check_collision(obj1, obj2, &normal, &out_depth)) {
				resolve_collision(obj1, obj2, normal, out_depth);
			}
		}
	}
}

void generate_random_shape(object_t* obj, float radius)
{
	obj->vertex_n = GetRandomValue(MIN_VERTICES, MAX_VERTICES);
	for(u32 iter = 0; iter < obj->vertex_n; iter++) {
		float a = (float)iter / obj->vertex_n * 2.0f * PI;
		a += GetRandomValue(-30, 30) * DEG2RAD;
		float r = radius * (0.4f + (0.4f + (float)GetRandomValue(0, 80)/100.0f));

		obj->local_vertices[iter] = (Vector2){
			cosf(a) * r,
			sinf(a) * r
		};
	}
}
