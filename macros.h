// Include Guard
#ifndef MACROS_H
#define MACROS_H

#define set_bit(address, bit) (address |= (1 << bit)) // Sets bit by ORing with zeroes and one in the bit's place
#define clr_bit(address, bit) (address &=!(1 << bit)) // Clears bit by ANDing with ones and zero in the bit's place
#define tgl_bit(address, bit) (address ^= (1 << bit)) // Toggles bit by XORing with zeroes and one in the bit's place
#define get_bit(address, bit) (address & ((1 << bit) >> bit)) // Gets bit by ANDing with zeroes and itself then shifts back

#endif // MACROS_H