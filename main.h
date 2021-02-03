#ifndef _MAIN_H
#define _MAIN_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

void endProgram(int);
void handleKeys(SDL_Keysym*);
void handleEvents();
void renderOpenGL(unsigned int, unsigned int);
void setupOpenGL(const char*, const char*, unsigned int*, unsigned int*);
void resizeOpenGL(int, int);
SDL_Window* createWindow(int, int, int);
char* readFile(const char*);

#endif // _MAIN_H
