
#include <iostream>

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
		printPlayerField(array, length);
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

void printPlayerField(const short array[][10], const short length) {
	cout << endl;
	cout << "    1 2 3 4 5 6 7 8 9 10\n";

	cout << "   " << leftTopCorner;
	for (short i = 0; i < length * 2; i++)
		cout << horizontal;
	cout << rightTopCorner << endl;

	for (int i = 0; i < length; i++) {
		cout << ' ' << char(65 + i) << ' ' << vertical;
		for (int j = 0; j < length; j++) {
			if (array[i][j] > 1)
				paint(black, red);

			if (array[i][j] == 0)
				cout << "  ";

			else
				cout << boldVertical << boldVertical;
			paint(black, white);
		}
		cout << vertical << endl;
	}

	cout << "   " << leftBottomCorner;
	for (short i = 0; i < length * 2; i++)
		cout << horizontal;
	cout << rightBottomCorner << endl;

}

void printGameField(const short array[][10], const short enemy[][10], const short length, const short x, const short y) {
	system("cls");
	cout << endl;
	cout << "    1 2 3 4 5 6 7 8 9 10\t"
		<< "    1 2 3 4 5 6 7 8 9 10\n";

	cout << "   " << leftTopCorner;
	for (short i = 0; i < length * 2; i++)
		cout << horizontal;
	cout << rightTopCorner << '\t';

	cout << "   " << leftTopCorner;
	for (short i = 0; i < length * 2; i++)
		cout << horizontal;
	cout << rightTopCorner << endl;

	for (int i = 0; i < length; i++) {
		// поле игрока
		cout << ' ' << char(65 + i) << ' ' << vertical;
		for (int j = 0; j < length; j++) {
			if (array[i][j] == 4) {
				paint(black, red);
				cout << "><";
			}
			else if (array[i][j] == 5) {
				paint(black, gray);
				cout << "()";
			}
			else if (array[i][j] == 0)
				cout << "  ";

			else
				cout << boldVertical << boldVertical;
			paint(black, white);
		}
		cout << vertical << '\t';


		// поле противника
		cout << ' ' << char(65 + i) << ' ' << vertical;
		for (int j = 0; j < length; j++) {
			if (i == x && j == y)
				paint(red, white);
			if (enemy[i][j] == 4) {
				if (i == x && j == y)
					paint(red, white);
				else
					paint(black, red);
				cout << "><";
			}
			else if (enemy[i][j] == 5) {
				if (i == x && j == y)
					paint(red, white);
				else
					paint(black, gray);
				cout << "()";
			}
			else
				cout << "  ";
			paint(black, white);
		}
		cout << vertical << endl;
	}

	cout << "   " << leftBottomCorner;
	for (short i = 0; i < length * 2; i++)
		cout << horizontal;
	cout << rightBottomCorner << '\t';

	cout << "   " << leftBottomCorner;
	for (short i = 0; i < length * 2; i++)
		cout << horizontal;
	cout << rightBottomCorner << endl;

}

