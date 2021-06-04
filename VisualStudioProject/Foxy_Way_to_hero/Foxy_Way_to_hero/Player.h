#pragma once

#include "Headers.h"



namespace godot {

	class Player : public KinematicBody2D
	{

		// Godot structure
	private:
		GODOT_CLASS(Player, KinematicBody2D)


	public:
		Player();
		~Player();

		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();
		
		void _move_state();
		void _attack_state();
		
		void _attack_animation_is_finished();

lay variables
	public:

	private:
		Vector2 _motion;
		Vector2 _input_vector;
		AnimationPlayer* _animation = nullptr;
		AnimationTree* _animation_tree = nullptr;
		AnimationNodeStateMachinePlayback* _animation_state = nullptr;

		bool _is_alive;

		int _speed;

		float _hp;
		float _damage;

		int _current_state;
	};
}
