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

	_wing_item = cast_to<TextureButton>(get_node("/root/World/UI/Backpack/GridContainer/BatWing"));
	_fur_item = cast_to<TextureButton>(get_node("/root/World/UI/Backpack/GridContainer/BoarFur"));
	_snake_item = cast_to<TextureButton>(get_node("/root/World/UI/Backpack/GridContainer/SnakeSpike"));

	_label_wing = cast_to<Label>(_wing_item->get_child(0));
	_label_fur = cast_to<Label>(_fur_item->get_child(0));
	_label_spike = cast_to<Label>(_snake_item->get_child(0));


	_resource_loader = ResourceLoader::get_singleton();
}

void godot::UpdateScoreButton::_process(float delta)
{
}

void godot::UpdateScoreButton::_update_speed_player()
{
	if (get_name() == "SpeedItemButton") {
		const auto pos = cast_to<Node2D>(get_parent()->get_parent()->get_parent()->get_parent())->get_global_position();
		Ref<PackedScene> prefab = _resource_loader->load("res://Scenes/Items/SpeedItem.tscn");

		Godot::print("Load item");
		if (_label_wing->get_text().to_int() >= 3
			&& _label_fur->get_text().to_int() >= 1)
		{
			Godot::print("_update_speed_player");
			/*Player::_get_singleton()->_set_player_speed(200.f);*/

			_label_wing->set_text(String::num(_label_wing->get_text().to_int() - 3));
			_label_fur->set_text(String::num(_label_fur->get_text().to_int() - 1));

			Loader::get_singleton()->set_num_bat_wings(_label_wing->get_text().to_int());
			Loader::get_singleton()->set_num_boar_furs(_label_fur->get_text().to_int());

			auto item = cast_to<KinematicBody2D>(prefab->instance());


			get_node(NodePath("/root/World/YSort/SpeedItem/"))->add_child(item);

			item->set_global_position(pos + Vector2(0, 10));
		}
		else
		{
			cast_to<TextureRect>(get_parent()->get_parent()->get_node("DialogCraftman3"))->set_visible(true);
		}
	}
	else if (get_name() == "InvisibleItemButton") {
		const auto pos = cast_to<Node2D>(get_parent()->get_parent()->get_parent()->get_parent())->get_global_position();
		Ref<PackedScene> prefab = _resource_loader->load("res://Scenes/Items/DamageItem.tscn");

		Godot::print("Load item");
		if (_label_wing->get_text().to_int() >= 2
			&& _label_spike->get_text().to_int() >= 4)
		{
			Godot::print("_update_speed_player");
			/*Player::_get_singleton()->_set_player_speed(200.f);*/

			_label_wing->set_text(String::num(_label_wing->get_text().to_int() - 2));
			_label_spike->set_text(String::num(_label_spike->get_text().to_int() - 4));
			
			Loader::get_singleton()->set_num_bat_wings(_label_wing->get_text().to_int());
			Loader::get_singleton()->set_num_snake_fangs(_label_spike->get_text().to_int());


			auto item = cast_to<KinematicBody2D>(prefab->instance());

			get_node(NodePath("/root/World/YSort/DamageItem/"))->add_child(item);

			item->set_global_position(pos + Vector2(0, 10));

		}
		else
		{
			cast_to<TextureRect>(get_parent()->get_parent()->get_node("DialogCraftman3"))->set_visible(true);
		}
	}
}
