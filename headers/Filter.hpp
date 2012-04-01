#pragma once

class Image;

class Filter
{
public:
	Filter() {}

	virtual void apply(Image* image) = 0;
};
