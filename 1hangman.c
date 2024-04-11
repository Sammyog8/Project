//hangman
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define words 5

void lives(int);
void game(char [20],char [100]);
void dis_guess(char [6]);
char search(char,char [20],int);
int main()
{
	char word[words][20]={"Suyash","Samyog","Sandeep","Dikchhya","Amina"};
	char hint[words][100]={"Roll no. 19","Roll no. 14","Roll no. 15","Roll no. 4","Roll no. 1"};
	srand(time(NULL));
	int index=rand()%words;
	game(word[index],hint[index]);
}
void game(char word[20],char hint[100])
{
	int i,len,life=6;
	char ch,guess[6];
	len=strlen(word);
	printf("Your word is:\n");
	for(i=0;i<len;i++)
		printf("_ ");
	printf("\nHint: %s\n",hint);
	
	do
	{
		printf("Enter your guess: ");
		scanf("%c",&ch);
		for(i=0;i<len;i++)
		{
			guess[6-life]=search(ch,word,life);
		}
		dis_guess(guess);
	}while(life!=0);
}
void dis_guess(char guess[6])
{
	int i;
	for(i=0;i<6;i++)
		printf("%c ",guess[i]);
}
char search(char ch,char word[20],int life)
{
	int len=strlen(word),i;
	for(i=0;i<len;i++)
		if(word[i]==ch)
			break;
	if(i<len)
	{
		printf("Correct Guess\n");
		return (ch); 
	}
	else
		{
			printf("Wrong Guess\n");
			life--;
			return(ch);
		}
}
