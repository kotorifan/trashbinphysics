// main.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>
#include <math.h>

#include "common.h"
#include "graphics.h"
#include "physics.h"


void draw_graphics_info()
{
	char buffer[128];
	snprintf(buffer, sizeof(buffer), "FPS: %d", GetFPS());
	DrawText(buffer, 10, 10, 20, BLACK);
	/* snprintf(buffer, sizeof(buffer), "OBJ: %d/%d", objects, MAX_OBJECTS); */
    /* DrawText(buffer, 10, 35, 20, BLACK); */
	DrawText("ESC: Exit", 10, 60, 20, BLACK);
	DrawText("R: Random velocity", 10, 85, 20, BLACK);
	DrawText("G: Random gravity", 10, 110, 20, BLACK);
	DrawText("C: Clear screen", 10, 135, 20, BLACK);
	DrawText("RCLICK: Push object", 10, 160, 20, BLACK);
	DrawText("LCLICK: Add object", 10, 185, 20, BLACK);
	DrawText("1: Spawn Circle", 10, 210, 20, BLACK);
	DrawText("2: Spawn Square", 10, 235, 20, BLACK);
	DrawText("3: Spawn Rectangle", 10, 260, 20, BLACK);
}

int main(void)
{
	bool should_run = true;

	// physics related
	object_t world[MAX_OBJECTS];
	float force_resitution = FORCE_RESITUTION_DEFAULT;
	float force_gravity = FORCE_GRAVITY_DEFAULT;
	float force_linear_damping = FORCE_LINEAR_DAMPING_DEFAULT;

	InitWindow(WINDOW_X, WINDOW_Y, SCREEN_TITLE);
	SetTargetFPS(60);

	while(!WindowShouldClose() && should_run)
	{	
		/* handle_input(world) */
		// physics_update
		
		begin_graphics_drawing();

		clear_graphics(RAYWHITE);
		draw_graphics_objects(world, object_count, BLACK);
		draw_graphics_info(GetFPS(), object_count, MAX_OBJECTS);

		end_graphics_drawing();
	}

	CloseWindow();
	return EXIT_SUCCESS;
}
