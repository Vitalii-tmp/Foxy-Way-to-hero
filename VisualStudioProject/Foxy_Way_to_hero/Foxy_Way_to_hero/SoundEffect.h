#pragma once
#include "Headers.h"

namespace godot
{
	class SoundEffect : public AudioStreamPlayer2D
	{
		GODOT_CLASS(SoundEffect, AudioStreamPlayer2D);

		
	public:
		static void _register_methods();
		
		void _init();
		void _ready();
		void _on_time_out();

	private:
		float _duration;
		Timer* _timer;
	};
}


