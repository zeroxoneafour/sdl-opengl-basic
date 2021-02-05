### sdl2-opengl-basic

despite the name, this example is not really basic.

`gcc main.c opengl.c functions.c -lSDL2 -lGLEW -lGL -ggdb -o sdl_opengl_basic`   
`./sdl_opengl_basic`  

### changelog

#### also 2/05/2020
Hey, no segfault anymore! I'm glad to report this code is now not leaking large chunks of memory all over the place. Still doesn't render... but that's ok for now.

#### 2/05/2020   
filetest.c is now OBSOLETE. It does not use the newly defined functions and leaks memory BADLY. Funnily enough that memory leak isn't the source of the segfault...
