
#include <iostream>

using namespace std;

void printGameBox(const short array[][10], const short);

int main()
{
	const short length{ 10 };
	short gameBox[length][length]{};
	printGameBox(gameBox, length);

}

void printGameBox(const short array[][10], const short length) {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			cout << array[i][j] << "   ";
		}
		cout << "\n\n";
	}
}