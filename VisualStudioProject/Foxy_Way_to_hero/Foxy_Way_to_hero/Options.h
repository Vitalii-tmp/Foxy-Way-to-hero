#pragma once
#include"Headers.h"

namespace godot
{

	class Options : public Control
	{

		GODOT_CLASS(Options,Control)


	public:

		Options();


		static void _register_methods();
		void _init();
		void _ready();

		void _on_full_screen_button_up();
		void _on_sound_effects_slider_value_changed();
		void _on_music_slider_value_changed();
	private:


		bool is_full_screen;


		CheckBox* _full_screen_check_box = nullptr;

		OS* _os = nullptr;

		HSlider* _sound_effects_hslider = nullptr;
		HSlider* _music_hslider = nullptr;
	};

}


