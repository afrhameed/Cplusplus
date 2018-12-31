/*Afreen Hameed 
print a float with binary input using IEEE standard*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float btof(char bin[]); //converts 32-bit binary to float 

int main(int argc, char **argv) {
    int i=1;
    char binary[32];
    char letter;
    int count=0;

    while(i<argc){ //read command line args
        for(int j=0; j<strlen(argv[i]);j++){
            letter= (argv[i])[j];
            if(letter=='1' || letter=='0') binary[count++]=letter;
        }
       i++;
    }

    printf("%f\n",btof(binary));  


  return 0;
}

float btof(char bin[]){
    int exp=0;
    double f=0;
    //int c=1;

    for(int i=8,c=1; i>0;i--,c=c<<1){
        if(bin[i]=='1') exp+=c;
    }
    if(exp==0) exp=-126;
    else{
        exp-=127;
        f=1;
    }
    double c=0.5;

    for(int i=9;i<32;i++,c/=2){
        if(bin[i]=='1'){
            f+=c;
        }
    }
    if(exp<0){
        for(int i=exp;i<0;i++){
            f/=2;
        }

    }
    else if (exp>0){
        for(int i=exp;i>0;i--){
            f*=2;
        }
    }
    if(bin[0]=='1') f=-f;
    return (float) f;

}

//0.75 when you type "0 01111110 10000000000000000000000." 32 bits
//0 01111110 10000000000000000000000
//0 12345678 9