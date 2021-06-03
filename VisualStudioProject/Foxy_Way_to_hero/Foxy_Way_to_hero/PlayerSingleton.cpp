#include "Headers.h"

using namespace godot;

PlayerSingleton* PlayerSingleton::_instance = nullptr;

PlayerSingleton::PlayerSingleton() 
{
	_speed = 100;

	_motion = Vector2(0, 0);
	_inpun_vector=Vector2(0,0);

	_is_alive = true;
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

void godot::PlayerSingleton::_ready()
{

}

PlayerSingleton* PlayerSingleton::get_singleton()
{
	if( _instance==nullptr)
	{
		_instance = new PlayerSingleton;
	}
	
	return _instance;	
	
}

Vector2 PlayerSingleton::_get_motion()
{
	return _motion;
}

Vector2 PlayerSingleton::_get_input_vector()
{
	return _inpun_vector;
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

			
		_motion = _motion.normalized()*_speed;
		
		if(_motion!=Vector2(0,0))
			_inpun_vector = _motion;

	}
	
}
