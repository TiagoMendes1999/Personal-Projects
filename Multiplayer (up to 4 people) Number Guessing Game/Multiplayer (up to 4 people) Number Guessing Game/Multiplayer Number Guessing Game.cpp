#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

void DisplayWelcomeMessage();
void HandlePlayerQuantity(string playerNames[], int playerGuesses[], string& winningPlayes);
bool PlayNewRound(int totalNumberOfPlayers, string playerNames[], int playerGuesses[], string& winningPlayers);
int DetermineResult(int totalNumberOfPlayers, string playerNames[], int playerGuesses[], string& winningPlayers); 
bool PlayFinalRound(string playerNames[], int playerGuesses[], string& winningPlayers, int numberOfPlayers, int totalNumberOfPlayers);
void HandlePlayerGuess(int& playerGuess, string playerName);
void GetplayerNames(string playerNames[], int totalNumberOfPlayers); 

int main()
{
	srand((unsigned)time(0));

	int playerGuesses[4];
	int totalNumberOfPlayers = 0;
	string playerNames[4];
	string winningPlayers;

	DisplayWelcomeMessage();
	PlayNewRound(totalNumberOfPlayers, playerNames, playerGuesses, winningPlayers); 
}

void DisplayWelcomeMessage()
{
	cout << " ------ Welcome to the Number Guessing Game Multiplayer Edition! ------ " << endl;
	cout << "This edition of the Number Guessing Game allows up to 4 players " << endl;
	cout << "Players will have one chance to guess the randomly generated number " << endl;
	cout << "Whoever's guess is closest to the random number wins!" << endl;
	cout << "If it's a draw, only the people who drew the correct number will play in one final round to determine who the winner is!" << endl;
}

bool PlayNewRound(int totalNumberOfPlayers, string playerNames[], int playerGuesses[], string& winningPlayers)
{
	cout << " ---- Press 1 to Play ---- " << endl;
	cout << " ---- Press 2 to Quit ---- " << endl;

	int userInput;
	cin >> userInput;

	if (userInput == 1)
	{
		HandlePlayerQuantity(playerNames, playerGuesses, winningPlayers);  
	}
	else if (userInput == 2)
	{
		system("cls");
		cin.clear();
		cin.ignore(500, '\n');
		cout << "Goodbye!" << endl;
		return false;
	}
	else if (cin.fail() || userInput > 2 || userInput == 0)
	{
		system("cls");
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Error: Invalid input!" << endl;
		return PlayNewRound(totalNumberOfPlayers, playerNames, playerGuesses, winningPlayers); 
	}
}

void HandlePlayerQuantity(string playerNames[], int playerGuesses[], string& winningPlayers)
{
	cout << "Please enter the total amount of players (between 1 and 4):" << endl;
	float totalNumberOfPlayers;
	cin >> totalNumberOfPlayers;
	
	if (cin.fail() || totalNumberOfPlayers < 1 || totalNumberOfPlayers > 4 || totalNumberOfPlayers != static_cast<int>(totalNumberOfPlayers))
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Error: Invalid player amount! Please enter an integer between 1 and 4." << endl; 
		HandlePlayerQuantity(playerNames, playerGuesses, winningPlayers); 
	}
	else
	{
		DetermineResult(totalNumberOfPlayers, playerNames, playerGuesses, winningPlayers); 
	}
}

int DetermineResult(int totalNumberOfPlayers, string playerNames[], int playerGuesses[], string& winningPlayers)
{
	GetplayerNames(playerNames, totalNumberOfPlayers); 

	int randomNumber = 1 + rand() % 50;
	cout << randomNumber << endl;
	cout << endl;
	
	int numberOfWinners = 0;

	for (int i = 0; i < totalNumberOfPlayers; i++)  
	{
		HandlePlayerGuess(playerGuesses[i], playerNames[i]);

		if (playerGuesses[i] == randomNumber)
		{
			numberOfWinners++;
			winningPlayers += playerNames[i] + " ";
		}
	}

	if (numberOfWinners >= 1)
	{
		system("cls");
		bool didSomebodyTie = numberOfWinners >= 2;
		if (didSomebodyTie)
		{
			cout << winningPlayers << "guessed the random number!" << endl;
			cout << "The random number was: " << randomNumber << endl;
			cout << "This means " << winningPlayers << " will need to play an additional round to determine the real winner!" << endl;
			return PlayFinalRound(playerNames, playerGuesses, winningPlayers, numberOfWinners, totalNumberOfPlayers);
		}
		else
		{
			cout << winningPlayers << "guessed the random number!" << endl;
			cout << "The random number was: " << randomNumber << endl;

		}
	}
	else if (totalNumberOfPlayers > 1)
	{
		int minDifference = 10000;
		vector<string> closestPlayerNames;
		{
			for (int i = 0; i < totalNumberOfPlayers; i++) 
			{
				int guessDifference = abs(randomNumber - playerGuesses[i]);
				if (guessDifference < minDifference)
				{
					minDifference = guessDifference;
					closestPlayerNames.clear();
					closestPlayerNames.push_back(playerNames[i]);
				}
				else if (guessDifference == minDifference)
				{
					closestPlayerNames.push_back(playerNames[i]);
				}
			} 
			if (closestPlayerNames.size() > 1)
			{
				cout << endl; 
				cout << "There is a draw among the following players with a difference of " << minDifference << ": " << endl; 
				for (const string& playerName : closestPlayerNames)
				{
					cout << playerName << "\n";
				}
				cout << endl; 
				cout << "This means a final round will need to be played to determine the real winner!" << endl;
				return PlayFinalRound(playerNames, playerGuesses, winningPlayers, numberOfWinners, totalNumberOfPlayers); 
			}
			else
			{
				cout << "The closest player is " << closestPlayerNames[0] << " with a difference of " << minDifference << "!" << endl; 
				cout << "Well done!" << endl; 
			}
		}
	
	}
	else
	{
		cout << "The random number was: " << randomNumber << "!" << endl; 
		cout << "Better luck next time!" << endl; 
	}
}


