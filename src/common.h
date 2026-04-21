// common.h
#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

typedef uint_least8_t u8;
typedef int_least8_t i8;
typedef uint_least16_t u16;
typedef int_least16_t i16;
typedef uint_least32_t u32;
typedef int_least32_t i32;



// settings
// UI
#define SCREEN_TITLE "physics"
#define WINDOW_X 1250
#define WINDOW_Y 1000
// physics
#define MAX_OBJECTS 100
#define FORCE_RESITUTION_DEFAULT 0.8f
#define FORCE_GRAVITY_DEFAULT 1000.0f
#define FORCE_LINEAR_DAMPING_DEFAULT 0.995f;

#define ARR_LEN(arr) (sizeof(arr)/sizeof(arr[0]))

typedef enum {
	SHAPE_CIRCLE,
	SHAPE_SQUARE,
	SHAPE_RECTANGLE
} shape_t;

shape_t get_random_shape(void)
{
	shape_t valid_shapes[] = {
		SHAPE_CIRCLE,
		SHAPE_SQUARE,
		SHAPE_RECTANGLE
	};

	return valid_shapes(GetRandomValue(0, ARR(valid_shapes)));
}

#endif // COMMON_H
