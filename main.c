#include "main.h"

int main()
{
	const char* base_path = SDL_GetBasePath();
	const char* vertpath = strapp(base_path, "assets/shaders/shader.vert");
	const char* fragpath = strapp(base_path, "assets/shaders/shader.vert");
	const char* vertshader = readFile(vertpath);
	const char* fragshader = readFile(fragpath);

	int width = 800;
	int height = 600;
	int sdlFlags = SDL_WINDOW_OPENGL;

	int sdlInit = SDL_Init(SDL_INIT_VIDEO);
	if (sdlInit < 0) {
		fprintf(stderr, "SDL couldn't initialize - %s\n", SDL_GetError());
		endProgram(1);
	}

	SDL_Window* window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, sdlFlags);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	if (window == 0) {
		fprintf(stderr, "SDL_Window failed - %s\n", SDL_GetError());
		endProgram(1);
	}

	unsigned int* VAO = malloc(sizeof(unsigned int));
	unsigned int* shaderProgram = malloc(sizeof(unsigned int));

	char* glStatus = initOpenGL(vertshader, fragshader, VAO, shaderProgram);

	int doLoop = 1;

	if (glStatus != NULL) {
		fprintf(stderr, "Failure - OpenGL shaders couldn't initialize - %s\n", glStatus);
		doLoop = 0;
		return 1;
	}

	SDL_Event event;

	while (doLoop != 0)
	{
		doLoop = handleInput(event);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, width, height);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(glcontext);
	endProgram(0);
	return 0;
}
