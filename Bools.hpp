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
#pragma region Constructors
        Bools(uint8_t set_vals = 0x00) : data(set_vals) {}

        Bools(const Bools& rhs) : data(rhs.data) {}
#pragma endregion
#pragma region Methods
        bool get_val(int index) const { return (data >> mf::modulo(index, 8)) & 1; }
        void inv_val(int index) { data ^= 1 << mf::modulo(index, 8); }

        void set_val(int index, bool val) {
            if (get_val(index) != val)
                inv_val(index);
        }


        std::string str() const {
            std::string out =
                  mf::btos(get_val(7))
                + mf::btos(get_val(6))
                + mf::btos(get_val(5))
                + mf::btos(get_val(4))
                + mf::btos(get_val(3))
                + mf::btos(get_val(2))
                + mf::btos(get_val(1))
                + mf::btos(get_val(0));
            return out;
        }

        void reset(int index) { set_val(index, false); }

        void off(int index) { set_val(index, false); }

        void on(int index) { set_val(index, true); }

        void flip(int index) { inv_val(index); }


        std::vector<uint8_t> get_on() const {
            std::vector<uint8_t> out;

            for (uint8_t i = 0; i < 8; i++)
                if (get_val(i))
                    out.push_back(i);

            return out;
        }

        std::vector<uint8_t> get_off() const {
            std::vector<uint8_t> out;

            for (uint8_t i = 0; i < 8; i++)
                if (!get_val(i))
                    out.push_back(i);

            return out;
        }
#pragma endregion
#pragma region Operators
        bool operator[](int index) const { return get_val(index); }

        Bools& operator=(uint8_t setValue) {
            data = setValue;
            return *this;
        }
        Bools& operator=(Bools rhs) {
            data = rhs.data;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& out, Bools vals) {
            out << vals.str();
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

        friend Bools operator<<(Bools b, uint8_t n) {
            return Bools(b.data << n);
        }

        friend Bools operator>>(Bools b, uint8_t n) {
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

#pragma endregion
    };
}
