#pragma once
#include "Headers.h"
namespace godot
{
	class CheckPoint : public Area2D
	{
		GODOT_CLASS(CheckPoint, Area2D);
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		void _on_area_body_entered(Node* _other_body);
		void _on_check_point_area_body_exited(Node* _other_body);

		void _on_check_point_animation_finished();
		
	private:
		AnimatedSprite* _check_point_animated_sprite = nullptr;
	};

}
