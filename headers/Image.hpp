#pragma once
#include <string>
#include <iostream>
#include <Imlib2.h>

class Image
{
public:
	Image(const std::string& path);
	~Image();

	/*!
	 * Color a single pixel on the image.
	 */
	void paintPixel(int x, int y, int red, int green, int blue);

	/*!
	 * Read the color channels for a single pixel.
	 */
	void readPixel(int x, int y, int& red, int& green, int& blue);

	/*!
	 * Save the image from memory to a file.
	 */
	void save(const std::string& path);

	/*!
	 * Get the image path.
	 */
	const std::string& path()
	{
		return m_path;
	}

	/*!
	 * Get the pitch of the image.
	 */
	unsigned int pitch() const
	{
		return m_pitch;
	}

	/*!
	 * Get the number of color channels used in the image.
	 */
	unsigned int channels() const
	{
		return m_channels;
	}

	/*!
	 * Get the image width.
	 */
	unsigned int width() const
	{
		return m_width;
	}

	/*!
	 * Get the image height.
	 */
	unsigned int height() const
	{
		return m_height;
	}

private:
	std::string    m_path;
	Imlib_Image    m_image;
	unsigned int   m_pitch;
	unsigned int   m_width;
	unsigned int   m_height;
	unsigned int   m_channels;
	unsigned char* m_data;

	bool loadImage();
};
