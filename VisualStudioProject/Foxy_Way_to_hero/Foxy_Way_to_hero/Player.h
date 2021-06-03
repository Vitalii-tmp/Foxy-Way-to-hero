#pragma once

#include "Headers.h"

namespace godot {
	
	class Player : public KinematicBody2D 
	{
	
	// Godot structure
	private:
		GODOT_CLASS(Player, KinematicBody2D)
	public:
		
		static void _register_methods();
		void _init();
		void _process(float delta);

		Player();
		~Player();

	// Gameplay variables
	public:
		const int speed = 100;

		int coins = 0;

	private:
		Vector2 motion;



	// Gameplay methods
	public:
		void UpdateMotionFromInput();
	
	private:

	};
}
