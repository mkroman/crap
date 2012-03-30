#include "Image.hpp"

Image::Image(const std::string& path)
	: m_path(path)
{
	if (!loadImage()) {
		std::cerr << "crap: failed to load image" << std::endl;
	}
}

Image::~Image()
{
	imlib_context_set_image(m_image);

	imlib_free_image();
}

bool Image::loadImage()
{
	// Load the actual image.
	m_image = imlib_load_image(m_path.c_str());

	// Set the loaded image as the current context, if it was successfully loaded.
	if (m_image != NULL) {
		imlib_context_set_image(m_image);

		return true;
	}
	else {
		return false;
	}
}
