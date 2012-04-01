#include "Image.hpp"
#include "LineExtrusionFilter.hpp"

LineExtrusionFilter::LineExtrusionFilter(Filter::Mode mode)
	: m_mode(mode)
{
}

void LineExtrusionFilter::apply(Image* image)
{
	int x, y;
	int red, green, blue;
	int red_top, red_bottom;

	// Remove “white lines”
	for (x = 0; x < image->width(); x++) {
		for (y = 0; y < image->height(); y++) {
			image->readPixel(x, y, &red, &green, &blue);
			
			if (y > 0 && y < image->height() - 1) {
				image->readPixel(x, y - 1, &red_top, &green, &blue);
				image->readPixel(x, y + 1, &red_bottom, &green, &blue);

				if (red > red_top && (red - red_top) * (red - red_bottom) > 5000)
					image->paintPixel(x, y, red_top, red_top, red_top);
			}
		}
	}

	// Remove “black lines”
	for (x = 0; x < image->width(); x++) {
		for (y = 0; y < image->height(); y++) {
			image->readPixel(x, y, &red, &green, &blue);
			
			if (y > 0 && y < image->height() - 1) {
				image->readPixel(x, y - 1, &red_top, &green, &blue);
				image->readPixel(x, y + 1, &red_bottom, &green, &blue);

				if (red > red_top && (red - red_top) * (red - red_bottom) > 500)
					image->paintPixel(x, y, red_top, red_top, red_top);
			}
		}
	}
}
