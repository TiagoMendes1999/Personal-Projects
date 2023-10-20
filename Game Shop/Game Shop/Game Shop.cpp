#include <iostream>
#include <random>
#include <string>


using namespace std;

void DisplayWelcomeMessage();
void TitleScreen(double& playerCash, int stockQuantityRemaining[], double itemPrice[], string itemName[], string purchasedItems[]);
void GetPlayerName(double& playerCash, int stockQuantityRemaining[], double itemPrice[], string itemName[], string purchasedItems[]);
void DisplayInventoryMenu(string playerName, double& playerCash, int stockQuantityRemaining[], double itemPrice[], string itemName[], string purchasedItems[]);
void VerifyStockQuantity(string playerName, double& playerCash, int stockQuantityRemaining[], double itemPrice[], string itemName[], string purchasedItems[]);
void DisplayOutOfStockMessage();
bool HasEnoughCash(double& playerCash, double itemPrice[], float userInput);
void DisplayCheckOutScreen(string purchasedItems[], double itemPrice[], string playerName, double& playerCash, int stockQuantityRemaining[], string itemName[], float userInput);
bool PurchaseStock(float userInput, double& playerCash, double itemPrice[], int stockQuantityRemaining[], string purchasedItems[], string itemName[]);
bool RemoveItemFromPurchase(string purchasedItems[], double itemPrice[], double& playerCash, int stockQuantityRemaining[], string itemName[], string playerName);

int main()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(500, 2000);

	double playerCash = dis(gen);

	int stockQuantityRemaining[14] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	double itemPrice[14] = { 479.00,479.00,300.00,1299.00,699.99,569.00,325.00,50.00,1599.99,479.00,59.99,39.99,100.00, 41.99 };
	string itemName[14] = { "PlayStation 5", "Xbox Series X", "Nintendo Switch", "VIVE XR Elite", "Arcade Machine", "Steam Deck (512GB)", "Wii Console bundle", "Gameboy Console", "NVIDIA GeForce RTX 4090 24GB", "Quest 3 VR Headset", "God Of War (PlayStation)", "Pokemon Violet (Nintendo Switch)", "Gameboy Game Bundle", "Elden Ring(Xbox)" };
	string purchasedItems[14];

	DisplayWelcomeMessage();
	TitleScreen(playerCash, stockQuantityRemaining, itemPrice, itemName, purchasedItems);
}

void DisplayWelcomeMessage()
{
	cout << " ------ Welcome to Tiago's Game Shop!  ------ " << endl;
	cout << "You will start by being allocated a random amount of cash" << endl;
	cout << "You will then be shown a list of items along with their quantity - Choose wisely!" << endl;
}

void TitleScreen(double& playerCash, int stockQuantityRemaining[], double itemPrice[], string itemName[], string purchasedItems[])
{
	cout << " ------ Press 1 to start ------ " << endl;
	cout << " ------ Press 2 to quit ------ " << endl;
	float userInput;
	cin >> userInput;

	system("cls");

	if (userInput == 1)
	{
		GetPlayerName(playerCash, stockQuantityRemaining, itemPrice, itemName, purchasedItems);
	}
	else if (cin.fail() || userInput < 1 || userInput > 2 || userInput != static_cast<int>(userInput))   
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Error: Invalid Input!" << endl;
		TitleScreen(playerCash, stockQuantityRemaining, itemPrice, itemName, purchasedItems);
	}
	else
	{
		cout << "Goodbye!" << endl;
	}
}

void GetPlayerName(double& playerCash, int stockQuantityRemaining[], double itemPrice[], string itemName[], string purchasedItems[])
{
	cout << "Please enter your name: " << endl;
	string playerName;
	cin >> playerName;
	system("cls");
	DisplayInventoryMenu(playerName, playerCash, stockQuantityRemaining, itemPrice, itemName, purchasedItems);
}

