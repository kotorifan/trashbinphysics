// main.c
#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "graphics.h"
#include "physics.h"



int(void)
{
	// physics related
	object_t world = malloc(sizeof(object_t)*max_objs);
	uint32_t objs_count = 0;
	float force_gravity = FORCE_GRAVITY_DEFAULT;
	float force_linear_damping = FORCE_LINEAR_DAMPING_DEFAULT;

	world[0] = (object_t){
		.color = BLUE,
		.elast = 0.9f,
		.frict = 0.99f,
		.grabbed = true,
		.pos_prev = {0},
		.registered = true;
		.size_x = 40,
		.size_y = 40,
		.vel = {200, 200},
		.pos = {GetScreenWidth()/2.0f, GetScreenheight()/2.0f},
		object_type_t = OBJECT_CIRCLE
	};

	init_graphics(WINDOW_X, WINDOW_Y, SCREEN_TITLE);
	while(!WindowShouldClose())
	{	
		/* handle_input(world) */
		// physics_update
		float dt = GetFrameTime(); // delta time
		Vector2 pos_cursor = GetMousePosition();
		
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			for(uint32 iter = objs_count -1; iter >= 0; i--)
			{
				object_t* obj = &world[i];
				
				if(hypot(pos_cursor.x, pos_cursor.y) <= (obj->size_x && obj->size_y))
				{
					obj->grabbed = true;
					grabbed_obj = obj;
					break;
				}
			}
		}
		
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			if(grabbed_obj != NULL)
			{
				grabbed_obj->grabbed = false;
				grabbed_obj = NULL;
			}
		}

		if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			if(objs_count =< max_objs)
			{
				world[objs_count++] = (object_t*){
					.color = { 
						GetRandomValue(0, 255),
						GetRandomValue(0, 255),
						GetRandomValue(0, 255),
						255
					},
					.elast = 0.9f,
					.frict = 0.99f,
					.pos = pos_cursor;
					.pos_prev = 0.99f,
					.vel = { 
						(float)GetRandomValue(-300, 300), 
						(float)GetRandomValue(-300, 300)
					},
					.grabbed = false,
					.registered = true;
					.mass = GetRandomValue(0, 100), // will be done later
					.size_x = GetRandomValue(3, 20), //everything smaller than 3 would be too small
					.size_y = GetRandomValue(3, 20),
					.obj_type = get_random_shape()
				};
			}
		}

		begin_graphics_drawing();

		clear_graphics(RAYWHITE);
		draw_graphics_objects(world, objs_count);
		draw_graphics_info(GetFPS(), objs_count, MAX_OBJECTS);

		end_graphics_drawing();
	}

    close_graphics();
	return EXIT_SUCCESS;
}
