/*
Author: Darren Koh
Connect 4 is a 6 Vertical , 7 Across (Horizontal) board game (6holes by 7 holes)
There are two different type of colors of play piece
Player that matches 4 of the same color in a row (diag/horizontal/vertical) wins the game
Player can only place 1 play piece per turn
Play piece cannot be placed together in the same hole
When each place piece is inserted, they stack ontop of the previous one
*/
#include "main.h"

enum DisplayIcon{ EMPTY= 0, PLAYER1= 1 , PLAYER2= 2 } ; //if element is 0, the hole is not filled //if element contains 1, it is filled by player 1 //if element contains 2, it is filled by player 2
template <size_t rows, size_t cols> void PrintBoard_template(int(&array)[rows][cols], Player PlayerTurn); //create a function template to accept double array
void PlayGame();
bool CheckGameWon(int,int,Player);
void StartGame(); //Ask for details to create player profile

//create character
Player Player1;
Player Player2;

bool GameWon = false;
const int MAXROW = 6; //6 rows
const int MAXCOLUMN = 7; //7 columns

int Board[MAXROW][MAXCOLUMN]	//initialise board (6 by 7)
{ 
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
};									   			   

main::main()
{

}

main::~main()
{
}

int main()
{
	PrintBoard_template(Board, Player1);
	StartGame();
	PlayGame();
	std::cout << "Press enter to exit" << std::endl;
	std::cin.get();
	return 0;
}

void Player::SetName(std::string InputName){PlayerName = InputName;}
std::string Player::GetName() { return PlayerName; }
int Player::Get1_2() { return OneOrTwo; }
void Player::Set1_2(int Input) { OneOrTwo = Input; }

bool CheckGameWon(int X, int Y,Player PlayerTurn)
{
	///to win: 4 same tokens connected
	std::cout << "[" << PlayerTurn.GetName() << "] turn" << std::endl;

	///Player's token
	int PlayerToken = Board[X][Y];

	int CheckVertical;
	int CheckHorizontal;
	int ConnectingVert = 1;
	int ConnectingHort = 1;
	int ConnectingForwardSlash = 1;
	int ConnectingBackSlash = 1;

	///check for horizontal
	for (CheckVertical = X + 1; Board[CheckVertical][Y] == PlayerToken && CheckVertical <= 5; CheckVertical++, ConnectingVert++);//check from current position to up
	for (CheckVertical = X - 1; Board[CheckVertical][Y] == PlayerToken && CheckVertical >= 0; CheckVertical--, ConnectingVert++);//Check from current position to down
	if (ConnectingVert == 4){return true;}

	///check for vertical
	for (CheckHorizontal = Y + 1; Board[X][CheckHorizontal] == PlayerToken && CheckHorizontal <= 6; CheckHorizontal++, ConnectingHort++);//check from current position to right
	for (CheckHorizontal = Y - 1; Board[X][CheckHorizontal] == PlayerToken && CheckHorizontal >= 0; CheckHorizontal--, ConnectingHort++);//Check from current position to left
	if (ConnectingHort == 4){return true;}
	
	///check for diagonal
	///there are two diagonals to look out for: ['/': bottom left to top right , top right to bottom left], ['\' : top left to bottom right, bttom right to top left]

	///to get /, horizontal +1 and vertical + 1 , horizontal -1 and vertical -1
	for (CheckVertical = X - 1, CheckHorizontal = Y + 1; Board[CheckVertical][CheckHorizontal] == PlayerToken && CheckVertical <= 5 && CheckHorizontal <= 6; ConnectingForwardSlash++, CheckVertical++, CheckHorizontal++);//up and right
	for (CheckVertical = X + 1, CheckHorizontal = Y - 1; Board[CheckVertical][CheckHorizontal] == PlayerToken && CheckVertical >= 0 && CheckHorizontal >= 0; ConnectingForwardSlash++, CheckVertical--, CheckHorizontal--);//down and left
	if (ConnectingForwardSlash == 4){return true;}
																																																						   
	///to get \, horizontal +1 and vertical -1 , horizontal -1 and vertical +1																																														
	for (CheckVertical = X - 1, CheckHorizontal = Y + 1; Board[CheckVertical][CheckHorizontal] == PlayerToken && CheckVertical >= 0 && CheckHorizontal >= 6; ConnectingBackSlash++, CheckVertical--, CheckHorizontal++);//down and right
	for (CheckVertical = X + 1, CheckHorizontal = Y - 1; Board[CheckVertical][CheckHorizontal] == PlayerToken && CheckVertical <= 5 && CheckHorizontal >= 0; ConnectingBackSlash++, CheckVertical++, CheckHorizontal--);//up and left
	if (ConnectingBackSlash == 4){return true;}

	return false;
}

