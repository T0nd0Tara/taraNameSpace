#pragma once
#include "Headers.h"
#include "MiscFuncs.h"



namespace tara {


    struct Bools {
        uint8_t data = 0x00;

        bool get_val(int index) {
            return (data >> modulu(index, 8)) & 1;
        }
        void inv_val(int index) {
            data ^= 1 << modulu(index, 8);
        }

        void set_val(int index, bool val) {
            if (get_val(index) != val)
                inv_val(index);
        }

        bool operator[](int index) {
            //return (data>>index) & 1;
            return get_val(index);
        }

        friend std::ostream& operator<<(std::ostream& out, Bools vals) {
            out << vals[7]
                << vals[6]
                << vals[5]
                << vals[4]
                << vals[3]
                << vals[2]
                << vals[1]
                << vals[0];
            return out;
        }

        friend Bools operator^(Bools b1, Bools b2) {
            return Bools(b1.data ^ b2.data);
        }

        friend Bools operator&(Bools b1, Bools b2) {
            return Bools(b1.data & b2.data);
        }

        friend Bools operator|(Bools b1, Bools b2) {
            return Bools(b1.data | b2.data);
        }

        friend Bools operator<<(Bools b, int n) {
            return Bools(b.data << n);
        }

        friend Bools operator>>(Bools b, int n) {
            return Bools(b.data >> n);
        }


        // friend bools operator^(bools b1, char n){
        //     return bools(b1.data ^ n);
        // }

        // friend bools operator&(bools b1, char n){
        //     return bools(b1.data & n);
        // }

        // friend bools operator|(bools b1, char n){
        //     return bools(b1.data | n);
        // }



        void reset(int index) { set_val(index, false); }

        void off(int index) { set_val(index, false); }

        void on(int index) { set_val(index, true); }

        void flip(int index) { inv_val(index); }


        std::vector<uint8_t> get_on() {
            std::vector<uint8_t> out;

            for (uint8_t i = 0; i < 8; i++)
                if (get_val(i))
                    out.push_back(i);


            return out;
        }

        std::vector<uint8_t> get_off() {
            std::vector<uint8_t> out;

            for (uint8_t i = 0; i < 8; i++)
                if (!get_val(i))
                    out.push_back(i);


            return out;
        }

        Bools(uint8_t set_vals = 0x00) {
            data = set_vals;
        }
    };

    
}



std::string to_str(tara::Bools in) {
    std::string out;
    out += btos(in[7]);
    out += btos(in[6]);
    out += btos(in[5]);
    out += btos(in[4]);
    out += btos(in[3]);
    out += btos(in[2]);
    out += btos(in[1]);
    out += btos(in[0]);

    return out;
}