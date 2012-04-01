#include "Crap.hpp"
#include "ClottingFilter.hpp"
#include "IsolationFilter.hpp"
#include "LineExtrusionFilter.hpp"

int main(int argc, char* argv[])
{
	Image image("captcha.jpg");
	ClottingFilter clotting_filter;
	IsolationFilter isolation_filter(60);
	LineExtrusionFilter line_filter;

	image.applyFilter(isolation_filter);
	image.applyFilter(line_filter);
	image.applyFilter(clotting_filter);

	image.save("test.png");

	return 0;
}
