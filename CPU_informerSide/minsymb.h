/********************************************************
*
* CPU INFORMER is GPLv3 licenced source code.
*
* (C) Vertver, 2018
*
* CPU INFORMER Source Code is free software:
* You can redistribute it and/or modify it.
*
* minsymb.h - includes defines
*
*********************************************************/

#pragma once

#define CONSOLE_RED(X)			printf("%s %s %s",RED_CONSOLE_COLOR,	X,RESET_CONSOLE_COLOR)
#define CONSOLE_YELLOW(X)		printf("%s %s %s",YELLOW_CONSOLE_COLOR,	X,RESET_CONSOLE_COLOR)
#define CONSOLE_BLUE(X)			printf("%s %s %s",BLUE_CONSOLE_COLOR,	X,RESET_CONSOLE_COLOR)
#define CONSOLE_GREEN(X)		printf("%s %s %s",GREEN_CONSOLE_COLOR,	X,RESET_CONSOLE_COLOR)
#define CONSOLE_CYAN(X)			printf("%s %s %s",CYAN_CONSOLE_COLOR,	X,RESET_CONSOLE_COLOR)

#define RESET_CONSOLE_COLOR			"\033[0m\\]"
#define BLACK_CONSOLE_COLOR			"\033[22; 30m\\]"
#define RED_CONSOLE_COLOR			"\033[22; 31m\\]"
#define GREEN_CONSOLE_COLOR			"\033[22; 32m\\]"
#define BROWN_CONSOLE_COLOR			"\033[22; 33m\\]"
#define BLUE_CONSOLE_COLOR			"\033[22; 34m\\]"
#define MAGENTA_CONSOLE_COLOR		"\033[22; 35m\\]"
#define CYAN_CONSOLE_COLOR			"\033[22; 36m\\]"
#define GRAY_CONSOLE_COLOR			"\033[22; 37m\\]"
#define DARKGRAY_CONSOLE_COLOR		"\033[01; 30m\\]"
#define LIGHTRED_CONSOLE_COLOR		"\033[01; 31m\\]"
#define LIGHTGREEN_CONSOLE_COLOR	"\033[01; 32m\\]"
#define YELLOW_CONSOLE_COLOR		"\033[01; 33m\\]"
#define LIGHTBLUE_CONSOLE_COLOR		"\033[01; 34m\\]"
#define LIGHTMAGENTA_CONSOLE_COLOR	"\033[01; 35m\\]"
#define LIGHTCYAN_CONSOLE_COLOR		"\033[01; 36m\\]"
#define WHITE_CONSOLE_COLOR			"\033[01; 37m\\]"

#define CXX 199711L