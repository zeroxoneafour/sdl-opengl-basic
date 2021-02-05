### sdl2-opengl-basic

despite the name, this example is not really basic.

`gcc -lSDL2 -lGLEW -lGL -ggdb main.c function.c -o sdl_opengl_basic`  
`./sdl_opengl_basic`  
Currently ends in segfault :\

### changelog

filetest.c is now OBSOLETE. It does not use the newly defined functions and leaks memory BADLY. Funnily enough that memory leak isn't the source of the segfault...
