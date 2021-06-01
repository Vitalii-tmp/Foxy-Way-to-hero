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
		const int speed = 100;
	private:

		Vector2 motion;

		bool bDead;

		// Gameplay methods
	public:

		static PlayerSingleton* getSingleton();

		void UpdateMotionFromInput();

	private:

	};
}


