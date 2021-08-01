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
				-Fixing the warning from Matrix friend methods

					by putting "template <typename T__>" before them
				
 */
#pragma once
#include "..\Matrix.h"
#include "..\Bools.h"
