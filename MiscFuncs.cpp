#include "MiscFuncs.hpp"
namespace tara {
	int powi(int x, size_t n) {
		if (x == 0) return 0;
		int out = 1;
		for (size_t i = 0; i < n; i++) {
			out *= x;
		}
		return out;
	}

	template <typename T>
	T dotProd(std::vector<T>* a, std::vector<T>* b) {
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

	template <typename T>
	T* dotProd(std::vector<T>* a, std::vector<T>* b, size_t size, T* out = nullptr) {
		T* _out;
		if (out == nullptr) _out = new T[size];
		else _out = out;

		for (size_t i = 0U; i < size; i++) {
			*_out = dotProd(a, b);
			_out++;
			a++;
		}
		return _out;
	}

	template <typename T>
	void vecToArr(std::vector<T>* in, T* out) {
		for (size_t i = 0U; i < in->size(); i++) {
			out[i] = (*in)[i];
		}
	}

	template <typename T>
	std::string arrToString(T* in, size_t size) {
		std::string out = "{";
		for (size_t i = 0U; i < size; i++) {
			out += std::to_string(*in);
			in++;
			if (i + 1 != size)
				out += ',' + addSpace(11U - len(in[i + 1]));
		}
		out += '}';
		return out;
	}

	template <typename T>
	std::string arrToString(T* in, size_t size, size_t drop) {
		std::string out = "{ ";
		for (size_t i = 0U; i < size; i++) {
			out += std::to_string(in[i]);

			if (i + 1 != size) {
				out += ',' + addSpace(11 - len(in[i + 1]));

				if ((i + 1) % drop == 0)
					out += "\n" + addSpace(10U - len(in[i + 1]));
			}
		}

		out += " }";
		return out;
	}

	template <typename T>
	std::string vecToString(std::vector<T>* in) {
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
	void Transpose(float* io, size_t size, size_t new_line) {
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



#pragma region is_in


	template<typename T>
	bool is_in(T* arr, size_t arrSize, T elem) {
		for (size_t i = 0U; i < arrSize; i++)
			if (arr[i] == elem) return true;

		return false;
	}


	template<typename T>
	bool is_in(std::vector<T> vec, T elem, size_t start = 0U, size_t end = 0U) {
		if (end == 0U) end = vec.size();
		for (size_t i = start; i < end; i++) {
			if (vec[i] == elem) return true;
		}
		return false;
	}


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

	std::vector<std::string> pySplit(std::string str, std::string sep) {
		std::vector<std::string> out;
		boost::split(out, str, boost::is_any_of(sep), boost::token_compress_on);
		return out;
	}


	void pySplit(std::vector<std::string>& IOvec, std::string str, std::string sep) {
		boost::split(IOvec, str, boost::is_any_of(sep), boost::token_compress_on);
	}
#endif // TARA_NO_BOOST
#pragma endregion Python_Funcs


#pragma region Number_Theory
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

	uint32_t chinese(uint32_t* equives, uint32_t* mods, uint32_t equations) {
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
#pragma endregion Number_Theory


#pragma region encoding32
	const uint8_t decoder32(char c) {
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

		/*
		{'0', 0}, {'O', 0}, {'o', 0},
		{'1', 1}, {'I', 1}, {'i', 1}, {'L', 1}, {'l', 1},
		{'2', 2},
		{'3', 3},
		{'4', 4},
		{'5', 5},
		{'6', 6},
		{'7', 7},
		{'8', 8},
		{'9', 9},
		{'A', 10}, {'a', 10},
		{'B', 11}, {'b', 11},
		{'C', 12}, {'c', 12},
		{'D', 13}, {'d', 13},
		{'E', 14}, {'e', 14},
		{'F', 15}, {'f', 15},
		{'G', 16}, {'g', 16},
		{'H', 17}, {'h', 17},
		{'J', 18}, {'j', 18},
		{'K', 19}, {'k', 19},
		{'M', 20}, {'m', 20},
		{'N', 21}, {'n', 21},
		{'P', 22}, {'p', 22},
		{'Q', 23}, {'q', 23},
		{'R', 24}, {'r', 24},
		{'S', 25}, {'s', 25},
		{'T', 26}, {'t', 26},
		{'V', 27}, {'v', 27},
		{'W', 28}, {'w', 28},
		{'X', 29}, {'x', 29},
		{'Y', 30}, {'y', 30},
		{'Z', 31}, {'z', 31}
		*/
	};

	const char encoder32(uint8_t i) {
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
		/*
		{0,  '0'},
		{1,  '1'},
		{2,  '2'},
		{3,  '3'},
		{4,  '4'},
		{5,  '5'},
		{6,  '6'},
		{7,  '7'},
		{8,  '8'},
		{9,  '9'},
		{10, 'A'},
		{11, 'B'},
		{12, 'C'},
		{13, 'D'},
		{14, 'E'},
		{15, 'F'},
		{16, 'G'},
		{17, 'H'},
		{18, 'J'},
		{19, 'K'},
		{20, 'M'},
		{21, 'N'},
		{22, 'P'},
		{23, 'Q'},
		{24, 'R'},
		{25, 'S'},
		{26, 'T'},
		{27, 'V'},
		{28, 'W'},
		{29, 'X'},
		{30, 'Y'},
		{31, 'Z'},
		*/
	};

#pragma endregion encoding32

	template<typename T>
	void printVec(std::vector<T>& vec, std::string sep = ", ") {
		for (size_t i = 0; i < vec.size() - 1; i++)
			std::cout << vec[i] << sep;
		std::cout << vec.back();
	}
	void printError(std::string description, std::exception* error = nullptr, bool abortProgram = true, bool printInCout = false) {
		std::string print = description;
		if (error != nullptr) print += ": " + std::string(typeid(*error).name());

		if (printInCout) std::cout << print << '\n';
		else			 std::cerr << print << '\n';

		if (abortProgram) abort();
	}
}