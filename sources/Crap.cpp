#include "Crap.hpp"
#include "IsolationFilter.hpp"

int main(int argc, char* argv[])
{
	Image image("captcha.jpg");
	IsolationFilter filter;

	filter.apply(&image);
	image.save("test.png");

	return 0;
}