void mainInstruction(short array[][10], const short length) {
	bool flag = true;
	int select;
	short enemy[10][10]{};
	short* enemyCord;
	short* playerCord;

	while (flag) {
		select = showMenu();
		switch (select - 1)
		{
		case start:
			system("cls");
			select = showMethodChoise(array, length);
			if (select == 1)
				randomArrange(array, length, false);
			else if (select == 2)
				playerInstruction(array, length);
			enemyCord = randomArrange(enemy, length);
			startGame(array, enemy, enemyCord, length);
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
		else if (!checkCollision && flag) {
			for (short i = 0; i < shipSize; i++) {
				if (turned)
					array[x + i][y] = 1;
				else
					array[x][y + i] = 1;
			}
		}
		flag = true;
		system("cls");
		printPlayerField(array, length);
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
			printPlayerField(array, length);
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

short* randomArrange(short array[][10], const short length, const short showAnimation) {
	short coordinates[12]{};
	short singleCount{ 4 },
		twoCount{ 3 },
		threeCount{ 2 },
		fourCount{ 1 },
		shipsCount,
		randShip,
		randX,
		randY,
		turned,
		i{}, j{};
	const char animationFrames[] = { '|', '/', '-', '\\' };
	do
	{
		if (showAnimation) {
			system("cls");
			printPlayerField(array, length);
			cout << "\n\n\tLoading " << animationFrames[i] << endl;
			if (i == 3)
				i = 0;
			i++;
			Sleep(75);
		}
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
							coordinates[j++] = randX;
							coordinates[j++] = randY;
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
							coordinates[j++] = randX;
							coordinates[j++] = randY;
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
							coordinates[j++] = randX;
							coordinates[j++] = randY;
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
							coordinates[j++] = randX;
							coordinates[j++] = randY;
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
							coordinates[j++] = randX;
							coordinates[j++] = randY;
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
							coordinates[j++] = randX;
							coordinates[j++] = randY;
						}
					}
				}

			}
			break;
		default:
			break;
		}



	} while (shipsCount > 0);
	for (short i = 0; i < 12; i++) {
		cout << coordinates[i++] << ' ' << coordinates[i] << endl;
	}
	return coordinates;
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
			if (step != center) {
				if (x - 1 + i < 0) {
					i++;
					j = -1;
					step += 2;
					continue;
				}
				else if (x - 1 + i > 9) {
					break;
				}
				else if (y - 1 + j < 0) {
					continue;
				}
				else if (y - 1 + j > 9) {
					j = -1;
					i++;
					continue;
				}
				if (array[x - 1 + i][y - 1 + j] == 1 || array[x - 1 + i][y - 1 + j] == 4)
					return step;
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

void startGame(short array[][10], short enemy[][10], short* enemyCord, const short length) {
	bool flag = true;
	short x{ 4 }, y{ 4 },
		temp{}, key,
		playerShips{ 10 }, enemyShips{ 10 };

	while (playerShips > 0 && enemyShips > 0) {
		printGameField(array, enemy, length, x, y);
		key = _getch();
		if (key == 13) {
			if (!cellInstruction(enemy, x, y, &enemyShips))
				enemyInstruction(array, 0, &playerShips);
			continue;
		}
		switch (_getch())
		{
		case arrowUp:
			if (x > 0)
				x--;
			break;
		case arrowDown:
			if (x < length - 1)
				x++;
			break;
		case arrowLeft:
			if (y > 0)
				y--;
			break;
		case arrowRight:
			if (y < length - 1)
				y++;
			break;
		default:
			break;
		}

	}
	system("pause");
}

bool cellInstruction(short field[][10], short x, short y, short* shipsCount) {
	short direction,
		shipSize;
	bool turned;
	if (field[x][y] == 1) {
		field[x][y] = 4;
		direction = checkNear(field, 1, false, x, y);

		(direction == 2 || direction == 8) && direction != 0 ? turned = true : turned = false;

		if (direction == 0) {
			printNear(field, 1, x, y);
			*shipsCount -= 1;
		}
		else {
			findStartCoordination(field, direction, &x, &y);
			shipSize = findSize(field, turned, x, y);
			if (isDestroyed(field, shipSize, x, y, turned)) {
				printNear(field, shipSize, x, y, turned);
				*shipsCount -= 1;
			}

		}
		return true;
	}
	else if (field[x][y] != 4) {
		field[x][y] = 5;
		return false;
	}
}

void enemyInstruction(short field[][10], const short difficulty, short* playerShips) {
	short randX, randY,
		tempX, tempY,
		shipSize;
	bool flag = true;
	if (difficulty == soEasy) {
		randX = rand() % 10;
		randY = rand() % 10;
		if (cellInstruction(field, randX, randY, playerShips))
			enemyInstruction(field, 0, playerShips);
	}
	else if (difficulty == easy) {
		if (flag) {
			randX = rand() % 10;
			randY = rand() % 10;
		}
		if (cellInstruction(field, randX, randY, playerShips)) {
			flag = false;
			//shipSize = findSize()
			//if (isDestroyed(field, 1, randX, randY, false))
			tempX = randX;
			tempY = randY;
			enemyInstruction(field, 1, playerShips);
		}
	}

}

void printNear(short field[][10], const short shipSize, short x, short y, const bool turned) {
	short nearLength{},
		center{};
	if (shipSize == 1) {
		nearLength = 9,
			center = 5;
		for (short i = 0, j = 0, step = 1; step <= nearLength; step++, j++) {
			if (step != center) {
				if (x - 1 + i < 0) {
					i++;
					j = -1;
					step += 2;
					continue;
				}
				else if (x - 1 + i > 9) {
					break;
				}
				else if (y - 1 + j < 0) {
					continue;
				}
				else if (y - 1 + j > 9) {
					j = -1;
					i++;
					continue;
				}

				field[x - 1 + i][y - 1 + j] = 5;

			}

			if (step % 3 == 0) {
				j = -1;
				i++;
			}


		}
	}
	else if (turned) {
		for (short i = 0; i < shipSize; i++) {
			if (i == 0) {
				nearLength = 6;
				center = 5;
				for (short i = 0, j = 0, step = 1; step <= nearLength; step++, j++) {
					if (step != center) {
						if (x - 1 + i < 0) {
							i++;
							j = -1;
							step += 2;
							continue;
						}
						else if (x - 1 + i > 9) {
							break;
						}
						else if (y - 1 + j < 0) {
							continue;
						}
						else if (y - 1 + j > 9) {
							j = -1;
							i++;
							continue;
						}

						field[x - 1 + i][y - 1 + j] = 5;
					}
					if (step % 3 == 0) {
						j = -1;
						i++;
					}
				}
			}
			else if (i + 1 == shipSize) {
				nearLength = 6;
				center = 2;
				for (short i = 0, j = 0, step = 1; step <= nearLength; step++, j++) {
					if (step != center) {
						if (x + (shipSize - 1) - 1 + i < 0) {
							i++;
							j = -1;
							step += 2;
							continue;
						}
						else if (x + (shipSize - 1) - 1 + i > 9) {
							break;
						}
						else if (y - 1 + j < 0) {
							continue;
						}
						else if (y - 1 + j > 9) {
							j = -1;
							i++;
							continue;
						}
						field[x + (shipSize - 1) + i][y - 1 + j] = 5;
					}
					if (step % 3 == 0) {
						j = -1;
						i++;
					}
				}
			}
			else {
				if (y - 1 < 0)
					field[x + i][y + 1] = 5;
				else if (y + 1 > 9)
					field[x + i][y - 1] = 5;
				else {
					field[x + i][y + 1] = 5;
					field[x + i][y - 1] = 5;

				}
			}
		}
	}
	else {
		for (short i = 0; i < shipSize; i++) {
			if (i == 0) {
				nearLength = 6;
				center = 4;
				for (short i = 0, j = 0, step = 1; step <= nearLength; step++, j++) {
					if (step != center) {
						if (x - 1 + i < 0) {
							i++;
							j = -1;
							step++;
							continue;
						}
						else if (x - 1 + i > 9)
							break;
						else if (y - 1 + j < 0)
							continue;
						else if (y - 1 + j > 9) {
							j = -1;
							i++;
							continue;
						}
						field[x - 1 + i][y - 1 + j] = 5;
					}
					if (step % 2 == 0) {
						j = -1;
						i++;
					}
				}
			}
			else if (i + 1 == shipSize) {
				nearLength = 6;
				center = 3;
				for (short i = 0, j = 0, step = 1; step <= nearLength; step++, j++) {
					if (step != center) {
						if (x - 1 + i < 0) {
							i++;
							j = -1;
							step++;
							continue;
						}
						else if (x - 1 + i > 9)
							break;
						else if (y + (shipSize - 1) + j < 0)
							continue;
						else if (y + (shipSize - 1) + j > 9) {
							j = -1;
							i++;
							continue;
						}
						field[x - 1 + i][y + (shipSize - 1) + j] = 5;
					}
					if (step % 2 == 0) {
						j = -1;
						i++;
					}
				}
			}
			else {
				if (x - 1 < 0)
					field[x + 1][y + i] = 5;
				else if (x + 1 > 9)
					field[x - 1][y + i] = 5;
				else {
					field[x + 1][y + i] = 5;
					field[x - 1][y + i] = 5;
				}
			}
		}
	}
}

bool isDestroyed(short field[][10], const short shipSize, short x, short y, const bool turned) {

	if (turned) {
		for (short j = 0; j < shipSize; j++) {
			if (field[x + j][y] != 4)
				return false;
		}
		return true;
	}
	else {
		for (short j = 0; j < shipSize; j++) {
			if (field[x][y + j] != 4)
				return false;
		}
		return true;
	}
}

short findSize(short field[][10], const bool turned, short x, short y) {
	short shipSize{ 1 };

	for (short i = 0; i < 4; i++) {
		if (turned) {
			if (field[x + 1][y] == 1 || field[x + 1][y] == 4) {
				shipSize++;
				x++;
			}
			else
				return shipSize;
		}
		else {
			if (field[x][y + 1] == 1 || field[x][y + 1] == 4) {
				shipSize++;
				y++;
			}
			else
				return shipSize;
		}
	}


}

void findStartCoordination(const short field[][10], const short direction, short* x, short* y) {
	if (direction == 2) {
		for (short i = 0; i < 4; i++) {
			if ((field[*x - 1][*y] == 1 || field[*x - 1][*y] == 4) && *x > 0) {
				*x -= 1;
			}
		}
	}
	else if (direction == 4) {
		for (short i = 0; i < 4; i++) {
			if ((field[*x][*y - 1] == 1 || field[*x][*y - 1] == 4) && *y > 0) {
				*y -= 1;
			}
		}
	}
}