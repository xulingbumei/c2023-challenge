#include<stdlib.h>
#include<string.h>
#include<stdio.h>
int kaisa_encrypt(char *text,char *result,int k)
{
    char small_letter[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char big_letter[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    if(text == NULL || k <= 0){
        return -1;
    }
    int m = strlen(text);
    if(m <= 0){
        return -1;
    }
    for(int i=0;i<m;i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            result[i] = big_letter[((text[i] - 'A') + k) % 26];
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            result[i] = small_letter[((text[i] - 'a') + k) % 26];
        } else result[i] = text[i];
    }
    return 0;
}
//解密
int kaisa_decrypt(char *text,char *result,int k)
{
    int p;
    char small_letter[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char big_letter[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    if(text == NULL || k <= 0){
        return -1;
    }
    int m = strlen(text);
    if(m <= 0){
        return -1;
    }
    for(int i=0;i<m;i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            p = ((text[i] - 'A') - k);
            while (p < 0)p += 26;
            result[i] = big_letter[p];
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            p = ((text[i] - 'a') - k);
            while (p < 0)p += 26;
            result[i] = small_letter[p];
        }
        else result[i] = text[i];
    }
    return 0;
}

int main()
{
    char text[50]="";
    char result[50]="";
    int k;
    int type;
    printf("please write a sentence.");
    scanf("%[^\n]",text);
    printf("1 for encrypt and 2 for decrypt\n");
    scanf("%d",&type);
    printf("input the k\n");
    scanf("%d",&k);
    if(type == 1){
        /***加密****/
        kaisa_encrypt(text,result,k);
        printf("message is %s\n",result);
    }else if(type == 2){
        /***解密****/
        kaisa_decrypt(text,result,k);
        printf("the original one is %s\n",result);
    }
    return 0;
}


