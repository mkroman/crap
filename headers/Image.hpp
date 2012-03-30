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
	unsigned int m_pitch;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_channels;
	std::string  m_path;
	Imlib_Image  m_image;

	bool loadImage();
};
