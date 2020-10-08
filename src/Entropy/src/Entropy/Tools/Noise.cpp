#include "Noise.h"
#include <stdlib.h>

namespace Entropy {

	unsigned long long Lehmer64(unsigned long long seed)
	{
		unsigned long long nLehmer = seed;
		nLehmer += 0xe120fc15;
		unsigned long long temp;
		temp = (unsigned long long)nLehmer * 0x4a39b70d;
		unsigned long long m1 = (temp >> 32) ^ temp;
		temp = (unsigned long long)m1 * 0x12fad5c9;
		unsigned long long m2 = (temp >> 32) ^ temp;
		return m2;
	}
}
