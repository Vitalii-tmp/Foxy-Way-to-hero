#pragma once
#include "Headers.h"

namespace godot
{
	class LoadSceneButton : public Button
	{
		GODOT_CLASS(LoadSceneButton, Button);

	public:
		static void _register_methods();
		void _init();
		void _ready();

		void _on_button_pressed();
		void _load_world();
		void _load_main_menu();
		void _load_new_game();

		void _fade_main_menu_music_in();
		void _fade_main_menu_music_out();

		void _fade_world_music_in();
		void _fade_world_music_out();
	private:
		ResourceLoader* _resource_loader = nullptr;
		Timer* _timer = nullptr;
		Timer* _music_timer = nullptr;
	};
}

