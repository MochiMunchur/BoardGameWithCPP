// Nicholas Nguyen
//
// .cpp file holds the following:
// functions for base class player
// functions for trap class and its children
//
// Purpose is to control functions dealing with movement
// and interactions, but for simplicity sake, those were moved to 
// theRealm class and handled there.


#include "game.h"


// functions for player class
player:: player()
{

}

player:: player(const player & )
{


}	

player:: ~player()
{


}



bool player:: activateTrap(trap & trapType) // activates a trap
{



	return true;

}






int player:: getLocation()
{



	return 0;

}




// functions for trap class
trap:: trap()
{

}

trap:: ~trap()
{


}

// used to mark spaces on the game board. 55 represents no trap on that game spot
int trap:: resetTrap()
{

	return 55;

}

// virtual class call for children
int trap:: trapEffect()
{

	return 55;
}


// used for player interaction to see what is on the spot they're standing on. Virtual function also moves to children.
void trap:: trapInfo() const
{

	cout << "Empty space. Nothing but brush and leaves around you." << endl; 

}


// virtual function call for the children to activate their respective traps
bool trap:: activateTrap()
{

	cout << " No traps detected. " << endl;
	return false;
}



// functions for freeze class

freeze:: freeze()
{

}	


bool freeze:: activateTrap() // if die roll is equal to 6, player is unaffected
{
	dice die;
	int userRoll = die.rollDie();

	cout << "\nIce Trap Sprung!" << endl;
	cout << "Rolling die to determine activation..." << endl;
	cout << userRoll << " was rolled..." << endl;	
	if(userRoll == 6)
	{
		cout << "Trap avoided!\n" << endl;	
		return false;
	}	
	else
	{
		cout << "Trap sprung!\n" << endl;	
		return true;

	}

}


int freeze:: trapEffect()
{
	cout << "You're a frozen block. You'll have to wait around until the sun shines kindly on you." << endl;
	return 1;
}



// if 0 on gamespot, represents freeze trap
int freeze:: resetTrap()
{

	return 0;
}


void freeze:: trapInfo() const
{
	cout << "Ice Trap: When activating this type of trap, roll a die." << endl; 
	cout << "If a '6' is rolled, nullify the effects of the trap. " << endl;
	cout << "Failure to roll a 6 results in a day being added to the total. " << endl;
}


// functions for slow class
slow:: slow()
{

}

bool slow:: activateTrap() // if die roll is equal to or less than 2, player is unaffected
{
	dice die;
	int userRoll = die.rollDie();

	cout << "\nMudpit Trap Sprung!" << endl;
	cout << "Rolling die to determine activation..." << endl;
	cout << userRoll << " was rolled..." << endl;	
	if(userRoll <= 2)
	{
		cout << "Trap avoided!\n" << endl;	
		return false;
	}	
	else
	{
		cout << "Trap sprung!\n" << endl;	
		return true;
	}
}


int slow:: trapEffect()
{

	cout << "You're wading through mud. Use a coin to determine next movement." << endl;
	cout << "You flipped a coin." << endl;	
	dice die;	
	int userRoll = 0;	
	if (die.fiftyFifty() == true)
	{
		cout << "Good thing you brought your lucky coin." << endl;	
		userRoll = 50;	
	}
	else
	{
		cout << "You lost the coin... " << endl;	
		userRoll = 25;
	}	

	return userRoll;
}


// if 1 on game spot, represents slow trap
int slow:: resetTrap()
{

	return 1;
}


void slow:: trapInfo() const
{
	cout << "Mudpit Trap: When activating this type of trap, roll a die." << endl; 
	cout << "If a '1' or '2' is rolled, nullify the effects of the trap. " << endl;
	cout << "Failure to roll '1' or '2' results in moving using a smaller die for one turn." << endl;
}



// functions for backwards class

backwards:: backwards()
{


}

bool backwards:: activateTrap() // if die roll is equal to or greater than 3, player is unaffected
{

	dice die;
	int userRoll = die.rollDie();

	cout << "\nBackwards Trap Sprung!" << endl;
	cout << "Rolling die to determine activation..." << endl;
	cout << userRoll << " was rolled..." << endl;	
	if(userRoll >= 3)
	{
		cout << "Trap avoided!\n" << endl;	
		return false;
	}	
	else
	{
		cout << "Trap sprung!\n" << endl;	
		return true;
	}


}

int backwards:: trapEffect()
{
	dice die;
	cout << "You walk around in a daze, you find yourself somewhere you've been before..." << endl;	
	return 6;
}

// if 2 on game board, represents backwards trap
int backwards:: resetTrap()
{

	return 2;
}


void backwards:: trapInfo() const
{
	cout << "Reverse Trap: When activating this type of trap, roll a die." << endl; 
	cout << "If a value greater than '2' is rolled, nullify the effects of the trap. " << endl;
	cout << "Rolling a '1' or '2' forces the next die roll to be movement towards the starting point." << endl;
}








