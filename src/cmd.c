#include <stdint.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "main.h"

int8_t cmdpos(SDL_Window *win, char **args, uint16_t nargs)
{
	if (nargs < 2) {
		printf("'line' requires 2 arguments\n");
		return STAT_ERROR;
	}

	int32_t x = 0;
	int32_t y = 0;
	if (!strisnum(args[0])) {
		if (streq(args[0], "c") || streq(args[0], "center")) {
			x = SDL_WINDOWPOS_CENTERED;
		} else {
			printf("argument %s is invalid\n", args[0]);
			return STAT_ERROR;
		}
	} else {
		x = atoi(args[0]);
	}
	if (!strisnum(args[1])) {
		if (streq(args[1], "c") || streq(args[1], "center")) {
			x = SDL_WINDOWPOS_CENTERED;
		} else {
			printf("argument %s is invalid\n", args[1]);
			return STAT_ERROR;
		}
	} else {
		y = atoi(args[1]);
	}

	SDL_SetWindowPosition(win, x, y);

	return STAT_OK;
}

int8_t cmdsize(SDL_Window *win, char **args, uint16_t nargs)
{
	if (nargs < 2) {
		printf("'line' requires 2 arguments\n");
		return STAT_ERROR;
	}
	if (!strisnum(args[0]) || !strisnum(args[1])) {
		printf("one argument isn't a number\n");
		return STAT_ERROR;
	}

	int32_t w = atoi(args[0]);
	int32_t h = atoi(args[1]);
	SDL_SetWindowSize(win, w, h);

	return STAT_OK;
}

// TODO: code was stolen, rewrite
int8_t cmdcircle(SDL_Renderer *rend, char **args, uint16_t nargs)
{
	if (nargs < 3) {
		printf("'circle' requires 3 arguments\n");
		return STAT_ERROR;
	}
	if (!strisnum(args[0]) || !strisnum(args[1])) {
		printf("one argument isn't a number\n");
		return STAT_ERROR;
	}

	int32_t centrex = atoi(args[0]);
	int32_t centrey = atoi(args[1]);
	int32_t radius  = atoi(args[2]);

	const int32_t diameter = (radius * 2);
	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		if (bfill) {
			printf("'circle' doesn't currently support fill\n");
		} {
			SDL_RenderDrawPoint(rend, centrex + x, centrey - y);
			SDL_RenderDrawPoint(rend, centrex + x, centrey + y);
			SDL_RenderDrawPoint(rend, centrex - x, centrey - y);
			SDL_RenderDrawPoint(rend, centrex - x, centrey + y);
			SDL_RenderDrawPoint(rend, centrex + y, centrey - x);
			SDL_RenderDrawPoint(rend, centrex + y, centrey + x);
			SDL_RenderDrawPoint(rend, centrex - y, centrey - x);
			SDL_RenderDrawPoint(rend, centrex - y, centrey + x);
		}

		if (error <= 0) {
			++y;
			error += ty;
			ty += 2;
		}
		if (error > 0) {
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}

	return STAT_OK;
}

int8_t cmdclear(SDL_Renderer *rend, char **args, uint16_t nargs)
{
	SDL_RenderClear(rend);
	return STAT_OK;
}

int8_t cmdcolor(SDL_Renderer *rend, char **args, uint16_t nargs)
{
	if (nargs < 3) {
		printf("'color' requires 3 arguments\n");
		return STAT_ERROR;
	}
	if (!strisnum(args[0]) || !strisnum(args[1]) || !strisnum(args[2])) {
		printf("one argument isn't a number\n");
		return STAT_ERROR;
	}

	uint8_t r = atoi(args[0]);
	uint8_t g = atoi(args[1]);
	uint8_t b = atoi(args[2]);

	SDL_SetRenderDrawColor(rend, r, g, b, 255);

	return STAT_OK;
}

int8_t cmdcolorq(SDL_Renderer *rend, char **args, uint16_t nargs)
{
	uint8_t r, g, b;
	SDL_GetRenderDrawColor(rend, &r, &g, &b, NULL);

	printf("\t%d %d %d\n", r, g, b);

	return STAT_OK;
}

int8_t cmdfill(SDL_Renderer *rend, char **args, uint16_t nargs)
{
	if (nargs < 1) {
		printf("'line' requires 1 argument\n");
		return STAT_ERROR;
	}
	if (!strisnum(args[0])) {
		printf("argument isn't a number\n");
		return STAT_ERROR;
	}

	bfill = atoi(args[0]);

	return STAT_OK;
}

int8_t cmdfillq(SDL_Renderer *rend, char **args, uint16_t nargs)
{
	printf("\t%s\n", (bfill ? "true" : "false"));
	return STAT_OK;
}

// TODO: actually print help
int8_t cmdhelp(SDL_Renderer *rend, char **args, uint16_t nargs)
{
	printf("read the README you dum dum\n");
	return STAT_OK;
}

int8_t cmdline(SDL_Renderer *rend, char **args, uint16_t nargs)
{
	if (nargs < 4) {
		printf("'line' requires 4 arguments\n");
		return STAT_ERROR;
	}
	if (!strisnum(args[0]) || !strisnum(args[1]) || !strisnum(args[2]) ||!strisnum(args[3])) {
		printf("one argument isn't a number\n");
		return STAT_ERROR;
	}

	uint32_t x1 = atoi(args[0]);
	uint32_t y1 = atoi(args[1]);
	uint32_t x2 = atoi(args[2]);
	uint32_t y2 = atoi(args[3]);

	SDL_RenderDrawLine(rend, x1, y1, x2, y2);

	return STAT_OK;
}

int8_t cmdpoint(SDL_Renderer *rend, char **args, uint16_t nargs)
{
	if (nargs < 2) {
		printf("'line' requires 2 arguments\n");
		return STAT_ERROR;
	}
	if (!strisnum(args[0]) || !strisnum(args[1])) {
		printf("one argument isn't a number\n");
		return STAT_ERROR;
	}

	uint32_t x = atoi(args[0]);
	uint32_t y = atoi(args[1]);

	SDL_RenderDrawPoint(rend, x, y);

	return STAT_OK;
}

int8_t cmdrect(SDL_Renderer *rend, char **args, uint16_t nargs)
{
	if (nargs < 4) {
		printf("'rect' requires 4 arguments\n");
		return STAT_ERROR;
	}
	if (!strisnum(args[0]) || !strisnum(args[1]) || !strisnum(args[2]) ||!strisnum(args[3])) {
		printf("one argument isn't a number\n");
		return STAT_ERROR;
	}

	uint32_t x = atoi(args[0]);
	uint32_t y = atoi(args[1]);
	uint32_t w = atoi(args[2]);
	uint32_t h = atoi(args[3]);

	SDL_Rect rect = {
		.x = x, .y = y,
		.w = w, .h = h
	};

	if (bfill) {
		SDL_RenderFillRect(rend, &rect);
	} else {
		SDL_RenderDrawRect(rend, &rect);
	}

	return STAT_OK;
}

int8_t cmdwait(SDL_Renderer *rend, char **args, uint16_t nargs)
{
	if (nargs < 1) {
		printf("'line' requires 1 arguments\n");
		return STAT_ERROR;
	}
	if (!strisnum(args[0])) {
		printf("argument isn't a number\n");
		return STAT_ERROR;
	}

	uint32_t ms = atoi(args[0]);
	SDL_Delay(ms);

	return STAT_OK;
}
