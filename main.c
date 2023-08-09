#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int gWidth = 640;
const int gHeight = 480;

const float moveSpeed = 5.0f;
const int fl = 300;
const int centerX = gWidth / 2;
const int centerY = gHeight / 2;
const int centerZ = 1000;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

struct Vector3 {
      float x; float y; float z;
};

bool init() {
      if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL Erorr: %s", SDL_GetError());
		return false;
	}
	gWindow = SDL_CreateWindow("hi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gWidth, gHeight, 0);
	if(gWindow == NULL) {
		printf("SDL Erorr: %s", SDL_GetError());
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	if(gWindow == NULL) {
		printf("SDL Erorr: %s", SDL_GetError());
		return false;
	}
	return true;
}

void close() {
      SDL_DestroyRenderer(gRenderer);
      SDL_DestroyWindow(gWindow);
      SDL_Quit();
}

// moves 8 points
void translateModel(struct Vector3* input, float x, float y, float z) {
      for(int i = 0; i < 8; i++) {
            input[i].x += x;
            input[i].y += y;
            input[i].z += z;
      }
}

// project 3D point onto the 2D screen
SDL_Point projectPoint(struct Vector3 input) {
      float perspective = 1.0f;
      float distance = fl + input.z + centerZ;
      // comparing floating points
      if(distance > 1 || distance < -1) {
            perspective = fl / distance;
      }
      SDL_Point p;
      // + centerX makes origin sit in the middle of the screen
      p.x = input.x * perspective + centerX; 
      p.y = input.y * perspective + centerY; 
      return p;
}

// connects 8 points to form a cube
void drawCube(struct Vector3* input) {
      for(int i = 0; i < 4; i++) {
            SDL_Point p0 = projectPoint(input[i]); // 0 1   1 2   2 3   3 0
            SDL_Point p1 = projectPoint(input[(i + 1) % 4]);
            SDL_RenderDrawLine(gRenderer, p0.x, p0.y, p1.x, p1.y);
      }
      for(int i = 0; i < 4; i++) {
            SDL_Point p0 = projectPoint(input[i + 4]);
            SDL_Point p1 = projectPoint(input[(i + 1) % 4 + 4]);
            SDL_RenderDrawLine(gRenderer, p0.x, p0.y, p1.x, p1.y);
      }
      for(int i = 0; i < 4; i++) {
            SDL_Point p0 = projectPoint(input[i]);
            SDL_Point p1 = projectPoint(input[(i + 4)]);
            SDL_RenderDrawLine(gRenderer, p0.x, p0.y, p1.x, p1.y);
      }
}

void draw(struct Vector3* input) {
      SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderClear(gRenderer);
      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      
      drawCube(input);

      SDL_RenderPresent(gRenderer);
}

int main() {
      // initialize SDL stuff
      init();
      bool isRunning = true;
      SDL_Event e;
      const Uint8* gKeyStates = SDL_GetKeyboardState(NULL);

      struct Vector3 points[8] = {
            [0] = {-150, -150, 150},
            [1] = {150, -150, 150},
            [2] = {150, 150, 150},
            [3] = {-150, 150, 150},
            [4] = {-150, -150, -150},
            [5] = {150, -150, -150},
            [6] = {150, 150, -150},
            [7] = {-150, 150, -150},
      };

      while(isRunning) {
            SDL_PollEvent(&e);
            if(e.type == SDL_QUIT) {
                  return false;
            }
            if(gKeyStates[SDL_SCANCODE_LEFT]) { // add "tickrate" so that speed matches with diffrent frame rates
                  translateModel(points, -moveSpeed, 0, 0);
            }
            if(gKeyStates[SDL_SCANCODE_RIGHT]) {
                  translateModel(points, moveSpeed, 0, 0);
            }
            if(gKeyStates[SDL_SCANCODE_UP]) {
                  translateModel(points, 0, 0, -moveSpeed);
            }
            if(gKeyStates[SDL_SCANCODE_DOWN]) {
                  translateModel(points, 0, 0, moveSpeed);
            }
            draw(points);
      }
      close();

      return 0;
}
