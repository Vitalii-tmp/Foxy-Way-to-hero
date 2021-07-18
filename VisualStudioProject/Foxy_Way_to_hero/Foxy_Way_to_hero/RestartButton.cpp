#include "RestartButton.h"

void godot::RestartButton::_register_methods()
{
	register_method("_ready", &RestartButton::_ready);
	register_method("_process", &RestartButton::_process);
	register_method("_on_restart_button_pressed", &RestartButton::_on_restart_button_pressed);
	register_method("_restart_world", &RestartButton::_restart_world);
	register_method("_fade_world_music_in", &RestartButton::_fade_world_music_in);
}

void godot::RestartButton::_init()
{
}

void godot::RestartButton::_ready()
{
	connect("pressed", this, "_on_restart_button_pressed");

	_resource_loader = ResourceLoader::get_singleton();

	_timer = Timer::_new();
	this->add_child(_timer);

	_music_timer = Timer::_new();
	this->add_child(_music_timer);
}

void godot::RestartButton::_process(float delta)
{
	Input* i = Input::get_singleton();


	if (i->is_action_just_pressed("ui_cancel") && get_tree()->is_paused())
	{
		SoundEffectsManager::_get_singleton()->_play_sound_effect("ButtonClickSE", get_node("/root/"));
		i->action_release("ui_cancel");

		Godot::print("esc action");
		get_tree()->set_pause(false);
		this->get_parent()->queue_free();
	}

	
}

void godot::RestartButton::_on_restart_button_pressed()
{
	_fade_world_music_in();

	SoundEffectsManager::_get_singleton()->_play_sound_effect("ButtonClickSE", get_node("/root/"));
	_button_name = this->get_name();
	Ref<PackedScene> fade_out = _resource_loader->load("res://Scenes/Effects/FadeOut.tscn");
	this->add_child(fade_out->instance());

	if (!_timer->is_connected("timeout", this, "_restart_world"))
	{
		_timer->connect("timeout", this, "_restart_world");
		_timer->start(1);
	}

	
}

void godot::RestartButton::_restart_world()
{
	Ref<PackedScene> world = _resource_loader->load("res://World.tscn");

	if (_button_name == "RestartButton") {
		Loader::get_singleton()->set_to_start_values();
		Loader::get_singleton()->save_all_fields();
		get_node("/root/World")->set_name("to_delete");
		get_node("/root/to_delete")->queue_free();
		get_tree()->set_pause(false);
	}
	else if (_button_name == "RestartDeathButton")
	{
		get_node("/root/World")->set_name("to_delete");
		get_node("/root/to_delete")->queue_free();
	}
	get_node("/root")->add_child(world->instance());



	if (_timer->is_connected("timeout", this, "_restart_world"))
	{
		_timer->disconnect("timeout", this, "_restart_world");
	}


}

void godot::RestartButton::_fade_world_music_in()
{
	AudioController::_get_singleton()->_fade_world_music_in(_music_timer,this);
}
