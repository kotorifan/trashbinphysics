/**
 * @file common.h
 * @brief Functions and values used throughout most files
 * @date 2026-04-27
*/
#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <raylib.h>
#include <raymath.h>
#include <math.h>

#define MIN_VERTICES 3
#define MAX_VERTICES 16
#define MIN_EDGES 3
#define MAX_EDGES 16

// how many times to run update_physics per frame
// should be balanced between accuracy and CPU load, the higher 
// the number the more resource-intensive it is
#define ITER_PER_FRAME 8

// settings
// UI
#define SCREEN_TITLE "physics"
#define WINDOW_X 1250
#define WINDOW_Y 1000
// physics
#define MAX_OBJECTS 100
#define FORCE_RESITUTION_DEFAULT 0.7f
#define FORCE_GRAVITY_DEFAULT 1000.0f
#define FORCE_LINEAR_DAMPING_DEFAULT 0.995f

#define ARR_LEN(arr) (sizeof(arr)/sizeof(arr[0]))

#define RANDOM_COLOR() ((Color) {				\
			GetRandomValue(0, 255),				\
			GetRandomValue(0, 255),				\
			GetRandomValue(0, 255),				\
			255									\
		})

typedef uint_least8_t u8;
typedef int_least8_t i8;
typedef uint_least16_t u16;
typedef int_least16_t i16;
typedef uint_least32_t u32;
typedef int_least32_t i32;

typedef struct {
	Color color;
	
	float elast; // restitution
	float frict;
	float angle;
	float angle_vel;
	float mass;
	float inertia;
	
	Vector2 pos;
	Vector2 pos_prev;
	Vector2 vel;
    Vector2 vertices[MAX_VERTICES];
	Vector2 local_vertices[MAX_VERTICES];
	Vector2 edges[MAX_EDGES];

	float line_thickness;
	u32 vertex_n; // number of vertices
	u32 edge_n; // number of edges
	bool grabbed;
	bool registered;
} object_t;

#endif // COMMON_H
