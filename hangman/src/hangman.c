#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

void printWord(char word[]) {
    int letters = strlen(word);
    for (int i = 0; i < letters; i++)
    {
        printf("%c ", word[i]);
    }
    printf("\n");
}

void printHangman(int mistakes) {
    switch(mistakes) {
        case 0:
            printf("  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n");
            break;
        case 1:
            printf("  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n");
            break;
        case 2:
            printf("  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n");
            break;
        case 3:
            printf("  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n");
            break;
        case 4:
            printf("  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n");
            break;
        case 5:
            printf("  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n");
            break;
        case 6:
            printf("  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n");
            break;
    }
}

void printGuessedLetters(char letters[]) {
    int len = strlen(letters);
    printf("Guessed letters: ");
    for (int i = 0; i < len; i++) {
        printf(" %c ,", letters[i]);
    }
    printf("\n");
}


char getGuess () {
    char guess;
    printf("Enter your guess: ");
    scanf(" %c", &guess);
    return guess;
}

int checkLetter(char letter, char guessedLetters[]) {
    int good = 0;
    int length = strlen(guessedLetters);
    if (isalpha(letter)) {
        if (!strchr(guessedLetters, tolower(letter)))
        {
            good = 1;
        }
        else{
        good = -1; 
        }
    }
    return good;
}

int main() {
    char wordArray[10][50] = {"apple", "banana", "cherry", "date", "fig", "grape", "kiwi", "lemon", "mango", "nectarine"};
    srand(time(NULL));
    int wrongGuesses = 0;
    int letterCheck;
    char secretWord[50] = "";
    strcpy(secretWord, wordArray[rand() % (sizeof(wordArray)/sizeof(wordArray[0]))]);
    char guessedWord[50] = "";
    char guessedLetters[50] = "";
    for (int i = 0; i < strlen(secretWord); i++)
    {
        guessedWord[i] = '_';
    }    
    printf("Welcome to Hangman!\n");
    while (wrongGuesses < 6) {
        printf("Wrong guesses left: %d\n", 6 - wrongGuesses);
        printHangman(wrongGuesses);
        printGuessedLetters(guessedLetters);
        printWord(guessedWord);
        char guess = getGuess();
        letterCheck = checkLetter(guess, guessedLetters);
        if (letterCheck != 1 || !(strchr(secretWord, tolower(guess))))
        {
            if (letterCheck == -1)
            {
                printf("You already guessed that letter. Try again.\n");
            }
            else if (letterCheck == 0)
            {
                printf("Its a bad guess! try a letter\n");
            }
            else if (letterCheck == 1)
            {
                printf("good guess, but wrong letter!\n");
            }
            guessedLetters[strlen(guessedLetters)] = tolower(guess);
            guessedLetters[strlen(guessedLetters) + 1] = '\0';
            wrongGuesses++;
            continue;
        }
        for (int i = 0; i < strlen(secretWord); i++)
        {
            if (secretWord[i] == tolower(guess))
            {
                guessedWord[i] = tolower(guess);
            }
        }
        if (strcmp(secretWord, guessedWord) == 0) {
            printf("Congratulations! You've guessed the word! the word is '%s'\n", secretWord);
            break;
        }
    
    }
    if (wrongGuesses >= 6)
    {
        printf("You've lost! the word is '%s' \n", secretWord);
    }
    return 0;
}