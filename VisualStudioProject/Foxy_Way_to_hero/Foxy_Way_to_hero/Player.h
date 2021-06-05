#pragma once

#include "Headers.h"

enum state
{
	MOVE,
	ROLL,
	ATTACK
};

namespace godot {

	class Player : public KinematicBody2D
	{

		// Godot structure
		GODOT_CLASS(Player, KinematicBody2D)


		// Gameplay methods
	public:
		Player();
		~Player();

		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();
		
		void _move_state();
		void _attack_state();
		void _roll_state();

		void _attack_animation_is_finished();
		void _roll_animation_is_finished();
		void _change_state_depend_on_behavior();

		void _on_hurt_area_area_entered(Area2D* _other_area);

		Vector2 _get_input_vector();
		float _get_damage();
		// Gameplay variables
	public:
		
	private:
		Vector2 _motion;
		Vector2 _input_vector;
		AnimationPlayer* _animation = nullptr;
		AnimationTree* _animation_tree = nullptr;
		AnimationNodeStateMachinePlayback* _animation_state = nullptr;
		Area2D* _hit_area = nullptr;

		bool _is_alive;

		int _speed;

		float _hp;
		float _damage;

		int _current_state;
	};
}
