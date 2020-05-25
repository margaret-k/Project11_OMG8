#include "OMG8.h"
#include <stdio.h>
#include <stdlib.h>

OMG8 createOMG8(int len){
	OMG8 str;
	str.len = len;
	str.string = (unsigned long long*)malloc(len * sizeof(unsigned long long));
	for (int i = 0; i < len; i++)
		str.string[i] = 0;
	return str;
}

OMG8 copy(OMG8* str){
	OMG8 rez = createOMG8(str->len);
	
	for (int i = 0; i < str->len; i++){
		rez.string[i] = str->string[i];
	} 

	return rez;
}

void scan(OMG8* str, int len, FILE* in){
	*str = createOMG8(len);
	for (int i = 0; i < len; i++)
    	fscanf(in, "%lld", str->string + i);
}

void print(OMG8* str, FILE* out){
	for (int i = 0; i < str->len; i++)
    	fprintf(out, "%llu ", str->string[i]);
    fprintf(out, "\n");
}

void add(OMG8* str1, int ind, unsigned long long val){
	unsigned long long *string = (unsigned long long*)malloc((str1->len + 1) * sizeof(unsigned long long));
	
	for (int i = 0; i < ind; i++)
		string[i] = str1->string[i];
	string[ind] = val;

	for (int i = ind; i < str1->len; i++)
		string[i + 1] = str1->string[i];

	free(str1->string);
	str1->string = string;
	str1->len ++; 
}

void addS(OMG8* str1, int ind, OMG8* str2){
	unsigned long long *string = (unsigned long long*)malloc((str1->len + str2->len) * sizeof(unsigned long long));

	for (int i = 0; i < ind; i++)
		string[i] = str1->string[i];
	
	for (int i = 0; i < str2->len; i++)
		string[ind + i] = str2->string[i];

	for (int i = ind; i < str1->len; i++)
		string[i + str2->len] = str1->string[i];
		
	free(str1->string);
	str1->string = string;
	str1->len += str2->len; 
}

OMG8 cut(OMG8* str, int ind1, int ind2){
	OMG8 rez;
	rez = createOMG8(ind2 - ind1);

	for (int i = ind1; i < ind2; i++)
		rez.string[i - ind1] = str->string[i];
	
	return rez;
}

int find(OMG8* str1, OMG8* str2){
	if (str1->len < str2->len)
		return -1;
	for (int i = 0; i <= str1->len - str2->len; i++){
		for (int j = 0; j < str2->len; j++){
			if (str1->string[i + j] != str2->string[j])
				break;
			if (j + 1 == str2 -> len)
				return i;
		}
	}
	return -1;
}

unsigned char* encode(OMG8* str, int* size){
	int len = 0;
	unsigned char buf;
	unsigned long long k;
	for (int i = 0; i < str->len; i++) {
		k = str->string[i];
		if (str->string[i] == 0)
			len++;
		while (k > 0) {
			k /= 128;			
			len++;
		}
	}

	unsigned char* rez = (unsigned char*)malloc(len * sizeof(char));
	int t = 0;

	for (int i = 0; i < str->len; i++) {
		k = str->string[i];
		while (1) {
			buf = k & 127;
			if (k < 128) {
				rez[t++] = buf;
				break;
			}
			else {
				rez[t++] = buf + 128;
				k -= buf + 128;
				k /= 128;
			}
		}
	}
	*size = len;
	return rez;
}

OMG8 decode(unsigned char* bytes, int size){
	int len = 0;
	for (int i = 0; i < size; i++) {
		if ((bytes[i] & 128) == 0)
			len++;
	}
	
	OMG8 rez = createOMG8(len);
	int t = 0;
	unsigned long long k = 1;

	for (int i = 0; i < size; i++) {
		rez.string[t] += (k * bytes[i]);
		k *= 128;

		if ((bytes[i] & 128) == 0) {
			t++;
			k = 1;
		}
	}
	return rez;
}

long long toInt(OMG8* str1, int dim){
	long long t = 0;
	for (int i = 0; i < str1->len; i++){
		if (str1->string[i] >= dim){
			return -1;
		}
		t *= dim;
		t += str1->string[i];
	}
	return t;
}

OMG8 fromInt(int n, int dim){
	unsigned long long k = n;
	int len = 0;
	while (k > 0) {
		len++;
		k/=dim;
	}
	if (len == 0)
		len = 1;
	OMG8 rez = createOMG8(len);
	k = n;
	for (int i = len - 1; i >= 0; i--){
		rez.string[i] = k % dim;
		k /= dim;
	}
	return rez;
}