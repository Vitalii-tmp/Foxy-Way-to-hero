#include "AudioController.h"


void godot::AudioController::_fade_main_menu_music_in(Timer* _timer, Node* node)
{
	if (_timer->is_connected("timeout", node, "_fade_main_menu_music_in"))
		_timer->disconnect("timeout", node, "_fade_main_menu_music_in");

	auto _menu_music_bass_index = audio_server->get_bus_index("MainMenuBackground");


	if (audio_server->get_bus_volume_db(_menu_music_bass_index) > -75)
	{
		audio_server->set_bus_volume_db(_menu_music_bass_index, audio_server->get_bus_volume_db(_menu_music_bass_index) - 0.8);

		_timer->connect("timeout", node, "_fade_main_menu_music_in");
		_timer->start(0.01);
	}

}

void godot::AudioController::_fade_main_menu_music_out(Timer* _timer, Node* node)
{
	if (_timer->is_connected("timeout", node, "_fade_main_menu_music_out"))
		_timer->disconnect("timeout", node, "_fade_main_menu_music_out");

	auto _menu_music_bass_index = audio_server->get_bus_index("MainMenuBackground");


	if (audio_server->get_bus_volume_db(_menu_music_bass_index) < 0)
	{
		audio_server->set_bus_volume_db(_menu_music_bass_index, audio_server->get_bus_volume_db(_menu_music_bass_index) + 0.8);

		_timer->connect("timeout", node, "_fade_main_menu_music_out");
		_timer->start(0.01);
	}

}

void godot::AudioController::_fade_world_music_in(Timer* _timer, Node* node)
{
	if (_timer->is_connected("timeout", node, "_fade_world_music_in"))
		_timer->disconnect("timeout", node, "_fade_world_music_in");
	
	auto _world_music_bass_index = audio_server->get_bus_index("WorldBackground");


	if (audio_server->get_bus_volume_db(_world_music_bass_index) > -75)
	{
		audio_server->set_bus_volume_db(_world_music_bass_index, audio_server->get_bus_volume_db(_world_music_bass_index) - 5);

		_timer->connect("timeout", node, "_fade_world_music_in");
		_timer->start(0.01);
	}
	Godot::print(String::num(audio_server->get_bus_volume_db(_world_music_bass_index)));
	Godot::print("_fade_world_music_in");
	
}

void godot::AudioController::_fade_world_music_out(Timer* _timer, Node* node)
{
	if (_timer->is_connected("timeout", node, "_fade_world_music_out"))
		_timer->disconnect("timeout", node, "_fade_world_music_out");

	auto _world_music_bass_index = audio_server->get_bus_index("WorldBackground");


	if (audio_server->get_bus_volume_db(_world_music_bass_index) < 0)
	{
		audio_server->set_bus_volume_db(_world_music_bass_index, audio_server->get_bus_volume_db(_world_music_bass_index) + 0.8);

		_timer->connect("timeout", node, "_fade_world_music_out");
		_timer->start(0.01);
		Godot::print("_fade_world_music_out");
	}

}

void godot::AudioController::_set_music_volume(Timer* _timer, Node* node)
{
}

void godot::AudioController::_set_sound_effects_volume(Timer* _timer, Node* node)
{
}
