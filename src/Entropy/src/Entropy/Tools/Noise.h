#pragma once

namespace Entropy {

	// Performant and accurate pseudo-random function from seed
	unsigned long long Lehmer64(unsigned long long seed);
}
