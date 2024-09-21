
eval cc main.cpp -framework IOKit -framework Cocoa -framework OpenGL $(pkg-config --libs --cflags raylib) -o raylib-pong-cpp --std=c++11
