#include <iostream>
#include <time.h>

using namespace std;

bool DetermineResult(int randomNumberPlayer, int randomnumberAI);
bool PlayRound();

int main()
{
	cout << " ---------- Welcome to the Higher Number Game ---------- " << endl;
	cout << "You will be playing against AI. You and the AI will be given a random number." << endl;
	cout << "Whoever gets the higher number wins!" << endl;
	cout << "Good luck!" << endl;

	cout << "Please enter your name to continue: " << endl;
	string name;
	cin >> name;

	cout << "Welcome " << name << "!" << endl;
	bool isGameOver = false;


	while (!isGameOver)
	{
	isGameOver = PlayRound();
	}

}

bool DetermineResult(int randomNumberPlayer, int randomnumberAI)
{
	bool isDraw = (randomNumberPlayer == randomnumberAI);
	bool isWin = (randomNumberPlayer > randomnumberAI);

	if (isDraw)
	{
		cout << "It's a draw! You have one more chance!" << endl;
		return false;
	}
	else if (isWin)
	{
		cout << "You won! The AI's random number was " << randomnumberAI << endl;
		return false;
	}
	else
	{
		cout << "You lost! The AI's random number was " << randomnumberAI << endl;
	}
	return true;
}

bool PlayRound()
{
	cout << "Please press 1 when you are ready to play." << endl; 

	int input;
	cin >> input;

	if (input == 1)
	{
		cout << "Let's begin!" << endl; 
	}
	else
	{
		cout << "Error: Invalid input. Goodbye!" << endl; 
			
	}

	srand((unsigned)time(0));

	int randomNumberPlayer = 1 + rand() % 10;
	cout << "Your random number is " << randomNumberPlayer << endl;

	int randomnumberAI = 1 + rand() % 10;
	return DetermineResult(randomNumberPlayer, randomnumberAI);
}
