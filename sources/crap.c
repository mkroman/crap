#include <assert.h>
#include "crap.h"

struct image_t crap_image_load(char* path)
{
	struct image_t image = { 0 };

	image.path = path;

	// Load the image.
	image.im = imlib_load_image(image.path);

	// Could not load image.
	if (!image.im) {
		printf("crap: failed to load image\n");
	}

	// Set the current context.
	imlib_context_set_image(image.im);

	// Get the width and height of the image.
	image.width = imlib_image_get_width();
	image.height = imlib_image_get_height();
	image.pitch = image.width * 4;
	image.channels = 4;
	image.pixels = (unsigned char*)imlib_image_get_data();

	return image;
}

int crap_image_isolate_black(struct image_t* image)
{
	int x, y, offset = 0, sum = 0;
	unsigned char *r, *g, *b, *a;

	for (x = 0; x < image->width; x++) {
		for (y = 0; y < image->height; y++) {
			offset = (y * image->pitch + x * image->channels);

			b = &image->pixels[offset];
			g = &image->pixels[offset + 1];
			r = &image->pixels[offset + 2];
			a = &image->pixels[offset + 3];

			sum = *r + *g + *b;

			if (sum > kThreshold) {
				*r = 255;
				*g = 255;
				*b = 255;
			}
			else {
				*r = 0;
				*g = 0;
				*b = 0;
			}
		}
	}

	return 0;
}

int main(int argc, char** argv)
{
	int result = 0;
	struct image_t image = crap_image_load("/home/mk/captcha.jpg");

	printf("image.path: %s\n", image.path);
	printf("image.width: %d\n"
		   "image.height: %d\n", image.width, image.height);

	result = crap_image_isolate_black(&image);

	imlib_save_image("test.png");

	return 0;
}
