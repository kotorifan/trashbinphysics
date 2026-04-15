// main.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>
#include <math.h>

#include "common.h"
#include "graphics.h"
#include "physics.h"

void physics_init(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
	SetTargetFPS(60);
}

void physics_close(void)
{
	CloseWindow();
}

void physics_draw_info()
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
}
int main(void)
{
	bool should_run = true;

	// physics related
	object_t objects[MAX_OBJECTS];
	float force_resitution = FORCE_RESITUTION_DEFAULT;
	float force_gravity = FORCE_GRAVITY_DEFAULT;
	float force_linear_damping = FORCE_LINEAR_DAMPING_DEFAULT;

	physics_init();

	while(!WindowShouldClose() && should_run)
	{
		BeginDrawing();
		ClearBackground(WHITE);
		physics_draw_info();
		EndDrawing();
	}

	physics_close();
	return EXIT_SUCCESS;
}
