#pragma once

#include "Headers.h"
#include "MiscFuncs.h"
 
namespace tara {
#pragma region Crockfords Base32

    inline const std::map<char, uint32_t> decoder32 = {
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
    };

    inline const std::map<uint8_t, char>  encoder32 = {
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
    };

    uint32_t decoding32(std::string str) {
        uint32_t out = 0;
        for (uint32_t i = 0; i < str.length(); i++) {
            try {
                out += decoder32.at(str[i]) * powi(32, str.length() - i - 1);
            } catch(std::out_of_range e) {
                assert(false &&
                    "A wrong character was inserted. It is not part of Crockford's Base32");
            }
        }
        return out;
    } 
    std::string encoding32(uint32_t num) {
        if (num == 0) return "0";

        std::string out = "";
        while (num != 0) {
            out.insert(0, std::string(1, encoder32.at(num % 32)));

            //num = num >> 5;
            num = num / 32;
        }
        return out;

    }
#pragma endregion
}
