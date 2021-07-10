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

	_meat_item = cast_to<TextureButton>(get_node("/root/World/UI/Backpack/GridContainer/Meat"));
	_cheese_item = cast_to<TextureButton>(get_node("/root/World/UI/Backpack/GridContainer/Cheese"));

	_label_meat = cast_to<Label>(_meat_item->get_child(0));
	_label_cheese = cast_to<Label>(_cheese_item->get_child(0));

	_resource_loader = ResourceLoader::get_singleton();
}

void godot::UpdateScoreButton::_process(float delta)
{
}

void godot::UpdateScoreButton::_update_speed_player()
{
	const auto pos = cast_to<Node2D>(Player::_get_singleton())->get_global_position();
	Ref<PackedScene> prefab = _resource_loader->load("res://Scenes/Items/SpeedItem.tscn");

	Godot::print("Load item");
	if(Player::_get_singleton()->_backpack->_get_number_meat() >= 3 && Player::_get_singleton()->_backpack->_get_number_cheese() >= 1)
	{
		Godot::print("_update_speed_player");
		/*Player::_get_singleton()->_set_player_speed(200.f);*/

		_label_meat->set_text(String::num(_label_meat->get_text().to_int() - 3));
		_label_cheese->set_text(String::num(_label_cheese->get_text().to_int() - 1));

		Loader::get_singleton()->set_num_meat(_label_meat->get_text().to_int());
		Loader::get_singleton()->set_num_cheese(_label_cheese->get_text().to_int());

		auto item = cast_to<KinematicBody2D>(prefab->instance());


		get_node(NodePath("/root/World/YSort/SpeedItem/"))->add_child(item);

		item->set_global_position(pos + Vector2(0, 20));
	}
}
