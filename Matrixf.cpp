#include "Matrixf.h"

// Default-constructor
Matrixf::Matrixf() { 
	_Error = "";
	_ok = true;

	width = 1;
	height = 1;
	size = 1;
	arr = new float[size];
	arr[0] = 0.0f;
}

// for array
Matrixf::Matrixf(float* setArr, int setWidth, int setHeight) { 
	_ok = true;
	_Error = "";
	
	width = setWidth;
	height = setHeight;

	size = width * height;

	arr = new float[size];

	
	for (int i = 0; i < size; i++) {
		arr[i] = *setArr;
		setArr++;
	}
}

// for vector
Matrixf::Matrixf(std::vector<float>* setVec, int setWidth) { 
	_ok = true;
	_Error = "";


	width = setWidth;
	height = setVec->size() / setWidth;

	size = setVec->size();

	arr = new float[size];

	for (float* i = arr; i < arr + size; i++) {
		*i = (*setVec)[i - arr];
	}

}

// for array of vectors
Matrixf::Matrixf(std::vector<float>* setVec, int setHeight, bool ArrayOfVectors) { 
	_ok = true;
	_Error = "";


	if (!ArrayOfVectors) {
		_ok = false;
		_Error += "Can not define Matrixf type with {std::vector<float>*, int, false} - For array of vector, initialize list have to be {std::vector<float>*, int, true}\n";
		return;
	}

	// making a copy of setVec
	std::vector<float>* setVecDup = setVec;


	// checking if input is ok
	width = setVec->size();
	for (int i = 0; i < setHeight - 1; i++) {
		setVec++;
		if (width != setVec->size()) {
			// Error
			_ok = false;
			_Error += "Can not have different sized rows inside of Matrixf type.\n";
			return;
		}
	}


	height = setHeight;
	size = width * height;
	// initialize
	arr = new float[size];
	for (int i = 0; i < height; i++) {
		vecToArr(setVecDup, arr + i*width);
		setVecDup++;
	}



}

Matrixf::Matrixf(std::vector<std::pair<float, float>>* in) {
	_ok = true;
	_Error = "";

	width = 2;
	height = in->size();

	size = (height << 1);

	arr = new float[size];

	for (int i = 0; i < size; i+=2) {
		arr[i] = (*in)[i >> 1].first;
		arr[i + 1] = (*in)[i >> 1].second;

	}
}
Matrixf::Matrixf(std::vector<Matrixf> in) {
	_ok = true;
	_Error = "";

	std::string modelDim = in[0].get_dim();

	for (Matrixf m : in) {
		if (m.get_width() != 1 && m.get_height() != 1) {
			_ok = false;
			_Error = "Cannot construct Matrixf of Marices,\nIf the vector got matrixf m, such that: m.get_width() != 1 && m.get_height() != 1\n";
			throw std::invalid_argument(_Error);
			std::cout << _Error;
			return;
		}
		if (m.get_dim() != modelDim) {
			_ok = false;
			_Error = "All matrices got to be the same dimension\n";
			throw std::invalid_argument(_Error);
			std::cout << _Error;
			return;
		}
	}



	bool Horizontals = (in[0].get_height() == 1);

	if (Horizontals) {
		height = in.size();
		width = in[0].get_width();
		size = height * width;
		
		arr = new float[size];

		for (int row = 0; row < height; row++) {
			for (int cell = 0; cell < width; cell++) {
				arr[cell + row * width] = in[row][cell];
			}
		}
	}
	else { // verticals
		height = in[0].get_height();
		width = in.size();

		size = height * width;

		arr = new float[size];

		for (int col = 0; col < width; col++) {
			for (int cell = 0; cell < height; cell++) {
				arr[col + cell * height] = in[col][cell];
			}
		}
	}
	
}
// sets all of the array to setVal
Matrixf::Matrixf(float setVal, int setWidth, int setHeight) { 
	_ok = true;
	_Error = "";
	
	width = setWidth;
	height = setHeight;
	size = width * height;

	arr = new float[size];

	for (int i = 0; i < size; i++) {
		arr[i] = setVal;
	}
}



