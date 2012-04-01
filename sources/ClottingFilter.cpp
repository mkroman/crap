#include "Image.hpp"
#include "ClottingFilter.hpp"

ClottingFilter::ClottingFilter()
{
}

void ClottingFilter::apply(Image* image)
{
	int x, y;
	int colors[4];
	int red, green, blue;

	// Horizontal “restorization”
	for (x = 2; x < image->width() - 2; x++) {
		for (y = 0; y < image->height(); y++) {
			image->readPixel(x - 2, y, &colors[0], &green, &blue);
			image->readPixel(x - 1, y, &colors[1], &green, &blue);
			image->readPixel(x    , y, &colors[2], &green, &blue);
			image->readPixel(x + 1, y, &colors[3], &green, &blue);
			image->readPixel(x + 2, y, &colors[4], &green, &blue);

			if (colors[0] < 127 && colors[1] < 127 && colors[2] > 128 && colors[3] < 127) {
				colors[2] = (colors[0] + colors[1] + colors[3]) / 3;
			}
			else if (colors[1] < 127 && colors[2] > 128 && colors[3] < 127 && colors[4] < 127)
			{
				colors[2] = (colors[1] + colors[3] + colors[4]) / 3;
			}

			image->paintPixel(x, y, colors[2], colors[2], colors[2]);
		}
	}

	// Vertical “restorization”
	for (x = 0; x < image->width(); x++) {
		for (y = 2; y < image->height() - 2; y++) {
			image->readPixel(x, y - 2, &colors[0], &green, &blue);
			image->readPixel(x, y - 1, &colors[1], &green, &blue);
			image->readPixel(x, y,     &colors[2], &green, &blue);
			image->readPixel(x, y + 1, &colors[3], &green, &blue);
			image->readPixel(x, y + 2, &colors[4], &green, &blue);

			if (colors[0] < 127 && colors[1] < 127 && colors[2] > 128 && colors[3] < 127) {
				colors[2] = (colors[0] + colors[1] + colors[3]) / 3;
			}
			else if (colors[1] < 127 && colors[2] > 128 && colors[3] < 127 && colors[4] < 127)
			{
				colors[2] = (colors[1] + colors[3] + colors[4]) / 3;
			}

			image->paintPixel(x, y, colors[2], colors[2], colors[2]);
		}
	}
}
