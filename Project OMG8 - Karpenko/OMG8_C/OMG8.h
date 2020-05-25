#pragma once
#include <stdio.h>

typedef struct OMG8 {
	int len;
	unsigned long long *string;
} OMG8;

OMG8 createOMG8(int len);
OMG8 copy(OMG8* str);

void scan(OMG8* str, int len, FILE* in);
void print(OMG8* str, FILE* out);

void add(OMG8* str1, int ind, unsigned long long val);
void addS(OMG8* str1, int ind, OMG8* str2);

OMG8 cut(OMG8* str, int ind1, int ind2);

int find(OMG8* str1, OMG8* str2);

long long toInt(OMG8* str1, int dim);
OMG8 fromInt(int n, int dim);

unsigned char* encode(OMG8* str, int* size);
OMG8 decode(unsigned char* str, int size);