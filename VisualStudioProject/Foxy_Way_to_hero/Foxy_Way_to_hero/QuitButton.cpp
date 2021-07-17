#include "QuitButton.h"

void godot::QuitButton::_register_methods()
{
	register_method("_ready", &QuitButton::_ready);
	register_method("_on_button_quit_pressed", &QuitButton::_on_button_quit_pressed);
}

void godot::QuitButton::_init()
{
}

void godot::QuitButton::_ready()
{
	connect("pressed", this, "_on_button_quit_pressed");

	_resource_loader = ResourceLoader::get_singleton();
}

void godot::QuitButton::_on_button_quit_pressed()
{
	//get_node("/root")->set_name("to_delete");
	SoundEffectsManager::_get_singleton()->_play_sound_effect("ButtonClickSE", get_node("/root/"));
	get_node("/root")->queue_free();
}
