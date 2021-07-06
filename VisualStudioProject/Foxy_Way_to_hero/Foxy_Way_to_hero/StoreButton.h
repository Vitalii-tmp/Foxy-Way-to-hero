#pragma once
#include "Headers.h"

namespace godot
{
	class StoreButton : public TextureButton
	{
		GODOT_CLASS(StoreButton, TextureButton);

	public:
		static void _register_methods();
		void _init();
		void _ready();

		void _on_button_pressed();

	private:
		ResourceLoader* _resource_loader = nullptr;
	};
}

