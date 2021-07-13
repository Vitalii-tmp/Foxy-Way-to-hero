#include "HealthUI.h"

void godot::HealthUI::_register_methods()
{
	register_method("_ready", &HealthUI::_ready);
	register_method("_delete_next_full_heart", &HealthUI::_delete_next_full_heart);
	register_method("_turn_on_hit_anim", &HealthUI::_turn_on_hit_anim);
	register_method("_process", &HealthUI::_process);
	
}

void godot::HealthUI::_init()
{
	_instance = this;
}

void godot::HealthUI::_ready()
{
	_first_heart = cast_to<Sprite>(get_node("FullHeart"));
	_second_heart = cast_to<Sprite>(get_node("FullHeart2"));
	_third_heart = cast_to<Sprite>(get_node("FullHeart3"));
	_fourth_heart = cast_to<Sprite>(get_node("FullHeart4"));

}

void godot::HealthUI::_process(float delta)
{
	
	if (_player_health > 87.5)
	{
		_fourth_heart->set_visible(true);
		_first_heart->set_visible(true);
		_second_heart->set_visible(true);
		_third_heart->set_visible(true);
		

		_first_heart->set_frame(0);
		_second_heart->set_frame(0);
		_third_heart->set_frame(0);
		_fourth_heart->set_frame(0);
	}

	if (_player_health > 75 && _player_health <= 87.5)
	{
		_fourth_heart->set_visible(true);
		

		_first_heart->set_visible(true);
		_second_heart->set_visible(true);
		_third_heart->set_visible(true);

		_first_heart->set_frame(0);
		_second_heart->set_frame(0);
		_third_heart->set_frame(0);
		_fourth_heart->set_frame(1);
	}

	if (_player_health > 62.5 && _player_health <= 75)
	{
		_first_heart->set_visible(true);
		_second_heart->set_visible(true);
		_third_heart->set_visible(true);
		_third_heart->set_frame(0);
		_fourth_heart->set_visible(false);

		_first_heart->set_frame(0);
		_second_heart->set_frame(0);
		_third_heart->set_frame(0);
		_fourth_heart->set_frame(1);
	}

	if (_player_health > 50 && _player_health <= 62.5)
	{
		_first_heart->set_visible(true);
		_second_heart->set_visible(true);
		_third_heart->set_visible(true);
		_third_heart->set_frame(1);
		_fourth_heart->set_visible(false);

		_first_heart->set_frame(0);
		_second_heart->set_frame(0);
		_third_heart->set_frame(1);
		_fourth_heart->set_frame(1);
	}

	if (_player_health > 37.5 && _player_health <= 50)
	{
		_first_heart->set_visible(true);
		_second_heart->set_visible(true);
		_third_heart->set_visible(false);
		_fourth_heart->set_visible(false);

		_first_heart->set_frame(0);
		_second_heart->set_frame(0);
		_third_heart->set_frame(1);
		_fourth_heart->set_frame(1);
	}

	if (_player_health > 25 && _player_health <= 37.5)
	{
		_first_heart->set_visible(true);
		_second_heart->set_visible(true);
		_third_heart->set_visible(false);
		_fourth_heart->set_visible(false);

		_first_heart->set_frame(0);
		_second_heart->set_frame(1);
		_third_heart->set_frame(1);
		_fourth_heart->set_frame(1);
	}

	if (_player_health > 12.5 && _player_health <= 25)
	{
		_first_heart->set_visible(true);
		_second_heart->set_visible(false);
		_third_heart->set_visible(false);
		_fourth_heart->set_visible(false);

		_first_heart->set_frame(0);
		_second_heart->set_frame(1);
		_third_heart->set_frame(1);
		_fourth_heart->set_frame(1);
	}

	if (_player_health > 0 && _player_health <= 12.5)
	{
		_first_heart->set_visible(true);
		_second_heart->set_visible(false);
		_third_heart->set_visible(false);
		_fourth_heart->set_visible(false);

		_first_heart->set_frame(1);
		_second_heart->set_frame(1);
		_third_heart->set_frame(1);
		_fourth_heart->set_frame(1);
	}

	if(_player_health<=0)
	{
		_first_heart->set_visible(false);
		_second_heart->set_visible(false);
		_third_heart->set_visible(false);
		_fourth_heart->set_visible(false);
	}

}

godot::HealthUI* godot::HealthUI::_get_singleton()
{
	return _instance;
}

void godot::HealthUI::_turn_on_hit_anim()
{
	cast_to<AnimatedSprite>(this->get_child(0)->get_child(0))->set_visible(true);
	cast_to<AnimatedSprite>(this->get_child(0)->get_child(0))->play("hitAnim");
}

void godot::HealthUI::_delete_next_full_heart()
{
	this->get_child(0)->queue_free();
}

void godot::HealthUI::_set_health(float _new_value)
{
	_player_health = _new_value;
}

float godot::HealthUI::_get_health()
{
	return _player_health;
}
