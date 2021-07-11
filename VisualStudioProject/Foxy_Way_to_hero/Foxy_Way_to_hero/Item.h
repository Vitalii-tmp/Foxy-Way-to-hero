#pragma once
#include "Headers.h"

namespace godot
{
	enum type
	{
		MEAT,
		CHEESE,
		FISH,
		SPEED_ITEM,
		BAT_WING,
		BOAR_FUR,
		SNAKE_FANG,
		DAMAGE_ITEM
	};
	
	class Item : public Area2D
	{
	private:
		GODOT_CLASS(Item, Area2D)
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		void _on_item_area_body_entered(Node* body);
		Sprite* _item_sprite = nullptr;
		type _type;
		
	private:

		int _speed = 60;

		Vector2 _move_vector;

		KinematicBody2D* _meat_kinematic_body = nullptr;
	};
}

