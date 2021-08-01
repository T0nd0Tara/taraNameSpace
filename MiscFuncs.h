#pragma once

#include "Headers.h"

template <typename T>
inline T dotProd(std::vector<T>* a, std::vector<T>* b) {
	if (a->size() != b->size()) {
		throw std::invalid_argument("Cannot do dot product with to different sized arrays");
		std::cout << "An 'std::invalid_argument' error has occured in dotProd.\n";
		return 0.0f;
	}

	T sum = (T)0;
	for (int i = 0; i < (a->size()); i++)
		sum += (*a)[i] * (*b)[i];

	return sum;
}

template <typename T>
inline void dotProd(std::vector<T>* a, std::vector<T>* b, int size, T* out) {
	for (int i = 0; i < size; i++) {
		*out = dotProd(a, b);
		out++;
		a++;
	}
}

template <typename T>
inline void vecToArr(std::vector<T>* in, T* out) {
	for (int i = 0; i < in->size(); i++) {
		out[i] = (*in)[i];
	}
}

template <typename T>
inline int len(T);

inline std::string addSpace(int);

template <typename T>
inline std::string arrToString(T* in, int size) { // doesn't drop
	std::string out = "{";
	for (int i = 0; i < size; i++) {
		out += std::to_string(*in);
		in++;
		if (i + 1 != size)
			out += ',' + addSpace(11 - len(in[i + 1]));
	}
	out += '}';
	return out;
}


template <typename T>
inline std::string arrToString(T* in, int size, int drop) {
	std::string out = "{ ";
	for (int i = 0; i < size; i++) {
		out += std::to_string(in[i]);

		if (i + 1 != size) {
			out += ',' + addSpace(11 - len(in[i + 1]));

			if ((i + 1) % drop == 0)
				out += "\n" + addSpace(10 - len(in[i + 1]));
		}
	}

	out += " }";
	return out;
}

template <typename T>
inline std::string vecToString(std::vector<T>* in) {
	std::string out = "{";

	
	for (int i = 0; i < in->size(); i++) {
		out += std::to_string((*in)[i]);
		if (i + 1 != in->size())
			out += ',' + addSpace(11 - len((*in)[i+1]));
	}
	out += '}';

	return out;
}

inline std::string addTabs(int n) {
	std::string out;
	for (int indT = 0; indT < n; indT++) out += '\t';
	return out;
}

inline std::string addSpace(int n) {
	std::string out;
	for (int indT = 0; indT < n; indT++) out += ' ';
	return out;
}

template <typename T>
inline void Transpose(float* io, int size, int new_line) {
	if (size % new_line != 0) {
		std::cout << "An error has occured in Transpose.\n";
		return;
	}
	T* temp_out = new T[size];

	
	for (int y = 0; y < size / new_line; y++) {
		for (int x = 0; x < new_line; x++) {
			temp_out[x + new_line * y] = io[y + new_line * x];
		}
	}


	// puting back temp_out into io
	for (int y = 0; y < size / new_line; y++) {
		for (int x = 0; x < new_line; x++) {
			io[x + y * new_line] = temp_out[x + y * new_line];
		}
	}

	delete[] temp_out;
	
}

template <typename T>
inline int len(T in) {
	return std::to_string(in).length();
}

// random number between 0 and 1
inline float rand0_1() { 
	return (float)rand() / (float)RAND_MAX;
}

// random number between -1 and 1
inline float rand_1_1() { 
	return 2.0f * rand0_1() - 1.0f;
}

// return a random array with each element v: -1<=v<=1
inline void randArr(float* out, int size) { 
	for (int i = 0; i < size; i++) {
		*out = 2.0f * rand0_1() - 1.0f;
		out++;
	}
}


template<typename To, typename From>
inline std::pair<To, To> convert(const std::pair<From, From> p) {
	return std::make_pair(static_cast<To>(p.first),
						   static_cast<To>(p.second));
}

template<typename From, typename To>
inline void convert(std::vector<std::pair<From, From>>* in, std::vector<std::pair<To, To>>* out, int _array = 1) {
	for (int arr = 0; arr < _array; arr++) {
		out->resize(in->size());

		for (int i = 0; i < in->size(); i++)
			(*out)[i] = convert<To>((*in)[i]);

		in++;
		out++;
	}
}

// Checks if element is in an array
template<typename T>
bool is_in(T* arr, uint32_t arrSize, T elem) {
	for (uint32_t i = 0; i < arrSize; i++)
		if (arr[i] == elem) return true;
		
	return false;
}

// Checks if element is in a vector
template<typename T>
bool is_in(std::vector<T> vec, T elem) {
	for (T test : vec) {
		if (test == elem) return true;
	}
	return false;
}

// Checks if element is in an array of vectors
template<typename T>
bool is_in(std::vector<T>* vec, uint32_t arrSize, T elem) {
	for (uint32_t i=0; i<arrSize; i++)
		for (T test : vec[i]) {
			if (test == elem) return true;
		}
	return false;
}


// The Chinese Remainder Theorem - returns a value in [0,..., m1 * m2 * ... * mn)
// DISCLAIMER: DOES NOT CHECK IF MODS ARE PAIRWISE COPRIME
uint32_t chinese(uint32_t* equives, uint32_t* mods, uint32_t equations){
    uint32_t N = 1;

    for (uint32_t i=0; i<equations; i++){
        N *= mods[i];
    }

    uint32_t* e = new uint32_t[equations];

    for (uint32_t i=0; i<equations; i++){
        uint32_t temp = N / mods[i];
        e[i] = temp;
        while (e[i] % mods[i] != 1){
            e[i] *= temp;
        }
    }

    uint32_t x=0;
    for (uint32_t i=0; i<equations; i++){
        x += equives[i]*e[i];
    }

    delete[] e;
    return x % N;

}
