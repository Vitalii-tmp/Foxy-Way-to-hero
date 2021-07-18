#pragma once
#include "Headers.h"

namespace godot
{

	class MainMenuCamera : public Camera2D
	{

		GODOT_CLASS(MainMenuCamera, Camera2D);

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _physics_process(float delta);

		MainMenuCamera();

	private:
		bool _move_left;
		bool _move_right;
	};

}


