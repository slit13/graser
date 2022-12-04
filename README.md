# graser - GRAphics command parSER

Write commands, see them

## Building
Make sure you have SDL2 and GNU readline installed.

```
$ make
```

## Commands
```
color  r  g  b    - set the drawing color, SDL_SetRenderDrawColor
clear             - fill the screen with color, SDL_RenderClear
nop               - do nothing
wait   n          - wait n seconds
line  x1 y1 x2 y2 - draw a line
exit              - exit
```
