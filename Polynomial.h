#pragma once

#include "Headers.h"
#include "MiscFuncs.h"

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


	// ======================Protected Funcs=======================
#pragma region Protected_Funcs
#ifndef TARA_NO_BOOST
	void Polynomial::ConstructByStr(std::string in_) {
		std::string in = in_;

		std::vector<std::string>* polyTempStr0 = new std::vector<std::string>();
		std::vector<std::string>* polyTempStr1 = new std::vector<std::string>();
		std::vector<std::string>* polyTempStr2;
		std::pair<int, uint32_t>* polyTempPair;


		pyReplace(in, " ", "");
		pyReplace(in, "-", "$-");

		// pySplit uses Boost
		*polyTempStr0 = pySplit(in, "+");

		for (std::string x : *polyTempStr0) {
			for (std::string i : pySplit(x, "$")) {
				polyTempStr1->push_back(i);
			}
		}

		polyTempStr2 = new std::vector<std::string>[polyTempStr1->size()]();

		for (uint32_t i = 0; i < polyTempStr1->size(); i++) {
			polyTempStr2[i] = pySplit((*polyTempStr1)[i], "x^");
			if (polyTempStr2[i].size() > 2) { // Error
				throw std::invalid_argument("too many instances of x^");
				return;

			}
			else if (polyTempStr2[i].size() == 1) polyTempStr2[i].push_back("0");

			if (polyTempStr2[i][0] == "") polyTempStr2[i][0] = "1";

			// make it work with -x^2 and not just -1x^2
			else if (polyTempStr2[i][0] == "-") polyTempStr2[i][0] = "-1";

		}

		polyTempPair = new std::pair<int, uint32_t>[polyTempStr1->size()]();
		for (uint32_t i = 0; i < polyTempStr1->size(); i++) {

			polyTempPair[i].first = std::stoi(polyTempStr2[i][0]);

			// can't have signed ints the exponent
			pyReplace(polyTempStr2[i][1], "-", "");
			polyTempPair[i].second = (uint32_t)std::stoi(polyTempStr2[i][1]);
		}

		deg = 0;

		for (uint32_t i = 0; i < polyTempStr1->size(); i++) {
			deg = std::max(deg, polyTempPair[i].second);
		}


		coeffs = new int32_t[deg + 1]();
		for (uint32_t i = 0; i <= deg; i++) coeffs[i] = 0;

		for (uint32_t i = 0; i < polyTempStr1->size(); i++) {
			coeffs[polyTempPair[i].second] += polyTempPair[i].first;
		}

		// making sure the most segnificent coeff != 0
		while (coeffs[deg] == 0 && deg > 0) deg--;


		delete   polyTempStr0;
		delete   polyTempStr1;
		delete[] polyTempStr2;
		delete[] polyTempPair;
	}
#endif // TARA_NO_BOOST
#pragma endregion Protected_Funcs

	// ========================Constructors========================
#pragma region Constructors
	// Copy constructor
	Polynomial::Polynomial(const Polynomial& p) {
		deg = p.deg;

		coeffs = new int32_t[deg + 1]();
		for (uint32_t i = 0; i <= deg; i++)
			coeffs[i] = p.coeffs[i];

	}

	Polynomial::Polynomial(int32_t* setCoeffs, uint32_t setDeg) {
		deg = setDeg;
		while (setCoeffs[deg] == 0 && deg > 0) deg--;

		coeffs = new int32_t[deg + 1]();
		for (uint32_t i = 0; i <= deg; i++) {
			coeffs[i] = setCoeffs[i];
		}
	}


#ifndef TARA_NO_BOOST
	Polynomial::Polynomial(std::string in_) { ConstructByStr(in_); }
	Polynomial::Polynomial(const char* in_) { ConstructByStr(std::string(in_)); }
#endif // TARA_NO_BOOST

	Polynomial::~Polynomial() {
		delete[] coeffs;
	}

#pragma endregion Constructors
	
	// ==========================Methods===========================
#pragma region Methods
	

	int32_t Polynomial::eval(int32_t x) {
		int32_t out = coeffs[0];

		for (uint32_t i = 1; i <= deg; i++) {
			out += coeffs[i] * powi(x, i);
		}

		return out;
	}
	float Polynomial::eval(float x) {
		float out = (float)coeffs[0];

		for (uint32_t i = 1; i <= deg; i++) {
			out += (float)coeffs[i] * powf(x, (float)i);
		}

		return out;
	}

	double Polynomial::eval(double x) {
		double out = (double)coeffs[0];

		for (uint32_t i = 1; i <= deg; i++) {
			out += (double)coeffs[i] * pow(x, (double)i);
		}

		return out;
	}

	Polynomial Polynomial::prime() {
		int32_t* newCoeff = new int32_t[deg]();
		for (uint32_t i = 0; i < deg; i++) {
			newCoeff[i] = coeffs[i + 1] * (i + 1);
		}
		return Polynomial(newCoeff, deg - 1);
	}

	std::string Polynomial::str() {
		if (deg == 0 && coeffs[0] == 0) return "0";

		std::string out = "";
		for (uint32_t i = deg; i > 0; i--) {
			if (coeffs[i] == 0) continue;
			if (coeffs[i] > 0 && i != deg) out += "+";

			if (coeffs[i] != 1)
				out += std::to_string(coeffs[i]);

			if (i == 1) out += "x";
			else if (i > 1) out += "x^" + std::to_string(i);
		}
		if (coeffs[0] != 0) {
			if (coeffs[0] > 0) out += "+";
			out += std::to_string(coeffs[0]);
		}
		return out;
	}