void Player::SetMove(int MovePoint, Player PlayerTurn)
{	
	//All movepoint has to be deducted by 1 to keep account of 0
	MovePoint = MovePoint - 1;	
	int RowToInsert = MAXROW-1; //Player see 1-6, Game see 0-5, convert player input to game input
	bool CheckToken = false; //used to keep the while loop moving
	std::string temp;
	do
	{		
		if (MovePoint > 6 || MovePoint < 0)//check if integer is between 0-5
		{
			std::cout << "Please choose another column" << std::endl; //inform player for another choice
			RowToInsert = MAXROW - 1;
			std::getline(std::cin, temp);
			MovePoint = stoi(temp);
		}
		if((Board[RowToInsert][MovePoint] == 0))//If hole is filled , go to the next row
		{
			Board[RowToInsert][MovePoint] = PlayerTurn.OneOrTwo;//Set Player's token into the selected column's earliest row		
			CheckToken = true;
			if (CheckGameWon(RowToInsert, MovePoint, PlayerTurn) == true)
			{
				GameWon = true;
				PrintBoard_template(Board, PlayerTurn);
				std::cout << "congratulations on winning the game, " << PlayerTurn.GetName() << std::endl;
			}
			break;
		}
		RowToInsert--;
		//If all holes in the column is filled,
		if (RowToInsert == -1)
		{
			std::cout << "Please choose another column" << std::endl; //inform player for another choice
			RowToInsert = MAXROW - 1;
			std::getline(std::cin, temp);
			MovePoint = stoi(temp);
		}
	} while (CheckToken==false);
}

void StartGame()
{
	std::cout << "Welcome to connect 4" << std::endl << std::endl;
	std::cout << "Please enter player 1 name: " << std::endl;
	std::getline(std::cin, Player1Name);
	std::cout << "Please enter player 2 name: " << std::endl;
	std::getline(std::cin, Player2Name);

	//assign names
	Player1.SetName(Player1Name);//Player1.SetName
	Player2.SetName(Player2Name);//Player2.SetName
	//assign tokens
	Player1.Set1_2(1);//Assign Player 1's token = 1
	Player2.Set1_2(2);//Assign Player 2's token = 2

	std::cout << "Player1 name :" << Player1.GetName() <<" .Tokens: [X]"<<std::endl;
	std::cout << "Player2 name :" << Player2.GetName() <<" .Tokens: [O]" << std::endl;
}

void PlayGame()
{
	while (GameWon==false) ///while game is not won, repeat
	{
		std::string PlayerMove;

		PrintBoard_template(Board,Player1); ///print board
		std::cout << "Press 1-7 to indicated which column to drop your piece" << std::endl;
		std::getline(std::cin, PlayerMove);
		Player1.SetMove(stoi(PlayerMove),Player1);	///Player 1 Move (insert play piece)
		if (GameWon == true) {break; }
		PrintBoard_template(Board, Player2);			///print board
		std::cout << "Press 1-7 to indicated which column to drop your piece" << std::endl;
		std::getline(std::cin, PlayerMove);
		Player2.SetMove(stoi(PlayerMove),Player2);	///Player 2 Move	
	}	
	std::cout << "Game ended" << std::endl;
}

template <size_t rows, size_t cols> 
void PrintBoard_template(int(&array)[rows][cols], Player PlayerTurn)
{
	std::cout << std::endl << std::endl << std::endl << std::endl;
	std::cout << "[" << PlayerTurn.GetName() <<"] turn" << std::endl;

	std::cout << "    ";
	for (size_t i = 0; i < cols; ++i) //print column number
	{
		std::cout << i+1  << "  ";
	}
	std::cout << std::endl;
	for (size_t i = 0; i < rows; ++i) //check row
	{
		std::cout << i+1 << "  ";	//print row number
		for (size_t j = 0; j < cols; ++j) //check column
			switch (Board[i][j])
			{
				case DisplayIcon::EMPTY:{	std::cout << "[ ]";	break;	}
				case DisplayIcon::PLAYER1:{	std::cout << "[X]";	break;	}
				case DisplayIcon::PLAYER2:{	std::cout << "[O]";	break;	}
				default:					std::cout << "Error";
			}
		std::cout << std::endl;
	}
}