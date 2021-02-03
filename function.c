#include "main.h"

void endProgram(int code)
{
	SDL_Quit();
	exit(code);
}

void resizeOpenGL(int width, int height)
{
	glViewport(0, 0, width, height);
}

SDL_Window* createWindow(int width, int height, int sdlFlags) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Failure, SDL error - %s\n", SDL_GetError());
		endProgram(1);
	}

	SDL_Window* window =
	    SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED,
			     SDL_WINDOWPOS_UNDEFINED, width, height, sdlFlags);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	if (window == 0) {
		fprintf(stderr, "Failure, SDL error - %s\n", SDL_GetError());
		endProgram(1);
	}

	return window;
}

void handleKeys(SDL_Keysym* keysym)
{
	switch (keysym->sym)
	{
		case SDLK_ESCAPE:
			endProgram(0);
			break;
		default:
			break;
	}
}

void handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				handleKeys(&event.key.keysym);
			case SDL_QUIT:
				endProgram(0);
				break;
			case SDL_WINDOWEVENT_RESIZED:
				resizeOpenGL(event.window.data1, event.window.data2);
			default:
				break;
		}
	}
}

void setupOpenGL(const char* vshader, const char* fshader, unsigned int* VAO, unsigned int* shaderProgram)
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar* const*)vshader, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar* const*)fshader, NULL);
	glCompileShader(fragmentShader);

	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = 
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int* VBO;
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

char* readFile(const char* file) {
	SDL_RWops* rw = SDL_RWFromFile(file, "rb");
	if (rw == NULL) return NULL;
	int size = SDL_RWsize(rw);
	char* ret = malloc(size + 1);
	char* buf = ret;

	for (int i = 0; i < size; i = (i+1))
	{
		SDL_RWread(rw, buf, sizeof(char), i);
		buf += i;
	}
	SDL_RWclose(rw);
	ret[size+1] = '\0';
	return ret;
}

void renderOpenGL(unsigned int program, unsigned int vao)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
