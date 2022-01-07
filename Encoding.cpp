#include "Encoding.hpp"

namespace tara {
    size_t decoding32(std::string str) {
        size_t out = 0;
        for (size_t i = 0; i < str.length(); i++) {
            try {
                out += (size_t)decoder32(str[i]) * powi(32, str.length() - i - 1);
            }
            catch (std::out_of_range& e) {
                printError("A wrong character was inserted. '" + std::string(1, str[i]) + "' is not part of Crockford's Base32");
            }
        }
        return out;
    }

    std::string encoding32(size_t num) {
        if (num == 0) return "0";

        std::string out = "";
        while (num != 0) {
            out.insert(0, std::string(1, encoder32(num & 0x1F /*equiv to num % 32 */)));

            num = num >> 5;
            // equiv to num = num / 32;
        }
        return out;

    }

    // AES - encryption
    // Uses 16 byte of data and 128 bit key (so 10 rounds)
    void* AES_en(void* data, void* key, sbox::s_box* sbox) {
        printError("this function has not been implemented yet...", nullptr, true, true);
        assert(sbox->in_bits == sbox->out_bits &&
            sbox->in_bits == 8);

        // ------------ initializing ------------

        uint8_t* uData = (uint8_t*)data;

        uint8_t** rows_a = new uint8_t * [4];
        uint8_t** rows_b = new uint8_t * [4];
        for (uint8_t i = 0; i < 4; i++) {
            rows_a[i] = new uint8_t[4];
            rows_b[i] = new uint8_t[4];
        }

        for (uint8_t i = 0; i < 16; i++) {
            //    [i>> 2][i & 3]
            rows_a[i / 4][i % 4] = *uData;
            rows_b[i / 4][i % 4] = *(uint8_t*)sbox->conv(uData++);
        }

        // ------------ rotating ------------
        {
            auto ROTL4 = [](uint8_t* arr, uint8_t i) {
                for (uint8_t j = 0; j < i; j++) {
                    uint8_t temp = arr[0];
                    arr[0] = arr[1];
                    arr[1] = arr[2];
                    arr[2] = arr[3];
                    arr[3] = temp;
                }
            };
            for (uint8_t i = 0; i < 4; i++) ROTL4(rows_a[i], i);
        }

        // TODO
        // Mixing columns
        // Adding round key

        // ------------ Garbage Collection------------
        for (uint8_t i = 0; i < 4; i++)
            delete[] rows_a[i], rows_b[i];

        delete[] rows_a, rows_b;

        return nullptr;
    }
    void* AES_de(void* data, void* key, sbox::s_box* sbox) {
        printError("this function has not been implemented yet...", nullptr, true, true);
        return nullptr;
    }
}