std::string Matrixf::to_string() {
	std::string out = "{ ";
	int spaceAdd = 0;
	if (8 <= len(arr[0]))
		spaceAdd = len(arr[0]) - 8;

	for (int i = 0; i < size; i++) {
		out += std::to_string(arr[i]);

		if (i + 1 != size) {
			out += ',' + addSpace(11 - len(arr[i+1]));

			if ((i + 1) % width == 0)
				out += "\n" + addSpace(10 - len(arr[i+1]) + spaceAdd);
		}
	}

	out += " }";
	return out;
}
std::vector<float>* Matrixf::to_vec() {
	std::vector<float>* out = new std::vector<float>();

	for (int i = 0; i < size; i++) {
		out->push_back(arr[i]);
	}

	return out;
}

float Matrixf::sum() {
	float out = 0.0f;
	for (int i = 0; i < size; i++) {
		out += arr[i];
	}
	return out;
}
Matrixf Matrixf::row_sum() {
	float* temp_arr = new float[height];
	for (int i = 0; i < height; i++) {
		temp_arr[i] = get_row(i).sum();
	}
	return Matrixf(temp_arr, 1, height);
}

Matrixf Matrixf::col_sum() {
	float* temp_arr = new float[width];
	for (int i = 0; i < width; i++) {
		temp_arr[i] = get_col(i).sum();
	}
	return Matrixf(temp_arr, width, 1);
}

float Matrixf::biggest() {
	float b = arr[0];
	for (int i = 1; i < size; i++) {
		if (arr[i] > b) b = arr[i];
	}
	return b;
}

float Matrixf::smallest() {
	float s = arr[0];
	for (int i = 1; i < size; i++) {
		if (arr[i] < s) s = arr[i];
	}
	return s;
}

float Matrixf::abs_biggest() {
	float b = std::abs(arr[0]);
	for (int i = 1; i < size; i++) {
		float temp = std::abs(arr[i]);
		if (temp > b) b = temp;
	}
	return b;
}

Matrixf Matrixf::T() {
	float* out = new float[size];


	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			out[x + height * y] = arr[y + width * x];
		}
	}

	return Matrixf(out, height, width);
}

Matrixf Matrixf::Transpose() {
	return this->T();
}

Matrixf Matrixf::norm() {// returning a new Matrixf that all the values are between [-1,1]

	float b = abs_biggest();
	if (b == 0.0f)
		return *this;

	float* tempArr = new float[size];
	for (int i = 0; i < size; i++) {
		tempArr[i] = arr[i] / b;
	}
	return Matrixf(tempArr, width, height);
}

Matrixf Matrixf::get_row(int ind) {
	float* data = new float[width];

	for (int x = 0; x < width; x++) {
		data[x] = arr[x + ind * width];
	}

	return Matrixf(data, width, 1);
}

Matrixf Matrixf::get_col(int ind) {
	float* data = new float[height];

	for (int y = 0; y < height; y++) {
		data[y] = arr[ind + y * width];
	}

	return Matrixf(data, 1, height);
}

std::vector<float>* Matrixf::get_rowVec(int ind) {
	return get_row(ind).to_vec();
}

std::vector<float>* Matrixf::get_colVec(int ind) {
	return get_col(ind).to_vec();
}
float Matrixf::get_cell(int i) const{
	while (i < 0) {
		i += size;
	}
	if (i >= size) {
		// Error
		/*this->_Error += "Cannot access an indexed cell i when i >= Matrixf::size.\n";
		this->_ok = false;*/
	}
	return arr[i];
}

void Matrixf::set_cell(int i, float val) {
	arr[i] = val;
}

bool Matrixf::ok(std::string* out) const {
	*out = _Error;
	return _ok;
}

void Matrixf::setHeightWidth(int setHeight, int setWidth) {
	
	width = setWidth;
	height = setHeight;
	size = width*height;
}

