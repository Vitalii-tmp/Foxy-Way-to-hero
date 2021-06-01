#pragma once

#include "Headers.h"

namespace godot 
{
	class SplashScreen : public KinematicBody2D
	{
		// Godot structure
	private:
		GODOT_CLASS(SplashScreen, KinematicBody2D)
	public:

		static void _register_methods();
		void _init();
		void _process(float delta);

		SplashScreen();
		~SplashScreen();
	};
}