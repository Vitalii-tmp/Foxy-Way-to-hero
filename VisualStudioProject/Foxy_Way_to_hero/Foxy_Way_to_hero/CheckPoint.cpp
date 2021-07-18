#include "CheckPoint.h"

void godot::CheckPoint::_register_methods()
{
	register_method("_ready", &CheckPoint::_ready);
	register_method("_process", &CheckPoint::_process);
	register_method("_on_area_body_entered", &CheckPoint::_on_area_body_entered);
	register_method("_on_check_point_animation_finished", &CheckPoint::_on_check_point_animation_finished);
	register_method("_on_check_point_area_body_exited", &CheckPoint::_on_check_point_area_body_exited);
	
}

void godot::CheckPoint::_init()
{
}

void godot::CheckPoint::_process(float delta)
{
}

void godot::CheckPoint::_ready()
{
	_check_point_animated_sprite = cast_to<AnimatedSprite>(this->get_parent());
}

void godot::CheckPoint::_on_area_body_entered(Node* _other_body)
{
	if (_other_body->get_name() == "Player")
	{
		Godot::print("SaveData");
		_check_point_animated_sprite->play("Saving");
	}
		
}

void godot::CheckPoint::_on_check_point_area_body_exited(Node* _other_body)
{
	_check_point_animated_sprite->set_frame(0);
	_check_point_animated_sprite->stop();
}

void godot::CheckPoint::_on_check_point_animation_finished()
{
	//save data
	Loader::get_singleton()->set_start_position(this->get_global_position()+Vector2(0,30));
	Loader::get_singleton()->save_all_fields();

	SoundEffectsManager::_get_singleton()->_play_sound_effect("CheckPointSE", this);
}
