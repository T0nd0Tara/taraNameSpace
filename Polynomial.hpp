#pragma once

#include "Headers.hpp"
#include "MiscFuncs.hpp"

namespace tara {

	//template <typename T>
	class Polynomial {
	protected:
		int32_t* coeffs;
		uint32_t deg;

#ifndef TARA_NO_BOOST
		void ConstructByStr(std::string);
#endif // TARA_NO_BOOST

	public:
		// Copy constructor
		Polynomial(const Polynomial&);

		Polynomial(int32_t*, uint32_t);

#ifndef TARA_NO_BOOST
		Polynomial(std::string);
		Polynomial(const char*);
#endif // TARA_NO_BOOST

		~Polynomial();


		int32_t eval(int32_t);
		float   eval(float);
		double  eval(double);

		Polynomial prime();

		std::string str();

#ifdef TARA_PGE_EXTENSION
		void Draw(olc::PixelGameEngine*, olc::vi2d offset = { 0,0 }, olc::vd2d scale = { 1.0,1.0 }, double step = 0.01);
#endif // TARA_PGE_EXTENSION

		// Evals
		int32_t operator()(int32_t);
		float   operator()(float);
		double  operator()(double);

		// Multiplicity
		friend Polynomial operator*(Polynomial, int32_t);
		friend Polynomial operator*(int32_t, Polynomial);

		friend Polynomial operator-(Polynomial);

		// +/- Operators
		friend Polynomial operator+(Polynomial, Polynomial);

		friend Polynomial operator+(Polynomial, int32_t);
		friend Polynomial operator+(int32_t, Polynomial);

		friend Polynomial operator-(Polynomial, Polynomial);

		friend Polynomial operator-(int32_t, Polynomial);
		friend Polynomial operator-(Polynomial, int32_t);

		// Strings
#ifndef TARA_NO_BOOST
		friend Polynomial operator+(Polynomial, std::string);
		friend Polynomial operator+(std::string, Polynomial);

		friend Polynomial operator-(Polynomial, std::string);
		friend Polynomial operator-(std::string, Polynomial);
#endif // TARA_NO_BOOST

		friend std::ostream& operator<<(std::ostream&, Polynomial);

		friend bool operator==(Polynomial&, Polynomial&);

		Polynomial& operator=(Polynomial);

#ifndef TARA_NO_BOOST
		Polynomial& operator=(std::string);
		Polynomial& operator=(const char*);
#endif // TARA_NO_BOOST
	};

	typedef Polynomial Polynom;


}