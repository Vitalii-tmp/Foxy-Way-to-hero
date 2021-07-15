#pragma once
#include"Headers.h"


namespace godot
{

	class BoarAI :public KinematicBody2D
	{
		GODOT_CLASS(BoarAI, KinematicBody2D)

			enum state
		{
			WALK,
			WANDER,
			CHASE
		};
	public:


		BoarAI();
		~BoarAI();

		static void _register_methods();
		void _init();
		void _ready();
		void _physics_process(float delta);

		void _walk_state();
		void _wander_state();
		void _chase_state();

		void _walk();

		void _change_state();

		void _on_detection_area_body_entered(Node2D* _other_body);
		void _on_detection_area_body_exited(Node2D* _other_body);

		void _on_hurt_area_area_entered(Area2D* _other_area);
		void _on_boar_hit_area_area_entered(Area2D* _other_area);
		void _on_hit_effect_animation_finished();
		void _set_move_vector();
		void _stoping();
		void _change_to_can_move();

		float _get_damage();
		bool _get_agressive();
		Vector2 _get_move_vector();

		void _spawn_coin();
		void _spawn_fur();
		
		//Gameplay variables
	private:

		int _current_state;
		int _start_time;

		float _hp;
		float _run_speed;
		float _walk_speed;
		float _damage;

		bool _is_alive;
		bool _agressive;
		bool _can_move;
		bool _is_stoping;

		Vector2 _move_vector;
		Vector2 _prew_position;
		Vector2 _current_position;
		Vector2 _knockback_vector;
		Vector2 _look_vector;

		Player* _player = nullptr;
		AnimatedSprite* _hit_effect = nullptr;

		Node2D* _enviroment = nullptr;
		Array _entered_bodies;
		Timer* _timer = nullptr;

		AnimationPlayer* _animation_player = nullptr;
		AnimationTree* _animation_tree = nullptr;
		AnimationNodeStateMachinePlayback* _animation_state = nullptr;

		RandomNumberGenerator* _timer_start_time = nullptr;

		ResourceLoader* _resource_loader;
	};
}


