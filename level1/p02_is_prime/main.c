#include <stdio.h >

int main() {
    int n,i;
    scanf("%d", &n);
    for (i = 2; i < n; i++) {
        if (n % i == 0) {
            printf("no\n");
            return 0;
        }
    }
    printf("yes\n");
    return 0;
}