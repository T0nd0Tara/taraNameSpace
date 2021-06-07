#pragma once
#include "Headers.h"

namespace tara {
	class Matrixf
	{
	private:
		int width, height, size;
		float* arr;


		bool _ok = true;

		std::string _Error = "";

	public:



		Matrixf();
		Matrixf(float*, int, int); // array, width, height
		Matrixf(std::vector<float>*, int);
		Matrixf(std::vector<float>*, int, bool);
		Matrixf(std::vector<std::pair<float, float>>*);
		Matrixf(std::vector<Matrixf>);

		Matrixf(float, int, int);


		std::string to_string();
		std::vector<float>* to_vec();

		float sum();
		Matrixf row_sum();
		Matrixf col_sum();

		float biggest();
		float smallest();

		float abs_biggest();

		Matrixf T();
		Matrixf Transpose();

		Matrixf norm();

		int get_width()  const { return width; }
		int get_height() const { return height; }
		int get_size() const { return size; }

		Matrixf get_row(int);
		Matrixf get_col(int);

		std::vector<float>* get_rowVec(int);
		std::vector<float>* get_colVec(int);

		float get_cell(int) const;

		void set_cell(int, float);

		bool ok(std::string*) const;

		void setHeightWidth(int, int);
		std::string get_dim();



		float operator[](int index) {
			return arr[index];
		}

		friend Matrixf operator*(Matrixf, float);
		friend Matrixf operator*(float, Matrixf);
		friend Matrixf operator*(Matrixf, Matrixf);

		friend Matrixf operator+(Matrixf, float);
		friend Matrixf operator+(float, Matrixf);
		friend Matrixf operator+(Matrixf, Matrixf);

		friend Matrixf operator-(Matrixf, float);


		friend std::ostream& operator<<(std::ostream& out, Matrixf a) {
			out << a.to_string();
			return out;
		}

		friend bool operator==(Matrixf, Matrixf);

	};
}
