#include "Bools.hpp"

namespace tara {
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