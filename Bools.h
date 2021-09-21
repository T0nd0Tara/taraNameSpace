#pragma once
#include "Headers.h"
#include "MiscFuncs.h"

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
    // ========================Constructors========================
#pragma region Constructors
    Bools::Bools(uint8_t set_vals) {
        data = set_vals;
    }

    Bools::Bools(const Bools& rhs) {
        data = rhs.data;
    }

#pragma endregion Constructors

    // ==========================Methods===========================
#pragma region Methods
    bool Bools::get_val(int index) {
        return (data >> modulu(index, 8)) & 1;
    }

    void Bools::inv_val(int index) {
        data ^= 1 << modulu(index, 8);
    }

    void Bools::set_val(int index, bool val) {
        if (get_val(index) != val)
            inv_val(index);
    }

    std::string Bools::str() {
        std::string out =
            btos(get_val(7))
            + btos(get_val(6))
            + btos(get_val(5))
            + btos(get_val(4))
            + btos(get_val(3))
            + btos(get_val(2))
            + btos(get_val(1))
            + btos(get_val(0));
        return out;
    }

    std::vector<uint8_t> Bools::get_on() {
        std::vector<uint8_t> out;

        for (uint8_t i = 0; i < 8; i++)
            if (get_val(i))
                out.push_back(i);


        return out;
    }

    std::vector<uint8_t> Bools::get_off() {
        std::vector<uint8_t> out;

        for (uint8_t i = 0; i < 8; i++)
            if (!get_val(i))
                out.push_back(i);


        return out;
    }
    
#pragma endregion Methods

    //	========================Operators==========================
#pragma region Operators
    bool Bools::operator[](int index) {
        return get_val(index);
    }

    Bools& Bools::operator=(uint8_t setValue) {
        data = setValue;
        return *this;
    }

    Bools& Bools::operator=(Bools rhs) {
        data = rhs.data;
        return *this;
    }

    std::ostream& operator<<(std::ostream& out, Bools vals) {
        out << vals.str();
        return out;
    }

    Bools operator^(Bools b1, Bools b2) {
        return Bools(b1.data ^ b2.data);
    }

    Bools operator&(Bools b1, Bools b2) {
        return Bools(b1.data & b2.data);
    }

    Bools operator|(Bools b1, Bools b2) {
        return Bools(b1.data | b2.data);
    }

    Bools operator<<(Bools b, uint8_t n) {
        return Bools(b.data << n);
    }

    Bools operator>>(Bools b, uint8_t n) {
        return Bools(b.data >> n);
    }
#pragma endregion Operators
}



