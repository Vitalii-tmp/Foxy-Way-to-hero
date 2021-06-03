#include <string>

#include "Headers.h"

using namespace godot;

PlayerSingleton* PlayerSingleton::_instance = nullptr;

PlayerSingleton::PlayerSingleton() 
{
	_speed = 100;

	_motion = Vector2(0, 0);

	_is_alive = true;

	_coins = 0;
}


PlayerSingleton::~PlayerSingleton()
{

}

void PlayerSingleton::_init(){}

void PlayerSingleton::_process(float delta, KinematicBody2D* Player)
{
	update_motion_from_input();
	Player->move_and_slide(_motion);
}

PlayerSingleton* PlayerSingleton::get_singleton()
{
	if( _instance==nullptr)
	{
		_instance = new PlayerSingleton;
	}
	
	return _instance;	
	
}

void PlayerSingleton::update_motion_from_input()
{
	_motion = Vector2(0, 0);

	if (_is_alive) 
	{
		Input* i = Input::get_singleton();

		if (i->is_action_pressed("ui_up"))
			_motion.y -= _speed;
		if (i->is_action_pressed("ui_down"))
			_motion.y += _speed;
		if (i->is_action_pressed("ui_left"))
			_motion.x -= _speed;
		if (i->is_action_pressed("ui_right"))
			_motion.x += _speed;
			
	}
	
}

void PlayerSingleton::set_coins(int coin)
{
	this->_coins += coin;
	printf(std::to_string(this->_coins).c_str());
}

