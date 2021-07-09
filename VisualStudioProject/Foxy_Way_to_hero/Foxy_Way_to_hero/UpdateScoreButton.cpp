#include "UpdateScoreButton.h"

void godot::UpdateScoreButton::_register_methods()
{
	register_method("_ready", &UpdateScoreButton::_ready);
	register_method("_process", &UpdateScoreButton::_process);

	register_method("_update_speed_player", &UpdateScoreButton::_update_speed_player);
}

void godot::UpdateScoreButton::_init()
{
}

void godot::UpdateScoreButton::_ready()
{
	connect("pressed", this, "_update_speed_player");

	_meat_item = cast_to<TextureButton>(get_node("/root")->find_node("/GridContainer/Meat"));
	_cheese_item = cast_to<TextureButton>(get_node("/root")->find_node("/GridContainer/Cheese"));
}

void godot::UpdateScoreButton::_process(float delta)
{
}

void godot::UpdateScoreButton::_update_speed_player()
{
	if(Player::_get_singleton()->_backpack->_get_number_meat() >= 3 && Player::_get_singleton()->_backpack->_get_number_cheese() >= 1)
	{
		Godot::print("_update_speed_player");
		Player::_get_singleton()->_set_player_speed(200.f);
	}
}
