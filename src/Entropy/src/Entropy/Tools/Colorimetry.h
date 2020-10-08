#pragma once

#include "GL/glm/vec4.hpp"

namespace Entropy {

	// Converting between SRGB and linear colors
	glm::vec4 EncodeSRGB(const glm::vec4& color);
	glm::vec4 DecodeSRGB(const glm::vec4& color);
}
