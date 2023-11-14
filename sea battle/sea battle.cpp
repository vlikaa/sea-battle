
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>

using namespace std;

enum Frame : char
{
	boldTopHorizontal = char(223),
	boldBottomHorizontal = char(220),
	boldVertical = char(219)
};

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

int showMethodChoise(const short array[][10], const short);

void printGameBox(const short array[][10], const short);

void shipMove(short array[][10], const short, const short, short, short);

void playerInstruction(short array[][10], const short, const short automatic = 0);

void makeShip(short array[][10], const short, short, short, const short turned = 0);

short checkNear(short array[][10], const short, const bool, short, short);

void mainInstruction(short array[][10], const short);

void randomArrange(short array[][10], const short);

void paint(const int, const int);

int main()
{

	const short length{ 10 };
	short player[length][length]{};
	short enemy[length][length]{};


	////HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	mainInstruction(player, length);
	/*randomArrange(enemy, length);
	printGameBox(enemy, length);*/


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

int showMethodChoise(const short array[][10], const short length) {

	int key = 1;
	while (true)
	{
		system("cls");
		printGameBox(array, length);
		if (key == 1) paint(red, white);
		else paint(black, white);
		cout << "    automatic  \n";

		if (key == 2) paint(red, white);
		else paint(black, white);
		cout << "    manual     \n";

		paint(black, white);

		if (_getch() == 13) {
			return key;
		}

		switch (_getch())
		{
		case arrowUp:
			if (key == 1) key = 2;
			else key--;
			break;
		case arrowDown:
			if (key == 2) key = 1;
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
	cout << boldVertical;
	for (short i = 0; i < length * 4; i++) {
		cout << boldTopHorizontal;
	}
	cout << boldVertical << endl;
	for (int i = 0; i < length; i++) {
		cout << boldVertical;
		for (int j = 0; j < length; j++) {
			if (array[i][j] > 1)
				paint(black, red);
			else
				paint(black, white);

			if (array[i][j] == 0)
				cout << "    ";
			
			else if (array[i][j] == 1)
				cout << " H  ";

			else if (array[i][j] > 1)
				cout << " H  ";
			

		}
		cout << boldVertical << endl << boldVertical;
		if (i == 9) {
			for (short i = 0; i < length * 4; i++) {
				cout << boldBottomHorizontal;
			}
			cout << boldVertical << endl;
		}
		else
			cout << setw(41) << boldVertical << endl;

	}

}

void mainInstruction(short array[][10], const short length) {
	bool flag = true;
	int select;
	while (flag) {
		select = showMenu();
		switch (select - 1)
		{
		case start:
			system("cls");
			select = showMethodChoise(array, length);
			if (select == 1)
				randomArrange(array, length);
			else if (select == 2)
				playerInstruction(array, length);

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
	bool turned = false,
		flag = true;
	short key, checkCollision, temp{};

	while (true) {

		if (array[x][y] == 2 || !flag)
			checkCollision = 0;
		else
			checkCollision = checkNear(array, shipSize, turned, x, y);

		if (checkCollision) {
			for (short i = 0; i < shipSize; i++) {
				if (turned)
					array[x + i][y] = 3;
				else
					array[x][y + i] = 3;
			} 
		}
		else if (!checkCollision && flag){
			for (short i = 0; i < shipSize; i++) {
				if (turned)
					array[x + i][y] = 1;
				else
					array[x][y + i] = 1;
			}
		}
		flag = true;
		system("cls");
		printGameBox(array, length);
		key = _getch();
		if (key == enter)
			return;

		else if (key == 82 || key == 114 || key == 138 || key == 170) {
			if (y + shipSize - 1 < length && x + shipSize - 1 < length && shipSize > 1) {
				for (short i = 1; i < shipSize; i++) {
					if (array[x][y + i] == 3 && !turned) {
						if (array[x + i][y] == 1) {
							array[x][y + i] = 0;
							array[x + i][y] = 2;
							flag = false;
						}
						else {
							swap(array[x][y + i], array[x + i][y]);
						}
					}
					else if (array[x][y + i] == 3 && turned) {
						if (array[x][y + i] == 1) {
							array[x + i][y] = 0;
							array[x][y + i] = 2;
							flag = false;
						}
						else {
							swap(array[x][y + i], array[x + i][y]);
						}
					}
					else if (array[x][y + i] == 2 && !turned) {
						if (array[x + i][y] == 1) {
							array[x][y + i] = 1;
							array[x + i][y] = 2;
						}
						else {
							array[x][y + i] = 1;
							array[x + i][y] = 1;
						}
					}
					else if (array[x + i][y] == 2 && turned) {
						if (array[x][y + i] == 1) {
							array[x + i][y] = 1;
							array[x][y + i] = 2;
						}
						else {
							array[x + i][y] = 1;
							array[x][y + i] = 1;
						}
					}
					else if (array[x][y + i] == 1 && !turned) {
						if (array[x + i][y] == 1) {
							array[x][y + i] = 0;
							array[x + i][y] = 2;
						}
						else {
							swap(array[x][y + i], array[x + i][y]);
						}
					}
					else if (array[x + i][y] == 1 && turned) {
						if (array[x][y + i] == 1) {
							array[x + i][y] = 0;
							array[x][y + i] = 2;
						}
						else {
							swap(array[x][y + i], array[x + i][y]);
						}
					}
					else 
						swap(array[x][y + i], array[x + i][y]);
				}
				if (turned)
					turned = false;
				else
					turned = true;
			}

			continue;
		}

		switch (_getch())
		{
		case arrowUp:
			if (x > 0) {
				for (short i = 0; i < shipSize; i++) {
					if (turned) {
						if (array[x + i][y] == 3) {
							if (array[x + i - 1][y] == 1) {
								array[x + i][y] = 0;
								array[x + i - 1][y] = 2;
								flag = false;
							}
							else 
								swap(array[x + i][y], array[x - 1 + i][y]);
						}
						else if (array[x + i][y] == 2) {
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
						if (array[x + i][y] == 3) {
							if (array[x - 1][y + i] == 1) {
								array[x][y + i] = 0;
								array[x - 1][y + i] = 2;
								flag = false;
							}
							else
								swap(array[x][y + i], array[x - 1][y + i]);
						}
						else if (array[x][y + i] == 2) {
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
					if (array[x + shipSize - (i + 1)][y] == 3) {
						if (array[x + 1 + shipSize - (i + 1)][y] == 1) {
							array[x + shipSize - (i + 1)][y] = 0;
							array[x + 1 + shipSize - (i + 1)][y] = 2;
							flag = false;
						}
						else
							swap(array[x + shipSize - (i + 1)][y], array[x + 1 + shipSize - (i + 1)][y]);
					}
					else if (array[x + shipSize - (i + 1)][y] == 2) {
						if (array[x + 1 + shipSize - (i + 1)][y] == 1) {
							array[x + shipSize - (i + 1)][y] = 1;
							array[x + 1 + shipSize - (i + 1)][y] = 2;
						}
						else {
							array[x + 1 + shipSize - (i + 1)][y] = 1;
							array[x + shipSize - (i + 1)][y] = 1;
						}
					}
					else if (array[x + 1 + shipSize - (i + 1)][y] == 1) {
						array[x + shipSize - (i + 1)][y] = 0;
						array[x + 1 + shipSize - (i + 1)][y] = 2;
					}
					else
						swap(array[x + shipSize - (i + 1)][y], array[x + shipSize - i][y]);
				}
				x++;
			}
			else if (x < length - 1 && !turned) {
				for (short i = 0; i < shipSize; i++) {
					if (array[x][y + i] == 3) {
						if (array[x + 1][y + i] == 1) {
							array[x][y + i] = 0;
							array[x + 1][y + i] = 2;
							flag = false;
						}
						else
							swap(array[x][y + i], array[x + 1][y + i]);
					}
					else if (array[x][y + i] == 2) {
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
						if (array[x + i][y] == 3) {
							if (array[x + i][y - 1] == 1) {
								array[x + i][y] = 0;
								array[x + i][y - 1] = 2;
								flag = false;
							}
							else
								swap(array[x + i][y], array[x + i][y - 1]);
						}
						else if (array[x + i][y] == 2) {
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
						if (array[x][y + i] == 3) {
							if (array[x][y + i - 1] == 1) {
								array[x][y + i] = 0;
								array[x][y + i - 1] = 2;
								flag = false;
							}
							else
								swap(array[x][y + i], array[x][y + i - 1]);
						}
						else if (array[x][y + i] == 2) {
							if (array[x][y + i - 1] == 1) {
								array[x][y + i] = 1;
								array[x][y + i - 1] = 2;
							}
							else {
								array[x][y + i] = 1;
								array[x][y + i - 1] = 1;
							}
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
			if (y + shipSize - 1 < length - 1 && !turned) {
 				for (short i = 0; i < shipSize; i++) {
					if (array[x][y + shipSize - (i + 1)] == 3) {
						if (array[x][y + 1 + shipSize - (i + 1)] == 1) {
							array[x][y + shipSize - (i + 1)] = 0;
							array[x][y + 1 + shipSize - (i + 1)] = 2;
							flag = false;
						}
						else
							swap(array[x][y + shipSize - (i + 1)], array[x][y + 1 + shipSize - (i + 1)]);
					}
					else if (array[x][y + shipSize - (i + 1)] == 2) {
						if (array[x][y + 1 + shipSize - (i + 1)] == 1) {
							array[x][y + shipSize - (i + 1)] = 1;
							array[x][y + 1 + shipSize - (i + 1)] = 2;
						}
						else {
							array[x][y + shipSize - (i + 1)] = 1;
							array[x][y + 1 + shipSize - (i + 1)] = 1;
						}
					}
					else if (array[x][y + 1 + shipSize - (i + 1)] == 1) {
						array[x][y + shipSize - (i + 1)] = 0;
						array[x][y + 1 + shipSize - (i + 1)] = 2;
					}
					else
						swap(array[x][y + shipSize - (i + 1)], array[x][y + 1 + shipSize - (i + 1)]);
				}
				y++;
			}
			else if (y < length - 1 && turned) {
				for (short i = 0; i < shipSize; i++) {
					if (array[x + i][y] == 3) {
						if (array[x + i][y + 1] == 1) {
							array[x + i][y] = 0;
							array[x + i][y + 1] = 2;
							flag = false;
						}
						else
							swap(array[x + i][y], array[x + i][y + 1]);
					}
					else if (array[x + i][y] == 2) {
						if (array[x + i][y + 1] == 1) {
							array[x + i][y] = 1;
							array[x + i][y + 1] = 2;
						}
						else {
							array[x + i][y] = 1;
							array[x + i][y + 1] = 1;
						}
					}
					else if (array[x + i][y + 1] == 1) {
						array[x + i][y] = 0;
						array[x + i][y + 1] = 2;
					}
					else
						swap(array[x + i][y], array[x + i][y + 1]);
				}
				y++;
			}
			break;
		default:
			return;
		}
	}
}

void playerInstruction(short array[][10], const short length, const short automatic) {


	if (automatic)
		randomArrange(array, length);
	else {
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
					//makeShip(array, 1, xSpawn, ySpawn);
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
}

void randomArrange(short array[][10], const short length) {
	
	srand(time(NULL));
	short singleCount{ 4 },
		twoCount{ 3 },
		threeCount{ 2 },
		fourCount{ 1 },
		shipsCount,
		randShip,
		randX,
		randY,
		turned;
	do
	{
		shipsCount = singleCount + twoCount + threeCount + fourCount;
		randShip = rand() % 4 + 49;
		randX = rand() % 10;
		randY = rand() % 10;
		turned = rand() % 2;

		switch (randShip)
		{
		case singleDeck:
			if (array[randX][randY] == 0) {
				if (singleCount > 0) {
					if (checkNear(array, 1, false, randX, randY))
						continue;
					else {
						array[randX][randY] = 1;
						singleCount--;
					}
				}
			}
			break;
		case twoDeck:
			if (twoCount > 0) {
				if (turned) {
					if (array[randX][randY] == 0 && array[randX + 1][randY] == 0) {
						if (randX + 2 > 9)
							continue;
						else if (checkNear(array, 2, true, randX, randY))
							continue;
						else {
							makeShip(array, 2, randX, randY, 1);
							twoCount--;
						}
					}
				}
				else {
					if (array[randX][randY] == 0 && array[randX][randY + 1] == 0) {
						if (randY + 2 > 9)
							continue;
						else if (checkNear(array, 2, false, randX, randY))
							continue;
						else {
							makeShip(array, 2, randX, randY);
							twoCount--;
						}
					}
				}
			}
			break;
		case threeDeck:
			if (threeCount > 0) {
				if (turned) {
					if (array[randX][randY] == 0 && array[randX + 1][randY] == 0 && array[randX + 2][randY] == 0) {
						if (randX + 1 > 9)
							continue;
						else if (checkNear(array, 3, true, randX, randY))
							continue;
						else {
							makeShip(array, 3, randX, randY, 1);
							threeCount--;
						}
					}
				}
				else {
					if (array[randX][randY] == 0 && array[randX][randY + 1] == 0 && array[randX][randY + 2] == 0) {
						if (randY + 2 > 9)
							continue;
						else if (checkNear(array, 3, false, randX, randY))
							continue;
						else {
							makeShip(array, 3, randX, randY);
							threeCount--;
						}
					}
				}

			}
			break;
		case fourDeck:
			if (fourCount > 0) {
				if (turned) {
					if (array[randX][randY] == 0 && array[randX + 1][randY] == 0 && array[randX + 2][randY] == 0 && array[randX + 3][randY] == 0) {
						if (randX + 3 > 9)
							continue;
						else if (checkNear(array, 4, true, randX, randY))
							continue;
						else {
							makeShip(array, 4, randX, randY, 1);
							fourCount--;
						}
					}
				}
				else {
					if (array[randX][randY] == 0 && array[randX][randY + 1] == 0 && array[randX][randY + 2] == 0 && array[randX][randY + 3] == 0) {
						if (randY + 3 > 9)
							continue;
						else if (checkNear(array, 4, false, randX, randY))
							continue;
						else {
							makeShip(array, 4, randX, randY);
							fourCount--;
						}
					}
				}

			}
			break;
		default:
			break;
		}
		

	} while (shipsCount > 0);
	
}

void makeShip(short array[][10], const short shipSize, short x, short y, const short turned) {
	for (int i = 0; i < shipSize; i++) {
		if (turned) {
			array[x][y] = 1;
			x++;
		}

		else {
			array[x][y] = 1;
			y++;
		}
	}
}

short checkNear(short array[][10], const short shipSize, const bool turned, short x, short y) {
	short nearLength{},
		center{};
	if (shipSize == 1) {
		nearLength = 9;
		center = 5;
		for (short i = 0, j = 0, step = 1; step <= nearLength; step++, j++) {
			if (step != center && array[x - 1 + i][y - 1 + j] == 1) {
				return 1;
			}
			if (step % 3 == 0) {
				j = -1;
				i++;
			}
		}
		return 0;
	}
	else if (turned) {
		for (short i = 0; i < shipSize; i++) {
			if (i == 0) {
				nearLength = 6;
				center = 5;
				for (short i = 0, j = 0, step = 1; step <= nearLength; step++) {
					if (step != center && array[x - 1 + i][y - 1 + j] == 1) {
						return 1;
					}
					if (step % 3 == 0) {
						j = -1;
						i++;
					}
					j++;
				}
			}
			else if (i + 1 == shipSize) {
				nearLength = 6;
				center = 2;
				for (short i = 0, j = 0, step = 1; step <= nearLength; step++) {
					if (step != center && array[x + (shipSize - 1) + i][y - 1 + j] == 1) {
						return 1;
					}
					if (step % 3 == 0) {
						j = -1;
						i++;
					}
					j++;
				}
			}
			else {
				if (array[x + i][y - 1] == 1) {
					return 1;
				}
				else if (array[x + i][y + 1] == 1) {
					return 1;
				}
			}
		}
		return 0;
	}

	else {
		for (short i = 0; i < shipSize; i++) {
			if (i == 0) {
				nearLength = 6;
				center = 4;
				for (short i = 0, j = 0, step = 1; step <= nearLength; step++) {
					if (step != center && array[x - 1 + i][y - 1 + j] == 1) {
						return 1;
					}
					if (step % 2 == 0) {
						j = -1;
						i++;
					}
					j++;
				}
			}
			else if (i + 1 == shipSize) {
				nearLength = 6;
				center = 3;
				for (short i = 0, j = 0, step = 1; step <= nearLength; step++) {
					if (step != center && array[x - 1 + i][y + (shipSize - 1) + j] == 1) {
						return 1;
					}
					if (step % 2 == 0) {
						j = -1;
						i++;
					}
					j++;
				}
			}
			else {
				if (array[x - 1][y + i] == 1) {
					return 1;
				}
				else if (array[x + 1][y + i] == 1) {
					return 1;
				}
			}
		}
		return 0;

	}

}