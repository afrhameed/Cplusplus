/* Print a float in binary: ftob.c 
HW3 problem 3*/
#include <stdio.h>
#include <stdlib.h>

void float_to_string(float f, char *s, int n);
//void float_to_string(float,char *,int);
void print_float();

#define LEN 32
#define EXP_32 8		/* ending index of s for exponent */
#define MAN_32 9		/* starting index of s for significand */

int main(int argc, char **argv) {
  int n=LEN;
  float f;
  char s[LEN];

  f = atof(argv[1]);
  printf("f=%f\n",f);

  float_to_string(f,s,n);
  print_float(s,n);
  printf("\n");

  return 0;
}

/* convert float to binary and store in s, a string of 32 chars */
void float_to_string(float f, char *s, int n){
  int i;			/* for loop index */

  union binary{
    float frac;
    int whole;
  }vol;
  vol.frac=f;

 for(i=n-1;i>=0;i--){
    if((vol.whole & 1U)==1U ){
      s[i]='1';
    }
    else s[i]='0';
    vol.whole>>=1;
  }

}

/* print space in between sign bit, exponent, and significand */
void print_float(char *s, int n) {
  int i=0;
  printf("%c ",s[i++]);
  while(i<9){
    printf("%c",s[i++]);
  }
  printf(" ");
  while(i<32){
    printf("%c",s[i++]);
  }
}
