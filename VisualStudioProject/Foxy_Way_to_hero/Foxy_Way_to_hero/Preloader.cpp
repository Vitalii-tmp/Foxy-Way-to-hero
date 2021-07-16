#include "Preloader.h"

void godot::Preloader::_register_methods()
{
	register_method("_ready", &Preloader::_ready);
	register_method("_process", &Preloader::_process);
	register_method("_on_video_player_finished", &Preloader::_on_video_player_finished);
}

void godot::Preloader::_init()
{
}

void godot::Preloader::_ready()
{
	_resource_loader = ResourceLoader::get_singleton();
}

void godot::Preloader::_process(float delta)
{

}

void godot::Preloader::_on_video_player_finished()
{
	Godot::print("Menu button");
	Ref<PackedScene> _main_menu = _resource_loader->load("res://MainMenu.tscn");
	queue_free();

	get_node("/root")->add_child(_main_menu->instance());

	
}
