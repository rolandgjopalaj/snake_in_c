#include "Rank.h"

fstream file;

Rank::Rank()
{

}
void Rank::PutInOrder(Aux myArray[], int n)
{
    bool flag=true;
    while(flag)
    {
        flag=false;
        for(int i=0;i<n-1;i++)
        {
            if(myArray[i].score<myArray[i+1].score)
            {
                Exchange(myArray[i],myArray[i+1]);
                flag=true;
            }
        }
        n--;
    }
}

void Rank::Exchange(Aux& a, Aux& b)
{
    Aux aux;
    aux=a;
    a=b;
    b=aux;
}

void Rank::SavePlayer(string name, int score)
{
	file.open("rankFile.txt",ios::out|ios::app);
	file<<name<<" "<<score<<endl;
	file.close();
}

void Rank::ViewRank()
{
	PutInOrder_Rank();

	string name;
	int punto;
	int j = 0;
	int length;
	file.open("rankFile.txt",ios::in);
	while(file)
	{
		file>>name;
		file>>punto;
		j++;
	}
	file.close();

	file.open("rankFile.txt",ios::in);
	cout<<"\t\t\t\t RANK"<<endl<<endl;
	for(int i=0;i<j-1;i++)
	{
		file>>name;
		file>>punto;
		length = 0;
		while(name[length]!='\0')
		{
			length++;
		}
		cout<<"\t\t    "<<i+1<<"^   "<<name;

		for(int k=0;k<(12-length);k++)
		{
			cout<<" ";
		}
		cout<<" ---->    "<<punto<<endl;
	}
	file.close();
	cout<<endl;
}

void Rank::PutInOrder_Rank()
{
	Aux myArray[CDIM];
	int nPlayers=-1;

	//////-------------------------------------
	string aux;
	file.open("rankFile.txt",ios::in);
	while(file)
	{
		file>>aux;
		file>>aux;
		nPlayers++;
	}
	file.close();

	file.open("rankFile.txt",ios::in);
	for(int i=0;i<nPlayers;i++)
	{
		file>>myArray[i].name;
		file>>myArray[i].score;
	}
	file.close();

	PutInOrder(myArray, nPlayers);// put in order the array

	file.open("rankFile.txt",ios::out);

	if(nPlayers>9)
        nPlayers=9;
	for(int c=0;c<nPlayers;c++)
	{
		file<<myArray[c].name<<" "<<myArray[c].score<<"\n";
	}
	file.close();
}
