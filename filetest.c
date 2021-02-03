#include "main.h"

int main ()
{
	char* filepath = SDL_GetBasePath();

	strcat(filepath, "assets/shaders/shader.vert");

	char* file = readFile(filepath);

	printf("%s", file);

	return 0;
}
