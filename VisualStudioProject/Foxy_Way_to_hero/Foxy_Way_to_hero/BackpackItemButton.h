#pragma once
#include "Headers.h"

namespace godot {
	class BackpackItemButton : public TextureButton
	{
		GODOT_CLASS(BackpackItemButton, TextureButton);

	public:

		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);

		void _on_item_button_pressed();

	private:
		ResourceLoader* _resource_loader;

		Label* _label = nullptr;

		
	};
}
