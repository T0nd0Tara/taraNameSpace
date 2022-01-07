/*
____________________________________
____________________________________

  _                  _   _  _____
 | |                | \ | |/ ____|
 | |_ __ _ _ __ __ _|  \| | (___
 | __/ _` | '__/ _` | . ` |\___ \
 | || (_| | | | (_| | |\  |____) |
  \__\__,_|_|  \__,_|_| \_|_____/

_____________________________________
_____________________________________

created by: Amir Secemsky aka T0nd0Tara
	

Updates:
	21.7.2021:	
			-writing this :D

			-adding olc::vi2d input to Matrix object
				can be accessed by putting 
				#define TARA_PGE_EXTENSION
				before including taraNS.h
				and after including olcPixelGameEngine.h


	25.7.2021:
			-adding "is_in" functions
				both to std::vector and tara::Matrix

	1.8.2021:
			-fixing the warning from Matrix friend methods

			-adding Polynomial class

	2.8.2021:
			-adding pySplit + pyReplace

			-adding option to not include boost
				by using #define TARA_NO_BOOST

	5.8.2021:
			-adding modulu function

			-changing int to uint32_t for tara::Matrix<T_>::width,height,size

			-changing methods of tara::Matrix to use the modulu function

			-adding PolynomialInt(std::string) method


	6.8.2021:
			-adding PolynomialInt::Draw for olc::PixelGameEngine support

			-adding an example for PolynomialInt::Draw
				
 */

#pragma once
//#include "..\MiscFuncs.hpp"
#include "..\Polynomial.hpp"
#include "..\Matrix.hpp"
#include "..\Bools.hpp"
#include "..\Encoding.hpp"
