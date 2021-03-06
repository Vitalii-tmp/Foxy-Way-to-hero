#pragma once
#include "Headers.h"
namespace godot
{
	class AudioController
	{

	private:
		AudioServer* audio_server = nullptr;
		static inline AudioController* _instance = nullptr;
		ResourceLoader* _resource_loader = nullptr;

		float _max_sound_value=10;
	public:

		

		AudioController()
		{
			audio_server = AudioServer::get_singleton();
		}

		static AudioController* _get_singleton()
		{
			if (_instance == nullptr)
				_instance = new AudioController;

			return _instance;
		}

		
		void _fade_main_menu_music_in(Timer* _timer, Node* node);
		void _fade_main_menu_music_out(Timer* _timer, Node* node);
		
		void _fade_world_music_in(Timer* _timer, Node* node);
		void _fade_world_music_out(Timer* _timer, Node* node);

		void _set_music_volume(float _value);
		void _set_sound_effects_volume(float _value);
	

		void _set_max_sound_value(float _value);
	};

}