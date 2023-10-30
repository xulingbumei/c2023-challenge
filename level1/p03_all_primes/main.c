#include <stdio.h>

int main() {
    int i,num,flag;
    num=2;
    flag=1;
    while (num<=999){
        for(i=2;i<num;i++){
            if(num%i==0){
                flag=0;
                break;}
        }
        if(flag==1){
            printf("%d\n" ,num);}
        else{
            flag=1;}
        num++ ;
    }
return 0;
}


