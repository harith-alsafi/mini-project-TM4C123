#include "helpers.h"

DEFINE_LIST_IMPLEMENTATION(char)

unsigned long randSeed = 12345; // Initial seed value

int Random() {
    randSeed = (1664525 * randSeed + 1013904223) % 4294967296;
    return randSeed;
}

// Function to get a random number within a given range
int RandomRange(int min, int max) {
    return min + (Random() % (max - min + 1));
}