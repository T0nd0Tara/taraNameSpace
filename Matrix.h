#pragma once
#include "Headers.h"
#include "MiscFuncs.h"

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

	// ========================Constructors========================
#pragma region Constructors

	// Default Constructor
	template <typename T_>
	Matrix<T_>::Matrix() {
		width = 1;
		height = 1;
		size = 1;
		arr = new T_[size];
		arr[0] = T_(0);
	}

	// Copy Constructor
	template <typename T_>
	Matrix<T_>::Matrix(const Matrix<T_>& rhs) {
		width = rhs.width;
		height = rhs.height;
		size = rhs.size;

		arr = new T_[size]();
		for (uint32_t i = 0; i < size; i++) {
			arr[i] = rhs.arr[i];
		}
	}

	// for array
	template <typename T_>
	Matrix<T_>::Matrix(uint32_t setWidth, uint32_t setHeight, T_* setArr) {
		width = setWidth;
		height = setHeight;

		size = width * height;

		arr = new T_[size];


		for (uint32_t i = 0; i < size; i++) {
			arr[i] = *setArr;
			setArr++;
		}
	}

	// for vector
	template <typename T_>
	Matrix<T_>::Matrix(std::vector<T_>* setVec, uint32_t setWidth) {
		width = setWidth;
		height = setVec->size() / setWidth;

		size = setVec->size();

		arr = new T_[size];

		for (float* i = arr; i < arr + size; i++) {
			*i = (*setVec)[i - arr];
		}

	}

	// for array of vectors
	template <typename T_>
	Matrix<T_>::Matrix(std::vector<T_>* setVec, uint32_t setHeight, bool ArrayOfVectors) {
		assert(ArrayOfVectors &&
			"Can not define Matrix type with {std::vector<float>*, int, false} - For array of vector,"
			" initialize list have to be {std::vector<float>*, int, true} or {std::vector<float>*, int}");


		// making a copy of setVec
		std::vector<float>* setVecDup = setVec;


		// checking if input is ok
		width = setVec->size();
		for (uint32_t i = 0; i < setHeight - 1; i++) {
			setVec++;
			assert((width == setVec->size()) &&
				"Can not have different sized rows inside of Matrix type.");
			
		}


		height = setHeight;
		size = width * height;
		// initialize
		arr = new T_[size];
		for (uint32_t i = 0; i < height; i++) {
			vecToArr<T_>(setVecDup, arr + i * width);
			setVecDup++;
		}



	}

	template <typename T_>
	Matrix<T_>::Matrix(std::vector<std::pair<T_, T_>>* in) {
		width = 2;
		height = in->size();

		size = (height << 1);

		arr = new T_[size];

		for (uint32_t i = 0; i < size; i += 2) {
			arr[i] = (*in)[i >> 1].first;
			arr[i + 1] = (*in)[i >> 1].second;

		}
	}

	// works only for 1xn or nx1 matrices
	template <typename T_>
	Matrix<T_>::Matrix(std::vector<Matrix<T_>> in) {
		std::string modelDim = in[0].get_dim();

		for (Matrix m : in) {
			assert((m.get_width() == 1 || m.get_height() == 1) &&
				"Cannot construct Matrix of Marices,\nIf the vector got matrix m, such that: m.get_width() != 1 && m.get_height() != 1");

				assert((m.get_dim() == modelDim) &&
					"All matrices got to be the same dimension");
			
		}



		bool Horizontals = (in[0].get_height() == 1);

		if (Horizontals) {
			height = in.size();
			width = in[0].get_width();
			size = height * width;

			arr = new T_[size];

			for (uint32_t row = 0; row < height; row++) {
				for (uint32_t cell = 0; cell < width; cell++) {
					arr[cell + row * width] = in[row][cell];
				}
			}
		}
		else { // verticals
			height = in[0].get_height();
			width = in.size();

			size = height * width;

			arr = new T_[size];

			for (uint32_t col = 0; col < width; col++) {
				for (uint32_t cell = 0; cell < height; cell++) {
					arr[col + cell * height] = in[col][cell];
				}
			}
		}

	}

	// sets all of the array to setVal
	template <typename T_>
	Matrix<T_>::Matrix(uint32_t setWidth, uint32_t setHeight, T_ setVal) {
		width = setWidth;
		height = setHeight;
		size = width * height;

		arr = new T_[size];

		for (uint32_t i = 0; i < size; i++) {
			arr[i] = setVal;
		}
	}
	template <typename T_>
	Matrix<T_>::~Matrix() {
		delete[] arr;
	}

