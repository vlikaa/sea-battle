
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>

using namespace std;

enum ships
{
	singleDeck = 49,
	twoDeck,
	threeDeck,
	fourDeck
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
	enter = 13,
	arrowUp = 72,
	arrowDown = 80,
	arrowLeft = 75,
	arrowRight = 77
};

int showMenu();

void printGameBox(const short array[][10], const short);

void shipMove(short array[][10], const short, const short, short, short);

void fillField(short array[][10], const short);

void makeShip(short array[][10], const short, short, short);

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
			fillField(array, length);
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

void shipMove(short array[][10], const short length, const short shipSize, short x, short y) {


	bool turned = false;
	while (true) {
		short key;
		system("cls");
		printGameBox(array, length);
		key = _getch();
		if (key == enter)
			return;
		else if (key == 82 || key == 114) {
			if (y + shipSize - 1 < length && x + shipSize - 1 < length) {
				for (short i = 1; i < shipSize; i++) {
					swap(array[x][y + i], array[x + i][y]);
				}
				if (array[x + 1][y] == 1)
					turned = true;
				else if (array[x][y + 1] == 1)
					turned = false;
			}
			continue;
		}
		switch (_getch())
		{
		case arrowUp:
			if (x > 0) {
				for (short i = 0; i < shipSize; i++) {
					if (turned) {
						if (array[x + i][y] == 2) {
							if (array[x + i - 1][y] == 1) {
								array[x + i][y] = 1;
								array[x + i - 1][y] = 2;
							}
							else {
								array[x + i][y] = 1;
								array[x + i - 1][y] = 1;
							}
						}
						else if (array[x + i - 1][y] == 1) {
							array[x + i][y] = 0;
							array[x + i - 1][y] = 2;
						}
						else
							swap(array[x + i][y], array[x + i - 1][y]);
					}
					else {
						if (array[x][y + i] == 2) {
							if (array[x - 1][y + i] == 1) {
								array[x][y + i] = 1;
								array[x - 1][y + i] = 2;
							}
							else {
								array[x][y + i] = 1;
								array[x - 1][y + i] = 1;
							}
						}
						else if (array[x - 1][y + i] == 1) {
							array[x][y + i] = 0;
							array[x - 1][y + i] = 2;
						}
						else
							swap(array[x][y + i], array[x - 1][y + i]);
					}
				}
				x--;
			}
			break;
		case arrowDown:
			if (x + shipSize - 1 < length - 1 && turned) {
				for (short i = 0; i < shipSize; i++) {
					if (array[x + shipSize - (i + 1)][y] == 2) {
						if (array[x + 1 + shipSize - (i + 1)][y] == 1) {
							array[x + shipSize - (i + 1)][y] = 1;
							array[x + 1 + shipSize - (i + 1)][y] = 2;
						}
						else {
							array[x + shipSize - (i + 2)][y] = 1;
							array[x + shipSize - (i + 1)][y] = 1;
						}
					}
					else if (array[x + 1 + shipSize - (i + 1)][y] == 1) {
						array[x + shipSize - (i + 1)][y] = 0;
						array[x + 1 + shipSize - (i + 1)][y] = 2;
					}
					else
						swap(array[x + shipSize - (i + 1)][y], array[x + shipSize - i][y]);
					system("cls");
					printGameBox(array, length);
				}
				x++;
			}
			else if (x < length - 1 && !turned) {
				for (short i = 0; i < shipSize; i++) {
					if (array[x][y + i] == 2) {
						if (array[x + 1][y + i] == 1) {
							array[x][y + i] = 1;
							array[x + 1][y + i] = 2;
						}
						else {
							array[x][y + i] = 1;
							array[x + 1][y + i] = 1;
						}
					}
					else if (array[x + 1][y + i] == 1) {
						array[x][y + i] = 0;
						array[x + 1][y + i] = 2;
					}
					else
						swap(array[x][y + i], array[x + 1][y + i]);
				}
				x++;
			}
			break;
		case arrowLeft:
			if (y > 0) {
				for (short i = 0; i < shipSize; i++) {
					if (turned) {
						if (array[x + i][y] == 2) {
							if (array[x + i][y - 1] == 1) {
								array[x + i][y] = 1;
								array[x + i][y - 1] = 2;
							}
							else {
								array[x + i][y] = 1;
								array[x + i][y - 1] = 1;
							}
						}
						else if (array[x + i][y - 1] == 1) {
							array[x + i][y] = 0;
							array[x + i][y - 1] = 2;
						}
						else
							swap(array[x + i][y], array[x + i][y - 1]);

					}
					else {
						if (array[x][y + i] == 2) {
							array[x][y + i] = 1;
							array[x][y + i - 1] = 1;
						}
						else if (array[x][y + i - 1] == 1) {
							array[x][y + i] = 0;
							array[x][y + i - 1] = 2;
						}
						else
							swap(array[x][y + i], array[x][y + i - 1]);
					}
				}
				y--;
			}
			break;
		case arrowRight:
			if (y + shipSize - 1 < length - 1) {
				for (short i = 0; i < shipSize; i++) {
					if (turned) {
						if (array[x + i][y] == 2) {
							array[x + i][y] = 1;
							array[x + i][y + 1] = 1;
						}
						else if (array[x + i][y + 1] == 1) {
							array[x + i][y] = 0;
							array[x + i][y + 1] = 2;
						}
						else
							swap(array[x + i][y], array[x + i][y + 1]);

					}
					else {
						if (array[x][y + shipSize - (i + 1)] == 2) {
							array[x][y + shipSize - (i + 1)] = 1;
							array[x][y + shipSize - (i + 2)] = 1;
						}
						else if (array[x][y + shipSize - (i + 2)] == 1) {
							array[x][y + shipSize - (i + 1)] = 0;
							array[x][y + shipSize - (i + 2)] = 2;
						}
						else
							swap(array[x][y + shipSize - (i + 1)], array[x][y + shipSize - (i + 2)]);
					}

				}
				y++;
			}
			break;
		default:
			return;
		}
	}
}

