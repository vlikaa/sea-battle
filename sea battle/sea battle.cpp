﻿
#include "libraries.h"

using namespace std;





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







