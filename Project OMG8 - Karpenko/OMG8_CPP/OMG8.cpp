#include "OMG8.h"

OMG8::OMG8() {
	symbols = std::vector<uint64_t>(0);
}

OMG8::OMG8(int n) {
	symbols = std::vector<uint64_t>(n);
}

OMG8::OMG8(std::vector<uint64_t>& str) {
	symbols = str;
}

OMG8::OMG8(std::vector<unsigned char>& str) {
	decode(str);
}

std::vector<unsigned char> OMG8::encode() {
	int len = 0;
	unsigned char buf;
	uint64_t k;
	std::vector<unsigned char> rez;
	for (int i = 0; i < symbols.size(); i++) {
		k = symbols[i];
		if (symbols[i] == 0)
			len++;
		while (k > 0) {
			k /= 128;
			len++;
		}
	}

	rez = std::vector<unsigned char>(len);
	int t = 0;

	for (int i = 0; i < symbols.size(); i++) {
		k = symbols[i];
		while (true) {
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
	return rez;
}

void OMG8::decode(std::vector<unsigned char>& bytes) {
	int len = 0;
	for (int i = 0; i < bytes.size(); i++) {
		if ((bytes[i] & 128) == 0)
			len++;
	}
	symbols = std::vector<uint64_t>(len);
	int t = 0;
	uint64_t k = 1;

	for (int i = 0; i < bytes.size(); i++) {
		symbols[t] += (k * bytes[i]);
		k *= 128;

		if ((bytes[i] & 128) == 0) {
			t++;
			k = 1;
		}
	}
}

void OMG8::print() {
	for (int i = 0; i < symbols.size(); i++)
		std::cout << symbols[i] << " ";
	std::cout << std::endl;
}

void OMG8::print(std::ostream* out) {
	for (int i = 0; i < symbols.size(); i++)
		*out << symbols[i] << " ";
	*out << std::endl;
}

void OMG8::read(int len) {
	symbols = std::vector<uint64_t>(len);
	for (int i = 0; i < len; i++)
		std::cin >> symbols[i];
}

void OMG8::read(std::istream* in, int len) {
	symbols = std::vector<uint64_t>(len);
	for (int i = 0; i < len; i++)
		*in >> symbols[i];
}

int OMG8::size() {
	return symbols.size();
}

uint64_t& OMG8::operator[](int ind) {
	return symbols[ind];
}

OMG8 OMG8::cut(int ind1, int ind2) {
	OMG8 rez = OMG8(ind2 - ind1);

	for (int i = ind1; i < ind2; i++)
		rez[i - ind1] = symbols[i];

	return rez;
}

int OMG8::find(OMG8& str) {
	for (int i = 0; i + str.size() < symbols.size(); i++) {
		for (int j = 0; j < str.size(); j++) {
			if (str[j] != symbols[i + j])
				break;
			if (j == str.size() - 1)
				return i;
		}
	}
	return -1;
}

void OMG8::add(int index, OMG8& str) {
	std::vector<uint64_t> buf = symbols;
	symbols = std::vector<uint64_t>(buf.size() + str.size());
	for (int i = 0; i < index; i++) {
		symbols[i] = buf[i];
	}
	for (int j = 0; j < str.size(); j++) {
		symbols[index + j] = str[j];
	}
	for (int i = index; i < buf.size(); i++) {
		symbols[i + str.size()] = buf[i];
	}
}

void OMG8::add(int index, uint64_t symb) {
	std::vector<uint64_t> buf = symbols;
	symbols = std::vector<uint64_t>(buf.size() + 1);
	for (int i = 0; i < index; i++) {
		symbols[i] = buf[i];
	}
	symbols[index] = symb;
	for (int i = index; i < buf.size(); i++) {
		symbols[i + 1] = buf[i];
	}
}

uint64_t OMG8::toInt(uint64_t dim){
	uint64_t t = 0;
	for (int i = 0; i < symbols.size(); i++){
		if (symbols[i] >= dim){
			return -1;
		}
		t *= dim;
		t += symbols[i];
	}
	return t;
}

void OMG8::fromInt(uint64_t n, uint64_t dim){
	uint64_t k = n;
	int len = 0;
	while (k > 0) {
		len++;
		k/=dim;
	}
	if (len == 0)
		len = 1;
	symbols = std::vector<uint64_t>(len);
	k = n;
	for (int i = len - 1; i >= 0; i--){
		symbols[i] = k % dim;
		k /= dim;
	}
}
