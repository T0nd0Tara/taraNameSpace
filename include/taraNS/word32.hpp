#pragma once
#include "..\..\Headers.hpp"
#include "mf.hpp"

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

		void ConstructByStr(std::string in) {
			if (in.length() > 8)
				in = in.substr(0U, 8);
			else while (in.length() < 8) {
				in.insert(in.begin(), '0');
			}


			set_char(mf::decoder32(in[0]), 7);
			set_char(mf::decoder32(in[1]), 6);
			set_char(mf::decoder32(in[2]), 5);
			set_char(mf::decoder32(in[3]), 4);
			set_char(mf::decoder32(in[4]), 3);
			set_char(mf::decoder32(in[5]), 2);
			set_char(mf::decoder32(in[6]), 1);
			set_char(mf::decoder32(in[7]), 0);

		}

	public:
		void set_char(uint8_t val, uint8_t index) {
			val = mf::modulo(val, (uint8_t)32);
			switch (mf::modulo(index, (uint8_t)8)) {
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

			mf::printError("modulu returned value "
				+ std::to_string(mf::modulo((uint8_t)index, (uint8_t)8))
				+ ", which is not between 0 and 7.\nPlease contact develepors if you encounter this error.\n");
		}
	public:
#pragma region Constructors
		word32() : a(0u), b(0u), c(0u), d(0u), e(0u) {}
		word32(const word32& in) : a(in.a), b(in.b), c(in.c), d(in.d), e(in.e) {}
		word32(uint8_t e_, uint8_t d_, uint8_t c_, uint8_t b_, uint8_t a_) :
			e(e_), d(d_), c(c_), b(b_), a(a_) {}
		word32(std::string in) { ConstructByStr(in); }
		word32(uint64_t in) :
			e(in >> 32), d(in >> 24), c(in >> 16), b(in >> 8), a(in) {}
#pragma endregion
#pragma region Methods
		uint8_t get_char(uint8_t index) {
			switch (mf::modulo(index, (uint8_t)8)) {
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
			mf::printError("modulu returned value "
				+ std::to_string(mf::modulo(index, (uint8_t)8))
				+ ", which is not between 0 and 7.\nPlease contact develepors if you encounter this error.\n");

			// to not have a warning :b
			return 0;
		}

		std::string to_str() {
			std::string out = "";
			try {
				out = std::string(1, mf::encoder32(get_char(7)))
					+ std::string(1, mf::encoder32(get_char(6)))
					+ std::string(1, mf::encoder32(get_char(5)))
					+ std::string(1, mf::encoder32(get_char(4)))
					+ std::string(1, mf::encoder32(get_char(3)))
					+ std::string(1, mf::encoder32(get_char(2)))
					+ std::string(1, mf::encoder32(get_char(1)))
					+ std::string(1, mf::encoder32(get_char(0)));
			}
			catch (std::out_of_range& e) {
				mf::printError("Can't convert to string", &e);
			}
			return out;
		}

		const char* c_str() { 
			std::string s = to_str();
			const char* out = s.c_str();
			return out;
		}
		uint64_t data() {
			return (
				((uint64_t)e << 32) |
				((uint64_t)d << 24) |
				((uint64_t)c << 16) |
				((uint64_t)b << 8)  |
				(uint64_t)a
				);
		}
#pragma endregion
#pragma region Operators
		word32& operator=(word32& in){
			a = in.a;
			b = in.b;
			c = in.c;
			d = in.d;
			e = in.e;

			return *this;
		}
		word32& operator=(std::string in) {
			ConstructByStr(in);
			return *this;
		}
		word32& operator=(size_t in) {
			ConstructByStr(mf::encoding32(in));
			return *this;
			
		}

		word32  operator|(uint64_t val) { return word32(data() | val); }
		word32  operator&(uint64_t val) { return word32(data() & val); }
		word32  operator^(uint64_t val) { return word32(data() ^ val); }

		friend word32 operator|(word32 lhs, word32 rhs) {
			return word32(
				lhs.e | rhs.e,
				lhs.d | rhs.d,
				lhs.c | rhs.c,
				lhs.b | rhs.b,
				lhs.a | rhs.a
			);
		}
		friend word32 operator&(word32 lhs, word32 rhs) {
			return word32(
				lhs.e & rhs.e,
				lhs.d & rhs.d,
				lhs.c & rhs.c,
				lhs.b & rhs.b,
				lhs.a & rhs.a
			);
		}
		friend word32 operator^(word32 lhs, word32 rhs) {
			return word32(
				lhs.e ^ rhs.e,
				lhs.d ^ rhs.d,
				lhs.c ^ rhs.c,
				lhs.b ^ rhs.b,
				lhs.a ^ rhs.a
			);
		}

		friend word32 operator<<(word32 lhs, uint8_t rhs) {
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
		friend word32 operator>>(word32 lhs, uint8_t rhs) {
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

		uint8_t operator[](uint8_t index) { return get_char(index); }

		friend std::ostream& operator<<(std::ostream& out, word32 a) {
			out << a.to_str();
			return out;
		}
#pragma endregion
	};
}