# Gusto Engine
This is a game-engine made in OpenGL.

## Running the engine
To run the engine, go to the bin folder, and run the executable game file.

Or in the terminal, go to the folder where this repo is cloned into, and enter these commands into the terminal:
```
cd bin
./game
```

### For people using old computers(like me)
If your graphics driver doesn't support OpenGL 3.3 or higher, this might make it work:
```
cd bin
export MESA_GL_VERSION_OVERRIDE=3.3
LIBGL_ALWAYS_SOFTWARE=1 ./game
```

## Compiling the code
The code is pre-compiled into the game executable file, but if you maybe want to change the code, recompile it with the following commands:
```
cd bin
cmake ..
make
./game
```
