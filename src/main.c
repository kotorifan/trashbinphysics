// main.c
#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#include "graphics.h"
#include "physics.h"
#include "common.h"


int main(void)
{
	// physics related
	object_t world[MAX_OBJECTS];
	uint32_t objs_count = 0;
	float force_gravity = FORCE_GRAVITY_DEFAULT;
	object_t* grabbed_obj = NULL;

	world[0] = (object_t){
		.color = RANDOM_COLOR(),
		.elast = 0.9f,
		.frict = 0.99f,
		.grabbed = true,
		.pos_prev = {0},
		.registered = true,
		.size_x = 75,
		.size_y = 75,
		.vel = {200, 200},
		.pos = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f },
	    .obj_type = RANDOM_SHAPE()
	};

	objs_count = 1;
	init_physics(world, MAX_OBJECTS);
	init_graphics(WINDOW_X, WINDOW_Y, SCREEN_TITLE);
	while(!WindowShouldClose())
	{	
		/* handle_input(world) */
		// physics_update
		/* float dt = GetFrameTime(); delta time */
		Vector2 pos_cursor = GetMousePosition();
		
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if(objs_count == 0)
			{
				grabbed_obj = NULL;
			} else {
				for(uint32_t iter = objs_count; iter > 0; iter--)
				{
					object_t* obj = &world[iter - 1];
				

					float dx = pos_cursor.x - obj->pos.x;
					float dy = pos_cursor.y - obj->pos.y;
				
					if(hypot(dx, dy) <= (obj->size_x && obj->size_y))
					{
						obj->grabbed = true;
						grabbed_obj = obj;
						break;
					}
				}
			}
		}
		
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			if(grabbed_obj != NULL) {
				grabbed_obj->grabbed = false;
				grabbed_obj = NULL;
			}
		}

		if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			if(objs_count < MAX_OBJECTS) {
				world[objs_count++] = (object_t){
					.color = RANDOM_COLOR(),
					.elast = 0.9f,
					.frict = 0.99f,
					.pos = pos_cursor,
					.pos_prev = pos_cursor,
					.vel = { 
						(float)GetRandomValue(-300, 300), 
						(float)GetRandomValue(-300, 300)
					},
					.grabbed = false,
					.registered = true,
					.mass = GetRandomValue(3, 100), // will be done later
					.size_x = GetRandomValue(50, 100), //everything smaller than 3 would be too small
					.size_y = GetRandomValue(50, 100),
					.obj_type = RANDOM_SHAPE()
				};
			}
		}

		float dt = GetFrameTime();
		update_physics(world, objs_count, force_gravity, dt);

		begin_graphics_drawing();

		clear_graphics(RAYWHITE);
		draw_graphics_objects(world, objs_count);
		draw_graphics_info(objs_count);

		end_graphics_drawing();
	}

    close_graphics();
	return EXIT_SUCCESS;
}
