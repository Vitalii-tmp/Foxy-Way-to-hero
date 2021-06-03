#include "Headers.h"

using namespace godot;

void Player::_register_methods() 
{
	register_method((char*)"_process", &Player::_process);

	register_property("coins", &Player::coins, 0);
	register_method((char*)"_init", &Player::_init);
}

void Player::_init() {}

Player::Player() {}

Player::~Player() {}

void Player::_process(float delta) 
{	
	PlayerSingleton::get_singleton()->_process(delta,this);
}

