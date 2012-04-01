#include "Image.hpp"

Image::Image(const std::string& path)
	: m_path(path)
{
	if (!loadImage()) {
		std::cerr << "crap: failed to load image" << std::endl;
	}
	else {
		m_width = imlib_image_get_width();
		m_height = imlib_image_get_height();
		m_pitch = 4 * m_width;
		m_channels = 4;
	}
}

Image::Image(int width, int height)
	: m_width(width), m_height(height)
{
	m_image = imlib_create_image(width, height);

	if (!m_image) {
		std::cerr << "crap: failed to create image" << std::endl;
	}
	else {
		m_pitch = 4 * width;
		m_channels = 4;

		imlib_context_set_image(m_image);

		m_data = (unsigned char*)imlib_image_get_data();
	}
}

Image::~Image()
{
	imlib_context_set_image(m_image);

	imlib_free_image();
}

Image& Image::operator=(Image& image)
{
	int x, y;
	int red, green, blue;

	if (image.width() != m_width || image.height() != m_height) {
		imlib_context_set_image(m_image);
		imlib_free_image();

		m_width = image.width();
		m_height = image.height();
		m_image = imlib_create_image(m_width, m_height);
	}

	for (x = 0; x < m_width; x++) {
		for (y = 0; y < m_height; y++) {
			image.readPixel(x, y, &red, &green, &blue);

			paintPixel(x, y, red, green, blue);
		}
	}

	return *this;
}

bool Image::loadImage()
{
	// Load the actual image.
	m_image = imlib_load_image(m_path.c_str());

	// Set the loaded image as the current context, if it was successfully loaded.
	if (m_image != NULL) {
		imlib_context_set_image(m_image);

		m_data = (unsigned char*)imlib_image_get_data();

		return true;
	}
	else {
		return false;
	}
}

void Image::paintPixel(int x, int y, int red, int green, int blue)
{
	int offset = ((x * m_channels) + (y * m_pitch));

	m_data[offset] = blue;
	m_data[offset + 1] = green;
	m_data[offset + 2] = red;
}

void Image::readPixel(int x, int y, int* red, int* green, int* blue)
{
	int offset = ((y * m_pitch) + (x * m_channels));

	*blue = m_data[offset];
	*green = m_data[offset + 1];
	*red = m_data[offset + 2];
}

void Image::save(const std::string& path)
{
	imlib_context_set_image(m_image);
	imlib_save_image(path.c_str());
}

void Image::applyFilter(Filter& filter)
{
	filter.apply(this);
}
