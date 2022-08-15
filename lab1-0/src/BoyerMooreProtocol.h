#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#define ALPHABET_SIZE 256
#define TEMPLATE_MAX_LEN 17

void BoyerMooreProtocol(FILE* in, unsigned char template[TEMPLATE_MAX_LEN]);
