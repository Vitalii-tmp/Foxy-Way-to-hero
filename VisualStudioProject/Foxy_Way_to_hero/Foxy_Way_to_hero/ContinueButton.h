#pragma once
#include "Headers.h"

namespace godot
{
	class ContinueButton : public Button
	{
		GODOT_CLASS(ContinueButton, Button);

	public:
		static void _register_methods();
		void _init();
		void _ready();
		//void _process(float delta);

		void _on_button_continue_pressed();

	private:
		CanvasLayer* _menu = nullptr;
		Button* _pause_button = nullptr;
	};
}

