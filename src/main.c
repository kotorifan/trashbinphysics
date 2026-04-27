/**
 * @file main.c
 * @brief The main loop and controls
 * @date 2026-04-27
 */
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
	bool anti_gravity_toggle = false;



	objs_count = 0;
	init_physics(world, MAX_OBJECTS);
	init_graphics(WINDOW_X, WINDOW_Y, SCREEN_TITLE);

	Color bg_color = RANDOM_COLOR();
    Image bg = GenImagePerlinNoise(GetScreenWidth(), GetScreenHeight(), 0, 0, 3.0f);
	Texture2D bg_tex = LoadTextureFromImage(bg);
	UnloadImage(bg);

	while(!WindowShouldClose()) {
		Vector2 pos_cursor = GetMousePosition();
		
		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
			if(grabbed_obj != NULL) {
				grabbed_obj->grabbed = false;
				grabbed_obj = NULL;
			}
		}

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if(objs_count < MAX_OBJECTS) {
				object_t obj = (object_t){
					.color = RANDOM_COLOR(),
					.elast = 0.05f,
//					.frict = 0.99f,
					.frict = 2.00f,
					.pos = pos_cursor,
					.pos_prev = pos_cursor,
					.vel = { 
						(float)GetRandomValue(-30, 75), 
						(float)GetRandomValue(-30, 75)
					},
					.grabbed = false,
					.registered = true,
					.line_thickness = 2,
					.mass = GetRandomValue(20, 50), // will be done later
					.angle = 0.0f,
					.angle_vel = 0.0f,
					.vertex_n = 0,
					.edge_n = 0,
				};
				generate_random_shape(&obj, (float)GetRandomValue(3, 30));
				world[objs_count++] = obj;
			}
		}

		if(IsKeyPressed(KEY_G)) {
			anti_gravity_toggle = !anti_gravity_toggle;
			// make the exact number customizable in the common.h
			force_gravity = anti_gravity_toggle ? -75.0f : FORCE_GRAVITY_DEFAULT;
		}

		
		float dt = GetFrameTime();
		const u32 steps = ITER_PER_FRAME;
		float sub_dt = dt/(float)steps;
		for(u32 iter = 0; iter < ITER_PER_FRAME; iter++) {
			update_physics(world, objs_count, force_gravity, sub_dt);
		}

		BeginDrawing();

		ClearBackground(BLACK);
		DrawTexture(bg_tex, 0, 0, bg_color);
		draw_graphics_objects(world, objs_count);
		draw_graphics_info(objs_count);

	    EndDrawing();
	}

    CloseWindow();
	return EXIT_SUCCESS;
}
