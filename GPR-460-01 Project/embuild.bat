rem build html
emcc -I./include/ ./GPR-460-01-Project.cpp source/emscripten/System_Emscripten.cpp -sUSE_SDL=2 -o ./../docs/index.html