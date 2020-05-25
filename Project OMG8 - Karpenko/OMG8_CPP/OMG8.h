#pragma once
#include <vector>
#include <iostream>
#include "time.h"

class OMG8
{
private:
	std::vector<uint64_t> symbols;
public:
	OMG8();
	OMG8(int n);
	OMG8(std::vector<uint64_t>& str);
	OMG8(std::vector<unsigned char>& str);

	std::vector<unsigned char> encode();
	void decode(std::vector<unsigned char>& bytes);

	void add(int index, OMG8& str);
	void add(int index, uint64_t symb);
	OMG8 cut(int ind1, int ind2);
	int find(OMG8& str);

	void print();
	void print(std::ostream* out);
	void read(int len);
	void read(std::istream* in, int len);

	uint64_t toInt(uint64_t dim);
	void fromInt(uint64_t n, uint64_t dim);

	int size();
	uint64_t& operator[](int ind);
};

