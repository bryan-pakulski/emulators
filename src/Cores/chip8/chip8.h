#pragma once

// Chip 8 is capable of accessign up to 4kb of ram, from location 0x000 to 0xFFF
// The first 512 bytes aare reserved and shouldn't be used by programs
// Most programs should start at 0x200, programs starting at 0x600 are intended for the ETI 660
