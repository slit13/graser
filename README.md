# TODO: complete redesign and rewrite

# graser - GRAphics command parSER

Write commands, see them

## Building
Make sure you have SDL2 and GNU readline installed.

```
$ make
```

## Commands
```
window:
	pos  x y - set window position to x, y
	size w h - set window size     to w, h
renderer:
	clear             - fill the screen with color
	color  r  g  b    - set the drawing color
	color?            - query the drawing color
	exit              - exit
	fill   t          - set whether shapes will be filled or not, C style boolean
	fill?             - query fill, true or false
	help              - print help
	line  x1 y1 x2 y2 - draw a line
	nop               - do nothing
	point  x  y       - draw a single point/pixel
	rect   x  y  w  h - draw a rectangle, fill is determined by `fill`
	wait   n          - wait n miliseconds
```
