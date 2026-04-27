/**
 * @file physics.h
 * @brief Header file with functions for physics.h; physics related, duh
 */
#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>
#include <time.h>
#include "common.h"

void init_physics(object_t* world, uint32_t max_objs);
bool check_collision(object_t* obj1, object_t* obj2, Vector2* out_n, float* out_depth);
void resolve_collision(object_t* obj1, object_t* obj2, Vector2 normal, float out_depth);
void update_shape(object_t* obj);
void update_physics(object_t* world, uint32_t objs_count, float gravity, float dt);
void clear_all_physics(object_t* world, uint32_t* count);
void generate_random_shape(object_t* obj, float radius);

#endif // PHYSICS_H
