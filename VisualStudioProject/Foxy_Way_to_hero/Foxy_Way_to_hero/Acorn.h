#pragma once
#include "Headers.h"

namespace godot
{
	class Acorn : public Area2D
	{
	private:
		GODOT_CLASS(Acorn, Area2D)
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		Acorn();
		~Acorn();

		void _on_acorn_area_body_entered(Node* body);
		

	private:
		
		
		int _speed;

		Vector2 _move_vector;
        
		KinematicBody2D* _acorn_kinematic_body = nullptr;
	};

}