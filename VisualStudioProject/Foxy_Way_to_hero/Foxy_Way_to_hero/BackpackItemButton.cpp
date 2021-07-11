#include "BackpackItemButton.h"

void godot::BackpackItemButton::_register_methods()
{
	register_method("_ready", &BackpackItemButton::_ready);
	register_method("_process", &BackpackItemButton::_process);
	register_method("_on_item_button_pressed", &BackpackItemButton::_on_item_button_pressed);
}

void godot::BackpackItemButton::_init()
{
}

void godot::BackpackItemButton::_ready()
{
	connect("pressed", this, "_on_item_button_pressed");
	_resource_loader = ResourceLoader::get_singleton();
	_label = cast_to<Label>(get_child(0));
}

void godot::BackpackItemButton::_process(float delta)
{
	if (_label->get_text().to_int() > 1)
		_label->set_visible(true);
	else
		_label->set_visible(false);

	if (_label->get_text().to_int() == 0)
		set_visible(false);
	else
		set_visible(true);
}

void godot::BackpackItemButton::_on_item_button_pressed()
{

	Input* _input = Input::get_singleton();

	const auto pos = cast_to<Node2D>(Player::_get_singleton())->get_global_position();
	Ref<PackedScene> prefab = _resource_loader->load("res://Scenes/Items/" + this->get_name() + ".tscn");

	String name;


	auto text = _label->get_text();
	if (_input->is_action_just_released("mouse_right"))
	{
		if (text.to_int() >= 1) {
			_label->set_text(std::to_string((text.to_int() - 1)).c_str());

			if (get_name() == "Meat") {
				Loader::get_singleton()->set_num_meat(_label->get_text().to_int());
				name = "Meat";
			}
			else if (get_name() == "Cheese") {
				Loader::get_singleton()->set_num_cheese(_label->get_text().to_int());
				name = "Cheese";
			}
			else if (get_name() == "Fish") {
				Loader::get_singleton()->set_num_fish(_label->get_text().to_int());
				name = "Fish";
			}
			else if (get_name() == "SpeedItem") {
				Loader::get_singleton()->set_num_speed_item(_label->get_text().to_int());
				name = "SpeedItem";
			}
			else if (get_name() == "BatWing")
			{
				Loader::get_singleton()->set_num_bat_wings(_label->get_text().to_int());
				name = "BatWing";
			}
			else if (get_name() == "BoarFur")
			{
				Loader::get_singleton()->set_num_boar_furs(_label->get_text().to_int());
				name = "BoarFur";
			}
			else if (get_name() == "SnakeSpike")
			{
				Loader::get_singleton()->set_num_snake_fangs(_label->get_text().to_int());
				name = "SnakeSpike";
			}
			else if (get_name() == "DamageItem")
			{
				Loader::get_singleton()->set_num_damage_item(_label->get_text().to_int());
				name = "DamageItem";
			}

			auto item = cast_to<KinematicBody2D>(prefab->instance());

			Godot::print("Name: " + name);

			get_node(NodePath("/root/World/YSort/" + name + "/"))->add_child(item);

			item->set_global_position(pos + Vector2(0, 20));
			item->set_name(get_name());
		}

	}


	if (_input->is_action_just_released("mouse_left"))
	{

		auto _player = Player::_get_singleton();

		float _meat_restore=17.5;
		float _cheese_restore=10.f;
		float _fish_restore=25.f;

		

			if (get_name() == "Meat") {
				Loader::get_singleton()->set_num_meat(_label->get_text().to_int());
				name = "Meat";

				if (_player->_get_hp() + _meat_restore >= 100)
					_player->_set_hp(100);
				else
				_player->_set_hp(_player->_get_hp() + _meat_restore);


				if (_player->_get_hunger() + _meat_restore * 2 >= 360)
					_player->_set_hunger(360);
				else
					_player->_set_hunger(_player->_get_hunger() + _meat_restore*2);
				
				if (text.to_int() >= 1)
					_label->set_text(std::to_string((text.to_int() - 1)).c_str());
			}
			else if (get_name() == "Cheese") {
				Loader::get_singleton()->set_num_cheese(_label->get_text().to_int());
				name = "Cheese";
				
				if (_player->_get_hp() + _cheese_restore >= 100)
					_player->_set_hp(100);
				else
					_player->_set_hp(_player->_get_hp() + _cheese_restore);

				if (_player->_get_hunger() + _cheese_restore * 2 >= 360)
					_player->_set_hunger(360);
				else
					_player->_set_hunger(_player->_get_hunger() + _cheese_restore * 2);

				if (text.to_int() >= 1)
					_label->set_text(std::to_string((text.to_int() - 1)).c_str());
			}
			else if (get_name() == "Fish") {
				Loader::get_singleton()->set_num_fish(_label->get_text().to_int());
				name = "Fish";
				
				if (_player->_get_hp() + _fish_restore >= 100)
					_player->_set_hp(100);
				else
					_player->_set_hp(_player->_get_hp() + _fish_restore);

				if (_player->_get_hunger() + _fish_restore * 2 >= 360)
					_player->_set_hunger(360);
				else
					_player->_set_hunger(_player->_get_hunger() + _fish_restore * 2);

				if (text.to_int() >= 1)
					_label->set_text(std::to_string((text.to_int() - 1)).c_str());
			}
			else if (get_name() == "SpeedItem") {
				Loader::get_singleton()->set_num_speed_item(_label->get_text().to_int());
				name = "SpeedItem";
				_player->_set_player_speed(200);

				if (text.to_int() >= 1)
					_label->set_text(std::to_string((text.to_int() - 1)).c_str());
			}
			
			else if (get_name() == "DamageItem")
			{
				Loader::get_singleton()->set_num_damage_item(_label->get_text().to_int());
				name = "DamageItem";

				if (text.to_int() >= 1)
					_label->set_text(std::to_string((text.to_int() - 1)).c_str());
			}

			
		}

	}

