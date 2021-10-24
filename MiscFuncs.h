#pragma once

#include "Headers.h"

// bool to char
char btoc(bool b) {
	if (b) return '1';
	return '0';
}

// bool to string
std::string btos(bool b) {
	if (b) return "1";
	return "0";
}

// integer power (doesn't uses doubles like pow)
// return x^n
// in this function 0^0 := 0
int powi(int x, size_t n) {
	if (x == 0) return 0;
	int out = 1;
	for (size_t i = 0; i < n; i++) {
		out *= x;
	}
	return out;
}

template <typename T>
inline T dotProd(std::vector<T>* a, std::vector<T>* b) {
	if (a->size() != b->size()) {
		throw std::invalid_argument("Cannot do dot product with to different sized arrays");
		std::cout << "An 'std::invalid_argument' error has occured in dotProd.\n";
		return (T)0;
	}

	T sum = (T)0;
	for (size_t i = 0; i < (a->size()); i++)
		sum += (*a)[i] * (*b)[i];

	return sum;
}

// Returns an array of which each element is the dot product of the two corresponding vectors
// 
// if the 'out' parameter is defined, the output will be 'out'
// and the array will be at that location
template <typename T>
inline T* dotProd(std::vector<T>* a, std::vector<T>* b, size_t size, T* out = nullptr) {
	T* _out;
	if (out == nullptr) _out = new T[size];
	else _out = out;

	for (size_t i = 0; i < size; i++) {
		*_out = dotProd(a, b);
		_out++;
		a++;
	}
	return _out;
}

template <typename T>
inline void vecToArr(std::vector<T>* in, T* out) {
	for (size_t i = 0; i < in->size(); i++) {
		out[i] = (*in)[i];
	}
}

template <typename T>
inline size_t len(T);

inline std::string addSpace(size_t);

template <typename T>
inline std::string arrToString(T* in, size_t size) { // doesn't drop
	std::string out = "{";
	for (size_t i = 0; i < size; i++) {
		out += std::to_string(*in);
		in++;
		if (i + 1 != size)
			out += ',' + addSpace(11 - len(in[i + 1]));
	}
	out += '}';
	return out;
}


