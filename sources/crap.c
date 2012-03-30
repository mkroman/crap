#include <assert.h>
#include "crap.h"


struct image_t *image_new(int width, int height)
{
	struct image_t *img;

	Imlib_Image priv = imlib_create_image(width, height);

	img = (struct image_t *)malloc(sizeof(struct image_t));
	imlib_context_set_image(priv);
	img->width = imlib_image_get_width();
	img->height = imlib_image_get_height();
	img->pitch = 4 * imlib_image_get_width();
	img->channels = 4;
	img->pixels = (char *)imlib_image_get_data();

	return img;
}

int getpixel(struct image_t *image, int x, int y, int *r, int *g, int *b)
{
	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
	{
		*r = 255;
		*g = 255;
		*b = 255;
		return -1;
	}

	*b = image->pixels[y * image->pitch + x * image->channels];
	*g = image->pixels[y * image->pitch + x * image->channels + 1];
	*r = image->pixels[y * image->pitch + x * image->channels + 2];

	return 0;
}

int setpixel(struct image_t *image, int x, int y, int r, int g, int b)
{
	if(x < 0 || y < 0 || x > image->width || y >= image->height)
		return -1;

	image->pixels[y * image->pitch + x * image->channels] = b;
	image->pixels[y * image->pitch + x * image->channels + 1] = g;
	image->pixels[y * image->pitch + x * image->channels + 2] = r;

	return 0;
}

void image_swap(struct image_t *image1, struct image_t *image2)
{
	struct image_t tmp;
	memcpy(&tmp, image1, sizeof(tmp));
	memcpy(image1, image2, sizeof(tmp));
	memcpy(image2, &tmp, sizeof(tmp));
}

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

void crap_image_remove_lines(struct image_t* image)
{
	struct image_t *dst;
	int x, y;
	int r, ra, rb, g, b;

	dst = image_new(image->width, image->height);

	/* Remove white lines */
	for(x = 0; x < image->width; x++)
		for(y = 0; y < image->height; y++)
		{
			getpixel(image, x, y, &r, &g, &b);
			setpixel(dst, x, y, r, g, b);
			if(y > 0 && y < image->height - 1)
			{
				getpixel(image, x, y - 1, &ra, &g, &b);
				getpixel(image, x, y + 1, &rb, &g, &b);
				if(r > ra && (r - ra) * (r - rb) > 5000)
					setpixel(dst, x, y, ra, ra, ra);
			}
		}


	/* Remove black lines */
	for (x = 0; x < image->width; x++)
		for (y = 0; y < image->height; y++)
		{
			getpixel(dst, x, y, &r, &g, &b);
			if(y > 0 < image->height - 1)
			{
				getpixel(image, x, y - 1, &ra, &g, &b);
				getpixel(image, x, y + 1, &rb, &g, &b);
				if (r < ra && (r - ra) * (r - rb) > 500)
					setpixel(dst, x, y, ra, ra, ra);
			}
		}
	image_swap(image, dst);
}

int main(int argc, char** argv)
{
	int result = 0;
	struct image_t image = crap_image_load("captcha.jpg");

	printf("image.path: %s\n", image.path);
	printf("image.width: %d\n"
		   "image.height: %d\n", image.width, image.height);

	result = crap_image_isolate_black(&image);
	crap_image_remove_lines(&image);

	imlib_save_image("test.png");

	return 0;
}
