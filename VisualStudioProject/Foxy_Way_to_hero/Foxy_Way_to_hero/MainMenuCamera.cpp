#include "MainMenuCamera.h"

void godot::MainMenuCamera::_register_methods()
{
	register_method("_ready", &MainMenuCamera::_ready);
	register_method("_process", &MainMenuCamera::_process);
}

void godot::MainMenuCamera::_init()
{
}

void godot::MainMenuCamera::_ready()
{
}

void godot::MainMenuCamera::_process(float delta)
{
	auto _current_pos = this->get_global_position();

	Vector2 _new_pos = _current_pos + Vector2::RIGHT / 2;;
	
	if (_current_pos.x > 3800)
	{
		_move_left = true;
		_move_right = false;
	}
		
	if (_current_pos.x < 161)
	{
		_move_left = false;
		_move_right = true;
	}

	if(_move_left)
		_new_pos = _current_pos + Vector2::LEFT / 2;
		
	if(_move_right)
		_new_pos = _current_pos + Vector2::RIGHT / 2;

	this->set_global_position(_new_pos);
}

godot::MainMenuCamera::MainMenuCamera()
{
	_move_right = true;
	_move_left = false;
}
