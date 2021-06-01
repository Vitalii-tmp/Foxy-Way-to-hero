#include "Headers.h"

using namespace godot;

void Player::_register_methods() 
{
	register_method((char*)"_process", &Player::_process);
	register_method((char*)"_init", &Player::_init);
}

void Player::_init() {}

Player::Player() {}

Player::~Player() {}

void Player::_process(float delta) 
{	
	PlayerSingleton::getSingleton()->_process(delta,this);
}

