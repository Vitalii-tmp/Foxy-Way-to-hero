#include "HungerUI.h"

void godot::HungerUI::_register_methods()
{
	register_method("_ready", &HungerUI::_ready);
	register_method("_process", &HungerUI::_process);
}

void godot::HungerUI::_init()
{
	_instance = this;
}

void godot::HungerUI::_ready()
{
	_first_meat = cast_to<Sprite>(get_node("FullMeat"));
	_second_meat = cast_to<Sprite>(get_node("FullMeat2"));
	_third_meat = cast_to<Sprite>(get_node("FullMeat3"));
	_fourth_meat = cast_to<Sprite>(get_node("FullMeat4"));
	Godot::print(String::num(_full_player_hunger));
}

void godot::HungerUI::_process()
{
	if (_player_hunger >_full_player_hunger*0.75)
	{
		_fourth_meat->set_visible(true);
		_fourth_meat->set_frame(0);
		_first_meat->set_visible(true);
		_second_meat->set_visible(true);
		_third_meat->set_visible(true);
	}

	/*if (_player_hunger > _full_player_hunger*0.75 && _player_hunger <= _full_player_hunger*0.875)
	{
		_fourth_meat->set_visible(true);
		_fourth_meat->set_frame(1);

		_first_meat->set_visible(true);
		_second_meat->set_visible(true);
		_third_meat->set_visible(true);
	}*/

	if (_player_hunger > _full_player_hunger*0.5 && _player_hunger <= _full_player_hunger*0.75)
	{
		_first_meat->set_visible(true);
		_second_meat->set_visible(true);
		_third_meat->set_visible(true);
		_third_meat->set_frame(0);
		_fourth_meat->set_visible(false);
	}

	/*if (_player_hunger > _full_player_hunger*0.50 && _player_hunger <= _full_player_hunger*0.625)
	{
		_first_meat->set_visible(true);
		_second_meat->set_visible(true);
		_third_meat->set_visible(true);
		_third_meat->set_frame(1);
		_fourth_meat->set_visible(false);
	}*/

	if (_player_hunger > _full_player_hunger*0.25 && _player_hunger <= _full_player_hunger*0.5)
	{
		_first_meat->set_visible(true);
		_second_meat->set_visible(true);
		_second_meat->set_frame(0);
		_third_meat->set_visible(false);
		_fourth_meat->set_visible(false);
	}

	/*if (_player_hunger > _full_player_hunger*0.25 && _player_hunger <= _full_player_hunger*0.375)
	{
		_first_meat->set_visible(true);
		_second_meat->set_visible(true);
		_second_meat->set_frame(1);
		_third_meat->set_visible(false);
		_fourth_meat->set_visible(false);
	}*/

	if (_player_hunger > 0 && _player_hunger <= _full_player_hunger*0.25)
	{

		_first_meat->set_visible(true);
		_first_meat->set_frame(0);
		_second_meat->set_visible(false);
		_third_meat->set_visible(false);
		_fourth_meat->set_visible(false);
	}

	/*if (_player_hunger > 0 && _player_hunger <= _full_player_hunger*0.125)
	{

		_first_meat->set_visible(true);
		_first_meat->set_frame(1);
		_second_meat->set_visible(false);
		_third_meat->set_visible(false);
		_fourth_meat->set_visible(false);
	}*/

	if (_player_hunger <= 0)
	{

		_first_meat->set_visible(false);
		_second_meat->set_visible(false);
		_third_meat->set_visible(false);
		_fourth_meat->set_visible(false);
	}
}

godot::HungerUI* godot::HungerUI::_get_singleton()
{
	return _instance;
}

void godot::HungerUI::_set_full_player_hunger(float _full_hunger)
{
	_full_player_hunger = _full_hunger;
}

void godot::HungerUI::_set_player_hunger(float _hunger)
{
	_player_hunger = _hunger;
}

float godot::HungerUI::_get_player_hunger()
{
	return _player_hunger;
}
