#pragma once
#include <string>

#define COLOR_Default       39
#define COLOR_Black         30
#define COLOR_Red           31
#define COLOR_Green         32
#define COLOR_Yellow        33
#define COLOR_Blue          34
#define COLOR_Magenta       35
#define COLOR_Cyan          36
#define COLOR_Light_Gray    38
#define COLOR_Dark_Gray     90
#define COLOR_Light_Red     91
#define COLOR_Light_Green   92
#define COLOR_Light_Yellow  93
#define COLOR_Light_Blue    94
#define COLOR_Light_Magenta 95
#define COLOR_Light_Cyan    96
#define COLOR_White         97

std::string to_ansi_escape(int code);