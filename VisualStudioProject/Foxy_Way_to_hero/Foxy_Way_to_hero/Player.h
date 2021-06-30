#pragma once
#include "Headers.h"



namespace godot {

	//class Bullet;

	enum state
	{
		MOVE,
		ROLL,
		SHORT_ATTACK,
		LONG_ATTACK
	};

	class Player : public KinematicBody2D
	{

		// Godot structure
		GODOT_CLASS(Player, KinematicBody2D)



	public:
		Player();
		~Player();

		static Player* _get_singleton();
		// Gameplay methods
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		//player states
		void _move_state();
		void _short_attack_state();
		void _long_attack_state();
		void _roll_state();

		void _short_attack_animation_is_finished();
		void _long_attack_animation_is_finished();

		void _roll_animation_is_finished();
		void _change_state_depend_on_behavior();

		void _on_hurt_area_area_entered(Area2D* _other_area);
		void _on_hit_effect_animation_finished();
		
		void _fire();
		void _death();

		Vector2 _get_input_vector();
		float _get_damage();
		int _get_current_state();
		bool _get_is_alive();
		// Gameplay variables
	public:

	private:

		static inline Player* _instance;


		Vector2 _motion;
		Vector2 _input_vector;
		AnimationPlayer* _animation = nullptr;
		AnimationTree* _animation_tree = nullptr;
		AnimatedSprite* _hit_effect = nullptr;
		AnimationNodeStateMachinePlayback* _animation_state = nullptr;
		Area2D* _hit_area = nullptr;
		Timer* _death_timer = nullptr;

		bool _is_alive;
		bool _can_fire;

		int _speed;
		//int _coins;

		float _hp;
		float _damage;

		int _current_state;

		Ref<PackedScene>* _bullet;
		ResourceLoader* _resource_loader;
	};
}
