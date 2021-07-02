#include "LoadSceneButton.h"

void godot::LoadSceneButton::_register_methods()
{
	register_method("_ready", &LoadSceneButton::_ready);
	register_method("_on_button_pressed", &LoadSceneButton::_on_button_pressed);
}

void godot::LoadSceneButton::_init()
{
}

void godot::LoadSceneButton::_ready()
{
	connect("pressed", this, "_on_button_pressed");

	_resource_loader = ResourceLoader::get_singleton();
}

void godot::LoadSceneButton::_on_button_pressed()
{
	if (get_name() == "PlayButton")
	{
		Godot::print("Play button");
		Ref<PackedScene> world = _resource_loader->load("res://World.tscn");

		get_node("/root/MainMenu")->set_name("to_delete");
		get_node("/root/to_delete")->queue_free();

		get_node("/root")->add_child(world->instance());
	}

	if (get_name() == "MainMenuButton")
	{
		Godot::print("Menu button");
		Ref<PackedScene> world = _resource_loader->load("res://MainMenu.tscn");

		get_node("/root/World")->set_name("to_delete");
		get_node("/root/to_delete")->queue_free();
		get_tree()->set_pause(false);

		get_node("/root")->add_child(world->instance());
	}

	if (get_name() == "MainMenuDeathButton")
	{
		Ref<PackedScene> world = _resource_loader->load("res://MainMenu.tscn");

		get_node("/root/DeathMenu")->set_name("to_delete");
		get_node("/root/to_delete")->queue_free();
		get_tree()->set_pause(false);

		get_node("/root")->add_child(world->instance());
	}

	if(get_name() == "BackpackButton")
	{
		if (cast_to<Node2D>(Player::_get_singleton()->get_child(8))->is_visible() == true)
			cast_to<Node2D>(Player::_get_singleton()->get_child(8))->set_visible(false);
		else cast_to<Node2D>(Player::_get_singleton()->get_child(8))->set_visible(true);
	}
}
