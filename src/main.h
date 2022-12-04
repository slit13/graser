#pragma once

#include <stdbool.h>

enum return_status {
	STAT_EXIT  = -1,
	STAT_OK    =  0,
	STAT_ERROR =  1
};

extern bool bfill;

bool strisnum(char *s);