#pragma endregion Constructors

	// ==========================Methods===========================
#pragma region Methods

	template <typename T_>
	Matrix<T_>* Matrix<T_>::copy() {
		T_* newArr = new T_[size];

		for (uint32_t i = 0; i < size; i++) {
			newArr[i] = arr[i];
		}

		return new Matrix<T_>(width, height, newArr);
	}

	template <typename T_>
	std::string Matrix<T_>::to_string(uint32_t spaces) {

		std::string out = "{";
		out += addSpace(spaces);

		for (uint32_t i = 0; i < size; i++) {
			out += std::to_string(arr[i]);

			if (i + 1 != size) {

				out += ',' + addSpace(spaces);
				if ((i + 1) % width == 0)
					out += "\n" + addSpace(spaces + 1);
			}
		}

		out += " }";
		return out;
	}
	
	template <typename T_>
	std::vector<T_>* Matrix<T_>::to_vec() {
		std::vector<T_>* out = new std::vector<T_>();

		for (uint32_t i = 0; i < size; i++) {
			out->push_back(arr[i]);
		}

		return out;
	}

	template <typename T_>
	T_ Matrix<T_>::sum() {
		T_ out = (T_)0;
		for (uint32_t i = 0; i < size; i++) {
			out += arr[i];
		}
		return out;
	}

	template <typename T_>
	Matrix<T_> Matrix<T_>::row_sum() {
		T_* temp_arr = new T_[height];
		for (uint32_t i = 0; i < height; i++) {
			temp_arr[i] = get_row(i).sum();
		}
		return Matrix(temp_arr, 1, height);
	}

	template <typename T_>
	Matrix<T_> Matrix<T_>::col_sum() {
		T_* temp_arr = new T_[width];
		for (uint32_t i = 0; i < width; i++) {
			temp_arr[i] = get_col(i).sum();
		}
		return Matrix<T_>(temp_arr, width, 1);
	}
	template <typename T_>
	T_ Matrix<T_>::biggest() {
		T_ b = arr[0];
		for (uint32_t i = 1; i < size; i++) {
			if (arr[i] > b) b = arr[i];
		}
		return b;
	}
	template <typename T_>
	T_ Matrix<T_>::smallest() {
		T_ s = arr[0];
		for (uint32_t i = 1; i < size; i++) {
			if (arr[i] < s) s = arr[i];
		}
		return s;
	}
	template <typename T_>
	T_ Matrix<T_>::abs_biggest() {
		T_ b = std::abs(arr[0]);
		for (uint32_t i = 1; i < size; i++) {
			T_ temp = std::abs(arr[i]);
			if (temp > b) b = temp;
		}
		return b;
	}
	template <typename T_>
	Matrix<T_> Matrix<T_>::T() {
		T_* out = new T_[size];


		for (int y = 0; y < width; y++) {
			for (int x = 0; x < height; x++) {
				out[x + height * y] = arr[y + width * x];
			}
		}

		return Matrix<T_>(out, height, width);
	}
	template <typename T_>
	Matrix<T_> Matrix<T_>::Transpose() {
		return this->T();
	}
	template <typename T_>
	Matrix<float> Matrix<T_>::norm() { // returning a new Matrix that all the values are between [-1,1]

		float b = (float)abs_biggest();
		if (b == 0.0f)
			return *this;

		float* tempArr = new float[size];
		for (uint32_t i = 0; i < size; i++) {
			tempArr[i] = arr[i] / b;
		}
		return Matrix<float>(tempArr, width, height);
	}

	template <typename T_>
	Matrix<T_> Matrix<T_>::get_row(uint32_t ind) {
		T_* data = new T_[width];

		for (uint32_t x = 0; x < width; x++) {
			data[x] = arr[x + ind * width];
		}

		return Matrix<T_>(data, width, 1);
	}
	template <typename T_>
	Matrix<T_> Matrix<T_>::get_col(uint32_t ind) {
		T_* data = new T_[height];

		for (uint32_t y = 0; y < height; y++) {
			data[y] = arr[ind + y * width];
		}

		return Matrix<T_>(data, 1, height);
	}
	template <typename T_>
	std::vector<T_>* Matrix<T_>::get_rowVec(uint32_t ind) {
		return get_row(ind).to_vec();
	}
	template <typename T_>
	std::vector<T_>* Matrix<T_>::get_colVec(uint32_t ind) {
		return get_col(ind).to_vec();
	}


	template <typename T_>
	T_& Matrix<T_>::cell(int64_t i) {
		return arr[modulu(i, (int64_t)size)];
	}


	template <typename T_>
	T_& Matrix<T_>::cell(int64_t x, int64_t y) {
		return arr[modulu(x, (int64_t)width) + modulu(y, (int64_t)height) * width];
	}


	template <typename T_>
	T_& Matrix<T_>::cell(uint32_t x, uint32_t y) {
		return arr[modulu(x, width) + modulu(y, height) * width];
	}

	template <typename T_>
	T_& Matrix<T_>::cell(std::pair<int, int> cords) {
		return cell(cords.first, cords.second);
	}

	template <typename T_>
	T_& Matrix<T_>::cell(std::pair<uint32_t, uint32_t> cords) {
		return cell(cords.first, cords.second);
	}