template <typename T>
inline std::string arrToString(T* in, size_t size, size_t drop) {
	std::string out = "{ ";
	for (size_t i = 0; i < size; i++) {
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

	
	for (size_t i = 0; i < in->size(); i++) {
		out += std::to_string((*in)[i]);
		if (i + 1 != in->size())
			out += ',' + addSpace(11 - len((*in)[i+1]));
	}
	out += '}';

	return out;
}

inline std::string addTabs(size_t n) {
	std::string out = "";
	for (size_t indT = 0; indT < n; indT++) out += '\t';
	return out;
}

inline std::string addSpace(size_t n) {
	std::string out = "";
	for (size_t indT = 0; indT < n; indT++) out += ' ';
	return out;
}

template <typename T>
inline void Transpose(float* io, size_t size, size_t new_line) {
	if (size % new_line != 0) {
		std::cout << "An error has occured in Transpose.\n";
		return;
	}
	T* temp_out = new T[size];

	
	for (size_t y = 0; y < size / new_line; y++) {
		for (size_t x = 0; x < new_line; x++) {
			temp_out[x + new_line * y] = io[y + new_line * x];
		}
	}


	// puting back temp_out into io
	for (size_t y = 0; y < size / new_line; y++) {
		for (size_t x = 0; x < new_line; x++) {
			io[x + y * new_line] = temp_out[x + y * new_line];
		}
	}

	delete[] temp_out;
	
}

template <typename T>
inline size_t len(T in) {
	return std::to_string(in).length();
}

#pragma region Random

// random number between 0 and 1
inline float rand0_1() { 
	return (float)rand() / (float)RAND_MAX;
}

// random number between -1 and 1
inline float rand_1_1() { 
	return 2.0f * rand0_1() - 1.0f;
}

// return a random array with each element v: -1<=v<=1
inline void randArr(float* out, size_t size) {
	for (size_t i = 0; i < size; i++) {
		out[i] = rand_1_1();
	}
}

#pragma endregion Random

#pragma region convert
template<typename To, typename From>
inline std::pair<To, To> convert(const std::pair<From, From> p) {
	return std::make_pair(static_cast<To>(p.first),
						   static_cast<To>(p.second));
}

template<typename From, typename To>
inline void convert(std::vector<std::pair<From, From>>* in, std::vector<std::pair<To, To>>* out, uint32_t _array = 1) {
	for (size_t arr = 0; arr < _array; arr++) {
		out->resize(in->size());

		for (size_t i = 0; i < in->size(); i++)
			(*out)[i] = convert<To>((*in)[i]);

		in++;
		out++;
	}
}
#pragma endregion convert

#pragma region olc::pge
#ifdef TARA_PGE_EXTENSION
template<typename T>
inline T min(olc::v2d_generic<T> vec) {
	if (vec.x < vec.y) return vec.x;
	return vec.y;
}

template<typename T>
inline T max(olc::v2d_generic<T> vec) {
	if (vec.x > vec.y) return vec.x;
	return vec.y;
}
#endif // TARA_PGE_EXTENSION
#pragma endregion olc::pge

#pragma region is_in

// Checks if element is in an array
template<typename T>
bool is_in(T* arr, size_t arrSize, T elem) {
	for (size_t i = 0U; i < arrSize; i++)
		if (arr[i] == elem) return true;
		
	return false;
}

// Checks if element is in a vector
template<typename T>
bool is_in(std::vector<T> vec, T elem, size_t start = 0U, size_t end = 0U) {
	if (end == 0U) end = vec.size();
	for (size_t i = start; i < end; i++) {
		if (vec[i] == elem) return true;
	}
	return false;
}

// Checks if element is in an array of vectors
template<typename T>
bool is_in(std::vector<T>* vec, size_t arrSize, T elem) {
	for (size_t i = 0U; i < arrSize; i++)
		for (T test : vec[i]) {
			if (test == elem) return true;
		}
	return false;
}
#pragma endregion is_in

#pragma region Python_Funcs

// The replace string from python
bool pyReplace(std::string& str, const std::string& from, const std::string& to) {
	bool beenReplaced = false;
	size_t start_pos = str.find(from);
	while (start_pos != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		beenReplaced = true;
		
		start_pos = str.find(from, start_pos + to.length());
	}

	return beenReplaced;
}

#ifndef TARA_NO_BOOST
// The split string from python
std::vector<std::string> pySplit(std::string str, std::string sep) {
	std::vector<std::string> out;
	boost::split(out, str, boost::is_any_of(sep), boost::token_compress_on);
	return out;
}

// The split string from python
void pySplit(std::vector<std::string>& IOvec, std::string str, std::string sep) {
		boost::split(IOvec, str, boost::is_any_of(sep), boost::token_compress_on);
}
#endif // TARA_NO_BOOST
#pragma endregion Python_Funcs

#pragma region Number_Theory

// real modulu (not like %) - also work for negative numbers
// works with floats and doubles
// returns y = x(mod m) where y in {0,..., m-1}
template<typename T>
T modulu(T x, T m) {
	if (x >= m) 
		do {
			x -= m;
		} while (x >= m);
	
	else if (x < T(0))
		do {
			x += m;
		} while (x < T(0));

	return x;
}

// The Chinese Remainder Theorem - returns a value in [0,..., m1 * m2 * ... * mn)
// DISCLAIMER: DOES NOT CHECK IF MODS ARE PAIRWISE COPRIME
uint32_t chinese(uint32_t* equives, uint32_t* mods, uint32_t equations){
	size_t N = 1;

    for (size_t i=0; i<equations; i++){
        N *= mods[i];
    }

	size_t* e = new size_t[equations];

    for (size_t i=0; i<equations; i++){
		size_t temp = N / mods[i];
        e[i] = temp;
        while (e[i] % mods[i] != 1){
            e[i] *= temp;
        }
    }

	size_t x=0;
    for (size_t i=0; i<equations; i++){
        x += equives[i]*e[i];
    }

    delete[] e;
    return x % N;

}
#pragma endregion Number_Theory

void printError(std::string description, std::exception* error = nullptr, bool abortProgram = true, bool printInCout = false) {
	std::string print = description;
	if (error != nullptr) print += ": " + std::string(typeid(*error).name());

	if (printInCout) std::cout << print << '\n';
	else			 std::cerr << print << '\n';

	if (abortProgram) abort();
}
