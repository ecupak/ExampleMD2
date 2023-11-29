#pragma once

#include <cstdint>


// Converts a hexadecimal color value into its RGB components, stored as percentages. Ignores alpha values.
void DeconstructColor(const uint32_t& hexValue, float& r, float& g, float& b)
{
	const float maxValue{ 255.0f };

	const uint32_t redMask{ 0x00FF0000 };
	const uint32_t greenMask{ 0x0000FF00 };
	const uint32_t blueMask{ 0x000000FF };

	// Put into range [0 ... 255] then divide by max value to get percentage.
	r = ((hexValue & redMask) >> 16) / maxValue;
	g = ((hexValue & greenMask) >> 8) / maxValue;
	b = (hexValue & blueMask) / maxValue;
}


// Contains RGB components as percentages. Deconstructed from a hexadecimal value.
struct DColor
{
public:
	DColor(const uint32_t hexValue)
	{
		DeconstructColor(hexValue, r, g, b);
	}

	float r{ 0.0f };
	float g{ 0.0f };
	float b{ 0.0f };
};