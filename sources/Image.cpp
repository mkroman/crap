#include "Image.hpp"

// struct image_t crap_image_new(int width, int height)
// {
// 	struct image_t image;

// 	image.im = imlib_create_image(width, height);
// 	imlib_context_set_image(image.im);

// 	image.width = imlib_image_get_width();
// 	image.height = imlib_image_get_height();
// 	image.pitch = 4 * image.width;
// 	image.channels = 4;
// 	image.pixels = (unsigned char*)imlib_image_get_data();

// 	return image;
// }

// int getpixel(struct image_t* image, int x, int y, int* r, int* g, int* b)
// {
// 	if (x < 0 || y < 0 || x >= image->width || y >= image->height) {
// 		*r = 255;
// 		*g = 255;
// 		*b = 255;

// 		return -1;
// 	}

// 	*b = image->pixels[y * image->pitch + x * image->channels];
// 	*g = image->pixels[y * image->pitch + x * image->channels + 1];
// 	*r = image->pixels[y * image->pitch + x * image->channels + 2];

// 	return 0;
// }

// int setpixel(struct image_t* image, int x, int y, int r, int g, int b)
// {
// 	if (x < 0 || y < 0 || x > image->width || y >= image->height) {
// 		return -1;
// 	}

// 	image->pixels[y * image->pitch + x * image->channels] = b;
// 	image->pixels[y * image->pitch + x * image->channels + 1] = g;
// 	image->pixels[y * image->pitch + x * image->channels + 2] = r;

// 	return 0;
// }

// void crap_image_swap(struct image_t* source, struct image_t* target)
// {
// 	struct image_t image = { 0 };

// 	memcpy(&image, source, sizeof(struct image_t));
// 	memcpy(source, target, sizeof(struct image_t));
// 	memcpy(target, &image, sizeof(struct image_t));
// }

// struct image_t crap_image_load(char* path)
// {
// 	struct image_t image = { 0 };

// 	image.path = path;

// 	// Load the image.
// 	image.im = imlib_load_image(image.path);

// 	// Could not load image.
// 	if (!image.im) {
// 		printf("crap: failed to load image\n");
// 	}

// 	// Set the current context.
// 	imlib_context_set_image(image.im);

// 	// Get the width and height of the image.
// 	image.width = imlib_image_get_width();
// 	image.height = imlib_image_get_height();
// 	image.pitch = image.width * 4;
// 	image.channels = 4;
// 	image.pixels = (unsigned char*)imlib_image_get_data();

// 	return image;
// }

// int crap_image_isolate_black(struct image_t* image)
// {
// 	int x, y, offset = 0, sum = 0;
// 	unsigned char *r, *g, *b, *a;

// 	for (x = 0; x < image->width; x++) {
// 		for (y = 0; y < image->height; y++) {
// 			offset = (y * image->pitch + x * image->channels);

// 			b = &image->pixels[offset];
// 			g = &image->pixels[offset + 1];
// 			r = &image->pixels[offset + 2];
// 			a = &image->pixels[offset + 3];

// 			sum = *r + *g + *b;

// 			if (sum > kThreshold) {
// 				*r = 255;
// 				*g = 255;
// 				*b = 255;
// 			}
// 			else {
// 				*r = 0;
// 				*g = 0;
// 				*b = 0;
// 			}
// 		}
// 	}

// 	return 0;
// }

// void crap_image_remove_lines(struct image_t* image)
// {
// 	int x, y;
// 	int r, ra, rb, g, b;
// 	struct image_t dst;

// 	dst = crap_image_new(image->width, image->height);

// 	/* Remove white lines */
// 	for(x = 0; x < image->width; x++) {
// 		for (y = 0; y < image->height; y++) {
// 			getpixel(image, x, y, &r, &g, &b);
// 			setpixel(&dst, x, y, r, g, b);

// 			if (y > 0 && y < image->height - 1) {
// 				getpixel(image, x, y - 1, &ra, &g, &b);
// 				getpixel(image, x, y + 1, &rb, &g, &b);

// 				if (r > ra && (r - ra) * (r - rb) > 5000) {
// 					setpixel(&dst, x, y, ra, ra, ra);
// 				}
// 			}
// 		}
// 	}


// 	/* Remove black lines */
// 	for (x = 0; x < image->width; x++) {
// 		for (y = 0; y < image->height; y++) {
// 			getpixel(&dst, x, y, &r, &g, &b);

