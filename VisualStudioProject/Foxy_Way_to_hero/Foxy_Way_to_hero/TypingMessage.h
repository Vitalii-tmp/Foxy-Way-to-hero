#pragma once
#include "Headers.h"

namespace godot
{
	class TypingMessage : public TextureRect
	{
		GODOT_CLASS(TypingMessage, TextureRect);

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);

		void _add_char();
		void _delete_cut_scene();

	private:
		Label* _text = nullptr;
		Timer* _timer = nullptr;

		String _message;
		String _current_text;

		int _pos = 0;
	};

}

