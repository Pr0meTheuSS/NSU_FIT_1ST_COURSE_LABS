#pragma once
#include "Stack.h"
#include "Token.h"
#include <string.h>
#include <ctype.h>

ETokenStatus GetRPNStack(char* str, TStack* RPNStack);

ETokenStatus RPNCalc(char* inputString, int* result);

