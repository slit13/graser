#pragma once

#include <SDL2/SDL.h>

#define defwincmd(name)  int8_t cmd##name(SDL_Window   *win,  char **args, uint16_t nargs)
#define defrendcmd(name) int8_t cmd##name(SDL_Renderer *rend, char **args, uint16_t nargs)

defwincmd(pos);
defwincmd(size);

defrendcmd(clear);
defrendcmd(color);
defrendcmd(colorq);
defrendcmd(fill);
defrendcmd(fillq);
defrendcmd(help);
defrendcmd(line);
defrendcmd(point);
defrendcmd(rect);
defrendcmd(wait);
