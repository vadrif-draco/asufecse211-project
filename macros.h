// Include Guard
#ifndef MACROS_H
#define MACROS_H

#define set_bit(address, bit) (address |= (1 << bit)) // Sets bit by ORing with zeroes and one in the bit's place
#define clr_bit(address, bit) (address &= ~(1 << bit)) // Clears bit by ANDing with ones and zero in the bit's place
#define tgl_bit(address, bit) (address ^= (1 << bit)) // Toggles bit by XORing with zeroes and one in the bit's place
// TODO: Consider using bit-banding for the above macros
#define get_bit(address, bit) ((address >> bit) & 1) // Gets bit by ANDing with zeroes and itself then shifts back
#define delay(n) for(unsigned long i=0; i < n; ++i) // Delays for approximately 'n' instructions (n/80MHz seconds)

#endif // MACROS_H