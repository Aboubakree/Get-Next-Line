#include <stdio.h>

void incrementAndPrint() {
    static int count = 0; // Static variable declaration and initialization
    count++;
    printf("Count: %d\n", count);
}

int main() {
    incrementAndPrint(); // Output: Count: 1
    incrementAndPrint(); // Output: Count: 2
    incrementAndPrint(); // Output: Count: 3

    return 0;
}
