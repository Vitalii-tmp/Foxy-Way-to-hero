#pragma once
#include "Headers.h"



namespace godot {
	class Meat;
	class Backpack;

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
		void _physics_process(float delta);
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
		bool _get_invisible();
		float _get_hp();
		float _get_hunger();

		void _set_hp(float _new_value);
		void _set_hunger(float _new_value);
		//void _add_to_backpack(Meat* meat);

		void _on_escape_pressed();

		void _reset_player_speed_after_snake();
		void _reser_player_visibility();
		void _reser_player_speed_after_item();

		void _set_player_speed(float speed);
		void _set_to_invisible();
		// Gameplay variables
	public:
		Backpack* _backpack = nullptr;
	private:

		static inline Player* _instance = nullptr;

		Sprite* _player_sprite = nullptr;
		Sprite* _shadow = nullptr;

		Vector2 _motion;
		Vector2 _input_vector;
		Vector2 _knockback_vector;

		AnimationPlayer* _animation = nullptr;
		AnimationTree* _animation_tree = nullptr;
		AnimatedSprite* _hit_effect = nullptr;
		AnimationNodeStateMachinePlayback* _animation_state = nullptr;
		Area2D* _hit_area = nullptr;

		Timer* _death_timer = nullptr;
		Timer* _timer = nullptr;
		Timer* _cool_down_timer = nullptr;

		bool _is_alive;
		bool _invisible;
		bool _can_fire;

		float _speed;
		//int _coins;

		float _hp;
		float _damage;
		float _hunger;

		int _current_state;
		int _invisibility_cooldown;
		int _speed_cooldown;

		Ref<PackedScene>* _bullet;
		ResourceLoader* _resource_loader;
	};
}
