#include "LoadSceneButton.h"

void godot::LoadSceneButton::_register_methods()
{
	register_method("_ready", &LoadSceneButton::_ready);
	register_method("_on_button_pressed", &LoadSceneButton::_on_button_pressed);
	register_method("_load_world", &LoadSceneButton::_load_world);
	register_method("_load_main_menu", &LoadSceneButton::_load_main_menu);
	register_method("_load_new_game", &LoadSceneButton::_load_new_game);
}

void godot::LoadSceneButton::_init()
{
}

void godot::LoadSceneButton::_ready()
{
	connect("pressed", this, "_on_button_pressed");

	_resource_loader = ResourceLoader::get_singleton();

	_timer = Timer::_new();
	this->add_child(_timer);
}

void godot::LoadSceneButton::_on_button_pressed()
{
	if (get_name() == "PlayButton")
	{
		Godot::print("Play button");

		Ref<PackedScene> fade_out = _resource_loader->load("res://Scenes/Effects/FadeOut.tscn");
		
		get_node("/root/MainMenu/UI")->add_child(fade_out->instance());

		if (!_timer->is_connected("timeout", this, "_load_world"))
		{
			_timer->connect("timeout", this, "_load_world");
			_timer->start(1);
		}
	}

	if (get_name() == "MainMenuButton")
	{
		
		
		Ref<PackedScene> fade_out = _resource_loader->load("res://Scenes/Effects/FadeOut.tscn");

		this->add_child(fade_out->instance());

		if (!_timer->is_connected("timeout", this, "_load_main_menu"))
		{
			_timer->connect("timeout", this, "_load_main_menu");
			_timer->start(1);
		}
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
		if (cast_to<Node2D>(get_node("/root/World/UI/Backpack"))->is_visible())
			cast_to<Node2D>(get_node("/root/World/UI/Backpack"))->set_visible(false);
		else cast_to<Node2D>(get_node("/root/World/UI/Backpack"))->set_visible(true);
	}

	if(get_name() == "NewGameButton")
	{
		Ref<PackedScene> fade_out = _resource_loader->load("res://Scenes/Effects/FadeOut.tscn");

		get_node("/root/MainMenu/UI")->add_child(fade_out->instance());

		if (!_timer->is_connected("timeout", this, "_load_new_game"))
		{
			_timer->connect("timeout", this, "_load_new_game");
			_timer->start(1);
		}
	}
}

void godot::LoadSceneButton::_load_world()
{
	Ref<PackedScene> world = _resource_loader->load("res://World.tscn");
	get_node("/root/MainMenu")->set_name("to_delete");
	get_node("/root/to_delete")->queue_free();

	get_node("/root")->add_child(world->instance());

	Godot::print("Main menu");

	if (_timer->is_connected("timeout", this, "_load_world"))
	{
		_timer->disconnect("timeout", this, "_load_world");
	}

	if (_timer->is_connected("timeout", this, "_load_new_game"))
	{
		_timer->disconnect("timeout", this, "_load_new_game");
	}
}

void godot::LoadSceneButton::_load_main_menu()
{
	Godot::print("Menu button");
	Ref<PackedScene> _main_menu = _resource_loader->load("res://MainMenu.tscn");

	get_node("/root/World")->set_name("to_delete");
	get_node("/root/to_delete")->queue_free();
	get_tree()->set_pause(false);

	get_node("/root")->add_child(_main_menu->instance());

	if (_timer->is_connected("timeout", this, "_load_main_menu"))
	{
		_timer->disconnect("timeout", this, "_load_main_menu");
	}
}

void godot::LoadSceneButton::_load_new_game()
{
	Loader::get_singleton()->set_to_start_values();

	/*if (_timer->is_connected("timeout", this, "_load_new_game"))
	{
		_timer->disconnect("timeout", this, "_load_new_game");
	}*/

	_load_world();
}
