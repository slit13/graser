#pragma once

#include <stdbool.h>

#define streq(str1, str2) (!strcmp(str1, str2))

enum return_status {
	STAT_EXIT  = -1,
	STAT_OK    =  0,
	STAT_ERROR =  1
};

extern bool bfill;

bool strisnum(char *s);
