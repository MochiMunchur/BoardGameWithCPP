// Nicholas Nguyen, Program 2, CS 202
//
// The purpose of this program is to learn and utilize dynamic binding in a hierarchy.
// The program will allow a player to navigate through an obstacle course and interact 
// with three different obstacles. The three obstacles are a freeze trap, a slow trap,
// and a trap forcing the player to move backwards.
//
// This .h file holds all the classes for the program

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <time.h>

using namespace std;

class dice // for moving forward/backwards
{
	public:
		dice();
		~dice();
		int rollDie();
		bool fiftyFifty();
};



class trap // base class for three different kinds of traps
{
	public:
		trap();
		~trap();


		virtual	int resetTrap();
		virtual void trapInfo() const;	
		virtual bool activateTrap();
		virtual int trapEffect();



	protected:
		char * data;

};



class player 
{
	public:
		player();
		player(const player & );

		~player();

		bool activateTrap(trap & trapType); // activates a trap on LLL
		bool deactivateTrap(trap & trapType); // deactivates the next trap in the LLL dependent on position	
		int displayInfo(); // displays trap status and info
		int trapStatus(); // displays info about what traps are on the LLL and where they are	

		int getLocation(); // location of player



	protected:
		dice sixSidedDie;

};




class freeze: public trap
{
	public:
		freeze();
		bool activateTrap(); // trap that prevents a player from moving for one turn	
		int trapEffect();
		int resetTrap();	
		void trapInfo() const;	

	protected:

};

class slow: public trap
{
	public:
		slow();
		bool activateTrap(); // trap that forces player to flip a coin to move 1 or 2 spaces rather than rolling a 6 sided die
		int trapEffect();
		int resetTrap();
		void trapInfo() const;	

	protected:


};	


class backwards: public trap
{
	public:
		backwards();
		bool activateTrap(); // trap that forces player to move backwards
		int trapEffect();
		int resetTrap();
		void trapInfo() const;	

	protected:


};	



struct node // utilizing strct node for node usage in a DLL
{

	int data;
	trap * trapThing;

	node * previous;
	node * next;


};





class theRealm // the DLL for game board -- data structure
{
	public:
		theRealm();
		~theRealm();

		int build();	
		int build(node * & head, int gameLength); // build gameboard		
		int remove(int i); // delete a node from the DLL
		bool removeAll(); // delete all nodes from the DLL	
		int displayRealm(); // displays the DLL gameboard
		int displayRealmReverse(); // displays the DLL gameboard backwards for opposing player

		int movePlayer(int numMove); // player movement turn wrapper	
		int movePlayer(int moveSpace, int & index, node * & player); //player movement turn recursive
		int movePlayerBack(int moveSpace, int & index, node * & player); // player movement backwards recursive

		int trapInfo();	 // function call for trap information the player is standing on
		int resolveTrap();	// function call to resolve trap effects on a positive trap space	

		bool checkSpace(); // checks space to see if player pointer is on trap pointer	
		bool checkEndGame();// checks if player is on the last spot of the game board

	protected:
		node ** head;
		int boardSize;
		node * player1;
		int playerIndex;
		node * finish;

		freeze iceCube;
		slow mudPuddle;
		backwards reverse;
		trap noTrap;

		dice sixSidedDie;

	private:
		int displayRealm(node * head);
		// int displayRealmReverse(node * tail);

		int removeAll(node * & head);

};




/*
   class dungeon // each spot on the game board is a "dungeon" --- part of the  data structure 
// not sure if this class will be used any longer
{
public:
dungeon();
~dungeon();

void displayDungeon(); // displays any info on node	

protected:
node * head;
node * tail;
trap * randomTrap;
};
*/
