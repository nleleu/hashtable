#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdio.h>

typedef struct buffer_s
{
    char* data;
    size_t len;
}buffer_Ts;

uint32_t murmur3_32(const char *key, uint32_t len, uint32_t seed);

#endif