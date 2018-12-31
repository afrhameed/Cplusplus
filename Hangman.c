#include<stdio.h>
#include<ctype.h>


//Afreen Hameed 15/9/18
//CS 288 HW1, Hangman game

int main (){
	int tries=6;
	char  word[15];
	char letter;
	char dumb;
	char guessWord[15];
	int length=0;
	int correct=0;
	int won=1;

	printf("Welcome to Hangman! Player1, please enter a secret word for Player2 to guess\nSecret Word:");
	do {
         	scanf("%c",&dumb);
         	if(dumb!='\n' && dumb!=' '){
         		word[length]= (islower(dumb) ? dumb-32 : dumb);
         		guessWord[length++]='*';
         	}
	    }while(dumb != '\n');
	printf("\nWelcome to Hangman!\nTry guessing the secret word by entering one letter at a time\n");
	
	do{
		won=1;
		printf("\n# misses left=%d		word=%s\nenter one letter:",tries,guessWord);
		do {
         	scanf("%c",&dumb);
         	if(dumb!='\n' && dumb!=' ')letter=dumb;
	    }while(dumb != '\n');

	    if(islower(letter)) letter=letter-32;

		for(int i=0;i<length;i++){
			if(letter==word[i]){
				guessWord[i]=letter;
				correct=1;

			}
			if(guessWord[i]=='*') won=0;
		}
		if(correct==0) tries--;
		else correct=0;

	}while(tries>0 && won==0);

	if(won==1) printf("\nSecret Word: %s \nCongratulations! You won!!!\n",word);
	else printf("You lose!\n The secret word was %s!\n",word);

}