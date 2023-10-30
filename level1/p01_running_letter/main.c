#include <stdio.h>
#include <string.h>
#include <windows.h>
int main() {
    char str[]="hello world!";
    int i=0;
    while (i<strlen(str)) {
        printf("%s",i+str);
        Sleep(500);
        system("cls");
        i++;
    }
    return 0;
}