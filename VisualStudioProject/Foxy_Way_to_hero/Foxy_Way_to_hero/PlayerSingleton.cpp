#include "Headers.h"

using namespace godot;

PlayerSingleton* PlayerSingleton::_instance = nullptr;

PlayerSingleton::PlayerSingleton() 
{
	motion = Vector2(0, 0);

	bDead = false;
}


PlayerSingleton::~PlayerSingleton()
{

}

void PlayerSingleton::_init(){}

void PlayerSingleton::_process(float delta, KinematicBody2D* Player)
{
	UpdateMotionFromInput();
	Player->move_and_slide(motion);
}

PlayerSingleton* PlayerSingleton::getSingleton()
{
	if( _instance==nullptr)
	{
		_instance = new PlayerSingleton;
	}
	
	return _instance;	
	
}

void PlayerSingleton::UpdateMotionFromInput()
{
	motion = Vector2(0, 0);

	if (!bDead) 
	{
		Input* i = Input::get_singleton();

		if (i->is_action_pressed("ui_up"))
			motion.y -= speed;
		if (i->is_action_pressed("ui_down"))
			motion.y += speed;
		if (i->is_action_pressed("ui_left"))
			motion.x -= speed;
		if (i->is_action_pressed("ui_right"))
			motion.x += speed;
	}
	
}
