/****************************************************
* Author: Braeden Kilburn
* Section: 1005
*
* Date Created: 28 March 2020
*
* Description: Based on the classic game Mastermind,
* this program will have the players attempting to find
* a passcode using logical deduction. Based on the
* chosen difficulty, a 3, 4, or 5 digit passcode will be
* generated. The player is then allowed a number of
* guesses to find the passcode and is told how close
* they are to the correct passcode in order to guide
* the player to the solution.
*
****************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

//Function Prototypes
void setupGame();
void displayHelp();
void foldCase(string& choice);
void generatePasscode(string& passcode, int& digitCount, int& minimumDigitValue, int& maximumDigitValue);
void startGame(int& digitCount, int& minimumDigitValue, int& maximumDigitValue, int& attemptsRemaining);
bool validateGuess(string& playerGuess, int& minimumDigitValue, int& maximumDigitValue, int& digitCount);
void reportDifferences(string& passcode, string& playerGuess);

//-----------------------------------------------
//------------DO NOT ALTER MAIN-----------
//-----------------------------------------------
int main(int argc, char* argv[])
{
	//Check command line arguments for debug mode
	//Normal
	if (argc == 1)
	{
		srand((unsigned int)time(NULL));
	}
	else if (argc >= 2)
	{
		//Debug Mode
		string argument = argv[1];
		if (argc == 2 && argument == "debug")
		{
			srand(0);
		}
		//Usage Guidelines
		else
		{
			cout << "To start program in debug mode: \n";
			cout << argv[0] << " debug\n";
			return -1;
		}
	}

	//Main Menu
	string choice = "";
	do
	{
		cout << "+--------------------+\n";
		cout << "| Main Menu          |\n";
		cout << "+--------------------+\n";
		cout << "| [Start] Simulation |\n";
		cout << "| [Help] Guide       |\n";
		cout << "| [Quit]             |\n";
		cout << "+--------------------+\n";
		cout << endl;

		do
		{
			cout << "Select a menu option: ";
			cin >> choice;
			foldCase(choice);
			if (choice == "start")
			{
				setupGame();
				break;
			}
			else if (choice == "help")
			{
				displayHelp();
				break;
			}
			else if (choice == "quit")
			{
				break;
			}
			else
			{
				cout << "Invalid menu selection.\n";
			}
		} while (true);
	} while (choice != "quit");

	return 0;
}
//-----------------------------------------------
//------------DO NOT ALTER MAIN-----------
//-----------------------------------------------

void setupGame() // Gives the player the opportunity to choose their difficulty
{
	cout << endl;
	cout << left << setw(21) << setfill('-') << "+" << "+" << endl;
	cout << "|" << right << setw(18) << setfill(' ') << "Select Difficulty" << setw(3) << "|" << endl;
	cout << left << setw(21) << setfill('-') << "+" << "+" << endl;
	cout << "| " << setw(19) << setfill(' ') << "[Easy]" << "|" << endl;
	cout << "| " << setw(19) << "[Medium]" << "|" << endl;
	cout << "| " << setw(19) << "[Hard]" << "|" << endl;
	cout << setw(21) << setfill('-') << "+" << "+" << endl;
	cout << "| " << setw(19) << setfill(' ') << "[Help]" << "|" << endl;
	cout << "| " << setw(19) << "[Main] Menu" << "|" << endl;
	cout << setw(21) << setfill('-') << "+" << "+" << endl;

	int digitCount{ 0 }; // How many digits in the passcode
	int minimumDigitValue{ 1 }; // This will always be one
	int maximumDigitValue{ 0 }; // The range of the digits (1 - what max?)
	int attemptsRemaining{ 0 };
	string difficulty;

	do
	{
		cout << "\nSelect a menu option: ";
		cin >> difficulty;
		foldCase(difficulty);
		if (difficulty == "easy") // User chose the easy difficulty
		{
			maximumDigitValue = 3;
			digitCount = 3;
			attemptsRemaining = 10;
			startGame(digitCount, minimumDigitValue, maximumDigitValue, attemptsRemaining);
			break;
		}
		else if (difficulty == "medium") // Medium difficulty
		{
			maximumDigitValue = 5;
			digitCount = 4;
			attemptsRemaining = 15;
			startGame(digitCount, minimumDigitValue, maximumDigitValue, attemptsRemaining);
			break;
		}
		else if (difficulty == "hard") // Hard difficulty
		{
			maximumDigitValue = 9;
			digitCount = 5;
			attemptsRemaining = 20;
			startGame(digitCount, minimumDigitValue, maximumDigitValue, attemptsRemaining);
			break;
		}
		else if (difficulty == "help") // Displays help screen
		{
			displayHelp();
		}
		else if (difficulty == "main") // Returns to the main menu
		{
			cout << endl;
			return;
		}
		else // Anything that's not a menu screen option
		{
			cout << "Invalid menu selection.\n";
		}
	} while (true);
}

void foldCase(string& choice) // Turns user input to lowercase
{
	for (unsigned int i = 0; i < choice.length(); i++) // For loop will continue for however long the string is
	{
		choice[i] = tolower(choice[i]);
	}
}

void displayHelp() // Instructions on how to play
{
	cout << endl;
	cout << setw(75) << setfill('~') << "" << endl;
	cout << "Goal:" << endl << endl;
	cout << "You must attempt to find a passcode using logical deduction." << endl;
	cout << "The passcode is a string of randomly generated digits and," << endl;
	cout << "depending on your selected difficulty, a predetermined length." << endl << endl;
	cout << "To win, you must input the correct password within a limited" << endl;
	cout << "amount of attempts before you are discovered by the New Order!\n" << endl;
	cout << "Difficulties:" << endl << endl;
	cout << "* EASY - The passcode will be composed of THREE (3) digits with values" << endl;
	cout << "         ranging between 1 & 3 (inclusive). You will have TEN (10)" << endl;
	cout << "         attempts to input the code." << endl << endl;
	cout << "* MEDIUM - The passcode will be composed of FOUR (4) digits with" << endl;
	cout << "         values ranging between 1 & 5 (inclusive). You will have" << endl;
	cout << "         FIFTEEN (15) attempts to input the code." << endl << endl;
	cout << "* HARD - The passcode will be composed of FIVE (5) digits with values" << endl;
	cout << "         ranging between 1 & 9 (inclusive). You will have TWENTY" << endl;
	cout << "         (20) attempts to input the code." << endl;
	cout << setw(75) << setfill('~') << "" << endl << endl;
}

void generatePasscode(string& passcode, int& digitCount, int& minimumDigitValue, int& maximumDigitValue) // Generates passcode based on the difficulty
{
	for (int i = 0; i < digitCount; i++) // For loop depending on digitCount (3, 4, or 5)
	{
		int randomNumber{ 0 };
		randomNumber = rand() % (maximumDigitValue - minimumDigitValue + 1) + minimumDigitValue; // rand() % (MAX - MIN + 1) + MIN  will always keep it in the range that you want [MIN, MAX] (inclusive)
		passcode += to_string(randomNumber); // Append an integer to the end of a string using to_string
	}
}

void startGame(int& digitCount, int& minimumDigitValue, int& maximumDigitValue, int& attemptsRemaining) // Plays the game after difficulty is chosen
{
	string passcode;
	generatePasscode(passcode, digitCount, minimumDigitValue, maximumDigitValue); // Generates the code to guess

	cout << endl;
	cout << left << setw(21) << setfill('-') << "+" << "+" << endl;
	cout << "|" << right << setw(19) << setfill(' ') << "Additional Options" << " |" << endl;
	cout << left << setw(21) << setfill('-') << "+" << "+" << endl;
	cout << "| " << setw(19) << setfill(' ') << "[Help]" << "|" << endl;
	cout << "| " << setw(19) << "[Main] Menu" << "|" << endl;
	cout << left << setw(21) << setfill('-') << "+" << "+" << endl << endl;

	int attemptsTotal{ attemptsRemaining }; // Variable that doesn't change but is referenced from the attempts remaining
	string playerGuess;

	do
	{
		cout << "Guess Code (" << digitCount << " Digits, " << minimumDigitValue << "-" << maximumDigitValue << ") "
			<< "[Attempts: " << attemptsRemaining << "/" << attemptsTotal << "]: ";
		cin >> playerGuess;
		foldCase(playerGuess); // Makes player's guess lowercase (for help and main)

		if (playerGuess == "help")
		{
			displayHelp();
		}
		else if (playerGuess == "main")
		{
			cout << endl;
			break; // Ends the Do Loop
		}
		else
		{
			bool guessValidation = validateGuess(playerGuess, minimumDigitValue, maximumDigitValue, digitCount); // Is their guess valid? Goes to validateGuess function to find out

			if (!guessValidation) // Guess Validation is not valid ( == false)
			{
				cout << "Error. Invalid Code Format." << endl << endl;
			}
			else
			{
				reportDifferences(passcode, playerGuess); // Compares the passcode and the guess to see how many are right, high, and low
				attemptsRemaining--; // Tracks how many attempts you have remaining

				// If you run out of attempts, game over
				if (attemptsRemaining == 0)
				{
					cout << "Abort Mission: Imperial security alerted to intrusion!" << endl;
					cout << "Code was " << passcode << "." << endl << endl;
					break;
				}

				// You figured out the right solution
				if (passcode == playerGuess)
				{
					cout << endl;
					break;
				}
			}
		}
	} while (playerGuess != "main");
}

bool validateGuess(string& playerGuess, int& minimumDigitValue, int& maximumDigitValue, int& digitCount) // Checks if the player's guess is valid (right amount of digits, etc.)
{
	int playerGuessLength = playerGuess.length(); // How long is the player's guess?

	if (playerGuessLength == digitCount) // Correct length
	{
		for (int i = 0; i < digitCount; i++) // For loop to read each character of the playerGuess string
		{
			if (playerGuess[i] < static_cast<char>(minimumDigitValue + 48) || playerGuess[i] > static_cast<char>(maximumDigitValue + 48)) // Converting the int to it's char equivalent based on ASCII table
			{
				return false; // The player's guess includes a digit not within the minimum and maximum allotted values
			}
		}
		return true; // Valid guess
	}
	else // Wrong passcode length
		return false;
}

void reportDifferences(string& passcode, string& playerGuess) // Tests the player's guess to the passcode and returns the differences
{
	int passcodeLength = passcode.length(); // Variable for the digit comparison loop
	int digitsCorrect{ 0 };
	int digitsHigh{ 0 };
	int digitsLow{ 0 };

	if (passcode != playerGuess)
	{
		for (int i = 0; i < passcodeLength; i++)
		{
			if (passcode[i] == playerGuess[i]) // Passcode and Guess are the same
				digitsCorrect++;
			else if (passcode[i] > playerGuess[i]) // Passcode digit is greater than the guess
				digitsLow++;
			else // Passcode digit is less than the guess
				digitsHigh++;
		}

		cout << endl;
		cout << left << setw(14) << setfill('-') << "+" << setw(7) << "+" << "+" << endl;
		cout << "|" << right << setw(13) << setfill(' ') << "Correct " << "|" << setw(5) << digitsCorrect << " |" << endl;
		cout << "|" << setw(13) << setfill(' ') << "Too High " << "|" << setw(5) << digitsHigh << " |" << endl;
		cout << "|" << setw(13) << setfill(' ') << "Too Low " << "|" << setw(5) << digitsLow << " |" << endl;
		cout << left << setw(14) << setfill('-') << "+" << setw(7) << "+" << "+" << endl << endl;

		// Reset the digit counters
		digitsCorrect = 0;
		digitsHigh = 0;
		digitsLow = 0;
	}
	else
	{
		digitsCorrect = passcodeLength; // The amount of digits correct is all of them, thus the entire passcode length.

		cout << endl;
		cout << left << setw(14) << setfill('-') << "+" << setw(7) << "+" << "+" << endl;
		cout << "|" << right << setw(13) << setfill(' ') << "Correct " << "|" << setw(5) << digitsCorrect << " |" << endl;
		cout << "|" << setw(13) << setfill(' ') << "Too High " << "|" << setw(5) << digitsHigh << " |" << endl;
		cout << "|" << setw(13) << setfill(' ') << "Too Low " << "|" << setw(5) << digitsLow << " |" << endl;
		cout << left << setw(14) << setfill('-') << "+" << setw(7) << "+" << "+" << endl << endl;

		cout << "Code Found Successfully: " << passcode << endl;
	}
}