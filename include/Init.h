#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "TypeDefinitions.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

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

#endif