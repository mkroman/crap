#include "Image.hpp"
#include "IsolationFilter.hpp"

IsolationFilter::IsolationFilter(int threshold)
	: m_threshold(threshold)
{	
}

void IsolationFilter::apply(Image* image)
{
	int x, y;
	int red, green, blue;

	for (x = 0; x < image->width(); x++) {
		for (y = 0; y < image->height(); y++) {
			image->readPixel(x, y, &red, &green, &blue);

			if ((red + green + blue) >= m_threshold) {
				image->paintPixel(x, y, 255, 255, 255);
			}
			else {
				image->paintPixel(x, y, red, green, blue);
			}
		}
	}
}
