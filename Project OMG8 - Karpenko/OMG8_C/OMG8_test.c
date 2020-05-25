#include <stdio.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdlib.h>

#include "OMG8.h"

int main(int argc, char** argv){
	FILE* in = stdin;
	FILE* out = stdout;

	if (argc > 2){
		in = fopen(argv[1], "r");
		out = fopen(argv[2], "w");
	}
	
	int n1, n2;
	OMG8 str1, str2, str3;
	int size;
	unsigned long long val;
	int ind1, ind2;

	fprintf(out, "Enter length n1, n2 and two sets of numbers with such length:\n");
	fscanf(in, "%d%d", &n1, &n2);
	scan(&str1, n1, in);
	scan(&str2, n2, in);
	fprintf(out, "Two strings:\n");
	print(&str1, out);
	print(&str2, out);
	fprintf(out, "\n");

	
	fprintf(out, "enter index and value\n");
	fscanf(in, "%d%llu", &ind1, &val);
	fprintf(out, "first string, add %llu to index %d\n", val, ind1);
	str3 = copy(&str1);
	add(&str3, ind1, val);
	print(&str3, out);
	fprintf(out, "\n");

	fprintf(out, "enter index and value\n");
	fscanf(in, "%d%llu", &ind1, &val);
	fprintf(out, "first string, replace by %llu on index %d\n", val, ind1);
	free(str3.string);
	str3 = copy(&str1);
	str3.string[ind1] = val;
	print(&str3, out);
	fprintf(out, "\n");

	fprintf(out, "enter index\n");
	fscanf(in, "%d", &ind1);
	fprintf(out, "add second string to first string on index %d\n", ind1);
	free(str3.string);
	str3 = copy(&str1);
	addS(&str3, ind1, &str2);
	print(&str3, out);
	fprintf(out, "\n");

	fprintf(out, "find second (return first index where meet second string in first)\n%d\n\n", find(&str1, &str2));

	fprintf(out, "enter index1 and index2\n");
	fscanf(in, "%d%d", &ind1, &ind2);
	free(str3.string);
	str3 = cut(&str1, ind1, ind2);
	fprintf(out, "cut first string from index %d to %d\n", ind1, ind2);
	print(&str3, out);
	fprintf(out, "\n");

	
	fprintf(out, "encode first string\n");
	unsigned char* bytes = encode(&str1, &size);
	for (int i = 0; i < size; i++)
		fprintf(out, "%d ", (int)bytes[i]);
	fprintf(out, "\n\n");

	fprintf(out, "decode next bytes\n");
	for (int i = 0; i < size; i++)
		fprintf(out, "%d ", (int)bytes[i]);
	fprintf(out, "\n");
	free(str3.string);
	str3 = decode(bytes, size);
	print(&str3, out);
	fprintf(out, "\n");

	fprintf(out, "2 : %lld\n", toInt(&str1, 2));
	fprintf(out, "10 : %lld\n", toInt(&str1, 10));
	fprintf(out, "16 : %lld\n", toInt(&str1, 16));

	if (toInt(&str1, 10) > 0){
		free(str3.string);
		str3 = fromInt(toInt(&str1, 10), 2);
		fprintf(out,"\nstr1 is number, binary:\n");
		print(&str3, out);
	}
}