void DisplayInventoryMenu(string playerName, double& playerCash, int stockQuantityRemaining[], double itemPrice[], string itemName[], string purchasedItems[])
{
	cout << ("\x1B[96mInventory Menu\033[0m\t\t") << endl;

	cout << "Here you will be able to view what's for sale " << endl;
	cout << "You can also see each item's available quantity and your remaining cash amount " << endl;
	cout << "Choose wisely!" << endl;
	cout << endl;

	cout << ("\x1B[96m ------ Inventory ------ \033[0m\t\t") << endl;

	int sizeOfIndex = 14; 
	
	for (int i = 0; i < sizeOfIndex; i++) 
	{
		cout << " - [" << i + 1 << "] " << itemName[i] << ": " << char(156) << itemPrice[i] << " - Quantity remaining:" << "[" << stockQuantityRemaining[i] << "]" << endl;
	}
	
	cout << endl; 
	cout << playerName << ", your cash amount is: " << char(156) << playerCash << endl;

	cout << ("\x1B[96mPlease enter the number corresponding to the item you wish to purchase\033[0m\t\t") << endl;

	cout << "\x1B[97mPlease type" "\x1B[92m 'Checkout'" "\x1B[97m to proceed to the checkout screen\033[0m\t\t" << endl;
	VerifyStockQuantity(playerName, playerCash, stockQuantityRemaining, itemPrice, itemName, purchasedItems);
	cout << endl;


}

void VerifyStockQuantity(string playerName, double& playerCash, int stockQuantityRemaining[], double itemPrice[], string itemName[], string purchasedItems[])
{
	string userInputStr;
	cin >> userInputStr;

	float userInput = 0.0; 

	if (userInputStr == "Checkout" || userInputStr == "checkout")
	{
		DisplayCheckOutScreen(purchasedItems, itemPrice, playerName, playerCash, stockQuantityRemaining, itemName, userInput); 
	}
	else
	{
		try
		{
			userInput = stof(userInputStr); 
		}
		catch (...)
		{
			system("cls");
			cin.clear();
			cin.ignore(100, '\n');
			cout << ("\x1B[91mError: Invalid input!\033[0m\t\t") << endl;
			DisplayInventoryMenu(playerName, playerCash, stockQuantityRemaining, itemPrice, itemName, purchasedItems);
		}

		if (cin.fail() || userInput < 1 || userInput > 14 || userInput != static_cast<int>(userInput))
		{
			system("cls");
			cin.clear();
			cin.ignore(100, '\n');
			cout << ("\x1B[91mError: Invalid input!\033[0m\t\t") << endl;
			DisplayInventoryMenu(playerName, playerCash, stockQuantityRemaining, itemPrice, itemName, purchasedItems);
		}

		if (userInput >= 1 && userInput <= 14)
		{
			int itemIndex = static_cast<int>(userInput) - 1;
			if (stockQuantityRemaining[itemIndex] > 0)
			{
				HasEnoughCash(playerCash, itemPrice, userInput);  
				PurchaseStock(userInput, playerCash, itemPrice, stockQuantityRemaining, purchasedItems, itemName);
				DisplayInventoryMenu(playerName, playerCash, stockQuantityRemaining, itemPrice, itemName, purchasedItems);
			}
			else
			{
				DisplayOutOfStockMessage();
				DisplayInventoryMenu(playerName, playerCash, stockQuantityRemaining, itemPrice, itemName, purchasedItems);  
			}
		}
	}

}

void DisplayOutOfStockMessage()
{
	system("cls");
	cout << "\x1B[91mThis item is out of stock!\033[0m\t\t" << endl;
	cout << endl;
}

bool HasEnoughCash(double& playerCash, double itemPrice[], float userInput)
{
	int itemIndex = static_cast<int>(userInput) - 1;
	if (playerCash >= itemPrice[itemIndex])
	{
		return true;
	}
	
	system("cls"); 
	cout << "\x1B[91mYou don't have enough cash to buy this item!\033[0m\t\t" << endl; 
	cout << endl;  
	return false;
}

