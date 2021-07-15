#pragma once
#include "Headers.h"
namespace godot
{
	class Tomb : public Sprite
	{
	private:
		GODOT_CLASS(Tomb, Sprite)

	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		void _load_death_menu();
		void _load_fadeout_effect();

	private:
		Timer* _timer = nullptr;
		ResourceLoader* _resource_loader;
	};
}


