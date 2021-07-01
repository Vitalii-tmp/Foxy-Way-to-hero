#pragma once
#include "Headers.h"

namespace godot
{
	class Meat : public Area2D
	{
	private:
		GODOT_CLASS(Meat, Area2D)
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		void _on_meat_area_body_entered(Node* body);


	private:


		int _speed = 60;

		Vector2 _move_vector;

		KinematicBody2D* _meat_kinematic_body = nullptr;
	};
}

