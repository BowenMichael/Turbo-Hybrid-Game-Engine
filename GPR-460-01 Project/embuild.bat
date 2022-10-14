rem build html
emcc -I./include/ ./GPR-460-01-Project.cpp source/emscripten/System_Emscripten.cpp ./source/GameObject.cpp ./source/Components/PlayerController.cpp ./source/Components/RectangleCollider.cpp ./source/Components/RectangleRenderer.cpp ./source/Components/Transform.cpp   -sUSE_SDL=2 -o ./build/index.html
if NOT "%ERRORLEVEL%"=="0" EXIT /B %ERRORLEVEL%


