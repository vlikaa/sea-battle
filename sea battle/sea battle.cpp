
#include "libraries.h"

using namespace std;



int showMenu();

int showMethodChoise(const short array[][10], const short);

void printPlayerField(const short array[][10], const short);

void printGameField(const short array[][10], const short enemy[][10], const short, const short, const short);

void shipMove(short array[][10], const short, const short, short, short);

void playerInstruction(short array[][10], const short, const short automatic = 0);

void makeShip(short array[][10], const short, short, short, const short turned = 0);

short checkNear(short array[][10], const short, const bool, short, short);

void mainInstruction(short array[][10], const short);

short* randomArrange(short array[][10], const short, const short showAnimation = false);

void paint(const int, const int);

void startGame(short array[][10], short enemy[][10], short*, const short);

bool cellInstruction(short field[][10], short, short, short*);

void enemyInstruction(short field[][10], const short, short*);

void printNear(short field[][10], const short, short, short, const bool turned = false);

bool isDestroyed(short field[][10], const short shipSize, short x, short y, const bool turned);

short findSize(short field[][10], const bool, short, short);

void findStartCoordination(const short field[][10], const short, short*, short*);

int main()
{
	srand(time(NULL));
	const short length{ 10 };
	short player[length][length]{};
	short enemy[length][length]{};


	////HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	mainInstruction(player, length);
	/*randomArrange(enemy, length);
	printGameBox(enemy, length);*/


}







