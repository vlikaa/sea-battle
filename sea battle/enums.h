enum difficulty
{
	soEasy,
	easy,
	medium,
	hard

};

enum direction
{
	upCell,
	downCell,
	leftCell,
	rightCell
};

enum Frame : char
{
	leftTopCorner = char(201),
	leftBottomCorner = char(200),
	rightTopCorner = char(187),
	rightBottomCorner = char(188),
	horizontal = char(205),
	vertical = char(186),
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