// physics.c
#include <raylib.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "physics.h"
#include "common.h"

#define GET_RECTANGLE_CENTER(rec) ((Vector2) {			\
			rec.x + rec.width/2, rec.y + rec.height/2	\
		};)


bool get_sat(object_t obj1, object_t obj2)
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

void init_physics(object_t* world, uint32_t max_objs)
{
	for(u32 iter = 0; iter < max_objs; iter++) {
		world[iter].registered = false;
		world[iter].grabbed = false;
	}
}

/* void update_physics(object_t* world, uint32_t objs_count, float gravity, float dt) */
/* { */
/* 	const uint32_t screen_width = GetScreenWidth(); */
/* 	const uint32_t screen_height = GetScreenHeight(); */

/* 	for(u32 iter = 0; iter < objs_count; iter++) { */
/* 		object_t* obj = &world[iter]; */
/* 		if(!obj->grabbed && obj->registered) { */
			
/* 			obj->pos.x += obj->vel.x * dt; */
/* 			obj->pos.y += obj->vel.y * dt; */

/* 			if((obj->pos.x + obj->size_x) >= screen_width) { */
/* 				obj->pos.x = screen_width - obj->size_x; */
/* 				obj->vel.x = -obj->vel.x * obj->elast; */

/* 			} else if((obj->pos.x - obj->size_x) <= 0) { */
/* 				obj->pos.x = obj->size_x; */
/* 				obj->vel.x = -obj->vel.x * obj->elast; */

/* 			} else if((obj->pos.y + obj->size_y) >= screen_height) { */
/* 				obj->pos.y = screen_height - obj->size_y; */
/* 				obj->vel.y = -obj->vel.y * obj->elast; */

/* 			} else if((obj->pos.y - obj->size_y) <= 0) { */
/* 				obj->pos.y = obj->size_y; */
/* 				obj->vel.y = -obj->vel.y * obj->elast; */

/* 			} */

/* 			obj->vel.x = obj->vel.x * obj->frict; */
/* 			obj->vel.y = (obj->vel.y + gravity * dt) * obj->frict; */
/* 		} */
		
/* 		for (u32 iter2 = 0; iter2 < objs_count; iter2++) { */
/* 			if(check_collision(&world[iter], &world[iter2])) { */
/* 			} */
/* 		} */
/* 	} */
/* 	/\* if(obj->grabbed) { *\/ */
/* 	/\* 	Vector2 cursor_pos = GetMousePosition(); *\/ */
/* 	/\* 	obj->pos = cursor_pos; *\/ */
/* 	/\* 	obj->vel = (Vector2){0, 0}; *\/ */
/* 	/\* } *\/ */

/* } */
