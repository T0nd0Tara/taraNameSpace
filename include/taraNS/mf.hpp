#pragma once

#include "..\..\Headers.hpp"

namespace tara{
	enum class text_color : uint8_t {
		DEFAULT = 0,
		FG_RED = 31,
		FG_GREEN = 32,
		FG_BLUE = 34,
		BG_RED = 41,
		BG_GREEN = 42,
		BG_BLUE = 44,
	};

	// MiscFuncs
	class mf {
	public:
		// bool to char
		static inline char btoc(bool b) {
			return (b) ? '1' : '0';
		}

		// bool to string
		static inline std::string btos(bool b) {
			return (b) ? "1" : "0";
		}

		// integer power (doesn't uses doubles like pow)
		// return x^n
		// in this function 0^0 := 0
		static int powi(int x, size_t n) {
			if (x == 0) return 0;
			int out = 1;
			for (size_t i = 0; i < n; i++) {
				out *= x;
			}
			return out;
		}

		template <typename T>
		static T dotProd(std::vector<T>* a, std::vector<T>* b) {
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
		static T* dotProd(std::vector<T>* a, std::vector<T>* b, size_t size, T* out = nullptr) {
			T* _out;
			if (out == nullptr) _out = new T[size];
			else _out = out;

			for (size_t i = 0U; i < size; i++) {
				_out[i] = dotProd(a[i], b[i]);
			}
			return _out;
		}

		template <typename T>
		static void vecToArr(std::vector<T>* in, T* out) {
			for (size_t i = 0U; i < in->size(); i++) {
				out[i] = (*in)[i];
			}
		}

		static inline std::string addTabs(size_t n) {
			std::string out = "";
			for (size_t indT = 0U; indT < n; indT++) out += '\t';
			return out;
		}

		static std::string addSpace(size_t n) {
			std::string out = "";
			for (size_t indT = 0U; indT < n; indT++) out += " ";
			return out;
		}

		template <typename T>
		static inline size_t len(T in) {
			return std::to_string(in).length();
		}

		// For len_ = 4:
		// From 35 to 0035
		// From -42 to -042
		static std::string sameLen(int num, size_t len_) {
			if (len_ < len(num)) return std::to_string(num);
			std::string out = "";
			for (size_t i = 0; i < len_ - len(num); i++) out += "0";
			
			out += std::to_string(std::abs(num));
			return ((num < 0) ? "-" : "") + out;
		}


		template <typename T>
		static std::string arrToString(T* in, size_t size, size_t drop = 0) {
			std::string out = "{ ";
			for (size_t i = 0U; i < size; i++) {
				out += std::to_string(in[i]);

				if (i + 1 != size) {
					out += ',' + addSpace(11 - len(in[i + 1]));

					if (drop)
						if ((i + 1) % drop == 0)
							out += "\n" + addSpace(10U - len(in[i + 1]));
				}
			}

			out += " }";
			return out;
		}

		template <typename T>
		static std::string vecToString(std::vector<T>* in) {
			std::string out = "{";


			for (size_t i = 0U; i < in->size(); i++) {
				out += std::to_string((*in)[i]);
				if (i + 1 != in->size())
					out += ',' + addSpace(11U - len((*in)[i + 1]));
			}
			out += '}';

			return out;
		}



		template <typename T>
		static void Transpose(float* io, size_t size, size_t new_line) {
			if (size % new_line != 0) {
				std::cout << "An error has occured in Transpose.\n";
				return;
			}
			T* temp_out = new T[size];


			for (size_t y = 0U; y < size / new_line; y++) {
				for (size_t x = 0U; x < new_line; x++) {
					temp_out[x + new_line * y] = io[y + new_line * x];
				}
			}


			// puting back temp_out into io
			for (size_t y = 0U; y < size / new_line; y++) {
				for (size_t x = 0U; x < new_line; x++) {
					io[x + y * new_line] = temp_out[x + y * new_line];
				}
			}

			delete[] temp_out;
		}

#pragma region Random

		// random number between 0 and 1
		static inline float rand0_1() {
			return (float)rand() / (float)RAND_MAX;
		}

		// random number between -1 and 1
		static inline float rand_1_1() {
			return 2.0f * rand0_1() - 1.0f;
		}

		// return a random array with each element v: -1<=v<=1
		static inline void randArr(float* out, size_t size) {
			for (size_t i = 0; i < size; i++)
				out[i] = rand_1_1();

		}

#pragma endregion

#pragma region convert
		template<typename To, typename From>
		static std::pair<To, To> convert(const std::pair<From, From> p) {
			return std::make_pair(static_cast<To>(p.first),
				static_cast<To>(p.second));
		}

		template<typename From, typename To>
		static void convert(std::vector<std::pair<From, From>>* in, std::vector<std::pair<To, To>>* out, uint32_t _array = 1) {
			for (size_t arr = 0; arr < _array; arr++) {
				out->resize(in->size());

				for (size_t i = 0; i < in->size(); i++)
					(*out)[i] = convert<To>((*in)[i]);

				in++;
				out++;
			}
		}

#pragma endregion

#pragma region olc::pge
#ifdef TARA_PGE_EXTENSION
		template<typename T>
		static inline T min(olc::v2d_generic<T> vec) {
			return (vec.x < vec.y) ? vec.x : vec.y;
		}

		template<typename T>
		static inline T max(olc::v2d_generic<T> vec) {
			return (vec.x > vec.y) ? vec.x : vec.y;
		}
#endif // TARA_PGE_EXTENSION
#pragma endregion

#pragma region is_in

		// Checks if element is in an array
		template<typename T>
		static bool is_in(T* arr, size_t arrSize, T elem) {
			for (size_t i = 0U; i < arrSize; i++)
				if (arr[i] == elem) return true;

			return false;
		}

		// Checks if element is in a vector
		template<typename T>
		static bool is_in(std::vector<T> vec, T elem, size_t start = 0U, size_t end = 0U) {
			if (end == 0U) end = vec.size();
			for (size_t i = start; i < end; i++) {
				if (vec[i] == elem) return true;
			}
			return false;
		}

		// Checks if element is in an array of vectors
		template<typename T>
		static bool is_in(std::vector<T>* vec, size_t arrSize, T elem) {
			for (size_t i = 0U; i < arrSize; i++)
				for (T test : vec[i]) {
					if (test == elem) return true;
				}
			return false;
		}
#pragma endregion

#pragma region Python_Funcs

		// The replace string from python
		static bool pyReplace(std::string& str, const std::string& from, const std::string& to) {
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
		static std::vector<std::string> pySplit(std::string str, std::string sep) {
			std::vector<std::string> out;
			boost::split(out, str, boost::is_any_of(sep), boost::token_compress_on);
			return out;
		}

		// The split string from python
		static void pySplit(std::vector<std::string>& IOvec, std::string str, std::string sep) {
			boost::split(IOvec, str, boost::is_any_of(sep), boost::token_compress_on);
		}
#endif // TARA_NO_BOOST
#pragma endregion

#pragma region Number_Theory

		// real modulo (not like %) - also work for negative numbers
		// works with floats and doubles
		// returns y = x (mod m) where y in {0,..., m-1}
		template<typename T>
		static T modulo(T x, T m) {
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
		static uint32_t chinese(uint32_t* equives, uint32_t* mods, uint32_t equations) {
			size_t N = 1U;

			for (size_t i = 0U; i < equations; i++) {
				N *= mods[i];
			}

			size_t* e = new size_t[equations];

			for (size_t i = 0U; i < equations; i++) {
				size_t temp = N / mods[i];
				e[i] = temp;
				while (e[i] % mods[i] != 1) {
					e[i] *= temp;
				}
			}

			size_t x = 0U;
			for (size_t i = 0U; i < equations; i++) {
				x += equives[i] * e[i];
			}

			delete[] e;
			return x % N;
		}
#pragma endregion

#pragma region Crockfords Base32
		static const uint8_t decoder32(char c) {
			switch (c) {
			case '0':
			case 'O': case 'o':
				return 0;
			case '1':
			case 'I': case 'i':
			case 'L': case 'l':
				return 1;
			case '2':
				return 2;
			case '3':
				return 3;
			case '4':
				return 4;
			case '5':
				return 5;
			case '6':
				return 6;
			case '7':
				return 7;
			case '8':
				return 8;
			case '9':
				return 9;

			case 'A': case 'a':
				return 10;
			case 'B': case 'b':
				return 11;
			case 'C': case 'c':
				return 12;
			case 'D': case 'd':
				return 13;
			case 'E': case 'e':
				return 14;
			case 'F': case 'f':
				return 15;
			case 'G': case 'g':
				return 16;
			case 'H': case 'h':
				return 17;
			case 'J': case 'j':
				return 18;
			case 'K': case 'k':
				return 19;
			case 'M': case 'm':
				return 20;
			case 'N': case 'n':
				return 21;
			case 'P': case 'p':
				return 22;
			case 'Q': case 'q':
				return 23;
			case 'R': case 'r':
				return 24;
			case 'S': case 's':
				return 25;
			case 'T': case 't':
				return 26;
			case 'V': case 'v':
				return 27;
			case 'W': case 'w':
				return 28;
			case 'X': case 'x':
				return 29;
			case 'Y': case 'y':
				return 30;
			case 'Z': case 'z':
				return 31;
			}

			throw std::out_of_range("A wrong character was inserted. '" + std::string(1, c) + "' is not part of Crockford's Base32");
			return 32;
		}

		static const char encoder32(uint8_t i) {
			switch (i) {
			case 0:
				return '0';
			case  1:
				return '1';
			case  2:
				return '2';
			case  3:
				return '3';
			case  4:
				return '4';
			case  5:
				return '5';
			case  6:
				return '6';
			case  7:
				return '7';
			case  8:
				return '8';
			case  9:
				return '9';
			case 10:
				return 'A';
			case 11:
				return 'B';
			case 12:
				return 'C';
			case 13:
				return 'D';
			case 14:
				return 'E';
			case 15:
				return 'F';
			case 16:
				return 'G';
			case 17:
				return 'H';
			case 18:
				return 'J';
			case 19:
				return 'K';
			case 20:
				return 'M';
			case 21:
				return 'N';
			case 22:
				return 'P';
			case 23:
				return 'Q';
			case 24:
				return 'R';
			case 25:
				return 'S';
			case 26:
				return 'T';
			case 27:
				return 'V';
			case 28:
				return 'W';
			case 29:
				return 'X';
			case 30:
				return 'Y';
			case 31:
				return 'Z';
			}

			throw std::out_of_range("Inserted a number (" + std::to_string(i) + ") greater than 32. Can't convert to Crockford's Base32");
			return 'U';
		}
		static size_t decoding32(std::string str) {
			size_t out = 0;
			for (size_t i = 0; i < str.length(); i++) {
				try {
					out += (size_t)decoder32(str[i]) * powi(32, str.length() - i - 1);
				}
				catch (std::out_of_range& e) {
					printError("A wrong character was inserted. '" + std::string(1, str[i]) + "' is not part of Crockford's Base32");
				}
			}
			return out;
		}

		static std::string encoding32(size_t num) {
			if (num == 0) return "0";

			std::string out = "";
			while (num != 0) {
				out.insert(0, std::string(1, encoder32(num & 0x1F /*equiv to num % 32 */)));

				num = num >> 5;
				// equiv to num = num / 32;
			}
			return out;

		}
#pragma endregion


		template<typename T>
		static void printVec(std::vector<T>& vec, std::string sep = ", ", std::ostream& os = std::cout){
			for (size_t i = 0; i < vec.size() - 1; i++)
				os << vec[i] << sep;
			os << vec.back();
		}
		static void printError(std::string description, std::exception* error = nullptr, bool abortProgram = true,
			std::ostream& os = std::cerr, text_color col = text_color::DEFAULT)
		{
			std::string print = description;
			if (error != nullptr) print += ": " + std::string(typeid(*error).name());
			if ((uint8_t)col) os << "\033[" + std::to_string((uint8_t)col) + "m";
			os << print << '\n';
			if ((uint8_t)col) os << "\033[0m";
			if (abortProgram) abort();
		}

	};
}