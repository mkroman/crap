#pragma once

class Image;

class Filter
{
public:
	enum Mode
	{
		ExtractMode,
		SubstractMode
	};

	Filter() {}

	virtual void apply(Image* image) = 0;
};
