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

	private:
		ResourceLoader* _resource_loader = nullptr;
	};
}

