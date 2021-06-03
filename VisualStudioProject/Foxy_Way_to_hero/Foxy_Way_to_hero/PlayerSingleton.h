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


		// Gameplay variables
	public:
		
	private:
		Vector2 _motion;

		bool _is_alive;

		int _speed;
		int _coins;
		
		float _hp;
		float _damage;


		// Gameplay methods
	public:

		static PlayerSingleton* get_singleton();

		void update_motion_from_input();

		void set_coins(int coin);
	private:

	};
}


