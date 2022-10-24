rem build html
emcc -I./include/ .\GPR-460-01-Project.cpp ./source/ ./source/emscripten/ ./source/Components ./source -sUSE_SDL=2 -o ./build/index.html
if NOT "%ERRORLEVEL%"=="0" EXIT /B %ERRORLEVEL%


