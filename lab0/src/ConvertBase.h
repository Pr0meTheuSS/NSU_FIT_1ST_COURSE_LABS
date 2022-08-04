#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Number.h" 

void BadInput();

int IsValidNumberFormat(char* numb_str, int base);

void ConvertFromBaseToBase(char* numb_str, int fromBase, int toBase, char Res[128]);
