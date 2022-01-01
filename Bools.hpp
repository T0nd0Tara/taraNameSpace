#pragma once
#include "Headers.hpp"
#include "MiscFuncs.hpp"

// This class is a way to utilize all of your memory with booleans
// 
// Every regular bool takes 1 whole byte, therefore 8 bools will take up 8 bytes
// tara::Bools make it easy to use 8 bools in 1 byte

namespace tara {


    class Bools {
        uint8_t data = 0x00;

    public:
        Bools(uint8_t set_vals = 0x00);

        Bools(const Bools&);

        bool get_val(int);
        void inv_val(int);

        void set_val(int, bool);


        std::string str();

        void reset(int index) { set_val(index, false); }

        void off(int index) { set_val(index, false); }

        void on(int index) { set_val(index, true); }

        void flip(int index) { inv_val(index); }


        std::vector<uint8_t> get_on();

        std::vector<uint8_t> get_off();

        bool operator[](int);

        Bools& operator=(uint8_t);
        Bools& operator=(Bools);

        friend std::ostream& operator<<(std::ostream&, Bools);


        friend Bools operator^(Bools, Bools);

        friend Bools operator&(Bools, Bools);

        friend Bools operator|(Bools, Bools);

        friend Bools operator<<(Bools, uint8_t);

        friend Bools operator>>(Bools, uint8_t);


        // friend bools operator^(bools b1, char n){
        //     return bools(b1.data ^ n);
        // }

        // friend bools operator&(bools b1, char n){
        //     return bools(b1.data & n);
        // }

        // friend bools operator|(bools b1, char n){
        //     return bools(b1.data | n);
        // }


    };
}
