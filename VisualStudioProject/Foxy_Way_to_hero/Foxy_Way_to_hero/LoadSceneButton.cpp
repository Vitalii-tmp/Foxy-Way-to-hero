#include "LoadSceneButton.h"

void godot::LoadSceneButton::_register_methods()
{
	register_method("_ready", &LoadSceneButton::_ready);
	register_method("_on_button_pressed", &LoadSceneButton::_on_button_pressed);
	register_method("_load_world", &LoadSceneButton::_load_world);
	register_method("_load_main_menu", &LoadSceneButton::_load_main_menu);

	register_method("_load_new_game", &LoadSceneButton::_load_new_game);
	register_method("_fade_main_menu_music_in", &LoadSceneButton::_fade_main_menu_music_in);
	register_method("_fade_main_menu_music_out", &LoadSceneButton::_fade_main_menu_music_out);

	register_method("_fade_world_music_in", &LoadSceneButton::_fade_world_music_in);
	register_method("_fade_world_music_out", &LoadSceneButton::_fade_world_music_out);
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

	_music_timer = Timer::_new();
	this->add_child(_music_timer);
}

void godot::LoadSceneButton::_on_button_pressed()
{

	SoundEffectsManager::_get_singleton()->_play_sound_effect("ButtonClickSE", get_node("/root/"));

	if (get_name() == "PlayButton")
	{
		_fade_main_menu_music_in();
		

		Godot::print("Play button");

		Ref<PackedScene> fade_out = _resource_loader->load("res://Scenes/Effects/FadeOut.tscn");

		get_node("/root/MainMenu/UI")->add_child(fade_out->instance());
		Godot::print("Play button");

		if (!_timer->is_connected("timeout", this, "_load_world"))
		{
			_timer->connect("timeout", this, "_load_world");
			_timer->start(1);
		}

		
	}

	if (get_name() == "MainMenuButton")
	{
		_fade_world_music_in();
		_fade_main_menu_music_out();
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
		_fade_world_music_in();
		_fade_main_menu_music_out();
		Ref<PackedScene> world = _resource_loader->load("res://MainMenu.tscn");

		get_node("/root/World")->set_name("to_delete");
		get_node("/root/to_delete")->queue_free();
		get_tree()->set_pause(false);

		get_node("/root")->add_child(world->instance());
	}

	if (get_name() == "BackpackButton")
	{
		if (cast_to<Node2D>(get_node("/root/World/UI/Backpack"))->is_visible())
			cast_to<Node2D>(get_node("/root/World/UI/Backpack"))->set_visible(false);
		else cast_to<Node2D>(get_node("/root/World/UI/Backpack"))->set_visible(true);
	}


	if(get_name() == "NewGameButton")
	{
		_fade_world_music_in();
		_fade_main_menu_music_in();

		Ref<PackedScene> fade_out = _resource_loader->load("res://Scenes/Effects/FadeOut.tscn");

		get_node("/root/MainMenu/UI")->add_child(fade_out->instance());

		if (!_timer->is_connected("timeout", this, "_load_new_game"))
		{
			_timer->connect("timeout", this, "_load_new_game");
			_timer->start(1);
		}
	}

	if (get_name() == "SettingsButton")
	{
		Ref<PackedScene> fade_out = _resource_loader->load("res://Scenes/Settings.tscn");

		//cast_to<TextureButton>(this->get_parent()->get_parent()->get_node("PlayButton"))->set_visible(false);
		//this->set_visible(false);
		//cast_to<TextureButton>(this->get_parent()->get_parent()->get_node("NewGameButton"))->set_visible(false);
		//cast_to<TextureButton>(this->get_parent()->get_parent()->get_node("QuitButton"))->set_visible(false);

		cast_to<TextureButton>(get_node("/root/MainMenu/UI/PlayButton"))->set_visible(false);
		cast_to<TextureButton>(get_node("/root/MainMenu/UI/NewGameButton"))->set_visible(false);
		cast_to<TextureButton>(get_node("/root/MainMenu/UI/QuitButton"))->set_visible(false);
		cast_to<TextureButton>(get_node("/root/MainMenu/UI/SettingsButton"))->set_visible(false);

		
		get_node("/root/MainMenu/UI")->add_child(fade_out->instance());
	}

	if (get_name() == "BackButton")
	{
		//Ref<PackedScene> fade_out = _resource_loader->load("res://Scenes/Settings.tscn");

		//cast_to<TextureButton>(this->get_parent()->get_parent()->get_node("PlayButton"))->set_visible(false);
		//this->set_visible(false);
		//cast_to<TextureButton>(this->get_parent()->get_parent()->get_node("NewGameButton"))->set_visible(false);
		//cast_to<TextureButton>(this->get_parent()->get_parent()->get_node("QuitButton"))->set_visible(false);

		cast_to<TextureButton>(get_node("/root/MainMenu/UI/PlayButton"))->set_visible(true);
		cast_to<TextureButton>(get_node("/root/MainMenu/UI/NewGameButton"))->set_visible(true);
		cast_to<TextureButton>(get_node("/root/MainMenu/UI/QuitButton"))->set_visible(true);
		cast_to<TextureButton>(get_node("/root/MainMenu/UI/SettingsButton"))->set_visible(true);


		get_node("/root/MainMenu/UI/Settings")->queue_free();
	}
}

void godot::LoadSceneButton::_load_world()
{
	Godot::print("Main menu");

	Ref<PackedScene> world = _resource_loader->load("res://World.tscn");
	get_node("/root/MainMenu")->set_name("to_delete");
	get_node("/root/to_delete")->queue_free();
	Godot::print("Main menu");

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

void godot::LoadSceneButton::_fade_main_menu_music_in()
{
	AudioController::_get_singleton()->_fade_main_menu_music_in(_music_timer, this);
}

void godot::LoadSceneButton::_fade_main_menu_music_out()
{
	AudioController::_get_singleton()->_fade_main_menu_music_out(_music_timer, this);
	Godot::print("is working");
}

void godot::LoadSceneButton::_fade_world_music_in()
{
	AudioController::_get_singleton()->_fade_world_music_in(_music_timer, this);
}

void godot::LoadSceneButton::_fade_world_music_out()
{
	AudioController::_get_singleton()->_fade_world_music_out(_music_timer, this);
}
