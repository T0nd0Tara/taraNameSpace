#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#define TARA_PGE_EXTENSION
#include <taraNS.h>

class PolynomialDrawDemo : public olc::PixelGameEngine
{
public:
	PolynomialDrawDemo() {
		sAppName = "PolynomialDrawDemo";
	}

private:

	tara::PolynomialInt* f;
	olc::vd2d offset;
	
protected:
	bool OnUserCreate() override {
		f = new tara::PolynomialInt("3x^3-8x^2-15x^1");
		std::cout << f->eval(0);
		return true;
	}

	bool OnUserUpdate(float elapsedTime) override {
		if (GetKey(olc::ESCAPE).bPressed) return false;

		Clear(olc::BLACK);

		if (GetKey(olc::D).bHeld) offset.x += 20 * elapsedTime;
		if (GetKey(olc::A).bHeld) offset.x -= 20 * elapsedTime;
		if (GetKey(olc::W).bHeld) offset.y -= 20 * elapsedTime;
		if (GetKey(olc::S).bHeld) offset.y += 20 * elapsedTime;

		DrawLine(0, ScreenHeight() / 2 + offset.y, ScreenWidth(), ScreenHeight() / 2 + offset.y, olc::GREEN);
		DrawLine(ScreenWidth() / 2 + offset.x, 0, ScreenWidth() / 2 + offset.x, ScreenHeight(), olc::GREEN);

		f->Draw(this, offset, olc::vd2d{0.1,1.0});

		return true;
	}
};

int main() {
	PolynomialDrawDemo demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}