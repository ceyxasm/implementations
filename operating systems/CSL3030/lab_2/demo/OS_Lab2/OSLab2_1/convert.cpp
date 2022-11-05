#include<bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(){

    while(1){
        int c = getchar();
        //fprintf(stderr,"%c",c);
        if(c== EOF){ exit(0);}
        if(isupper(c)){
            fprintf(stderr,"%c",tolower(c));
            putchar(tolower(c));
        }
        else if(islower(c)){
            fprintf(stderr,"%c",toupper(c));
            putchar(toupper(c));
        }
        else{
            fprintf(stderr,"%c",c);
            putchar(c);
        }
    }
}
