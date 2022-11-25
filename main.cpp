// Nicholas Nguyen

// main.cpp holds all the interactive functions and calling routines for the game 
// and player.
//
// As such, there is a lot of commented out code testing out different functions
// and how they interact with one another
//

#include "game.h"


int main()
{

	dice sixSidedDie;
	player playerOne;
	int totalTurns = 0;	

	theRealm gameBoard;

	// intro
	cout << "Welcome to the [Most Boring Game You'll Ever Play](TM)." << endl;
	cout << "Your goal is to make it through the board in as little moves as possible." << endl;
	cout << "How? Get lucky with your rolls.\n" << endl;
	cout << "After every movement phase, you'll have three options to select from." << endl;
	cout << "Rolling the die to move, displaying the map and your current location, and any information about the space you're standing on." << endl;
	cout << "Good luck in your venture.\n" << endl;


	int playerRoll = sixSidedDie.rollDie();

	cout << "\nYour journey begins... " << endl;
	gameBoard.displayRealm();


	do
	{
		int menuSelection;
		playerRoll = sixSidedDie.rollDie();
		// initial check to see if player is on a trap on day 1. also used again everytime the player selects a menu option
		if(gameBoard.checkSpace() == true)
		{ 
			int trapNum = gameBoard.resolveTrap();
			if(trapNum == 1)
			{
				totalTurns++;
			}
			else if(trapNum == 50)
			{
				gameBoard.movePlayer(2);
				totalTurns++;
			}	
			else if(trapNum == 25)
			{
				gameBoard.movePlayer(1);
				totalTurns++;	
			}
			else if(trapNum == 6)
			{	
				trapNum = -abs(sixSidedDie.rollDie());	
				gameBoard.movePlayer(trapNum);	
				totalTurns++;	
			}
		}

		cout << "Player One, please select an option from the following (1-3): " << endl;
		cout << "1. Roll die " << endl;
		cout << "2. Display map and current location " << endl;
		cout << "3. Display space status " << endl;
		cout << "Please make a selection: ";
		cin >> menuSelection;
		cin.ignore(100, '\n');

		// roll die
		if(menuSelection == 1)
		{
			cout << "Rolling Die..." << endl;	   
			cout << "Die Shows: " << playerRoll << endl;
			gameBoard.movePlayer(playerRoll);
			totalTurns++;		    
		}
		// displays map and position
		else if(menuSelection == 2)
		{
			cout << "The map is as follows: " << endl;

			gameBoard.displayRealm();
			cout << "You are that little * " << endl;

		}
		// displays the space's info (if there's a trap, what is it, if not, then nothing);
		else if(menuSelection == 3)
		{
			cout << "Space Status: ";
			gameBoard.trapInfo();
		}

		else
		{
			cout << "Invalid Entry" << endl;
		}
	}while(gameBoard.checkEndGame() == false); 



	// end
	cout << "YOU MADE IT!" << endl;
	cout << "It took you '" << totalTurns << "' days." << endl;
	cout << "Hope you had fun with [Most Boring Game You'll Ever Play](TM)" << endl;















	// cout << "REMOVING ONE SLOT" << endl;

	// gameBoard.remove(1);

	// gameBoard.displayRealm();

	// cout << endl;

	// cout << "DESTROYING BOARD" << endl;

	// gameBoard.removeAll();

	/*
	   if(gameBoard.displayRealm() == 0)
	   cout << "NO BOARD TO DISPLAY" << endl;
	   */

	return 0;
}






