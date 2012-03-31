#include "Crap.hpp"

int main(int argc, char* argv[])
{
	int x, y, red, green, blue;
	Image* image = new Image("captcha.jpg");
	
	image->save("test.png");

	delete image;
	return 0;
}
