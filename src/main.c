#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <SDL2/SDL.h>

enum return_status {
	STAT_EXIT     = -1,
	STAT_CONTINUE =  0,
	STAT_ERROR   =   1
};

// TODO: code was stolen, rewrite
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

void printhelp(void)
{
	printf("read the README you dum dum\n");
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

int8_t parseline(SDL_Renderer *rend, char *line)
{
#define streq(str1, str2) (!strcmp(str1, str2))

	uint32_t nargs = 0;
	char **toks = tokenize(line, &nargs);
	char  *cmd = toks[0];
	char **args = toks + 1;

	if (streq(cmd, "exit")) {
		return STAT_EXIT;
	} else if (streq(cmd, "help")) {
		printhelp();
	} else if (streq(cmd, "clear")) {
		SDL_RenderClear(rend);
	} else if (streq(cmd, "wait")) {
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
	} else if (streq(cmd, "point")) {
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
	} else if (streq(cmd, "line")) {
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
	} else if (streq(cmd, "color")) {
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
	} else if (streq(cmd, "nop")) {
	} else {
		printf("unknown command: %s\n", cmd);
	}

	return 0;
}

int main(void)
{
	char *line = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *win = SDL_CreateWindow("graser", 0, 0, 800, 600, 0);
	SDL_Renderer *rend = SDL_CreateRenderer(win, -1, 0);

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	SDL_RenderClear(rend);
	SDL_RenderPresent(rend);

	bool running = true;
	while (running) {
		SDL_Event ev = {0};
		SDL_PollEvent(&ev);

		switch (ev.type) {
		case SDL_QUIT:
			running = false;
			break;
		default:
			break;
		}

		line = readline("> ");
		int8_t status = parseline(rend, line);
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
