// Nicholas Beaudoin
// Assignment 1
// 2-14-16

#define _CRT_SECURE_NO_WARNINGS 1
#define MAXGUESSES 5

#include <stdio.h>

/*
 * function prototypes 
 */

//this function provides instructions to the user on how to play the game
void gameRules();

// this function gets the desired number of games from the 
// user.
int numGames();

//this function runs one entire game. It for checks either 5 incorrect guesses or a correct guess.
//It returns a 0 if the game is over and the player did not guess the letter, otherwise it returns 1.
int singleGame(char file_letter);

//this function prompts the player to make a guess and returns that guess
//this function is called from inside the SingleGame( ) function described above
char retrieveGuess();

//this function takes two arguments, the guess from the player 
//and the solution letter from the file. 
//It lets the user know if the guess comes alphabetically before or after the answer 
//The function returns 1 if the guess matches the solution and returns a 0 if they do not match
//this function is called from inside the OneGame( ) function described above
int guessedIt(char answer, char guess);

int main()
{
	// declare additiional variables
	
	char file_letter;
	int playGames = 0,
	gameAttempt,
	i = 0;
	FILE *inPtr;

	// display instructions
	gameRules();

	// open file
	inPtr = fopen("lettersin.txt", "r");

	// get number of games to play 
	playGames = numGames();
	
	// confirm that (1 <= playGames <= 4)
	if(playGames < 1 || playGames > 4){
		printf("\nThat's not an acceptable number of games!\n");
		printf("Give it another try.\n\n");
		return 0;
	}
	

	for (i = 0; i < playGames; i++) {
		
		printf("***************************************************\n");

		// get letter from file
		fscanf(inPtr, " %c", &file_letter);
		// play one game
		printf("Let's play game %d\n", i+1);
		gameAttempt = singleGame(file_letter);
		// check for win or lose
		if(gameAttempt == 1){
			printf("You guessed it!!!\n\n");
		} else {
			printf("You did not guess the letter. It was %c\n\n", file_letter);
			printf("----- GAME OVER -----\n\n");
		}
	}

	//close file
	fclose(inPtr);
	
	return 0;

}

/*
 * function definitions
 */



//this function provides instructions to the user on how to play the game
void gameRules()
{
	printf("\nWelcome to the Letter Guessing Game\n");
	printf("You will enter the number of games you want to play (1-4 games)\n");
	printf("You have 5 chances to guess each letter\n");
	printf("Let's begin: \n\n");
	printf("------------------------------\n");
}

// this function gets the desired number of games from the 
// keyboard.
int numGames(){
	int playGames;
	printf("How many games do you want to play (1-4)?: ");
	scanf(" %d", &playGames);
	return playGames;
}

//this function runs one entire game. It checks for either 5 incorrect guesses or a correct guess.
//It returns a 0 if the game is over and the player did not guess the letter, otherwise it returns 1.
int singleGame(char file_letter)
{
	
	int numGuesses = 0,
	verdict;
	char guess;
	
	while (numGuesses < MAXGUESSES)
	{
		// retrieveGuess funtion call
		guess = retrieveGuess();
		verdict = guessedIt(file_letter, guess);
		if(verdict == 1){ 
			return verdict;
		}
		// update counter for number of guesses used 
		numGuesses += 1;
	}
	return verdict;
}

//this function prompts the player to make a guess and returns that guess
//this function is called from inside the SingleGame( ) function described above
char retrieveGuess()
{
	char guess;
	printf("Enter a guess: ");
	scanf(" %c", &guess);
	return guess;
}

//this function takes two arguments, the guess from the player 
//and the solution letter from the file. 
//it lets the user know if the guess comes alphabetically before or after the answer 
//the function returns 1 if the guess matches the solution and returns a 0 if they do not match
//this function is called from inside the singleGame( ) function described above
int guessedIt(char answer, char guess)
{
	if(guess > answer){
		printf("\n\nThe letter you are trying to guess comes before %c\n", guess);
		return 0;
	}else if(guess < answer){
		printf("\n\nThe letter you are trying to guess comes after %c\n", guess);
		return 0;
	}else{
		return 1;
	}
}

