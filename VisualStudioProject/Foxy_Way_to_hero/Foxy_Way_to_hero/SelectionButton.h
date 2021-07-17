#pragma once
#include "Headers.h"

namespace godot {
	class SelectionButton : public TextureButton
	{
		GODOT_CLASS(SelectionButton, TextureButton);

	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		void _on_button_pressed();
	};
}
