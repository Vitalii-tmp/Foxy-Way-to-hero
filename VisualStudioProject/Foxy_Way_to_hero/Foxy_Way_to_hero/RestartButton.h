#pragma once
#include "Headers.h"

namespace godot
{
	class RestartButton : public Button
	{
		GODOT_CLASS(RestartButton, Button);

	public:
		static void _register_methods();
		void _init();

		void _ready();
		void _process(float delta);

		void _on_restart_button_pressed();

		void _restart_world();
		void _fade_world_music_in();
	private:
		ResourceLoader* _resource_loader = nullptr;

		Timer* _timer = nullptr;
		Timer* _music_timer = nullptr;

		String _button_name;
	};
}

