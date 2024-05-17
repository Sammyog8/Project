//hangman  w=wrong
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WORDS 5

void lives(int);
void game(char*, char*);
int search(char, char*, char*, int);

int main() 
{
	int index;
    char *word[WORDS] = {"Suyash", "Samyog", "Sandeep", "Dikchhya", "Dinesh"};
    char *hint[WORDS] = {"Roll no. 19", "Roll no. 14", "Roll no. 15", "Roll no. 4", "C Teacher"};
    srand(time(NULL));
    index = rand() % WORDS;
    game(word[index], hint[index]);
    return 0;
}

void game(char *word, char *hint) {
    int i, len, life = 6, w = 0;
    char ch, guess[26] = {0};
    char display[20] = {0};
    len = strlen(word);

    for (i = 0; i < len; i++) {
        display[i] = '_';
    }
    display[len] = '\0';

    printf("Hint: %s (1st letter is capital)\n", hint);
    
    do {
        lives(life);
        printf("Your word is: ");
        for (i = 0; i < len; i++) {
            printf("%c ", display[i]);
        }
        printf("\nEnter your guess: ");
        scanf(" %c", &ch);

        if (strchr(guess, ch) != NULL) {
            printf("Already Guessed!\n");
            continue;
        }

        guess[w] = ch;
        w++;
        
        int found;
        found = search(ch, word, display, len);
		if (found == 0){
            life--;
        }

    } while (life > 0 && strchr(display, '_') != NULL);

    if (life > 0) {
        printf("Congratulations! You've guessed the word: %s\n", word);
    } else {
        printf("You've run out of lives. The word was: %s\n", word);
    }
}

int search(char ch, char *word, char *display, int len) {
    int i, found = 0;
    for (i = 0; i < len; i++) {
        if (word[i] == ch) {
            display[i] = ch;
            found = 1;
        }
    }
    if (found) {
        printf("Correct Guess\n");
    } else {
        printf("Wrong Guess\n");
    }
    return found;
}

void lives(int life) {
    switch (life) {
        case 6:
            printf("-----\n");
            printf("|    \n");
            printf("|    \n");
            printf("|    \n");
            break;
        case 5:
            printf("-----\n");
            printf("|   O \n");
            printf("|    \n");
            printf("|    \n");
            break;
        case 4:
            printf("-----\n");
            printf("|   O \n");
            printf("|   | \n");
            printf("|    \n");
            break;
        case 3:
            printf("-----\n");
            printf("|   O \n");
            printf("|  /| \n");
            printf("|    \n");
            break;
        case 2:
            printf("-----\n");
            printf("|   O \n");
            printf("|  /|\\ \n");
            printf("|    \n");
            break;
        case 1:
            printf("-----\n");
            printf("|   O \n");
            printf("|  /|\\ \n");
            printf("|  /  \n");
            break;
        case 0:
            printf("-----\n");
            printf("|   O \n");
            printf("|  /|\\ \n");
            printf("|  / \\ \n");
            break;
        default:
            printf("ERROR?\n");
    }
}
