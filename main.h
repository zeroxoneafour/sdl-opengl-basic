#ifndef _MAIN_H
#define _MAIN_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void endProgram(int code);
char* readFile(const char* filename);
char* strapp(const char* str1, const char* str2);
int handleInput(SDL_Event event);
int handleKeys(SDL_Keysym* keysym);

int initOpenGL(const char* vertshader, const char* fragshader, unsigned* VAO, unsigned* shaderProgram);

#endif // _MAIN_H
