#pragma once
#include "Headers.h"

namespace godot
{
	//class Player;

	class Bullet : public KinematicBody2D
	{
		
		GODOT_CLASS(Bullet, KinematicBody2D);

	public:
		
		Bullet();
		~Bullet();

		//Gameplay methods
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();
		void _on_detect_area_body_entered(Node2D* _other_body);
		void _on_detect_area_area_entered(Area2D* _other_area);
		void _on_detect_area_shape_entered(Node2D* _other_shape);
		//Gameplay variables

	private:

		//Player* _player;
		Vector2 _move_vector;
	};


}


