#include <iostream>
#include <SFML/Graphics.hpp>
#include "conio.h"
#include <windows.h>

#define DIM 100
#include "Rank.h"

using namespace std;
using namespace sf;

void SetColor(short Color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,Color);
}

struct Snake
{
    int x;
    int y;
};

struct Fruit
{
    int x;
    int y;
};

Fruit fruit;
Snake snake[DIM];
Rank theRank;
int N=30,M=20;
int size=16;
int w =size*N;
int h=size*M;
int dir,nTail=4;
int level=100;
int score=0;
int addPoint=5;

//////////////////////////////////////////////////
//          S F M L
//////////////////////////////////////////////////
RenderWindow window;                                    //the window

RectangleShape map1(Vector2f(16,16));                   //the object for the map
CircleShape fruit_body(10.f);                           //the object for the fruit
CircleShape snake_body(10.f);                           //the object for the snake
//////////////////////////////////////////////////
int Menu();
void Instruction();
void DifficultyLevel();
void Enable_Close_Event();
void Play();
void Direction();
void Movements();
void Map_Draw();
void Fruit_Control();
bool Game_Over();
void Loading();
void GoodBye();
///////////////////////////////////////////////////

int main()
{
    int menu;

    Instruction();   //basic instructions on how to play the game
    getch();
    do
    {
        system("cls");
        menu=Menu();
        switch(menu)
        {
        case 1: Play();
        break;
        case 2: DifficultyLevel();
        break;
        case 3: system("cls");SetColor(14); theRank.ViewRank();SetColor(7); getch();
        break;
        case 0: system("cls");GoodBye();
        break;
        }
    }while(menu!=0);

    return 0;
}

///////////////////////////////////////////////////////
int Menu()
{
    int x;
    char choice;
    SetColor(13);
    do
    {
        system("cls");
        cout<<"\t\t _____________________________________ "<<endl;
        cout<<"\n\t\t|\t     SNAKE GAME               |"<<endl;
        cout<<"\t\t| Play ---------------------------->1 |"<<endl;
        cout<<"\t\t| Change the difficulty level ----->2 |"<<endl;
        cout<<"\t\t| View the ranking ---------------->3 |"<<endl;
        cout<<"\t\t| Close --------------------------->0 |"<<endl;
        cout<<"\t\t _____________________________________"<<endl;
        cout<<"\t\t                  |                   "<<endl;
        cout<<"\t\t                  |                   "<<endl;
        cout<<"\t\t                 "<<(char)92<<" /"<<endl;
        cout<<"\t\t                  ";

        choice=getch();
        x=((int)choice)-48;
    }while(x!=0 && x!=1 && x!=2 && x!=3);
    SetColor(7);
    return x;
}

void Instruction()
{
    SetColor(13);
    cout<<endl<<endl<<endl<<"\t\t\t\t\t INSTRUCTIONS "<<endl<<endl;
    SetColor(14);
    cout<<"\t->  A menu will open in front of you where you can select one of the 4 options given."<<endl;
    cout<<"\t->  You have to use the up, down, right or left arrows to move the snake."<<endl;
    cout<<"\t->  Every time the snake eats the food, its length will be increased by one element along with the score."<<endl;
    cout<<"\t->  The player loses when the snake runs into its own body."<<endl;
}

void DifficultyLevel()  //here the payer decides the difficulty level
{
	char choice;
    SetColor(10);
	do
	{
		system("cls");
		cout<<"\t\tChoose your level: "<<endl;
		cout<<endl<<"\t\t      Hard------------>h"<<endl;
		cout<<"\t\t      Normal---------->n"<<endl;
		cout<<"\t\t      Easy------------>e"<<endl;

		choice=getch();
	}while(choice!='n' && choice!='e' && choice!='h');

    switch(choice)
	{
		case 'h':
			addPoint=15;
			level= 50;
		break;
		case 'n':
			addPoint=5;
			level= 100;
		break;
		case 'e':
			addPoint=2;
			level= 150;
		break;
	}
	SetColor(7);
}

void Enable_Close_Event()  //to close the window
{
    Event e;
    while(window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                window.close();
        }
}

void Direction()  //get the directions commands
{
    if(Keyboard::isKeyPressed(Keyboard::Left) && dir!=2)
        dir=1;
    if(Keyboard::isKeyPressed(Keyboard::Right)&& dir!=1)
        dir=2;
    if(Keyboard::isKeyPressed(Keyboard::Up)&& dir!=0)
        dir=3;
    if(Keyboard::isKeyPressed(Keyboard::Down)&& dir!=3)
        dir=0;
}

