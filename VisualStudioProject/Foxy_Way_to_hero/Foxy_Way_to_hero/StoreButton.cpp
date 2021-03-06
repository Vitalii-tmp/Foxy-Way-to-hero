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

	Godot::print(get_parent()->get_name());

	const auto pos = cast_to<Node2D>(get_parent()->get_parent()->get_parent()->get_parent())->get_global_position();

	Ref<PackedScene> prefab;

	String name;

	

	if(get_name() == "MeatButton")
	{
		if (coins >= 50)
		{
			Loader::get_singleton()->set_coins(-50);
			prefab = _resource_loader->load("res://Scenes/Items/Meat.tscn");
			name = "Meat";
		}
		else {
			cast_to<TextureRect>(get_parent()->get_parent()->get_node("DialogCountryMan3"))->set_visible(true);
			return;
		}
	}
	else if(get_name() == "CheeseButton")
	{
		if (coins >= 40)
		{
			Loader::get_singleton()->set_coins(-40);
			prefab = _resource_loader->load("res://Scenes/Items/Cheese.tscn");
			name = "Cheese";
		}
		else{
			cast_to<TextureRect>(get_parent()->get_parent()->get_node("DialogCountryMan3"))->set_visible(true);
			return;
		}
	}
	else if(get_name() == "FishButton")
	{
		if (coins >= 60)
		{
			Loader::get_singleton()->set_coins(-60);
			prefab = _resource_loader->load("res://Scenes/Items/Fish.tscn");
			name = "Fish";
		}
		else
		{
			cast_to<TextureRect>(get_parent()->get_parent()->get_node("DialogCountryMan3"))->set_visible(true);
			return;
		}
	}
	/*else if(get_name() == "RedFishButton")
	{
		if (coins >= 100)
		{
			Loader::get_singleton()->set_coins(-100);
			prefab = _resource_loader->load("res://Scenes/Items/RedFish.tscn");
			name = "RedFish";
		}
		else
			return;
	}*/

	auto item = cast_to<KinematicBody2D>(prefab->instance());

	get_node(NodePath("/root/World/YSort/"+name+"/"))->add_child(item);

	item->set_global_position(pos + Vector2(0, 10));
	item->set_name(name);
	
	UI::get_singleton()->change_coins_information();
	Loader::get_singleton()->save_all_fields();
}
