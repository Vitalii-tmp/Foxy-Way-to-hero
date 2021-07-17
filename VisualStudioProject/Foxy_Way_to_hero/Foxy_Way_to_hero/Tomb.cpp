#include "Tomb.h"

void godot::Tomb::_register_methods()
{
	register_method("_ready", &Tomb::_ready);
	register_method("_process", &Tomb::_process);
	register_method("_load_death_menu", &Tomb::_load_death_menu);
	register_method("_load_fadeout_effect", &Tomb::_load_fadeout_effect);
}
void godot::Tomb::_init()
{
}

void godot::Tomb::_process(float delta)
{

}

void godot::Tomb::_ready()
{
	_timer = Timer::_new();
	this->add_child(_timer);
	_resource_loader = ResourceLoader::get_singleton();

	

	if (!_timer->is_connected("timeout", this, "_load_fadeout_effect"))
	{
		_timer->connect("timeout", this, "_load_fadeout_effect");
		_timer->start(3);
	}
}

void godot::Tomb::_load_death_menu()
{
	Godot::print("Timer disconnected");
	_timer->disconnect("timeout", this, "_load_death_menu");

	Ref<PackedScene> _death_menu = _resource_loader->load("res://Scenes/UI/DeathMenu.tscn");

	//get_node("/root/World")->set_name("to_delete");
	//get_node("/root/to_delete")->queue_free();

	get_node("/root/World/UI")->add_child(_death_menu->instance());


	if (_timer->is_connected("timeout", this, "_load_death_menu"))
	{
		_timer->disconnect("timeout", this, "_load_death_menu");
		
	}
}

void godot::Tomb::_load_fadeout_effect()
{
	Ref<PackedScene> fade_out = _resource_loader->load("res://Scenes/Effects/FadeOut.tscn");

	get_node("/root/World/UI")->add_child(fade_out->instance());
	
	if (_timer->is_connected("timeout", this, "_load_fadeout_effect"))
	{
		_timer->disconnect("timeout", this, "_load_fadeout_effect");
	}

	if (!_timer->is_connected("timeout", this, "_load_death_menu"))
	{
		Godot::print("Timer connected");
		_timer->connect("timeout", this, "_load_death_menu");
		_timer->start(1);
	}
}
