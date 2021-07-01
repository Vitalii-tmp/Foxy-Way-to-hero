#include "StoreButton.h"

void godot::StoreButton::_register_methods()
{
	register_method("_ready", &StoreButton::_ready);
	register_method("_on_button_pressed", &StoreButton::_on_button_pressed);
}

void godot::StoreButton::_init()
{
}

void godot::StoreButton::_ready()
{
	connect("pressed", this, "_on_button_pressed");
	_resource_loader = ResourceLoader::get_singleton();
}

void godot::StoreButton::_on_button_pressed()
{
	int coins = Loader::get_singleton()->get_coins();
	if(get_name() == "MeatButton")
	{
		if(coins>=50)
		{
			Loader::get_singleton()->set_coins(-50);

			const auto pos = cast_to<Node2D>(this->get_parent()->get_parent())->get_global_position();

			Ref<PackedScene> prefab = _resource_loader->load("res://Scenes/Items/Meat.tscn");

			auto meat = cast_to<KinematicBody2D>(prefab->instance());
			get_node("/root/World/YSort/")->add_child(meat);

			meat->set_global_position(pos + Vector2(0, 10));
		}
	}
	else if(get_name() == "CheeseButton")
	{
		
	}
	else if(get_name() == "FishButton")
	{
		
	}
	else if(get_name() == "RedFishButton")
	{
		
	}

	UI::get_singleton()->change_coins_information();
	Loader::get_singleton()->save_all_fields();
}
