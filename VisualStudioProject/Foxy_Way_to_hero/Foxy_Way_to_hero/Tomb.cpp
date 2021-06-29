#include "Tomb.h"

void godot::Tomb::_register_methods()
{
	register_method("_ready", &Tomb::_ready);
	register_method("_process", &Tomb::_process);
	register_method("_load_death_menu", &Tomb::_load_death_menu);
	
}
void godot::Tomb::_init()
{
}

void godot::Tomb::_process(float delta)
{
	if (!_death_timer->is_connected("timeout", this, "_load_death_menu"))
	{
		Godot::print("Timer connected");
		_death_timer->connect("timeout", this, "_load_death_menu");
		_death_timer->start(4);
	}
}

void godot::Tomb::_ready()
{
	_death_timer = Timer::_new();
	this->add_child(_death_timer);
	_resource_loader = ResourceLoader::get_singleton();
}

void godot::Tomb::_load_death_menu()
{
	Godot::print("Timer disconnected");
	_death_timer->disconnect("timeout", this, "_load_death_menu");

	Ref<PackedScene> _death_menu = _resource_loader->load("res://Scenes/UI/DeathMenu.tscn");

	get_node("/root/World")->set_name("to_delete");
	get_node("/root/to_delete")->queue_free();

	get_node("/root")->add_child(_death_menu->instance());

}
