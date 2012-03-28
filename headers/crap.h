#ifndef __CRAP_H
#define __CRAP_H

struct crap_t {
	char        code[6];
	const char* image_path;
};

struct crap_t* crap_new(const char* image_path);

#endif
