
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>

using namespace std;

enum ships
{
	singleTier = 49,
	twoTier,
	threeTier,
	fourTier
};

enum function
{
	start,
	load,
	exitGame
};

enum colors
{
	black,
	blue,
	green,
	aqua,
	red,
	purple,
	yellow,
	white,
	gray,
	lightBlue,
	lightGreen,
	lightAqua,
	lightRed,
	lightPurple,
	lightYellow,
	brightWhite
};

enum keys
{
	arrowUp = 72,
	arrowDown = 80,
	arrowLeft = 75,
	arrowRight = 77
};

int showMenu();

void printGameBox(const short array[][10], const short);

void gameInstruction();

void mainInstruction(short array[][10], const short);

void paint(const int, const int);

int main()
{

	const short length{ 10 };
	short gameBox[length][length]{};


	////HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	mainInstruction(gameBox, length);


}

int showMenu() {
	int key = 1;

	while (true)
	{
		system("cls");
		if (key == 1) paint(red, white);
		else paint(black, white);
		cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t    start game  \n";

		if (key == 2) paint(red, white);
		else paint(black, white);
		cout << "\t\t\t\t\t\t    load game   \n";

		if (key == 3) paint(red, white);
		else paint(black, white);
		cout << "\t\t\t\t\t\t    exit        \n";
		paint(black, white);

		if (_getch() == 13) {
			return key;
		}

		switch (_getch())
		{
		case arrowUp:
			if (key == 1) key = 3;
			else key--;
			break;
		case arrowDown:
			if (key == 3) key = 1;
			else key++;
			break;
		default:
			break;
		}


	}

}

void paint(const int bgcolor, const int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, (((bgcolor & 0x0f) << 4) + (color & 0x0f)));
}

void printGameBox(const short array[][10], const short length) {
	cout << endl;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			cout << setw(4) << array[i][j];
		}
		cout << "\n\n";
	}
}

void mainInstruction(short array[][10], const short length) {
	bool flag = true;
	while (flag) {
		int select = showMenu();
		switch (select - 1)
		{
		case start:
			gameInstruction();
			break;
		case load:
			break;
		case exitGame:
			break;
		default:
			break;
		}
	}
}

void gameInstruction() {

	const int length{ 10 };
	short newArray[length][length]{};

	short x{ 3 },
		y{ 9 };
	newArray[x][y] = 1;


	while (true) {
		system("cls");
		printGameBox(newArray, length);
		_getch();
		switch (_getch())
		{
		case arrowUp:
			if (x > 0) {
				swap(newArray[x][y], newArray[x - 1][y]);
				x--;
			}
			break;
		case arrowDown:
			if (x < length - 1) {
				swap(newArray[x][y], newArray[x + 1][y]);
				x++;
			}
			break;
		case arrowLeft:
			if (y > 0) {
				swap(newArray[x][y], newArray[x][y - 1]);
				y--;
			}
			break;
		case arrowRight:
			if (y < length - 1) {
				swap(newArray[x][y], newArray[x][y + 1]);
				y++;
			}
			break;
		default:
			return;
		}
	}
}

void fillField() {
	short singleCount{ 4 },
		twoCount{ 3 },
		threeCount{ 2 },
		fourCount{ 1 },
		shipsCount = singleCount + twoCount + threeCount + fourCount;
	while (shipsCount > 0)
	{
		switch (_getch())
		{
		case singleTier:
			if (singleCount > 0) {

				singleCount--;
			}
			break;
		case twoTier:
			break;
		case threeTier:
			break;
		case fourTier:
			break;
		default:
			break;
		}
	}
}