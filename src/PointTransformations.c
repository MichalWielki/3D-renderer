#include <SDL2/SDL.h>
#include "../include/TypeDefinitions.h"
#include "../include/PointTransformations.h"

const int gWidth = 640;
const int gHeight = 480;

const float moveSpeed = 5.0f;
const int fl = 300;
const int centerX = gWidth / 2;
const int centerY = gHeight / 2;
const int centerZ = 1000;

// moves model
void translateModel(struct Vector3* input, float x, float y, float z) {
      for(int i = 0; i < 8; i++) {
            input[i].x += x;
            input[i].y += y;
            input[i].z += z;
      }
}

// project 3D point onto the 2D screen resulting in 2D point
SDL_Point projectPoint(struct Vector3 input) {
      float perspective = 1.0f;
      float distance = fl + input.z + centerZ;
      // comparing floating points
      if(distance > 1 || distance < -1) {
            perspective = fl / distance;
      }
      SDL_Point p;
      p.x = input.x * perspective + centerX; 
      p.y = input.y * perspective + centerY; 
      return p;
}