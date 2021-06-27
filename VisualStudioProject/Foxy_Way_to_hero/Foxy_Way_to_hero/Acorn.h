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

		//Acorn();

		void _on_acorn_player_entered(Node* body);
		void _acorn_animation_effect_finished();

	/*private:
		float _time;
		float _angle;
		float _current_x;
		float _current_y;
		
		int _speed;

		Vector2 _move_vector;
		Vector2 _start_position;*/

	private:
		//AnimatedSprite* _animated_sprite = nullptr;
		//AnimatedSprite* _sprite = nullptr;
	};

}