#ifndef Rank_H
#define Rank_H
#include <windows.h>
#include <iostream>
#include <fstream>
#define CDIM 100

using namespace std;

struct Aux
{
	string name;
	int score;
};


class Rank
{
	private:

		void PutInOrder(Aux [],int);
		void Exchange(Aux&, Aux&);
		void PutInOrder_Rank();


	public:
		Rank();

		void SavePlayer(string, int);
		void ViewRank();
};

#endif
