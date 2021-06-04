#pragma once
#include"Headers.h"
namespace godot
{
	class BatAI :public KinematicBody2D
	{

	private:
		GODOT_CLASS(BatAI, Area2D)

	public:
		BatAI();
		~BatAI();

		//Gameplay methods
		static void _register_methods();
		void _init();
		void _physics_process(float delta);
		void _ready();
		
		void _on_player_hit_area_entered(Area2D* _other_area);
		void _on_die_effect_animation_finished();
		
		//Gameplay variables
	private:
		
		float _hp;

		Vector2 _knockback_vector;
		AnimatedSprite* _die_effect = nullptr;
		AnimatedSprite* _bat_sprite = nullptr;
	};
}


