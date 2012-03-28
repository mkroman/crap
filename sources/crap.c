#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "crap.h"

struct crap_t* crap_new(const char* image_path)
{
	struct crap_t* result;
	
	result = (struct crap_t*)malloc(sizeof(struct crap_t));

	memset(result, 0, sizeof(struct crap_t));

	if (result == NULL) {
		perror("Could not allocate memory");

		return NULL;
	}

	result->image_path = image_path;

	return result;
}

int main(int argc, char** argv)
{
	struct crap_t* c = crap_new("abc");

	printf("c->image_path: %s\n", c->image_path);

	return 0;
}
