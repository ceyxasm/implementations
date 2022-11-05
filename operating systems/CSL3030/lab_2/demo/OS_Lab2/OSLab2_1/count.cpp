#include<bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(){
    
int cnt=0;
    while(1){
        int c = getchar();
        if(c== EOF){ fprintf(stderr,"Count = %d",cnt);exit(0);}
        if(isalpha(c)){
            putchar(c);
            continue;
        }
        
        else{
            putchar(c);
            cnt+=1;
        }
    }
}
