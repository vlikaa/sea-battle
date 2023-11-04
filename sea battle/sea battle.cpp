
#include <iostream>
#include <conio.h>

using namespace std;

enum keys
{
	arrowUp = 72,
	arrowDown = 80,
	arrowLeft = 75,
	arrowRight = 77
};

void printGameBox(const short array[][10], const short);

void mainInstruction(short array[][10], const short);

int main()
{
	const short length{ 10 };
	short gameBox[length][length]{};
	//printGameBox(gameBox, length);
	mainInstruction(gameBox, length);


}

void printGameBox(const short array[][10], const short length) {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			cout << array[i][j] << "   ";
		}
		cout << "\n\n";
	}
}

void mainInstruction(short array[][10], const short length) {
	short x{},
		y{9};
	array[x][y] = 1;
	while (true) {
		system("cls");
		printGameBox(array, length);
		_getch();
		switch (_getch())
		{
		case arrowUp:
			if (x > 0) {
				swap(array[x][y], array[x - 1][y]);
				x--;
			}
			break;
		case arrowDown:
			if (x < length - 1) {
				swap(array[x][y], array[x + 1][y]);
				x++;
			}
			break;
		case arrowLeft:
			if (y > 0) {
				swap(array[x][y], array[x][y - 1]);
				y--;
			}
			break;
		case arrowRight:
			if (y < length - 1) {
				swap(array[x][y], array[x][y + 1]);
				y++;
			}
			break;
		default:
			break;
		}
	}
}