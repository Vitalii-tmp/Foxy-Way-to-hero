#pragma once
#include"Headers.h"



namespace godot
{

	class Player;

	class BatAI :public KinematicBody2D
	{

		GODOT_CLASS(BatAI, KinematicBody2D)
		
		enum state
		{
			IDLE,
			WANDER,
			CHASE
		};

	public:
		BatAI();
		~BatAI();

		//Gameplay methods
		static void _register_methods();
		void _init();
		void _physics_process(float delta);
		void _ready();
		
		void _on_hurt_area_area_entered(Area2D* _other_area);
		void _on_player_detection_area_body_entered(Node* _other_body);
		void _on_player_detection_area_body_exited(Node* _other_body);
		void _on_die_effect_animation_finished();
		void _on_hit_effect_animation_finished();
		
		void _spawn_coin();
		void _spawn_wing();


		//bat states and state changer
		void _change_state_depend_on_player_position();
		void _idle_state();
		void _wander_state();
		void _chase_state();

		float _get_damage();
		
		//Gameplay variables
	public:

	private:
		
		float _hp;
		float _damage;
		float _speed;

		bool _is_alive;
		
		int _current_state;
		

		Vector2 _knockback_vector;
		Vector2 _move_vector;
		Vector2 _start_position;

		AnimatedSprite* _die_effect = nullptr;
		AnimatedSprite* _hit_effect = nullptr;
		AnimatedSprite* _bat_sprite = nullptr;

		Player* _player=nullptr;

		Area2D* _bat_hit_area=nullptr;

		ResourceLoader* _resource_loader;
	};
}


