#pragma once
#include "Filter.hpp"

class ClottingFilter : public Filter
{
public:
	ClottingFilter();

	void apply(Image* image);
};
