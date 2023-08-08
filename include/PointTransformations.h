#ifndef POINT_TRANSFORMATION_H
#define POINT_TRANSFORMATION_H

#include <SDL2/SDL.h>
#include "TypeDefinitions.h"

void translateModel(struct Vector3* input, float x, float y, float z);

SDL_Point projectPoint(struct Vector3 input);

#endif