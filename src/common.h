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

#define SHAPE_ENUM_SIZE 3
typedef enum {
		SHAPE_CIRCLE,
		SHAPE_SQUARE,
		SHAPE_RECTANGLE
} shape_t;

typedef struct {
		Color color;
		float elast;
//	Vector2 force;
		float frict;
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

#define RANDOM_SHAPE() ((shape_t)(GetRandomValue(0, SHAPE_ENUM_SIZE - 1)))

#define RANDOM_COLOR() ((Color) {				\
						GetRandomValue(0, 255),	\
						GetRandomValue(0, 255),	\
						GetRandomValue(0, 255),	\
						255						\
				})


#endif // COMMON_H
