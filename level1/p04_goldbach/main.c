#include <stdio.h>
#include <math.h>

int is_prime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n = 100, j = 2;
    int flag = 0;
    while (j <= n) {
        for (int i = 2; i <= n / 2; i++) {
            if (is_prime(i) && is_prime(n - i)) {
                printf("%d = %d + %d\n", n, i, n - i);
                flag = 1;
            }
        }
        if (flag == 0) {
            printf("Failed to verify Goldbach's conjecture.\n");
        }
        j++;
        return 0;
    }

}