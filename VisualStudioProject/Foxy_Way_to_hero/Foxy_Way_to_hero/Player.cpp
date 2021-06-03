#include <string>

#include "Headers.h"

using namespace godot;

void Player::_register_methods() 
{
	register_method((char*)"_process", &Player::_process);
	register_method((char*)"_init", &Player::_init);
	//register_method("set_coins", &Player::set_coins);
	
	//register_property("coins", &Player::coins, 0);
}

void Player::_init() {}

Player::Player() {}

Player::~Player() {}

void Player::_process(float delta) 
{	
	PlayerSingleton::get_singleton()->_process(delta,this);
}

void Player::_ready()
{
	//PlayerSingleton::get_singleton()->set_coins(coins);
}

//void Player::set_coins(int coins)
//{
//	this->coins += coins;
//	printf(std::to_string(this->coins).c_str());
//}
