#pragma once
#include "Headers.h"

namespace godot
{
	enum type
	{
		MEAT,
		CHEESE,
		FISH,
		RED_FISH
	};
	
	class Meat : public Area2D
	{
		GODOT_CLASS(Meat, Area2D);

	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();
		void _on_item_area_body_entered(Node* body);

		type _type;

		Meat() = default;
		Meat(String name);
	private:
		

		int _speed = 60;

		Vector2 _move_vector;

		KinematicBody2D* _meat_kinematic_body = nullptr;
	};
}

