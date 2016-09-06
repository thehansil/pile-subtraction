// threepile.cpp

#include "threepile.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;



Threepile::Threepile(int p1, int p2, int p3)
	:pile1(p1),pile2(p2), pile3(p3) // define object Threepile
{}

vector<Threepile> Threepile::getMoves()
{
	vector<Threepile> list; // create vector list	
	Threepile move1(pile1 - pile2, pile2, pile3); //assign move1 piles
	move1.sortPile(); //sort move1's piles
	
	if (pile3 != 0) //if pile 3 is not empty
	{
		Threepile move2(pile1 - pile3, pile2, pile3); // assign move2 piles
		move2.sortPile(); // sort move2 piles
		Threepile move3(pile1, pile2 - pile3, pile3); // assign move3 piles
		move3.sortPile(); // sort move3 piles

		//list = { move1, move2, move3 };
		list.push_back(move1); // assign move1 to vector list
		list.push_back(move2); // assign move2 to vector list
		list.push_back(move3); // assign move3 to vector list

	}

	else //otherwise there is only one move
	{
		//list = {move1};
		list.push_back(move1); // assign move1 to vector list
	}

	return list; // return list to function that called getMoves
}

bool Threepile::isWinner(Threepile p, bool ***dynamic)
{
	if (dynamic[p.pile1][p.pile2][p.pile3] != NULL) // if location is memoized:
		return dynamic[p.pile1][p.pile2][p.pile3]; // return value in location

	if (p.pile1 == 0 && (p.pile2 == p.pile3)) // if size of pile1 is 0, and other two piles match:
		return true; //return true, this is a winning function
	else if (p.pile2 == 0 && (p.pile1 == p.pile3)) // if size of pile2 is 0, and other two piles match:
		return true; //return true, this is a winning function
	else if (p.pile3 == 0 && (p.pile1 == p.pile2)) // if size of pile3 is 0, and other two piles match:
		return true; //return true, this is a winning function

	vector<Threepile> moves = p.getMoves(); // call get moves on threepile p

	if (!p.isWinner(moves[0], dynamic)) // if p's move 0 is a winner
	{
		dynamic[p.pile1][p.pile2][p.pile3] = true; // set value of 3D array item queue
		return true; // return true to previous move
	}
	if (moves.size() == 3) // if moves vector has 3 values:
	{
		if (!p.isWinner(moves[1], dynamic)) // if the second move is not a winning move:
		{
			dynamic[p.pile1][p.pile2][p.pile3] = true; //assign true to current state's move value
			return true; // return true to pick this move next in bestMove
		}
		if (!p.isWinner(moves[2], dynamic)) // if the third move is not a winning move:
		{
			dynamic[p.pile1][p.pile2][p.pile3] = true; // assign true to current state's move value
			return true; // return true to pick this move next in bestMove
		}
	}

	dynamic[p.pile1][p.pile2][p.pile3] = false; // if none of the following moves are losing moves, assign false to current move
	return false; // return false to not choose this move next
}

Threepile Threepile::bestMove(bool ***dynamic)
{
	vector<Threepile> moves = getMoves(); //create vector for getMoves

	if (moves.size() == 3) // if the vector for moves is of size 3:
	{
		if (!moves[1].isWinner(moves[1], dynamic)) // if move 2 is a winner:
			return moves[1]; // return it
		if (!moves[2].isWinner(moves[2], dynamic)) // if move 3 is a winner:
			return moves[2]; // return it
	}

	return moves[0]; // winning move is move 1 - return it
}


void Threepile::printState()
{
	//prints out pile values.
	cout << "\nPile 1:\tPile 2:\tPile 3: \n" << pile1 << "\t" << pile2 << "\t" << pile3 << "\t\n\n"; 
}

void Threepile::setPile(int n, int value)
{
	//set pile n to size value
	if (n == 1)
		pile1 = value;
	else if (n == 2)
		pile2 = value;
	else if (n == 3)
		pile3 = value;
}

int Threepile::getPile(int n)
{
	// return pile value for whatever index n is used.
	if (n == 1)
		return pile1;
	else if (n == 2)
		return pile2;
	else
		return pile3;
}

void Threepile::sortPile()
{
	vector<int> data; // initialize data vector
	data.push_back(pile1); // set pile1 to data vector item 0
	data.push_back(pile2); // set pile2 to data vector item 1
	data.push_back(pile3); // set pile3 to data vector item 2

	//initiate swapsort for data vector - pretty sure we don't need to explain this
	for (int i = 0; i < 2; i++)
	{
		int maxloc = i;
		for (int j = i + 1; j < 3; j++)
			if (data[j] > data[maxloc])
				maxloc = j;
		swap(data[i], data[maxloc]);
	}

	//set data vector values back to piles once sorted.
	pile1 = data[0];
	pile2 = data[1];
	pile3 = data[2];
}
