// physics.h
#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>
#include <time.h>
#include "common.h"

typedef enum {
	SHAPE_CIRCLE,
	SHAPE_SQUARE,
	SHAPE_RECTANGLE
} shape_t;

typedef struct {
	Color color;
	Vector2 elast;
//	Vector2 force;
	Vector2 frict;
	Vector2 pos;
	Vector2 pos_prev;
	Vector2 vel;
	bool grabbed;
	bool registered;
	float mass;
	float size_x;
	float size_y;
	shape_t obj_type;
} object_t;

void init_physics(object_t* world, uint32_t max_objs);
void update_physics(object_t* world, uint32_t objs_count, float gravity, float damping);
void apply_force(object_t* obj, Vector2 force);
void add_object(object_t* world, uint32_t* count, object_type_t type, Vector2 pos);
void clear_all_physics(object_t* world, uint32_t* count);
void push_pos(object_t* world, uint32_t count, Vector2 pos, float radius, float strength);

#endif // PHYSICS_H
