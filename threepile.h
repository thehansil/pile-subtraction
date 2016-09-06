// threepile.h : Group 7
//

#include <vector>

using namespace std;

class Threepile
{
public:
	Threepile(int pile1, int pile2, int pile3);
	vector<Threepile> getMoves();
	bool isWinner(Threepile pile, bool ***dynamic);
	Threepile bestMove(bool ***dynamic);

	void printState();
	void setPile(int number, int value);
	int getPile(int number);
	void sortPile();

private:
	int pile1;
	int pile2;
	int pile3;
};