#ifdef TARA_PGE_EXTENSION
	template <typename T_>
	T_& Matrix<T_>::cell(olc::vi2d cords){
		return cell(cords.x, cords.y);
	}

	template <typename T_>
	T_& Matrix<T_>::cell(olc::vu2d cords){
		return cell(cords.x, cords.y);
	}

#endif // TARA_PGE_EXTENSION


	template <typename T_>
	void Matrix<T_>::set_arr(Matrix<T_>* m) {
		assert((size == m->get_size()) &&
			"Cannot set array from different sized Matrices.");
		
		for (uint32_t i = 0; i < size; i++) {
			arr[i] = m->get_cell(i);
		}
	}

	template <typename T_>
	void Matrix<T_>::set_arr(T_* setArr) {
		for (uint32_t i = 0; i < size; i++) {
			arr[i] = setArr[i];
		}
	}

	template <typename T_>
	void Matrix<T_>::clear(T_ setVal) {
		for (uint32_t i = 0; i < size; i++) {
			arr[i] = setVal;
		}
	}
	template <typename T_>
	bool Matrix<T_>::is_in(T_ val) {
		for (uint32_t i = 0; i < size; i++) {
			if (arr[i] == val)
				return true;
		}
		return false;
	}
	
	template <typename T_>
	void Matrix<T_>::setHeightWidth(uint32_t setHeight, uint32_t setWidth) {

		width = setWidth;
		height = setHeight;
		
		T_* newArr = new T_[width * height];
		for (uint32_t i = 0; i < size; i++) {
			newArr[i] = arr[i];
		}
		for (uint32_t i = size; i < width * height; i++) {
			newArr[i] = NULL;
		}
		delete[] arr;
		arr = newArr;
		size = width * height;
	}

	template <typename T_>
	std::string Matrix<T_>::get_dim_str() {
		return "{ " + std::to_string(width) + ", " + std::to_string(height) + " }";
	}

#pragma endregion Methods

	// =========================Operators==========================
