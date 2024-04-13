#pragma once
#include "common.h"

namespace utils {
void strcpyn(char* dest, uint8_t destSize, const char* src);
void swap(char *a, char *b);
void reverse(char *str, int length);
char* itoa(int val);
}