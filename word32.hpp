#pragma once
#include "Headers.hpp"
#include "MiscFuncs.hpp"
#include "Encoding.hpp"
namespace tara {

    // an 8 character string in 5 bit chars
   // every char is in base 32
    class word32 {
    protected:
        /*
        cell          :    7           6              5            4           3             2             1           0
        representation:_ _ _ _ _ | _ _ _ ~ _ _ | _ _ _ _ _ | _ ~ _ _ _ _ | _ _ _ _ ~ _ | _ _ _ _ _ | _ _ ~ _ _ _ | _ _ _ _ _
        container     :e---------------e   d-----------------d   c---------------c   b-----------------b   a---------------a
        */
        uint8_t e, d, c, b, a;

        void ConstructByStr(std::string);

    public:
        void set_char(uint8_t val, uint8_t index);
    public:
        word32();
        word32(const word32&);
        word32(uint8_t e, uint8_t d, uint8_t c, uint8_t b, uint8_t a);
        word32(std::string in);
        word32(uint64_t in);

        uint8_t get_char(uint8_t index);

        std::string to_str();
        const char* c_str();
        uint64_t data();

        word32& operator=(word32&);
        word32& operator=(std::string);
        word32& operator=(size_t);

        word32  operator|(uint64_t);
        word32  operator&(uint64_t);
        word32  operator^(uint64_t);

        friend word32 operator|(word32, word32);
        friend word32 operator&(word32, word32);
        friend word32 operator^(word32, word32);

        friend word32 operator<<(word32, uint8_t);
        friend word32 operator>>(word32, uint8_t);

        uint8_t operator[](uint8_t index) { return get_char(index); }

        friend std::ostream& operator<<(std::ostream& out, word32 a) {
            out << a.to_str();
            return out;
        }

    };
}