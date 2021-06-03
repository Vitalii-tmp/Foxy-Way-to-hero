#pragma once
#include "Headers.h"
namespace godot
{
	class PlayerSingleton
	{
		// Godot structure
	private:

		PlayerSingleton();
		~PlayerSingleton();

		static PlayerSingleton* _instance;

	public:

		void _init();
		void _process(float delta, KinematicBody2D* Player);
		void _ready();

		// Gameplay variables
	public:
		
	private:
		Vector2 _motion;
		Vector2 _inpun_vector;
		AnimationPlayer* _animation = nullptr;

		bool _is_alive;

		int _speed;
		
		float _hp;
		float _damage;

		// Gameplay methods
	public:

		static PlayerSingleton* get_singleton();

		void update_motion_from_input();

		Vector2 _get_motion();
		Vector2 _get_input_vector();

	private:

	};
}