void Movements()    //makes it possible for the snake to move
{   //the tail follows the head
    for(int i=nTail;i>0;i--)
    {
        snake[i].x=snake[i-1].x;
        snake[i].y=snake[i-1].y;
    }
    /////////////////////////////
    //  the movement of the head
    /////////////////////////////
    switch(dir)
    {
        case 0: snake[0].y++;
        break;
        case 1: snake[0].x--;
        break;
        case 2: snake[0].x++;
        break;
        case 3: snake[0].y--;
        break;
    }
    ////////////////////////////////////////////////
    // The snake stays on the map it doesn't go out
    ////////////////////////////////////////////////
    if(snake[0].x>N-1)
        snake[0].x=0;
    if(snake[0].y>M-1)
        snake[0].y=0;
    if(snake[0].x<0)
        snake[0].x=N;
    if(snake[0].y<0)
        snake[0].y=M;
}

void Map_Draw() //draws the game environment on the window
{
    window.clear();

    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
        {
            map1.setFillColor(Color::Cyan);
            map1.setPosition(i*size,j*size);                     //drawing the map
            window.draw(map1);
        }

    for(int i=nTail-1;i>-1;i--)
    {
        if(i==0 && Game_Over())
        {
            snake_body.setFillColor(Color::Red);
            snake_body.setPosition(snake[i].x*size,snake[i].y*size);
            window.draw(snake_body);
        }else                                                     // drawing the snake
        {
            snake_body.setFillColor(Color::Green);
            snake_body.setPosition(snake[i].x*size,snake[i].y*size);
            window.draw(snake_body);
        }
    }

    fruit_body.setFillColor(Color::Blue);
    fruit_body.setPosition(fruit.x*size,fruit.y*size);            // drawing the fruit
    window.draw(fruit_body);

    window.display();
}

void Fruit_Control()  //checks the fruit and places it randomly on the map
{
    if((snake[0].x==fruit.x)&& (snake[0].y==fruit.y))
    {
        nTail++;
        score+=addPoint;
        fruit.x=rand() % N;
        fruit.y=rand() % M;
    }
}

bool Game_Over()  // Game over controll
{
    for(int i=1;i<nTail;i++)
	{
		if(snake[0].y==snake[i].y && snake[0].x==snake[i].x)
    		return true;
	}
	return false;
}

void Play()
{
    Loading();
    string a;
    window.create(VideoMode(w,h), "The Best Snake Game");  //it creates a window

    do
    {
        Enable_Close_Event();

        Sleep(level);

        Direction();

        Fruit_Control();

        Movements();

        Map_Draw();

    }while(!Game_Over() && window.isOpen());

    Sleep(2000);
    window.close();

    SetColor(14);
    cout<<"\t\tGame over   Score: "<<score;     //it shows the score on the screen
    cout<<"\n \t\t\tEnter your name :    " ;    //it ask for the player name
    string name;
    SetColor(9);
    cin>>name;
    theRank.SavePlayer(name,score);
}

void Loading()    //Shows on the screen the loading...
{
    system("cls");
	SetColor(10);
	cout<<endl<<endl<<endl<<endl<<endl<<"\t\t\t\t\t Loading..."<<endl;
	SetColor(7);
	SetColor(13);
	cout<<"\t\t   :";

	for(int i=0;i<50;i++)
	{
		Sleep(30);
		cout<<":";
	}
	SetColor(7);
	cout<<endl;
	system("cls");
}

void GoodBye()   //Shows on the screen "GOOD BYE"
{
    SetColor(9);
    cout<<endl;
	cout<<"\t\t    ______       ______      ______     _____      "<<endl;
	cout<<"\t\t   / _____|     /  __  "<<(char)92<<"    /  __  "<<(char)92<<"   |  __ "<<(char)92<<endl;
    cout<<"\t\t  | |  ____    |  /  "<<(char)92<<"  |  |  /  "<<(char)92<<"  |  | |  "<<(char)92<<" |    "<<endl;
    cout<<"\t\t  | | |___ |   | |    | |  | |    | |  | |  | |    "<<endl;
    cout<<"\t\t  | |____/ |   |  "<<(char)92<<"__/  |  |  "<<(char)92<<"__/  |  | |__/ |    "<<endl;
    cout<<"\t\t   "<<(char)92<<"______/     "<<(char)92<<"______/    "<<(char)92<<"______/   |_____/     "<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\t\t\t    _______     __       __    __________            __"<<endl;
    cout<<"\t\t\t   |   __   "<<(char)92<<"   "<<(char)92<<" "<<(char)92<<"     / /   |   _______|          |  |"<<endl;
    cout<<"\t\t\t   |  |__|  |    "<<(char)92<<" "<<(char)92<<"   / /    |  |                  |  |"<<endl;
    cout<<"\t\t\t   |    ____/     "<<(char)92<<" "<<(char)92<<"_/ /     |  |------            |  |"<<endl;
    cout<<"\t\t\t   |   __   "<<(char)92<<"      "<<(char)92<<"   /      |  |------            |  |"<<endl;
    cout<<"\t\t\t   |  |__|  |      |  |       |  |_______           |  |"<<endl;
    cout<<"\t\t\t   |________/      |__|       |__________|          |__|"<<endl;
    cout<<"\t\t\t                                                     __"<<endl;
    cout<<"\t\t\t                                                    |__|"<<endl;
    SetColor(7);
}
