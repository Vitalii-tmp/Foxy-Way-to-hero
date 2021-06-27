#pragma once
#include "Headers.h"

namespace godot
{
	class QuitButton : public Button
	{
		GODOT_CLASS(QuitButton, Button);

	public:
		static void _register_methods();
		void _init();
		void _ready();

		void _on_button_quit_pressed();

	private:
		ResourceLoader* _resource_loader = nullptr;
	};
}

