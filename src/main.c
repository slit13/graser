#include <SDL2/SDL_events.h>
#include <bits/pthreadtypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <SDL2/SDL.h>
#include "cmd.h"
#include "main.h"

bool bfill = 0;

// TODO: code was stolen, rewrite it
char **tokenize(char *line, uint32_t *n)
{
#define BUFSZ 64
	uint32_t bufsize = BUFSZ;
	uint32_t position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens) {
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " ");
	while (token != NULL) {
		tokens[position] = token;
		position++;

		if (position >= bufsize) {
			bufsize += BUFSZ;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " ");
	}
	tokens[position] = NULL;
	*n = position;
	return tokens;
}

bool strisnum(char *s)
{
	uint32_t len = strlen(s);
	for (uint32_t i = 0; i < len; i++) {
		if (!(s[i] > '0' - 1 && s[i] < '9' + 1)) {
			return false;
		}
	}

	return true;
}

int8_t parseline(SDL_Window *win, SDL_Renderer *rend, char *line)
{
	uint32_t nargs = 0;
	char **toks = tokenize(line, &nargs);
	char  *cmd = toks[0];
	char **args = toks + 1;

	if (streq(cmd, "exit")) {
		return STAT_EXIT;
	} else if (streq(cmd, "pos")) {
		return cmdpos(win, args, nargs);
	} else if (streq(cmd, "size")) {
		return cmdsize(win, args, nargs);
	} else if (streq(cmd, "clear")) {
		return cmdclear(rend, args, nargs);
	} else if (streq(cmd, "color")) {
		return cmdcolor(rend, args, nargs);
	} else if (streq(cmd, "color?")) {
		return cmdcolorq(rend, args, nargs);
	} else if (streq(cmd, "fill")) {
		return cmdfill(rend, args, nargs);
	} else if (streq(cmd, "fill?")) {
		return cmdfillq(rend, args, nargs);
	} else if (streq(cmd, "help")) {
		return cmdhelp(rend, args, nargs);
	} else if (streq(cmd, "line")) {
		return cmdline(rend, args, nargs);
	} else if (streq(cmd, "nop")) {
		return STAT_OK;
	} else if (streq(cmd, "point")) {
		return cmdpoint(rend, args, nargs);
	} else if (streq(cmd, "rect")) {
		return cmdrect(rend, args, nargs);
	} else if (streq(cmd, "wait")) {
		return cmdwait(rend, args, nargs);
	} else {
		printf("unknown command: %s\n", cmd);
	}

	return STAT_OK;
}

// TODO: handle arguments
int main(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *win = SDL_CreateWindow("graser", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	SDL_Renderer *rend = SDL_CreateRenderer(win, -1, 0);

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	SDL_RenderClear(rend);
	SDL_RenderPresent(rend);
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

	char *line = NULL;
	bool running = true;
	while (running) {
		line = readline("> ");
		int8_t status = parseline(win, rend, line);
		if (status == STAT_EXIT) {
			running = false;
		} else if (status == STAT_ERROR) {
			printf("what did you try to do?\n");
		}

		SDL_RenderPresent(rend);
	}

	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(rend);
	SDL_Quit();

	return 0;
}
