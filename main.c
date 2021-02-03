#include "main.h"

int main() {
	glewExperimental = GL_TRUE;
	glewInit();

	char* shader_path = SDL_GetBasePath();
	strcat(shader_path, "assets/shaders/shader.vert");
	char* vertshader = readFile(shader_path);
	char* fragshader_path = SDL_GetBasePath();
	strcat(fragshader_path, "assets/shaders/shader.frag");
	char* fragshader = readFile(fragshader_path);

	int width = 640;
	int height = 480;
	int sdlFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	SDL_Window* window = createWindow(width, height, sdlFlags);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	unsigned int* shaderProgram = NULL;
	unsigned int* VAO = NULL;

	setupOpenGL(vertshader, fragshader, VAO, shaderProgram);
	glViewport(0, 0, width, height);

	while (1) {
		handleEvents(window);
		
		renderOpenGL(*shaderProgram, *VAO);

		SDL_GL_SwapWindow(window);

		SDL_Delay(50);
	}

	return 0;
}