void fillField(short array[][10], const short length) {

	short xSpawn{ 4 },
		ySpawn{ 4 };

	short singleCount{ 4 },
		twoCount{ 3 },
		threeCount{ 2 },
		fourCount{ 1 },
		shipsCount = singleCount + twoCount + threeCount + fourCount;


	while (shipsCount > 0)
	{
		printGameBox(array, length);
		cout << "\n    Select ship:"
			<< "\n\t1. single-deck ship"
			<< "\n\t2. two-deck ship"
			<< "\n\t3. three-deck ship"
			<< "\n\t4. four-deck ship";
		switch (_getch())
		{
		case singleDeck:
			if (singleCount > 0) {
				makeShip(array, 1, xSpawn, ySpawn);
				shipMove(array, length, 1, xSpawn, ySpawn);
				singleCount--;
			}
			break;
		case twoDeck:
			if (twoCount > 0) {
				makeShip(array, 2, xSpawn, ySpawn);
				shipMove(array, length, 2, xSpawn, ySpawn);
				twoCount--;
			}
			break;
		case threeDeck:
			if (threeCount > 0) {
				makeShip(array, 3, xSpawn, ySpawn);
				shipMove(array, length, 3, xSpawn, ySpawn);
				threeCount--;
			}
			break;
		case fourDeck:
			if (fourCount > 0) {
				makeShip(array, 4, xSpawn, ySpawn);
				shipMove(array, length, 4, xSpawn, ySpawn);
				fourCount--;
			}
			break;
		default:
			break;
		}
	}
}

void makeShip(short array[][10], const short shipSize, short x, short y) {
	for (int i = 0; i < shipSize; i++) {
		array[x][y] = 1;
		y++;
	}
}

bool checkNear(short array[][10], const short shipSize, short x, short y) {
	for (short i = 0; i < shipSize; i++) {
		if (array[x - 1][y] == 1)
			return true;
		else if (array[x + 1][y] == 1)
			return true;
		else if (array[x][y - 1] == 1)
			return true;
		else if (array[x][y + 1] == 1)
			return true;
	}

}