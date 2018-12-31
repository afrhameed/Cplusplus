/*
This code uses a DFA (Deterministic Finite Automata) to check whether a given string is a valid URL
*/


#include<stdio.h>
#include<string.h>
#define MAX 256  // max size of string

int isAlphabet(char letter);
void state(int i,char c);
void trapState(char curr[],int pos);
int q6(char curr[],int pos);
int q7(char curr[],int pos);

int main(){
	
	char choice;
	int accepted;
	printf("Project 1 for CS 341\nSemester:  Fall 2018\nWritten by:\nAfreen Hameed, ah453@njit.edu\nInstructor:  Marvin Nakayama, marvin@njit.edu\n\n");
	printf("Do you want to enter a string? Enter 'y' for YES and 'n' for NO:");
	scanf(" %c",&choice);  //reading user input

	while(choice=='y'){
		accepted=0;
		while ((getchar()) != '\n'); //clearing input buffer
		printf("Please enter a string: ");
		char buf[MAX];  //char array of string
    	fgets(buf, MAX, stdin); 
    	printf("The string is: %s\n", buf); 

    	//DFA code 
    	int i=0;  //position in string
    	printf("q1\n");   //start state
    	char letter=buf[i];
    	if(!isAlphabet(letter)) trapState(buf,i);
    	else if(letter=='w'){ //state q2
    		state(2,letter);  //prints state q2
    		letter=buf[++i];
    		if(letter=='w'){ //state q3
	    		state(3,letter);
	    		letter=buf[++i];
	    		if(letter=='w'){ //state q4
	    			state(4,letter);
	    			letter=buf[++i];
	    			if(isAlphabet(letter)){ //q6
	    				accepted=q6(buf,i);
	    			}
	    			else if(letter=='.'){ //q5
	    					state(5,letter);
     						letter=buf[++i];
     						if(isAlphabet(letter)){
     							accepted=q6(buf,i);
     						}
     						else{
     							trapState(buf,i);
     						}
	    			}
	    			else printf("You entered a letter not in {a-z,.}: %c",letter); 
	    		}
	    		else if (isAlphabet(letter)){ //q6
	    			accepted=q6(buf,i);
	    		}
	    		else if(letter=='.'){ //q7
	    			accepted=q7(buf,i);
	    		}
	    		else printf("You entered a letter not in {a-z,.}: %c",letter);
    		}
    		else if (isAlphabet(letter)){ 
    			accepted=q6(buf,i);
    		}
    		else if(letter=='.'){ //q7
    			accepted=q7(buf,i);
    		}
    		else printf("You entered a letter not in {a-z,.}: %c",letter);
    	}
    	else  accepted=q6(buf,i);

    	if(accepted==1) printf("The DFA recognizes the string: %s",buf);
    	else printf("The DFA doesn't recognize the string:  %s",buf);

    	
    	printf("Do you want to enter a string? Enter 'y' for YES and 'n' for NO:");
		scanf(" %c",&choice);
	}
	
	printf("Program will terminate. Bye!\n");

	return 0;
}

int isAlphabet(char letter){ //checks if letter is in a-z
	int asciiLetter=letter;
	if(asciiLetter>122 || asciiLetter < 97){
		return 0;
	}
	return 1;
}

void state(int i,char c){//prints current sate and character
	if(i==0){
		printf("%c --> trap state\n",c);
	}
	else printf("%c --> q%d \n",c,i);
}

void trapState(char curr[],int pos){ //handles trap state
	while(curr[pos]!='\n'){
		state(0,curr[pos++]);
	}
}

int q6(char curr[],int pos){ //handles trap state
	int trap=0;
	while(curr[pos]!='.'){
		if(!isAlphabet(curr[pos])){
			trap=1;
			break;
		}
		state(6,curr[pos]);
		pos++;
	}
	if(trap==0) return q7(curr, pos);
	else trapState(curr,pos);
	return 0;
}

int q7(char curr[],int pos){ //handles trap state
	if(curr[pos]!='.'){
		trapState(curr,pos);
		return 0;
	}
	else state(7,curr[pos++]);
	if(curr[pos]!='c'){
		trapState(curr,pos);
		return 0;
	}
	else state(7,curr[pos++]);
	if(curr[pos]!='o'){
		trapState(curr,pos);
	}
	else{
		state(7,curr[pos++]);
		if(curr[pos]=='\n') return 1;  //.co
	}
	if(curr[pos]!='m'){
		trapState(curr,pos);
		return 0;
	}
	else{
		state(7,curr[pos++]);
		if(curr[pos]=='\n') return 1; //.com
	}
	if(curr[pos]!='.'){
		trapState(curr,pos);
		return 0;
	}
	else state(7,curr[pos++]);
	if(curr[pos]!='c'){
		trapState(curr,pos);
		return 0;
	}
	else state(7,curr[pos++]);
	if(curr[pos]!='o'){
		trapState(curr,pos);
		return 0;
	}
	else state(7,curr[pos++]);
	if(curr[pos]!='\n'){
		trapState(curr,pos);
		return 0;
	}
	else return 1; //.com.co

	return 0;
}

