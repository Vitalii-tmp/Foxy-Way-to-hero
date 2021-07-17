#include "PauseButton.h"

void godot::PauseButton::_register_methods()
{
	register_method("_ready", &PauseButton::_ready);
	register_method("_on_button_pause_pressed", &PauseButton::_on_button_pause_pressed);
	register_method("_process", &PauseButton::_process);
}

void godot::PauseButton::_init()
{
}

void godot::PauseButton::_ready()
{
	_resource_loader = ResourceLoader::get_singleton();
	connect("pressed", this, "_on_button_pause_pressed");

}

void godot::PauseButton::_process(float delta)
{
	//_on_escape_button_pressed();
}

void godot::PauseButton::_on_button_pause_pressed()
{
	Godot::print("Pause pressed");

	this->set_visible(false);
	get_tree()->set_pause(true);
	
	Ref<PackedScene> prefab = _resource_loader->load("res://Scenes/UI/PauseMenu.tscn");

	auto* menu = cast_to<CanvasLayer>(prefab->instance());
	get_node("/root/World/UI/")->add_child(menu);

	SoundEffectsManager::_get_singleton()->_play_sound_effect("ButtonClickSE", get_node("/root/"));
}

void godot::PauseButton::_on_escape_button_pressed()
{
	Input* i = Input::get_singleton();

	if (i->is_action_just_pressed("ui_cancel") && !get_tree()->is_paused())
	{
		get_tree()->set_pause(true);

		Ref<PackedScene> prefab = _resource_loader->load("res://Scenes/UI/PauseMenu.tscn");

		auto* menu = cast_to<CanvasLayer>(prefab->instance());
		get_node("/root/World/UI/")->add_child(menu);
	}
}
