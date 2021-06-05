#pragma once
#include"Headers.h"
namespace godot
{
	enum state
	{
		IDLE,
		WANDER,
		CHASE
	};

	class BatAI :public KinematicBody2D
	{

	private:
		GODOT_CLASS(BatAI, Area2D)

	public:
		BatAI();
		~BatAI();

		//Gameplay methods
		static void _register_methods();
		void _init();
		void _physics_process(float delta);
		void _ready();
		
		void _on_player_hit_area_entered(Area2D* _other_area);
		void _on_player_detection_area_body_entered(Node* _other_body);
		void _on_player_detection_area_body_exited(Node* _other_body);
		void _on_die_effect_animation_finished();
		void _on_hit_effect_animation_finished();
		
		void _idle_state();
		void _wander_state();
		void _chase_state();

		float _get_damage();
		//Gameplay variables
	private:
		
		float _hp;
		bool _is_alive;
		float _damage;
		int _current_state;
		float _speed;

		Vector2 _knockback_vector;
		Vector2 _move_vector;

		AnimatedSprite* _die_effect = nullptr;
		AnimatedSprite* _hit_effect = nullptr;
		AnimatedSprite* _bat_sprite = nullptr;

		Player* _player;
	};
}


