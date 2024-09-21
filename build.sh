eval cc src/main.cpp -o a.out -framework IOKit -framework Cocoa -framework OpenGL $(pkg-config --libs --cflags raylib) --std=c++11