#pragma region Operators

	template <typename T_>
	Matrix<T_> operator*(Matrix<T_> a, T_ alpha) {
		T_* newArr = new T_[a.size];

		for (uint32_t i = 0; i < a.size; i++) {
			newArr[i] = alpha * a.arr[i];
		}
		return Matrix<T_>(newArr, a.width, a.height);
	}

	template <typename T_>
	Matrix<T_> operator*(T_ alpha, Matrix<T_> a) {
		return a * alpha;
	}
	template <typename T_>
	Matrix<T_> operator*(Matrix<T_> a, Matrix<T_> b) {
		assert((b.get_height() == a.get_width()) &&
			"Matrix mult error : b.height != a.width : b.height = "
			+ std::to_string(b.get_height()) + "; a.width = " + std::to_string(a.get_width()));
		


		T_* out = new T_[a.get_height() * b.get_width()];

		for (uint32_t y = 0; y < a.get_height(); y++) {
			for (uint32_t x = 0; x < b.get_width(); x++) {
				out[x + y * b.get_width()] = dotProd(a.get_rowVec(y), b.get_colVec(x));
			}
		}
		return Matrix<T_>(out, b.get_width(), a.get_height());

	}

	template <typename T_>
	Matrix<T_> operator+(Matrix<T_> a, T_ b) {
		T_* out = new T_[a.size];
		for (uint32_t i = 0; i < a.size; i++) {
			out[i] = a.arr[i] + b;
		}
		return Matrix<T_>(out, a.width, a.height);
	}
	template <typename T_>
	Matrix<T_> operator+(T_ a, Matrix<T_> b) {
		return b + a;
	}


	template <typename T_>
	bool is1x1(Matrix<T_>);

	template <typename T_>
	Matrix<T_> operator+(Matrix<T_> a, Matrix<T_> b) {
		assert((a.height == b.height || std::min(a.height, b.height) == 1) &&
			"Can not add matrices if heights are different, and no height is 1.");
		assert((a.width == b.width || std::min(a.width, b.width) == 1) &&
			"Can not add matrices if widths are different, and no width is 1.");


		if (a.height == b.height && a.width == b.width) {
			T_* newArr = new T_[a.size];

			for (uint32_t i = 0; i < a.size; i++) {
				newArr[i] = a.arr[i] + b.arr[i];
			}
			return Matrix<T_>(newArr, a.width, a.height);
		}


		// when a or b is 1x1
		if (is1x1(a)) {
			return b + a.arr[0];
		}
		if (is1x1(b)) {
			return a + b.arr[0];
		}


		// regular cases
		if (a.height == 1) {
			T_* newArr = new T_[b.size];

			for (uint32_t y = 0; y < b.height; y++)
				for (uint32_t x = 0; x < b.width; x++) {
					newArr[x + y * b.width] = b.arr[x + y * b.width] + a.arr[x];
				}
			return Matrix<T_>(newArr, b.width, b.height);
		}
		if (b.height == 1) {
			T_* newArr = new T_[a.size];

			for (uint32_t y = 0; y < a.height; y++)
				for (uint32_t x = 0; x < a.width; x++) {
					newArr[x + y * a.width] = a.arr[x + y * a.width] + b.arr[x];
				}
			return Matrix<T_>(newArr, a.width, a.height);
		}



		// copied code for widths

		if (a.width == 1) {
			T_* newArr = new T_[b.size];

			for (uint32_t y = 0; y < a.height; y++)
				for (uint32_t x = 0; x < b.width; x++) {
					newArr[x + y * b.width] = b.arr[x + y * b.width] + a.arr[y];
				}
			return Matrix<T_>(newArr, b.width, b.height);
		}
		else { // b.width == 1
			T_* newArr = new T_[a.size];

			for (uint32_t y = 0; y < b.height; y++)
				for (uint32_t x = 0; x < a.width; x++) {
					newArr[x + y * a.width] = a.arr[x + y * a.width] + b.arr[y];
				}
			return Matrix<T_>(newArr, a.width, a.height);
		}


	}

	template <typename T_>
	Matrix<T_> operator-(Matrix<T_> a, T_ b) {
		return a + (-1 * b);
	}

	template <typename T_>
	bool operator==(Matrix<T_> a, Matrix<T_> b) {
		if (a.width != b.width || a.height != b.height)
			return false;

		for (uint32_t i = 0; i < a.size; i++)
			if (a.arr[i] != b.arr[i])
				return false;

		return true;
	}
	template <typename T_>
	Matrix<T_>& Matrix<T_>::operator=(Matrix<T_> rhs) {
		delete[] arr;

		width = rhs.width;
		height = rhs.height;
		size = rhs.size;

		arr = new T_[size]();
		for (uint32_t i = 0; i < size; i++) {
			arr[i] = rhs.arr[i];
		}
		return *this;
	}
#pragma endregion Operators

} // namespace tara

// -------------------------------------------------------------------------------------------------
// ----------------------------------------OUTSIDE FUNCTIONS----------------------------------------
// -------------------------------------------------------------------------------------------------
template <typename T>
bool is1x1(tara::Matrix<T> a) {
	return (a.get_width() == 1 && a.get_height() == 1);
}

