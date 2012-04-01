#pragma once
#include "Filter.hpp"

class LineExtrusionFilter : public Filter
{
public:
	LineExtrusionFilter(Filter::Mode mode = Filter::SubstractMode);

	void apply(Image* image);

protected:
	Filter::Mode m_mode;
};
