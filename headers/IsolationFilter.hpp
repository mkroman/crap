#pragma once
#include "Filter.hpp"

class IsolationFilter : public Filter
{
public:
	/*!
	 * Create a new isolation filter with a threshold.
	 */
	IsolationFilter(int threshold = 120);

	/*!
	 * Apply the filter to an image.
	 */
	void apply(Image* image);

	/*!
	 * Set the isolation threshold.
	 */
	void setThreshold(int threshold)
	{
		m_threshold = threshold;
	}

	/*!
	 * Get the isolation threshold.
	 */
	int threshold() const
	{
		return m_threshold;
	}

protected:
	int m_threshold;
};
