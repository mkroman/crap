#include "Crap.hpp"
#include "IsolationFilter.hpp"
#include "ClottingFilter.hpp"

int main(int argc, char* argv[])
{
	Image image("captcha.jpg");
	IsolationFilter isolation_filter(60);
	ClottingFilter clotting_filter;

	image.applyFilter(isolation_filter);
	image.applyFilter(clotting_filter);

	image.save("test.png");

	return 0;
}
