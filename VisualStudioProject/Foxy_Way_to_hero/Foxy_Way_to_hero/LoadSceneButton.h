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

	private:
		ResourceLoader* _resource_loader = nullptr;
		Timer* _timer = nullptr;
	};
}