std::string Matrixf::get_dim() {
	return "{ " + std::to_string(width) + ", " + std::to_string(height) + " }";
}



Matrixf operator*(Matrixf a, float alpha) {
	float* newArr = new float[a.size];

	for (int i = 0; i < a.size; i++) {
		newArr[i] = alpha * a.arr[i];
	}
	return Matrixf(newArr, a.width, a.height);
}

Matrixf operator*(float alpha, Matrixf a) {
	return a * alpha;
}

Matrixf operator*(Matrixf a, Matrixf b) {
	if (b.get_height() != a.get_width()) {
		// Error

		std::cout << "Matrix mult error: b.height != a.width";
		throw std::invalid_argument("Matrix mult error: b.height != a.width : b.height = "
			+ std::to_string(b.get_height()) + "; a.width = " + std::to_string(a.get_width()));
		
		return a;
	}


	float* out = new float[a.get_height() * b.get_width()];

	for (int y = 0; y < a.get_height(); y++) {
		for (int x = 0; x < b.get_width(); x++) {
			out[x + y * b.get_width()] = dotProd(a.get_rowVec(y), b.get_colVec(x));
		}
	}
	return Matrixf(out, b.get_width(), a.get_height());

}

Matrixf operator+(Matrixf a, float b) {
	float* out = new float[a.size];
	for (int i = 0; i < a.size; i++) {
		out[i] = a.arr[i] + b;
	}
	return Matrixf(out, a.width, a.height);
}

Matrixf operator+(float a, Matrixf b) {
	return b + a;
}

bool is1x1(Matrixf);
Matrixf operator+(Matrixf a, Matrixf b) {
	if (a.height != b.height && std::min(a.height, b.height) > 1) {
		throw std::invalid_argument("Can not add matrices if heights are different, and no height is 1.");
		return a;
	}

	if (a.width != b.width && std::min(a.width, b.width) > 1) {
		throw std::invalid_argument("Can not add matrices if widths are different, and no width is 1.");
		return a;
	}

	if (a.height == b.height && a.width == b.width) {
		float* newArr = new float[a.size];

		for (int i = 0; i < a.size; i++) {
			newArr[i] = a.arr[i] + b.arr[i];
		}
		return Matrixf(newArr, a.width, a.height);
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
		float* newArr = new float[b.size];

		for (int y = 0; y < b.height; y++)
			for (int x = 0; x < b.width; x++) {
				newArr[x + y * b.width] = b.arr[x + y * b.width] + a.arr[x];
			}
		return Matrixf(newArr, b.width, b.height);
	}
	if  (b.height == 1){
		float* newArr = new float[a.size];

		for (int y = 0; y < a.height; y++)
			for (int x = 0; x < a.width; x++) {
				newArr[x + y * a.width] = a.arr[x + y * a.width] + b.arr[x];
			}
		return Matrixf(newArr, a.width, a.height);
	}



	// copied code for widths

	if (a.width == 1) {
		float* newArr = new float[b.size];

		for(int y = 0; y < a.height; y++)
			for (int x = 0; x < b.width; x++) {
				newArr[x + y * b.width] = b.arr[x + y * b.width] + a.arr[y];
			}
		return Matrixf(newArr, b.width, b.height);
	}else { // b.width == 1
		float* newArr = new float[a.size];

		for (int y = 0; y < b.height; y++)
			for (int x = 0; x < a.width; x++) {
				newArr[x + y * a.width] = a.arr[x + y * a.width] + b.arr[y];
			}
		return Matrixf(newArr, a.width, a.height);
	}


}

Matrixf operator-(Matrixf a, float b) {
	return a + (-b);
}


bool operator==(Matrixf a, Matrixf b) {
	if (a.width != b.width || a.height != b.height)
		return false;

	for (int i = 0; i < a.size; i++)
		if (a.arr[i] != b.arr[i])
			return false;

	return true;
}


bool is1x1(Matrixf a) {
	return (a.get_width() == 1 && a.get_height() == 1);
}