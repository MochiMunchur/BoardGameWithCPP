// Nicholas Nguyen

// .cpp file holds the following:
// functions concerning map creation (data structure DLL)
// functions concerning RNG for dice rolls and map creation
//
// 
//
#include "game.h"


// the realm class aka game board class
theRealm:: theRealm()
{	
	srand(time(NULL));
	boardSize = 1 + rand()%5;
	head = new node*[boardSize];

	build();

	player1 = head[0];

	playerIndex=0;

	finish = head[boardSize - 1];
	while(finish->next != NULL)
	{
		finish = finish->next;
	}

}

// destructor to dismantle gameboard
theRealm:: ~theRealm()
{
	player1 = NULL;
	finish = NULL;
	removeAll();

}



// builds the game board and gets called during the constructor
int theRealm:: build()
{

	// determines board size and length at runtime, and builds the first spot
	for(int i = 0; i < boardSize; i++)
	{	

		int length = 1 + rand()%5;	
		head[i] = new node;
		head[i]->data = length;
		head[i]->next = NULL;		
		head[i]->previous = NULL;		
		// while constructing a gamespace, determines whether that space will be a trap or not at a 30% chance
		if(rand()%10 >=7)
		{	
			int x = rand() % 100;

			// if the space is determined to be a trap, a 33% chance of being one of three traps 
			if(x%3 == 0)
			{
				head[i]->trapThing = &iceCube; 			
			}
			else if(x%3 == 1)
			{
				head[i]->trapThing = &mudPuddle;	

			}
			else if(x%3 == 2)
			{
				head[i]->trapThing = &reverse;	

			}	
		}
		else // if the spot is not a trap, the space will be labeled differently
		{
			head[i]->trapThing = &noTrap;
		}

		build(head[i], length - 1);	
	}
	return 0;
}

// recursive function for building the game board
int theRealm:: build(node * & head, int gameLength) 
{	


	if(gameLength == 0)
	{
		return 0;
	}
	node * temp = new node;
	temp->data = gameLength;
	temp->next = NULL;
	temp->previous = head;

	if(rand()%10 >=7)
	{	
		int x = rand()%100;
		if(x%3 == 0)
		{
			temp->trapThing = &iceCube; 			
		}
		else if(x%3 == 1)
		{
			temp->trapThing = &mudPuddle;	
		}
		else if(x%3 == 2)
		{
			temp->trapThing = &reverse;	
		}	
	}
	else
	{
		temp->trapThing = &noTrap;
	}

	head->next = temp;

	return build(head->next, gameLength - 1);

}

// removes the last game space on the board
int theRealm:: remove(int i)
{	


	if(!head[i])
		return 0;
	node * temp = head[i]->next;
	temp->previous = NULL;
	delete head[i];
	head[i] = temp;

	return 1;


}

// removes all gamespaces on the board. called in the destructor
bool theRealm:: removeAll()
{
	for(int i = boardSize - 1; i >= 0; i--)
	{	
		if(head[i])
		{	
			removeAll(head[i]);	
		}
	}


	return false;
}

// recursive function for removing all spaces on game board
int theRealm:: removeAll(node * & head)
{
	if(head->next == NULL)
	{
		delete head;
		head = NULL;	

		return 0;
	}	

	node * temp = head->next;
	temp->previous = NULL;
	delete head;
	head = temp;

	return removeAll(head);
}



// displays gameboard for player
int theRealm:: displayRealm()
{

	if(!head[0])
		return 0;

	for(int i = 0; i < boardSize; i++)
	{
		displayRealm(head[i]);
	}

	return 1;
}

// recursive for displaying
int theRealm:: displayRealm(node * head)
{

	if(head->next == NULL)
	{	
		if(head == player1)
			cout << " | * " << head->trapThing->resetTrap() << " | " << endl;						
		else
			cout << " | " << head->trapThing->resetTrap() << " | " << endl;			


		return head->data;	
	}	

	if(head == player1)
		cout << " | * " << head->trapThing->resetTrap();						
	else
		cout << " | " << head->trapThing->resetTrap();			


	return displayRealm(head->next);


}



// created initially for a two person game running from one end to the other
// left out due to time constraint
/*
   int theRealm:: displayRealmReverse()
   {

   if(!tail)
   return 0;

   return displayRealmReverse(tail);

   }

   int theRealm:: displayRealmReverse(node * tail)
   {

   if(tail == head)
   {
   cout << " | " << tail->data << " | " << endl;
   return tail->data;
   }


   cout << " | " << tail->data;

   return displayRealmReverse(tail->previous);

   }
   */

// player movement function wrapper
int theRealm:: movePlayer(int numMove)
{
	if(!head[playerIndex])
		return 0;

	// determines if the number moved in will be used for forward or backwards movement
	if(numMove > 0)
	{
		return movePlayer(numMove, playerIndex, player1);
	}
	else
	{
		return movePlayerBack(numMove, playerIndex, player1);
	}

	cout << player1->data << endl;

}


// forward movement function recusrive
int theRealm:: movePlayer(int moveSpace, int & index, node * & player)
{
	if(moveSpace == 0 || player == finish)
	{
		return 0;
	}

	if(player->next == NULL)
	{
		index++;	
		if(index == boardSize)
			return 99; // end of game


		player = head[index];	
		return movePlayer(moveSpace - 1, index, player);
	}


	player = player->next;
	return movePlayer(moveSpace - 1, index, player);

}

// backwards player movement for backwrads trap
int theRealm:: movePlayerBack(int moveSpace, int & index, node * & player)
{
	if(moveSpace == 0)
	{
		return 0;
	}

	if(player->previous == NULL)
	{
		index--;
		if(index < 0)
		{
			index = 0;
			return 0; // no more spaces to go back to; start of the board
		}
		else
		{
			node * temp = head[index]; // need a pointer to bring player back a row
			while(temp->next != NULL)
			{
				temp = temp->next;
			}
			player = temp; // player pointer now at the end of the previous row
			return movePlayerBack(moveSpace + 1, index, player); // continue recursion	
		}	
	}

	player = player->previous;
	return movePlayerBack(moveSpace + 1, index, player);
}


// after every movement and positive trap space, activates effects of trap
int theRealm:: resolveTrap()
{
	if(player1->trapThing->resetTrap() == 55)
	{
		return 0;
	}
	else
	{
		return player1->trapThing->trapEffect();
	}

}

// checks space for traps
bool theRealm:: checkSpace()
{

	if(player1->trapThing->resetTrap() == 55)
	{

		return false; // no trap
	}

	else
	{
		cout << "\n ---TRAP FOUND---" << endl;
		cout << player1->trapThing->resetTrap() << endl;
		return true;	

	}
}




// determines whether player is at the end of the game board
bool theRealm:: checkEndGame()
{
	if(player1 == finish)
	{
		return true;
	}

	return false;

}


// function call to send back info about any trap the player is standing on
int theRealm:: trapInfo()
{
	player1->trapThing->trapInfo();
	return 0;
}	




// dice function for class dice
dice:: dice() // constructor
{
	srand(time(NULL));
}


dice:: ~dice() // unneeded as we're not deallocating anything
{

}


int dice:: rollDie() // returns a random number between 1-6
{

	return 1 + rand()%6;
}


bool dice:: fiftyFifty() // returns a true/false value if rollDie function returns above or below a certain value
{

	if(rollDie() >= 4)
		return true;
	else	
		return false;

}








