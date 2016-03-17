#pragma once
#include <iostream>
#include <string>

std::string Player1Name, Player2Name;
class main
{
public:
	main();
	~main();
	

};

class Player
{
	public:
		std::string PlayerName;
		int OneOrTwo;
		void Player::CreateChar();
		
		void Player::SetName(std::string);
		std::string Player::GetName();
		void Player::SetMove(int MovePoint, Player PlayerTurn);
		int Player::Get1_2();
		void Player::Set1_2(int);
};
