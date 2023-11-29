#pragma once

#include "Utility.h"


class LightData
{
public:
	LightData() = default;


	// Setters.
	void SetAmbient(const float a, const bool isRelative = false)
	{
		if (isRelative)
		{
			ambientStrength_ += a;
			ClampValue(ambientStrength_);
		}
		else
		{
			ambientStrength_ = a;
		}

		UpdateValues();
	}


	void SetDiffuse(const float d, const bool isRelative = false)
	{
		if (isRelative)
		{
			diffuseStrength_ += d;
			ClampValue(diffuseStrength_);
		}
		else
		{
			diffuseStrength_ = d;
		}

		UpdateValues();
	}


	void SetSpecular(const float s, const bool isRelative = false)
	{
		if (isRelative)
		{
			specularStrength_ += s;
			ClampValue(specularStrength_);
		}
		else
		{
			specularStrength_ = s;
		}

		UpdateValues();
	}


	void SetDirection(const glm::vec3 direction)
	{
		direction_ = direction;
	}


	void SetAttenuation(const float constant, const float linear, const float quadratic)
	{
		constant_ = constant;
		linear_ = linear;
		quadratic_ = quadratic;
	}

	
	void SetCutoffAngles(const float innerAngle, const float outerAngle)
	{
		innerCutoffAngle_ = innerAngle;
		outerCutoffAngle_ = outerAngle;
	}


	// Getters.
	float GetAmbient() const
	{
		return ambientStrength_;
	}


	float GetDiffuse() const
	{
		return diffuseStrength_;
	}


	float GetSpecular() const
	{
		return specularStrength_;
	}


	const glm::vec3& GetDirection() const
	{
		return direction_;
	}


	const float GetAttenuationComponent(const int componentIndex)
	{
		switch (componentIndex)
		{
		case 0:
			return constant_;
		case 1:
			return linear_;
		case 2:
			return quadratic_;
		default:
			return 0.0f;
		}
	}


	const float GetCutoffAngle(const int angleIndex)
	{
		switch (angleIndex)
		{
		case 0:
			return innerCutoffAngle_;
		case 1:
			return outerCutoffAngle_;
		default:
			return 0.0f;
		}
	}


	float ambientCoefficient_{ 0.25f };
	float specularCoefficient_{ 0.50f };

private:
	void UpdateValues()
	{
		ambientStrength_ = diffuseStrength_ * ambientCoefficient_;
		specularStrength_ = diffuseStrength_ * specularCoefficient_;
	}

	float ambientStrength_{ 0.0f };
	float diffuseStrength_{ 0.0f };
	float specularStrength_{ 0.0f };

	// Directional/Spot light.
	glm::vec3 direction_{ 0.0f, 0.0f, 0.0f };

	// Point/Spot light.
	float constant_{ 1.0f };
	float linear_{ 1.0f };
	float quadratic_{ 1.0f };

	// Spot light..
	float innerCutoffAngle_{ 25.0f };
	float outerCutoffAngle_{ 35.0f };
};