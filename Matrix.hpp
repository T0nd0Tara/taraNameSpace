#pragma once
#include "Headers.hpp"
#include "MiscFuncs.hpp"

namespace tara {

	template <typename T_>
	class Matrix
	{
	private:
		uint32_t width, height, size;
		T_* arr;

	public:
		// Default Constructor
		Matrix();
		// Copy constructor
		Matrix(const Matrix<T_>&);
		// Constructor for (width, height, array)
		Matrix(uint32_t, uint32_t, T_*);
		// Constructor for vector
		Matrix(std::vector<T_>*, uint32_t);
		// Constructor for array of vectors
		Matrix(std::vector<T_>*, uint32_t, bool);

		Matrix(std::vector<std::pair<T_, T_>>*);

		Matrix(std::vector<Matrix<T_>>);
		// Sets all of the array to setVal (width, height, setVal)
		Matrix(uint32_t, uint32_t, T_);

		~Matrix();

		Matrix<T_>* copy();

		std::string to_string(uint32_t);

		std::vector<T_>* to_vec();

		T_ sum();
		Matrix<T_> row_sum();
		Matrix<T_> col_sum();

		T_ biggest();
		T_ smallest();

		T_ abs_biggest();

		Matrix<T_> T();
		Matrix<T_> Transpose();

		Matrix<float> norm();

		uint32_t get_width()  const { return width; }
		uint32_t get_height() const { return height; }
		uint32_t get_size()   const { return size; }

		Matrix<T_> get_row(uint32_t);
		Matrix<T_> get_col(uint32_t);

		// gets a row and convert it to a vector
		std::vector<T_>* get_rowVec(uint32_t);

		// gets a collumn and convert it to a vector
		std::vector<T_>* get_colVec(uint32_t);

		// The cell metods  are if you want to get a refrance
		// insted of getters and setters

		// cell through index of the array
		T_& cell(int64_t);
		// cell through (x,y) cords
		T_& cell(int64_t, int64_t);
		// cell through (x,y) cords
		T_& cell(uint32_t, uint32_t);
		// cell through std::pair(x,y) cords
		T_& cell(std::pair<int, int>);
		// cell through std::pair(x,y) cords
		T_& cell(std::pair<uint32_t, uint32_t>);


#ifdef TARA_PGE_EXTENSION
		// cell through olc::vi2d(x,y) cords
		T_& cell(olc::vi2d);
		// cell through olc::vu2d(x,y) cords
		T_& cell(olc::vu2d);
#endif // TARA_PGE_EXTENSION

		// get cell through index of the array
		const T_ get_cell(int64_t i) { return cell(i); }
		// get cell through (x,y) cords
		const T_ get_cell(int64_t x, int64_t y) { return cell(x, y); }
		// get cell through (x,y) cords
		const T_ get_cell(uint32_t x, uint32_t y) { return cell(x, y); }
		// get cell through std::pair(x,y) cords
		const T_ get_cell(std::pair<int, int> cords) { return cell(cords); }
		// get cell through std::pair(x,y) cords
		const T_ get_cell(std::pair<uint32_t, uint32_t> cords) { return cell(cords); }


#ifdef TARA_PGE_EXTENSION
		// get cell through olc::vi2d(x,y) cords
		const T_ get_cell(olc::vi2d cords) { return cell(cords); }
		// get cell through olc::vu2d(x,y) cords
		const T_ get_cell(olc::vu2d cords) { return cell(cords); }
		// get dimensions of the matrix by olc::vu2d(width, height)
		const olc::vu2d get_dim() { return olc::vu2d(width, height); }

#endif // TARA_PGE_EXTENSION

		// set cell through index of the array
		void set_cell(int64_t i, T_ val) { cell(i) = val; }
		// set cell through (x,y) cords
		void set_cell(int x, int y, T_ val) { cell(x, y) = val; }
		// set cell through (x,y) cords
		void set_cell(uint32_t x, uint32_t y, T_ val) { cell(x, y) = val; }
		// set cell through std::pair(x,y) cords
		void set_cell(std::pair<int, int> cords, T_ val) { cell(cords) = val; }
		// set cell through std::pair(x,y) cords
		void set_cell(std::pair<uint32_t, uint32_t> cords, T_ val) { cell(cords) = val; }

#ifdef TARA_PGE_EXTENSION
		// set cell through olc::vi2d(x,y) cords
		void set_cell(olc::vi2d cords, T_ val) { cell(cords) = val; }
		// set cell through olc::vu2d(x,y) cords
		void set_cell(olc::vu2d cords, T_ val) { cell(cords) = val; }
#endif // TARA_PGE_EXTENSION

		// set array from a different Matrix
		void set_arr(Matrix<T_>*);
		// set array from a different array
		void set_arr(T_*);
		// sets every value to what you put in
		void clear(T_);
		// checks if value is in the matrix
		bool is_in(T_);


		void setHeightWidth(uint32_t, uint32_t);
		std::string get_dim_str();



		T_& operator[](int index) { return cell(index); }
#ifdef TARA_PGE_EXTENSION
		T_& operator[](olc::vi2d cords) { return cell(cords.x, cords.y); }
#endif // TARA_PGE_EXTENSION

		template <typename T__>
		friend Matrix<T__> operator*(Matrix<T__>, T__);
		template <typename T__>
		friend Matrix<T__> operator*(T__, Matrix<T__>);
		template <typename T__>
		friend Matrix<T__> operator*(Matrix<T__>, Matrix<T__>);

		template <typename T__>
		friend Matrix<T__> operator+(Matrix<T__>, T__);
		template <typename T__>
		friend Matrix<T__> operator+(T__, Matrix<T__>);
		template <typename T__>
		friend Matrix<T__> operator+(Matrix<T__>, Matrix<T__>);

		template <typename T__>
		friend Matrix<T__> operator-(Matrix<T__>, T__);


		friend std::ostream& operator<<(std::ostream& out, Matrix<T_> a) {
			out << a.to_string(2);
			return out;
		}

		template <typename T__>
		friend bool operator==(Matrix<T__>, Matrix<T__>);

		Matrix<T_>& operator=(Matrix<T_>);


	};

	// making the Matrixf a thing you can use
	typedef Matrix<float> Matrixf;

} // TARA NAMESPACE

template<typename T>
bool is1x1(tara::Matrix<T>);