#include "RestartButton.h"

void godot::RestartButton::_register_methods()
{
	register_method("_ready", &RestartButton::_ready);
	register_method("_process", &RestartButton::_process);
	register_method("_on_restart_button_pressed", &RestartButton::_on_restart_button_pressed);
}

void godot::RestartButton::_init()
{
}

void godot::RestartButton::_ready()
{
	connect("pressed", this, "_on_restart_button_pressed");

	_resource_loader = ResourceLoader::get_singleton();
}

void godot::RestartButton::_process(float delta)
{
	Input* i = Input::get_singleton();


	if (i->is_action_just_pressed("ui_cancel") && get_tree()->is_paused())
	{
		Godot::print("esc action");
		get_tree()->set_pause(false);
		this->get_parent()->queue_free();
	}
}

void godot::RestartButton::_on_restart_button_pressed()
{
	Ref<PackedScene> world = _resource_loader->load("res://World.tscn");

	if (get_name() == "RestartButton") {
		get_node("/root/World")->set_name("to_delete");
		get_node("/root/to_delete")->queue_free();
		get_tree()->set_pause(false);
	}
	else if(get_name() == "RestartDeathButton")
	{
		get_node("/root/DeathMenu")->set_name("to_delete");
		get_node("/root/to_delete")->queue_free();
	}
	get_node("/root")->add_child(world->instance());
}
