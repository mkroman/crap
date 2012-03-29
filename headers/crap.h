#ifndef __CRAP_H
#define __CRAP_H
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <Imlib2.h>

struct image_t {
	Imlib_Image    im;
	const char*    path;
	unsigned char* pixels;
	unsigned int   width, height;
	unsigned int   channels, pitch;
};

struct image_t crap_image_load(char* path);
int crap_image_isolate_black(struct image_t* image);

static const int kThreshold = 60;

#endif
