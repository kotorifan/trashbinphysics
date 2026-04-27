// physics.h
#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>
#include <time.h>
#include "common.h"


void init_physics(object_t* world, uint32_t max_objs);
bool check_collision(object_t obj1, object_t obj2);
void update_physics(object_t* world, uint32_t objs_count, float gravity, float dt);
void apply_force(object_t* obj, Vector2 force);
void add_object(object_t* world, uint32_t* count, shape_t type, Vector2 pos);
void clear_all_physics(object_t* world, uint32_t* count);
void push_pos(object_t* world, uint32_t count, Vector2 pos, float radius, float strength);

#endif // PHYSICS_H
