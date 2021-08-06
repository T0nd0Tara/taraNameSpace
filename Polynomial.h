#pragma once

#include "Headers.h"
#include "MiscFuncs.h"

namespace tara {

	//template <typename T>
	class PolynomialInt {
	private:
		int32_t* coeffs;
		uint32_t deg;

	public:
		int32_t eval(int32_t);
		double eval(double);

#ifdef TARA_PGE_EXTENSION
		void Draw(olc::PixelGameEngine*, olc::vi2d offset = { 0,0 }, olc::vd2d scale = { 1.0,1.0 }, double step = 0.01);
#endif // TARA_PGE_EXTENSION

		PolynomialInt(int32_t*, uint32_t);

#ifndef TARA_NO_BOOST
		PolynomialInt(std::string);
#endif // TARA_NO_BOOST



		~PolynomialInt();
	};


	int32_t PolynomialInt::eval(int32_t x) {
		int32_t out = coeffs[0];

		for (uint32_t i = 1; i <= deg; i++) {
			out += coeffs[i] * powi(x, i);
		}

		return out;
	}

	double PolynomialInt::eval(double x) {
		double out = (double)coeffs[0];

		for (uint32_t i = 1; i <= deg; i++) {
			out += coeffs[i] * pow(x, i);
		}

		return out;
	}

#ifdef TARA_PGE_EXTENSION
	void PolynomialInt::Draw(olc::PixelGameEngine* pge, olc::vi2d offset, olc::vd2d scale, double step) {
		for (double x = 0.0; x < pge->ScreenWidth(); x += step) {
			pge->Draw(x, (offset.y - eval(scale.x * (x - pge->ScreenWidth() / 2 - offset.x))) * scale.y + pge->ScreenHeight() / 2);
		}
	}
#endif // TARA_PGE_EXTENSION
	// ========================Constructers========================
	PolynomialInt::PolynomialInt(int32_t* setCoeffs, uint32_t setDeg) {
		deg = setDeg;
		coeffs = new int32_t[deg + 1]();
		for (uint32_t i = 0; i <= deg; i++) {
			coeffs[i] = setCoeffs[i];
		}
	}


#ifndef TARA_NO_BOOST
	PolynomialInt::PolynomialInt(std::string in_) {
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
			for (std::string i: pySplit(x, "$")) {
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

		coeffs = new int32_t[deg+1]();
		for (uint32_t i = 0; i <= deg; i++) coeffs[i] = 0;
		for (uint32_t i = 0; i < polyTempStr1->size(); i++) {
			coeffs[polyTempPair[i].second] += polyTempPair[i].first;
		}


		delete   polyTempStr0;
		delete   polyTempStr1;
		delete[] polyTempStr2;
		delete[] polyTempPair;
	}
#endif // TARA_NO_BOOST

	PolynomialInt::~PolynomialInt() {
		delete[] coeffs;
	}

	
} // namespace tara