#pragma once

#include "Headers.h"
#include "MiscFuncs.h"

class word32;

namespace tara {
#pragma region Crockfords Base32

    size_t decoding32(std::string str) {
        size_t out = 0;
        for (size_t i = 0; i < str.length(); i++) {
            try {
                out += (size_t)decoder32(str[i]) * powi(32, str.length() - i - 1);
            } catch(std::out_of_range& e) {
                printError("A wrong character was inserted. '" + std::string(1 ,str[i]) + "' is not part of Crockford's Base32");
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
    // ========================Constructors========================
#pragma region Constructers
    word32::word32() {
        a = 0U;
        b = 0U;
        c = 0U;
        d = 0U;
        e = 0U;
    }

    word32::word32(const word32& in) {
        a = in.a;
        b = in.b;
        c = in.c;
        d = in.d;
        e = in.e;
    }
    word32::word32(uint8_t e_, uint8_t d_, uint8_t c_, uint8_t b_, uint8_t a_) {
        this->e = e_;
        this->d = d_;
        this->c = c_;
        this->b = b_;
        this->a = a_;
    }
    word32::word32(std::string in) {
        ConstructByStr(in);
    }

    word32::word32(uint64_t in) {
        e = in >> 32;
        d = in >> 24;
        c = in >> 16;
        b = in >> 8;
        a = in;
    }
#pragma endregion
    // ==========================Methods===========================
#pragma region Methods
    void word32::ConstructByStr(std::string in) {
        if (in.length() > 8)
            in = in.substr(0U, 8);
        else while (in.length() < 8) {
            in.insert(in.begin(), '0');
        }


        set_char(decoder32(in[0]), 7);
        set_char(decoder32(in[1]), 6);
        set_char(decoder32(in[2]), 5);
        set_char(decoder32(in[3]), 4);
        set_char(decoder32(in[4]), 3);
        set_char(decoder32(in[5]), 2);
        set_char(decoder32(in[6]), 1);
        set_char(decoder32(in[7]), 0);

    }

    void word32::set_char(uint8_t val, uint8_t index) {
        val = modulu(val, (uint8_t)32);
        switch (modulu(index, (uint8_t)8)) {
        case 0:
            a = (a & 0xE0) | val;
            return;
        case 1:
            a = (a & 0x1F) | (val << 5);
            b = (b & 0xFC) | (val >> 3);
            return;
        case 2:
            b = (b & 0x83) | (val << 2);
            return;
        case 3:
            b = (b & 0x7F) | (val << 7);
            c = (c & 0xF0) | (val >> 1);
            return;
        case 4:
            c = (c & 0x0F) | (val << 4);
            d = (d & 0xFE) | (val >> 4);
            return;
        case 5:
            d = (d & 0xC1) | (val << 1);
            return;
        case 6:
            d = (d & 0x3F) | (val << 6);
            e = (e & 0xF8) | (val >> 2);
            return;
        case 7:
            e = (e & 0x7) | (val << 3);
            return;
        }

        printError("modulu returned value "
            + std::to_string(modulu((uint8_t)index, (uint8_t)8))
            + ", which is not between 0 and 7.\nPlease contact develepors if you encounter this error.\n");
    }

    uint8_t word32::get_char(uint8_t index) {
        switch (modulu(index, (uint8_t)8)) {
        case 0:
            return a & 0x1F;
        case 1:
            return (a >> 5) | ((b & 3) << 3);
        case 2:
            return (b >> 2) & 0x1F;
        case 3:
            return (b >> 7) | ((c & 0xF) << 1);
        case 4:
            return (c >> 4) | ((d & 1) << 4);
        case 5:
            return (d >> 1) & 0x1F;
        case 6:
            return (d >> 6) | ((e & 0b111) << 2);
        case 7:
            return e >> 3;
        }
        printError("modulu returned value "
            + std::to_string(modulu(index, (uint8_t)8))
            + ", which is not between 0 and 7.\nPlease contact develepors if you encounter this error.\n");

        // to not have a warning :b
        return 0;
    }

    std::string word32::to_str() {
        std::string out = "";
        try {
            out = std::string(1, encoder32(get_char(7)))
                + std::string(1, encoder32(get_char(6)))
                + std::string(1, encoder32(get_char(5)))
                + std::string(1, encoder32(get_char(4)))
                + std::string(1, encoder32(get_char(3)))
                + std::string(1, encoder32(get_char(2)))
                + std::string(1, encoder32(get_char(1)))
                + std::string(1, encoder32(get_char(0)));
        }
        catch (std::out_of_range& e) {
            printError("Can't convert to string", &e);
        }
        return out;
    }

    const char* word32::c_str() {
        return to_str().c_str();
    }

    uint64_t word32::data() {
        return (
            ((uint64_t)e << 32) |
            ((uint64_t)d << 24) |
            ((uint64_t)c << 16) |
            ((uint64_t)b << 8 ) |
             (uint64_t)a
            );
    }
#pragma endregion

    // =========================Operators==========================
#pragma region Operators
    word32& word32::operator=(word32& in) {
        a = in.a;
        b = in.b;
        c = in.c;
        d = in.d;
        e = in.e;
        return *this;
    }
    word32& word32::operator=(std::string in) {
        ConstructByStr(in);
        return *this;
    }

    word32& word32::operator=(size_t in) {
        ConstructByStr(encoding32(in));
        return *this;
    }

    word32 word32::operator|(uint64_t val) {
        return word32( data() | val
            /*e | ((val >> 32) & 0xFF),
            d | ((val >> 24) & 0xFF),
            c | ((val >> 16) & 0xFF),
            b | ((val >> 8 ) & 0xFF),
            a | ((val >> 0 ) & 0xFF)*/
        );
    }

    word32 word32::operator&(uint64_t val) {
        return word32( data() & val
            /*e & ((val >> 32) & 0xFF),
            d & ((val >> 24) & 0xFF),
            c & ((val >> 16) & 0xFF),
            b & ((val >> 8 ) & 0xFF),
            a & ((val >> 0 ) & 0xFF)*/
        );
    }

    word32 word32::operator^(uint64_t val) {
        return word32( data() ^ val
            /*e ^ ((val >> 32) & 0xFF),
            d ^ ((val >> 24) & 0xFF),
            c ^ ((val >> 16) & 0xFF),
            b ^ ((val >> 8 ) & 0xFF),
            a ^ ((val >> 0 ) & 0xFF)*/
        );
    }

    word32 operator|(word32 lhs, word32 rhs) {
        return word32(
            lhs.e | rhs.e,
            lhs.d | rhs.d,
            lhs.c | rhs.c,
            lhs.b | rhs.b,
            lhs.a | rhs.a
        );
    }
    word32 operator&(word32 lhs, word32 rhs) {
        return word32(
            lhs.e & rhs.e,
            lhs.d & rhs.d,
            lhs.c & rhs.c,
            lhs.b & rhs.b,
            lhs.a & rhs.a
            );
    }
    word32 operator^(word32 lhs, word32 rhs) {
        return word32(
            lhs.e ^ rhs.e,
            lhs.d ^ rhs.d,
            lhs.c ^ rhs.c,
            lhs.b ^ rhs.b,
            lhs.a ^ rhs.a
            );
    }

    word32 operator<<(word32 lhs, uint8_t rhs) {
        uint8_t
            e_ = lhs.e,
            d_ = lhs.d,
            c_ = lhs.c,
            b_ = lhs.b,
            a_ = lhs.a;

        for (uint8_t i = 0; i < rhs; i++) {
            e_ = (e_ << 1) | (d_ >> 7);
            d_ = (d_ << 1) | (c_ >> 7);
            c_ = (c_ << 1) | (b_ >> 7);
            b_ = (b_ << 1) | (a_ >> 7);
            a_ = a_ << 1;
        }

        return word32(e_, d_, c_, b_, a_);
    }

    word32 operator>>(word32 lhs, uint8_t rhs) {
        uint8_t
            e_ = lhs.e,
            d_ = lhs.d,
            c_ = lhs.c,
            b_ = lhs.b,
            a_ = lhs.a;

        for (uint8_t i = 0; i < rhs; i++) {
            a_ = (a_ >> 1) | (b_ << 7);
            b_ = (b_ >> 1) | (c_ << 7);
            c_ = (c_ >> 1) | (d_ << 7);
            d_ = (d_ >> 1) | (e_ << 7);
            e_ = e_ >> 1;
        }

        return word32(e_, d_, c_, b_, a_);
    }

#pragma endregion
#pragma endregion Crockfords Base32

#pragma region encryption

    namespace sbox {
        class s_box {
        public:
            const size_t in_bits = 0, out_bits = 0;
            s_box() {}

            virtual void* conv(void* data)   const = 0;
            virtual void* deconv(void* data) const = 0;
        };

        class des_s5 : s_box {
        public:
            const size_t in_bits = 6, out_bits = 4;

            void* conv(void* data)   const override {
                uint8_t in = *(uint8_t*)data;

                std::vector<std::vector<uint8_t>> s = {
                    {0b0010, 0b1110, 0b0100, 0b1011}, // 0b0000
                    {0b1100, 0b1011, 0b0010, 0b1000}, // 0b0001
                    {0b0100, 0b0010, 0b0001, 0b1100}, // 0b0010
                    {0b0001, 0b1100, 0b1011, 0b0111}, // 0b0011

                    {0b0111, 0b0100, 0b1010, 0b0001}, // 0b0100
                    {0b1010, 0b0111, 0b1101, 0b1110}, // 0b0101
                    {0b1011, 0b1101, 0b0111, 0b0010}, // 0b0110
                    {0b0110, 0b0001, 0b1000, 0b1101}, // 0b0111

                    {0b1000, 0b0101, 0b1111, 0b0110}, // 0b1000
                    {0b0101, 0b0000, 0b1001, 0b1111}, // 0b1001
                    {0b0011, 0b1111, 0b1100, 0b0000}, // 0b1010
                    {0b1111, 0b1010, 0b0101, 0b1001}, // 0b1011

                    {0b1101, 0b0011, 0b0110, 0b1010}, // 0b1100
                    {0b0000, 0b1001, 0b0011, 0b0100}, // 0b1101
                    {0b1110, 0b1000, 0b0000, 0b0101}, // 0b1110
                    {0b1001, 0b0110, 0b1110, 0b0011}  // 0b1111
                };
                return (void*)&s[(in >> 1) & 0b1111][(in & 1) | ((in >> 5) & 1)];
            }

            void* deconv(void* data) const override {
                printError("FETAL ERROR: DES S5 is not 'one to one' function - therefore it doesn't have a deconv.");
                return nullptr;
            }
        };

        class Rijndael : s_box {
        public:
            const size_t in_bits = 8, out_bits = 8;


            void* conv(void* data) const {
                uint8_t in = *(uint8_t*)data;
                // cause who doesn't like a large block of values :)
                uint8_t s[256] = {
                     0x63 ,0x7c ,0x77 ,0x7b ,0xf2 ,0x6b ,0x6f ,0xc5 ,0x30 ,0x01 ,0x67 ,0x2b ,0xfe ,0xd7 ,0xab ,0x76
                    ,0xca ,0x82 ,0xc9 ,0x7d ,0xfa ,0x59 ,0x47 ,0xf0 ,0xad ,0xd4 ,0xa2 ,0xaf ,0x9c ,0xa4 ,0x72 ,0xc0
                    ,0xb7 ,0xfd ,0x93 ,0x26 ,0x36 ,0x3f ,0xf7 ,0xcc ,0x34 ,0xa5 ,0xe5 ,0xf1 ,0x71 ,0xd8 ,0x31 ,0x15
                    ,0x04 ,0xc7 ,0x23 ,0xc3 ,0x18 ,0x96 ,0x05 ,0x9a ,0x07 ,0x12 ,0x80 ,0xe2 ,0xeb ,0x27 ,0xb2 ,0x75
                    ,0x09 ,0x83 ,0x2c ,0x1a ,0x1b ,0x6e ,0x5a ,0xa0 ,0x52 ,0x3b ,0xd6 ,0xb3 ,0x29 ,0xe3 ,0x2f ,0x84
                    ,0x53 ,0xd1 ,0x00 ,0xed ,0x20 ,0xfc ,0xb1 ,0x5b ,0x6a ,0xcb ,0xbe ,0x39 ,0x4a ,0x4c ,0x58 ,0xcf
                    ,0xd0 ,0xef ,0xaa ,0xfb ,0x43 ,0x4d ,0x33 ,0x85 ,0x45 ,0xf9 ,0x02 ,0x7f ,0x50 ,0x3c ,0x9f ,0xa8
                    ,0x51 ,0xa3 ,0x40 ,0x8f ,0x92 ,0x9d ,0x38 ,0xf5 ,0xbc ,0xb6 ,0xda ,0x21 ,0x10 ,0xff ,0xf3 ,0xd2
                    ,0xcd ,0x0c ,0x13 ,0xec ,0x5f ,0x97 ,0x44 ,0x17 ,0xc4 ,0xa7 ,0x7e ,0x3d ,0x64 ,0x5d ,0x19 ,0x73
                    ,0x60 ,0x81 ,0x4f ,0xdc ,0x22 ,0x2a ,0x90 ,0x88 ,0x46 ,0xee ,0xb8 ,0x14 ,0xde ,0x5e ,0x0b ,0xdb
                    ,0xe0 ,0x32 ,0x3a ,0x0a ,0x49 ,0x06 ,0x24 ,0x5c ,0xc2 ,0xd3 ,0xac ,0x62 ,0x91 ,0x95 ,0xe4 ,0x79
                    ,0xe7 ,0xc8 ,0x37 ,0x6d ,0x8d ,0xd5 ,0x4e ,0xa9 ,0x6c ,0x56 ,0xf4 ,0xea ,0x65 ,0x7a ,0xae ,0x08
                    ,0xba ,0x78 ,0x25 ,0x2e ,0x1c ,0xa6 ,0xb4 ,0xc6 ,0xe8 ,0xdd ,0x74 ,0x1f ,0x4b ,0xbd ,0x8b ,0x8a
                    ,0x70 ,0x3e ,0xb5 ,0x66 ,0x48 ,0x03 ,0xf6 ,0x0e ,0x61 ,0x35 ,0x57 ,0xb9 ,0x86 ,0xc1 ,0x1d ,0x9e
                    ,0xe1 ,0xf8 ,0x98 ,0x11 ,0x69 ,0xd9 ,0x8e ,0x94 ,0x9b ,0x1e ,0x87 ,0xe9 ,0xce ,0x55 ,0x28 ,0xdf
                    ,0x8c ,0xa1 ,0x89 ,0x0d ,0xbf ,0xe6 ,0x42 ,0x68 ,0x41 ,0x99 ,0x2d ,0x0f ,0xb0 ,0x54 ,0xbb ,0x16
                };

                void* out = &s[(in & 0xF) + 16 * (in >> 4)];
                return out;
            }

            void* deconv(void* data) const {
                uint8_t in = *(uint8_t*)data;
                uint8_t s[256] = {
                    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
                    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
                    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
                    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
                    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
                    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
                    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
                    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
                    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
                    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
                    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
                    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
                    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
                    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
                    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
                    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
                };

                void* out = &s[(in & 0xF) + 16 * (in >> 4)];
                return out;
            }


        };
    };


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
#pragma endregion encryption
}