void DisplayCheckOutScreen(string purchasedItems[], double itemPrice[], string playerName, double& playerCash, int stockQuantityRemaining[], string itemName[], float userInput)
{
	system("cls");

	cout << ("\x1B[96m ------ Checkout ------ \033[0m\t\t") << endl; 
	cout << endl; 
	 
	float minPrice = FLT_MAX; 
	string leastExpensiveItem; 
	float maxPrice = 0.0; 
	string mostExpensiveItem;  
	double totalPrice = 0.0; 
	for (int i = 0; i < 14; i++)
	{
		if (!purchasedItems[i].empty())
		{
			cout << "\x1B[92m" << purchasedItems[i] << ": " << char(156) << itemPrice[i] << "\033[0m\t\t" << endl;
			totalPrice += itemPrice[i];
			cout << endl;

			if (itemPrice[i] < minPrice)
			{
				minPrice = itemPrice[i];
				leastExpensiveItem = purchasedItems[i];
			}
			if (itemPrice[i] > maxPrice)
			{
				maxPrice = itemPrice[i];
				mostExpensiveItem = purchasedItems[i];
			}
		}
	}

	cout << "\x1B[97mTotal Price: " << char(156) << totalPrice << "\033[0m\t\t" << endl; 
	cout << endl; 

	cout << "\x1B[97mThe least expensive item in your checkout is: " << leastExpensiveItem << "\033[0m\t\t" << endl; 
	cout << "\x1B[97mThe most expensive item in your checkout is: " << mostExpensiveItem << "\033[0m\t\t" << endl; 
	cout << endl;

	cout << "\x1B[97mPlease type" "\x1B[92m 'Confirm'" "\x1B[97m to proceed with your purchase\033[0m\t\t" << endl;
	cout << "\x1B[97mIf you wish to return an item, please type" "\x1B[92m 'Return'\033[0m\t\t" << endl; 
	cout << "\x1B[97mTo return back to the inventory menu, please type" "\x1B[92m 'Menu'\033[0m\t\t" << endl; 
	cout << endl;

	string userInputStr; 
	cin >> userInputStr; 
	if (userInputStr == "Confirm" || userInputStr == "confirm") 
	{
		system("cls"); 
		cin.clear(); 
		cin.ignore(100, '\n'); 
		cout << ("\x1B[96mThank you shopping at Tiago's Game Shop!\033[0m\t\t") << endl; 
		cout << endl; 
		cout << ("\x1B[96mGoodbye!\033[0m\t\t") << endl; 
		int doNotEnd; 
		cin >> doNotEnd; 
	}
	else if (userInputStr == "Menu" || userInputStr == "menu")
	{
		system("cls");
		DisplayInventoryMenu(playerName, playerCash, stockQuantityRemaining, itemPrice, itemName, purchasedItems);
	}
	else if (userInputStr == "Return" || userInputStr == "return")
	{
		system("cls");
		RemoveItemFromPurchase(purchasedItems, itemPrice, playerCash, stockQuantityRemaining, itemName, playerName); 
	}
	else
	{
		DisplayCheckOutScreen(purchasedItems, itemPrice, playerName, playerCash, stockQuantityRemaining, itemName, userInput);  
	}
}

bool PurchaseStock(float userInput, double& playerCash, double itemPrice[], int stockQuantityRemaining[], string purchasedItems[], string itemName[])
{

	int itemIndex = static_cast<int>(userInput) - 1;
	if (HasEnoughCash(playerCash, itemPrice, userInput))  
	{
		playerCash -= itemPrice[itemIndex]; 
		stockQuantityRemaining[itemIndex]--; 
		purchasedItems[itemIndex] = itemName[itemIndex];

		system("cls"); 
		cout << "\x1B[92mPurchase successful! Your remaining cash is: " << char(156) << playerCash << "\033[0m\t\t" << endl;
		cout << endl;
		return true;
	}
}

bool RemoveItemFromPurchase(string purchasedItems[], double itemPrice[], double& playerCash, int stockQuantityRemaining[], string itemName[], string playerName) 
{
	cout << ("\x1B[96mPlease enter the number corresponding to the item that you want to return\033[0m\t\t") << endl;

	int arrayIndex; 
	cin >> arrayIndex; 

	arrayIndex--; 

	if (arrayIndex >= 0 && arrayIndex < 14 && !purchasedItems[arrayIndex].empty()) 
	{
		playerCash += itemPrice[arrayIndex]; 
		stockQuantityRemaining[arrayIndex]++; 
		purchasedItems[arrayIndex] = "";
		system("cls"); 
		cout << "\x1B[92mItem returned successfully\033[0m\t\t" << endl;
		cout << endl; 
		DisplayInventoryMenu(playerName, playerCash, stockQuantityRemaining, itemPrice, itemName, purchasedItems); 
		return true;
	}
	else
	{
		system("cls"); 
		cout << "\x1B[91mInvalid input or item not found in purchased items!\033[0m\t\t" << endl;
		cout << endl; 
		DisplayInventoryMenu(playerName, playerCash, stockQuantityRemaining, itemPrice, itemName, purchasedItems); 
		return false;
	}
}
