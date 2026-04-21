// physics.h
#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>
#include "common.h"

typedef struct {
	shape_t type;
	Vec2d pos;
	Vec2d vel;
	Vec2d acc;
	float width;
	float height;
	Color color;
} object_t;

typedef sturct {
	object_t* object_arr;
	u16 object_count;
	size_t capacity;
} world_t;

void register_new_object(world_t* world, u32 object_x, u32 object_y);
void delete_object(world_t* world);
void clear_scene(world_t* world);
#endif // PHYSICS_H