// 			if (y > 0 < image->height - 1) {
// 				getpixel(image, x, y - 1, &ra, &g, &b);
// 				getpixel(image, x, y + 1, &rb, &g, &b);

// 				if (r < ra && (r - ra) * (r - rb) > 500) {
// 					setpixel(&dst, x, y, ra, ra, ra);
// 				}
// 			}
// 		}
// 	}

// 	crap_image_swap(image, &dst);
// }

// void crap_image_fill_holes(struct image_t* image)
// {
// 	int x, y;
// 	int r, g, b;
// 	struct image_t *dst;

// 	dst = image_new(image->width, image->height);

// 	for (x = 0; x < image->width; x++)
// 		for (y = 0; y < image->height; y++)
// 		{
// 			getpixel(image, x, y, &r, &g, &b);
// 			setpixel(image, x, y, r, g, b);
// 		}

// 	for(x = 2; x < dst->width - 2; x++)
// 		for(y = 0; y < dst->height; y++)
// 		{
// 			int c1, c2, c3, c4, c5;
// 			getpixel(image, x-2, y, &c1, &g, &b);
// 			getpixel(image, x-1, y, &c2, &g, &b);
// 			getpixel(image, x,   y, &c3, &g, &b);
// 			getpixel(image, x+1, y, &c4, &g, &b);
// 			getpixel(image, x+2, y, &c5, &g, &b);

// 			if (c1 < 127 && c2 < 127 && c3 > 128 && c4 < 127)
// 				c3 = (c1 + c2 + c4) / 3;
// 			else if(c2 < 127 && c3 > 128 && c4 < 127 && c5 < 127)
// 				c3 = (c2 + c4 + c5) / 3;
// 			setpixel(dst, x, y, c3, c3, c3);
// 		}

// 	for (x = 0; x < dst->width; x++)
// 		for (y = 2; y < dst->height - 2; y++)
// 		{
// 			int c1, c2, c3, c4, c5;
// 			getpixel(image, x-2, y, &c1, &g, &b);
// 			getpixel(image, x-1, y, &c2, &g, &b);
// 			getpixel(image, x,   y, &c3, &g, &b);
// 			getpixel(image, x+1, y, &c4, &g, &b);
// 			getpixel(image, x+2, y, &c5, &g, &b);

// 			if(c1 < 127 && c2 < 127 && c3 > 128 && c4 < 127)
// 				c3 = (c1, c2, c4) / 3;
// 			else if(c2 < 127 && c3 > 128 && c4 < 127 && c5 < 127)
// 				c3 = (c2 + c4 + c5) / 3;
// 			setpixel(dst, x, y, c3, c3, c3);
// 		}

// 	image_swap(image, dst);
// }

// void crap_image_smooth(struct image_t *image)
// {
// 	struct image_t *dst;
// 	int msize = 3, ssize = 3;
// 	int x, y, i, j, val[msize*msize];
// 	int r, g, b;

// 	dst = image_new(image->width, image->height);

// 	for (x=0; x < image->width; x++)
// 		for (y=0; y < image->height; y++)
// 			setpixel(dst, x, y, 255, 255, 255);

// 	for (x = msize/2; x < image->width - msize/2; x++)
// 		for (y = msize/2; y < image->height - msize/2; y++)
// 		{
// 			for (i = 0; i < msize; i++)
// 				for (j = 0; j < msize; j++)
// 				{
// 					getpixel(image, x + j - ssize/2, y + i - ssize/2, &r, &g, &b);
// 					val[i * msize + j] = r;
// 				}

// 			for (i = 0; i < msize * msize / 2 + 1; i++)
// 				for(j = i + 1; j < msize * msize; j++)
// 				{
// 					if(val[i] > val[j])
// 					{
// 						register int k = val[i];
// 						val[i] = val[j];
// 						val[j] = k;
// 					}
// 				}
// 			i = val[msize * msize / 2];
// 			setpixel(dst, x, y, i, i, i);
// 		}

// 	image_swap(image, dst);
// }
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

void Image::readPixel(int x, int y, int& red, int& green, int& blue)
{
	int offset = ((y * m_pitch) + (x * m_channels));

	blue = m_data[offset];
	green = m_data[offset + 1];
	red = m_data[offset + 2];
}

void Image::save(const std::string& path)
{
	imlib_context_set_image(m_image);
	imlib_save_image(path.c_str());
}
