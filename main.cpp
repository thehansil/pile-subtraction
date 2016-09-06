// Threepile.cpp : Defines the entry point for the console application.
//

#include "threepile.h"
#include <iostream>
using namespace std;


int main()
{
	int p1, p2, p3;
	int n;
	int x;
	
	//collect input to start game
	cout << "Welcome to the Threepile Subtraction.\n";
	cout << "Please enter the number of stones in pile 1: ";
	cin >> p1; //collect pile1 size
	cout << "Please enter the number of stones in pile 2: ";
	cin >> p2; //collect pile1 size
	cout << "Please enter the number of stones in pile 3: ";
	cin >> p3; //collect pile1 size
	cout << endl;

	//assign input to piles
	Threepile gamestate(p1, p2, p3);
	//sort input for piles
	gamestate.sortPile();
	//check to see if gamestate is valid and user didn't input a losing game.
	if (gamestate.getPile(2) == 0 && gamestate.getPile(3) == 0)
	{
		cout << "This gamestate is invalid, please try again.\n";
		return 0;
	}

	//instantiate a new 3D array based on pile input for memoization. O(N^3)
	bool *** dynamic = new bool**[gamestate.getPile(1)+1]; // create a new boolean array of pointers to an array of pointers, of size Pile1 + 1
	for (int i = 0; i <= gamestate.getPile(1); i++) // for each item in the outter array:
	{
		dynamic[i] = new bool*[gamestate.getPile(2)+1]; //instantiate an array of pointers to values, of size Pile2 + 1
		for (int j = 0; j <= gamestate.getPile(2); j++) // for each item in middle array
		{
			dynamic[i][j] = new bool[gamestate.getPile(3)+1]; //instantiate an array of values, of size Pile3 + 1
		}
	}

	//assign null to all values in order to make sure we know which locations we have visited. O(N^3)
	for (int i = 0; i <= gamestate.getPile(1); i++) // for each item in the outer array:
	{
		for (int j = 0; j <= gamestate.getPile(2); j++) // for each for each item in middle array:
		{
			for (int k = 0; k <= gamestate.getPile(3); k++) // for each item in inner array: 
			{
				dynamic[i][j][k] = NULL; // assign NULL to each point.
			}
		}
	}

	
	if (gamestate.isWinner(gamestate, dynamic)) //calls isWinner function to check if current state is a winning state to see if computer goes first or not.
	{
		cout << "I'll go first." << endl; //this state is a winninng state, computer goes first.
		gamestate = gamestate.bestMove(dynamic); //determines best move and makes it
		gamestate.sortPile(); //sorts piles after making move
	}

	else
		cout << "You go first." << endl; //this is a losing state, player goes first.
	
	do { //begin game
		if (gamestate.getPile(2) == 0 && gamestate.getPile(3) == 0) //if this is a winning state:
			break; // break out - computer is going first anyway

		gamestate.printState(); //print the current gamestate

		//get user input to make next move
		cout << "Remove the number of stones in pile x from pile n: Type your answer as n x\n";
		cin >> n >> x; //get input
		gamestate.setPile(n, (gamestate.getPile(n) - gamestate.getPile(x))); //use input to set new pile values
		gamestate.sortPile(); //sort new pile values
		gamestate.printState(); //print out current gamestate

		//computer takes move
		cout << "I will take my turn.\n";
		gamestate = gamestate.bestMove(dynamic); //computer calls bestMove to determine next move
		gamestate.sortPile(); //sort new pile values

	} while ((gamestate.getPile(1) != 0 && gamestate.getPile(2) != 0) || (gamestate.getPile(1) != 0 && gamestate.getPile(3) != 0) || (gamestate.getPile(2) != 0 && gamestate.getPile(3) != 0)); // while no two piles are equal to 0, play game

	gamestate.printState(); // print final state
	cout << "Looks like today was not your day, for I am victorious!" << endl; // declare victory over puny human
	return 0; //finish game and return
}

