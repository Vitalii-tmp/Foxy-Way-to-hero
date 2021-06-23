#pragma once
#include "Headers.h"

namespace godot
{
	class PauseButton : public Button
	{
		GODOT_CLASS(PauseButton, Button);

	public:
		static void _register_methods();
		void _init();
		void _ready();

		void _on_button_pause_pressed();

	private:
		ResourceLoader* _resource_loader = nullptr;
	};
}

