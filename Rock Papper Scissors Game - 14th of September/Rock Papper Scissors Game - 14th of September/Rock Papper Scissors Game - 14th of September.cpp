#include <iostream>
#include <time.h> 

constexpr int Rock = 1;
constexpr int Paper = 2;
constexpr int Scissors = 3;

using namespace std;

void DisplayWelcomeMessage();
int PlayGame();
bool DidPlayerWin(int userInput, int randomNumber);
int PlayRound(int& userInput, int& randomNumber);


int main()
{	
	srand((unsigned)time(0));

	DisplayWelcomeMessage();
	PlayGame();
}


void DisplayWelcomeMessage()
{
	cout << "--------- Welcome to Rock, Paper or Scissors! ---------" << endl;
	cout << "Please enter your name: " << endl;
	string name;
	cin >> name;
	system("cls"); 
	cout << "Hello " << name << "!" << endl;
}


int PlayGame()
{
	bool didPlayerWin = false;
	bool isGameOver = false; 

	while (!isGameOver) 
	{
		int userInput; 
		int randomNumber; 

		PlayRound(userInput,randomNumber); 

		didPlayerWin = DidPlayerWin(userInput, randomNumber);  
		if (didPlayerWin) 
		{
			isGameOver = false;
		}
		else
		{
			isGameOver = true;
		}
	}
	return 0;

}

bool DidPlayerWin(int userInput, int randomNumber)
{ 
	system("cls");
	cout << "AI picked ";
	switch (randomNumber) 
	{
	case 1:
		cout << "Rock";
		break;
	case 2:
		cout << "Paper";
		break;
	case 3:
		cout << "Scissors";
		break;
	}
	cout << endl; 

	bool isWinner = true;
	bool isLoser = false;

	if (userInput == 1 && randomNumber == 3)
	{
		cout << "You win!" << endl;
		return isWinner; 
	}
	else if(userInput == 3 && randomNumber == 1)
	{
		cout << "You lost!" << endl;
		return isLoser; 
	}
	else if (userInput == 1 && randomNumber == 2)
	{
		cout << "You lost!" << endl;
		return isLoser; 
	}
	else if (userInput == 2 && randomNumber == 3)
	{
		cout << "You lost!" << endl;
		return isLoser;
	}
	else if (userInput == 3 && randomNumber == 2)
	{
		cout << "You win!" << endl;
		return isWinner; 

	}
	else if (userInput == 2 && randomNumber == 1)
	{ 
		cout << "You win!" << endl; 
		return isWinner; 


	}
	else if (userInput == randomNumber)
	{
		cout << "It's a draw... try again!" << endl;
		return PlayGame();
	}
}

int PlayRound(int& userInput, int& randomNumber) 
{

	cout << "Please pick Rock, Paper or Scissors." << endl;
	cout << " 1 = Rock " << endl;
	cout << " 2 = Paper " << endl;
	cout << " 3 = Scissors " << endl;
	randomNumber = 1 + rand() % 3;
	cin >> userInput;
	if (userInput > 3)
	{
		system("cls");
		cin.ignore(100, '\n');
		cout << "Error: Invalid input!" << endl;
		return PlayRound(userInput, randomNumber); 
	}
	else if (cin.fail()) 
	{
		system("cls");
		cin.clear(); 
		cin.ignore(100, '\n');
		cout << "Error: Invalid input!" << endl;
		return PlayRound(userInput, randomNumber);
	}
}