bool PlayFinalRound(string playerNames[], int playerGuesses[], string& winningPlayers, int numberOfPlayers, int totalNumberOfPlayers)
{
	cout << " ---- Press 1 to commence the final round ---- " << endl;
	cout << " ---- Press 2 to quit ---- " << endl; 
	int userInput; 
	cin >> userInput; 
	
	while (true)
	{
		if (userInput == 1) 
		{ 
			int randomNumber = 1 + rand() % 50;
			int numberOfWinners = 0;
			int closestGuess = -1;
			string winningplayerNames;
			string closestplayerNames;  
			cout << randomNumber << endl;  

			for (int i = 0; i < totalNumberOfPlayers; i++) 
			{
				cout << playerNames[i] << ", please enter your guess (between 1 and 50): " << endl;
				cin >> playerGuesses[i];

				while (cin.fail() || playerGuesses[i] < 1 || playerGuesses[i] > 50)
				{
					cin.clear(); 
					cin.ignore(100, '\n'); 
					cout << "Error: Invalid input for " << playerNames[i] << "!" << endl;
					cout << "Please enter a valid number between 1 and 50!" << endl;
					cin >> playerGuesses[i];
				}

				int guessDifference = abs(playerGuesses[i] - randomNumber); 

				if (guessDifference == 0)
				{
					numberOfWinners += 1;
					winningplayerNames += playerNames[i] + " ";
				}
				else if (closestGuess == -1 || guessDifference < abs(closestGuess - randomNumber))
				{
					closestGuess = playerGuesses[i];
					closestplayerNames = playerNames[i] + " ";
				}
				else if (guessDifference == abs(closestGuess - randomNumber))
				{
					closestplayerNames += playerNames[i] + " ";
				}

			}
			if (numberOfWinners >= 1)
			{
				system("cls");
				cout << winningplayerNames << "guessed the random number!" << endl;
				cout << "The random number was: " << randomNumber << "!" << endl; 
				cout << "Well done!!" << endl;
			}
			else
			{ 
				cout << "Nobody guessed the random number!" << endl;
				cout << "The closest guess was " << closestGuess << " by " << closestplayerNames << "!" << endl; 
				cout << "The random number was: " << randomNumber << "!" << endl; 
			}
		}
		else if (userInput == 2)
		{
			system("cls");
			cin.clear();
			cin.ignore(500, '\n');
			cout << "Goodbye!" << endl;
			return false;
		}
		else if (cin.fail() || userInput > 2)
		{
			system("cls");
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Error: Invalid input!" << endl;
			cout << " ---- Press 1 to commence the final round ---- " << endl;
			cout << " ---- Press 2 to quit ---- " << endl;
			cin >> userInput;
			continue;
		}

		break;
	}

	return true;
}

void HandlePlayerGuess(int& playerGuess, string playerName)
{
	bool playerGuessValid = false;

	cout << playerName << ", please enter your guess (between 1 and 50): " << endl;
	do
	{
		cin >> playerGuess;
		if (cin.fail() || playerGuess < 1 || playerGuess > 50)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Error: Invalid input for " << playerName << "!" << endl;
			cout << "Please enter a valid number between 1 and 50!" << endl;
		}
		else
		{
			playerGuessValid = true;
		}
	} while (!playerGuessValid);
		

	

}

void GetplayerNames(string playerNames[], int totalNumberOfPlayers)
{

	for (int i = 0; i < totalNumberOfPlayers; i++)  
	{
		cout << "Player " << (i + 1) << ", please enter your name: " << endl;
		cin >> playerNames[i];
	}

	system("cls");

	cout << "List of players ready: " << endl;
	for (int i = 0; i < totalNumberOfPlayers; i++) 
	{
		cout << "Player " << (i + 1) << ": " << playerNames[i] << endl;
	}
}