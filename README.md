# Good Towar Dafance
A Open Source Tower Defence Game
*Typos in the name are voluntary*

This game is in W.I.P. to build you'll need SDL2 and SDL Image; no released will be made until tech demo

# Contribute
to contribute you can download the code using git or by zip
FOR VISUAL STUDIO:
  download the code and set under VC++ Directories the include directory and the library directory then go to Linker/Input and add:
    - SDL2main.lib
    - SDL2.lib
    - SDL2_image.lib
FOR LINUX | MINGW W64
  download the code and for compiling do that command:
    g++ -o bin/main (.exe if windows) main.cpp -I (include dir) -L (lib dir) -lSDL2main -lSDL2 -lSDL2_image -lmingw32 (only if using mingw w64)