#ifdef TARA_PGE_EXTENSION
	void Polynomial::Draw(olc::PixelGameEngine* pge, olc::vi2d offset, olc::vd2d scale, double step) {
		for (double x = 0.0; x < pge->ScreenWidth(); x += step) {
			pge->Draw(x, (offset.y - eval(scale.x * (x - pge->ScreenWidth() / 2 - offset.x))) * scale.y + pge->ScreenHeight() / 2);
		}
	}
#endif // TARA_PGE_EXTENSION
#pragma endregion Methods

	//	========================Operators==========================
#pragma region Operators
	int32_t Polynomial::operator()(int32_t x) { return eval(x); }
	float   Polynomial::operator()(float x)   { return eval(x); }
	double  Polynomial::operator()(double x)  { return eval(x); }

	Polynomial operator*(Polynomial p, int32_t alpha) {
		int32_t* newCoeff = new int32_t[p.deg + 1]();
		for (uint32_t i = 0; i <= p.deg; i++) {
			newCoeff[i] = p.coeffs[i] * alpha;
		}
		return Polynomial(newCoeff, p.deg);
	}
	Polynomial operator*(int32_t alpha, Polynomial p) { return p * alpha; }

	Polynomial operator-(Polynomial p) { return -1 * p; }

	Polynomial operator+(Polynomial lhs, Polynomial rhs) {
		// making sure that lhs.deg > rhs.deg
		if (rhs.deg > lhs.deg) return rhs + lhs;

		int32_t* newCoeffs = new int32_t[lhs.deg + 1]();
		for (uint32_t i = rhs.deg + 1; i <= lhs.deg; i++) {
			newCoeffs[i] = lhs.coeffs[i];
		}

		for (uint32_t i = 0; i <= rhs.deg; i++) {
			newCoeffs[i] = lhs.coeffs[i] + rhs.coeffs[i];
		}
		return Polynomial(newCoeffs, lhs.deg);
	}

	Polynomial operator+(Polynomial p, int32_t alpha) {
		int32_t* newCoeffs = new int32_t[p.deg + 1]();
		for (uint32_t i = 1; i <= p.deg; i++)
			newCoeffs[i] = p.coeffs[i];

		newCoeffs[0] = p.coeffs[0] + alpha;

		return Polynomial(newCoeffs, p.deg);
	}
	Polynomial operator+(int32_t alpha, Polynomial p) { return p + alpha; }

	Polynomial operator-(Polynomial lhs, Polynomial rhs) { return lhs + (-rhs); };

	Polynomial operator-(int32_t alpha, Polynomial p) { return (-p) + alpha; }
	Polynomial operator-(Polynomial p, int32_t alpha) { return p + (-alpha); }

#ifndef TARA_NO_BOOST
	Polynomial operator+(Polynomial p, std::string str) { return p + Polynomial(str); }
	Polynomial operator+(std::string str, Polynomial p) { return p + Polynomial(str); }

	Polynomial operator-(Polynomial p, std::string str) { return  p - Polynomial(str); }
	Polynomial operator-(std::string str, Polynomial p) { return -p + Polynomial(str); }
#endif // TARA_NO_BOOST

	std::ostream& operator<<(std::ostream& out, Polynomial p) {
		out << p.str();
		return out;
	}

	bool operator==(Polynomial& lhs, Polynomial& rhs) {
		if (lhs.deg != rhs.deg) return false;

		for (uint32_t i = 0; i <= lhs.deg; i++) 
			if (lhs.coeffs[i] != rhs.coeffs[i]) return false;

		return true;
	}

	Polynomial& Polynomial::operator=(Polynomial rhs) {
		delete[] coeffs;

		deg = rhs.deg;
		coeffs = new int32_t[deg + 1]();
		for (uint32_t i = 0; i <= deg; i++) {
			coeffs[i] = rhs.coeffs[i];
		}
		return *this;
	}

#ifndef TARA_NO_BOOST
	Polynomial& Polynomial::operator=(std::string rhs) {
		ConstructByStr(rhs);
		return *this;
	}

	Polynomial& Polynomial::operator=(const char* rhs) {
		ConstructByStr(std::string(rhs));
		return *this;
	}
#endif // TARA_NO_BOOST
#pragma endregion Operators


} // namespace tara