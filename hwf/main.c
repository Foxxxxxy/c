#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// 48th fibonacci number doesn't fit in integer type
#define FIB_ARR_SIZE 47

void fill_fibonacci_arr(int fibonacci_arr[]) {
    int i;

    fibonacci_arr[0] = 0;
    fibonacci_arr[1] = 1;

    for (i = 2; i < FIB_ARR_SIZE; ++i) {
        fibonacci_arr[i] = fibonacci_arr[i - 1] + fibonacci_arr[i - 2];
    }
}

int next_turn(int total, int possible) {
    int fibonacci_arr[FIB_ARR_SIZE];
    int i = FIB_ARR_SIZE, optimal;

    fill_fibonacci_arr(fibonacci_arr);

    while (total > 0) {
        i--;

        while (i > 0 && fibonacci_arr[i] > total) {
            i--;
        }

        total -= fibonacci_arr[i];
    }

    optimal = fibonacci_arr[i];

    return optimal > possible ? 1 : optimal;
}

int main() {
    int total, possible, scanned;
    int optimal_amount;

    printf("Enter total matches amount and amount possible to pick:\n");
    scanned = scanf("%d%d", &total, &possible);
    if (scanned != 2 || total <= 0 || possible <= 0) {
        printf("Amounts must be greater than zero, fit integer type size and be typed as two numbers!\n");
        abort();
    }
    assert(scanned == 2);
    assert(total > 0);
    assert(possible > 0);

    optimal_amount = next_turn(total, possible);

    printf("Your optimal amount to pick in the next turn would be: %d", optimal_amount);

    return 0;
}
