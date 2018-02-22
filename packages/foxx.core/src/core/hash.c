#include "core/hash.h"

/**
 * Murmur3 hash function.
 * https://github.com/aappleby/smhasher
 */
uint32_t hashMurmur3(const char *key)
{
	uint32_t h1 = HASH_SEED;
	
	int blocks = floor(strlen(key) / 4);
	uint8_t *data = (uint8_t*)key;
	uint32_t *block = (uint32_t*)(data + blocks * 4);

	for(int i = -blocks; i; i++) {
		uint32_t k1 = block[i];

		k1 *= 0xcc9e2d51;
		k1 = _rotl(k1, 15);
		k1 *= 0x1b873593;

		h1 ^= k1;
		h1 = _rotl(h1, 13); 
		h1 = h1 * 5+0xe6546b64;
	}

	uint32_t k1 = 0;
	uint8_t *tail = (uint8_t*)(data + blocks * 4);

	switch(strlen(key) & 3) {
		case 3: k1 ^= tail[2] << 16;
		case 2: k1 ^= tail[1] << 8;
		case 1: k1 ^= tail[0];
			k1 *= 0xcc9e2d51; 
			k1 = _rotl(k1, 15); 
			k1 *= 0x1b873593;
			h1 ^= k1;
	}

	h1 ^= strlen(key);
	
	h1 ^= h1 >> 16;
	h1 *= 0x85ebca6b;
	h1 ^= h1 >> 13;
	h1 *= 0xc2b2ae35;
	h1 ^= h1 >> 16;

	return h1;
}