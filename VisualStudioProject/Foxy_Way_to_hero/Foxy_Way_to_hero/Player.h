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
		void _ready();

		AnimationTree* _animation_tree = nullptr;
		//Variant* _animation_state = nullptr;

		Player();
		~Player();
	};
}
