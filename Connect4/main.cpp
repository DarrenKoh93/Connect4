/*
Connect 4 is a 6 Vertical , 7 Across (Horizontal) board game (6holes by 7 holes)
There are two different type of colors of play piece
Player that matches 4 of the same color in a row (diag/horizontal/vertical) wins the game
Player can only place 1 play piece per turn
Play piece cannot be placed together in the same hole
When each place piece is inserted, they stack ontop of the previous one
*/

/*
What we need
void playgame()	-start game running
	while loop	-continues if game is not won

string InsertPlayPiece(object, placetoInsert)	-used to insert play piece into the board
												-requires player and his choice of insert

bool CheckWin()	-check if there are 4 in a row

bool CheckIfFilled() -checks if hole is filled
void PrintBoard()	-prints the board
					-getArray value and print

*/


#include "main.h"


//#include <cstdlib>
//#include <stdexcept>


enum DisplayIcon{ EMPTY= 0, PLAYER1= 1 , PLAYER2= 2 } ; //if element is 0, the hole is not filled //if element contains 1, it is filled by player 1 //if element contains 2, it is filled by player 2
template <size_t rows, size_t cols> void PrintBoard_template(int(&array)[rows][cols], Player PlayerTurn); //create a function template to accept double array
void PlayGame();

bool CheckWin();
bool CheckIfFilled();
void PrintBoard();
void StartGame(); //Ask for details to create player profile

//create character
Player Player1;
Player Player2;

bool GameWon;
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

void Player::SetMove(int MovePoint, Player PlayerTurn)
{
	
	//All movepoint has to be deducted by 1 to keep account of 0
	MovePoint = MovePoint - 1;	
	int RowToInsert = MAXROW-1; //Player see 1-6, Game see 0-5, convert player input to game input
	bool CheckToken = false; //used to keep the while loop moving
	std::string temp;
	do
	{
		
		if (MovePoint > 5 || MovePoint < 0)//check if integer is between 0-5
		{
			std::cout << "Please choose another column" << std::endl; //inform player for another choice
			RowToInsert = MAXROW - 1;
			std::getline(std::cin, temp);
			MovePoint = stoi(temp);
		}
		std::cout << "you selected: " << MovePoint << std::endl; //To check if int parameter is correct
		std::cout << "Player's token: " << PlayerTurn.OneOrTwo << std::endl; //To check if object parameter is correct
		
		std::cout << "Your move is : " << Board[RowToInsert][MovePoint] << std::endl; //check to see if array is assigned
		if((Board[RowToInsert][MovePoint] == 0))//If hole is filled , go to the next row
		{
			std::cout << "Successful" << std::endl;
			Board[RowToInsert][MovePoint] = PlayerTurn.OneOrTwo;//Set Player's token into the selected column's earliest row		
			CheckToken = true;
			break;
		}
		std::cout << "Something Detected, stacking on" << std::endl;
		RowToInsert--;
		std::cout << "Placing on: " << RowToInsert << " , " << MovePoint << std::endl;
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
		PrintBoard_template(Board, Player2);			///print board
		std::cout << "Press 1-7 to indicated which column to drop your piece" << std::endl;
		std::getline(std::cin, PlayerMove);
		Player2.SetMove(stoi(PlayerMove),Player2);	///Player 2 Move	
	}	
}

template <size_t rows, size_t cols> 
void PrintBoard_template(int(&array)[rows][cols], Player PlayerTurn)
{
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