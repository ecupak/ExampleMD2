#pragma once


class Utility
{
public:
	static void ClampValue(float& value, float min = 0.0f, float max = 1.0f);


	static const bool WrapValue(float& value, float min = 0.0f, float max = 1.0f);
};


void Utility::ClampValue(float& value, float min = 0.0f, float max = 1.0f)
{
	if (value > max)
	{
		value = max;
	}
	else if (value < min)
	{
		value = min;
	}
}


const bool Utility::WrapValue(float& value, float min = 0.0f, float max = 1.0f)
{
	if (value > max)
	{
		while (value > max)
		{
			value -= (max - min);
		}

		return true;
	}

	return false;
}