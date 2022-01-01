#pragma once

#include "Headers.hpp"

namespace tara{

// bool to char
inline char btoc(bool b) {
	return (b) ? '1' : '0';
}

// bool to string
inline std::string btos(bool b) {
	return (b) ? "1" : "0";
}

// integer power (doesn't uses doubles like pow)
// return x^n
// in this function 0^0 := 0
int powi(int x, size_t n);

template <typename T>
T dotProd(std::vector<T>* a, std::vector<T>* b);

// Returns an array of which each element is the dot product of the two corresponding vectors
// 
// if the 'out' parameter is defined, the output will be 'out'
// and the array will be at that location
template <typename T>
T* dotProd(std::vector<T>* a, std::vector<T>* b, size_t size, T* out = nullptr);

template <typename T>
void vecToArr(std::vector<T>* in, T* out);

template <typename T>
inline size_t len(T);

inline std::string addSpace(size_t);

template <typename T>
std::string arrToString(T* in, size_t size); // doesn't drop



template <typename T>
std::string arrToString(T* in, size_t size, size_t drop);

template <typename T>
std::string vecToString(std::vector<T>* in);

inline std::string addTabs(size_t n) {
	std::string out = "";
	for (size_t indT = 0U; indT < n; indT++) out += '\t';
	return out;
}

inline std::string addSpace(size_t n) {
	std::string out = "";
	for (size_t indT = 0U; indT < n; indT++) out += ' ';
	return out;
}

template <typename T>
inline size_t len(T in) {
	return std::to_string(in).length();
}

template <typename T>
void Transpose(float* io, size_t size, size_t new_line);

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
	for (size_t i = 0; i < size; i++)
		out[i] = rand_1_1();
	
}

#pragma endregion Random

#pragma region convert
template<typename To, typename From>
inline std::pair<To, To> convert(const std::pair<From, From> p);

template<typename From, typename To>
inline void convert(std::vector<std::pair<From, From>>* in, std::vector<std::pair<To, To>>* out, uint32_t _array = 1);

#pragma endregion convert

#pragma region olc::pge
#ifdef TARA_PGE_EXTENSION
template<typename T>
inline T min(olc::v2d_generic<T> vec) {
	return (vec.x < vec.y) ? vec.x : vec.y;
}

template<typename T>
inline T max(olc::v2d_generic<T> vec) {
	return (vec.x > vec.y) ? vec.x : vec.y;
}
#endif // TARA_PGE_EXTENSION
#pragma endregion olc::pge

#pragma region is_in

// Checks if element is in an array
template<typename T>
bool is_in(T* arr, size_t arrSize, T elem);

// Checks if element is in a vector
template<typename T>
bool is_in(std::vector<T> vec, T elem, size_t start = 0U, size_t end = 0U);

// Checks if element is in an array of vectors
template<typename T>
bool is_in(std::vector<T>* vec, size_t arrSize, T elem);
#pragma endregion is_in

#pragma region Python_Funcs

// The replace string from python
bool pyReplace(std::string& str, const std::string& from, const std::string& to);

#ifndef TARA_NO_BOOST
// The split string from python
std::vector<std::string> pySplit(std::string str, std::string sep);

// The split string from python
void pySplit(std::vector<std::string>& IOvec, std::string str, std::string sep);
#endif // TARA_NO_BOOST
#pragma endregion Python_Funcs

#pragma region Number_Theory

// real modulu (not like %) - also work for negative numbers
// works with floats and doubles
// returns y = x(mod m) where y in {0,..., m-1}
template<typename T>
T modulu(T x, T m);

// The Chinese Remainder Theorem - returns a value in [0,..., m1 * m2 * ... * mn)
// DISCLAIMER: DOES NOT CHECK IF MODS ARE PAIRWISE COPRIME
uint32_t chinese(uint32_t* equives, uint32_t* mods, uint32_t equations);
#pragma endregion Number_Theory

#pragma region encoding32
const uint8_t decoder32(char c);

const char encoder32(uint8_t i);

#pragma endregion encoding32

template<typename T>
void printVec(std::vector<T>& vec, std::string sep = ", ");
void printError(std::string description, std::exception* error = nullptr, bool abortProgram = true, bool printInCout = false);


}