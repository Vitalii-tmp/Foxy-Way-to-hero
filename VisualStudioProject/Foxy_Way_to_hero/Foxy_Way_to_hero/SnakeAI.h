#pragma once
#include"Headers.h"
namespace godot
{
	class SnakeAI :public KinematicBody2D
	{
		GODOT_CLASS(SnakeAI, KinematicBody2D)

			enum state
		{
			IDLE,
			WANDER,
			CHASE
		};


	public:
		SnakeAI();
		~SnakeAI();

		//Gameplay methods
		static void _register_methods();
		void _init();
		void _physics_process(float delta);
		void _ready();


		void _change_state_depend_on_player_position();
		void _idle_state();
		void _wander_state();
		void _chase_state();

		float _get_damage();

		void _on_hurt_area_area_entered(Area2D* _other_area);
		void _on_detection_area_body_entered(Node2D* _other_body);
		void _on_detection_area_body_exited(Node2D* _other_body);
		void _on_hit_effect_animation_finished();
		void _on_attack_animation_finished();

		void walk();
		void _change_move_vector();
		//Gameplay variables
	public:

	private:

		
		int _start_time;

		float _hp;
		float _damage;
		float _speed;
		

		bool _is_alive;
		bool _is_attaking;

		int _current_state;


		Vector2 _knockback_vector;
		Vector2 _move_vector;
		Vector2 _look_vector;

		AnimatedSprite* _die_effect = nullptr;
		AnimatedSprite* _hit_effect = nullptr;
		AnimatedSprite* _bat_sprite = nullptr;

		Timer* _timer = nullptr;
		
		RandomNumberGenerator* _timer_start_time = nullptr;

		Player* _player;

		AnimationPlayer* _animation_player = nullptr;
		AnimationTree* _animation_tree = nullptr;
		AnimationNodeStateMachinePlayback* _animation_state = nullptr;
	};
}


