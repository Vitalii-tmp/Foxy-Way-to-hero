#pragma once
#include "Headers.h"
namespace godot
{
	class Mushrooms :public StaticBody2D
	{
		GODOT_CLASS(Mushrooms, StaticBody2D);

	public:

		

		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);


	private:
		Light2D* _light = nullptr;
		
	};
}


