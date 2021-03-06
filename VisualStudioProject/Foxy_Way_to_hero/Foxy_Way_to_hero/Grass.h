#pragma once
#include"Headers.h"


namespace godot {

	class Acorn;
	
	class Grass : public Area2D
	{
	private:
		GODOT_CLASS(Grass, Area2D)

	public:
		Grass();
		~Grass();

		//Gameplay methods
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		void _on_player_hit_area_entered(Area2D* _other_area);
		void _on_grass_effect_animation_finished();
		void _add_acorn();

		// Gameplay variables
	public:

	private:

		AnimatedSprite* _animated_sprite = nullptr;
		Sprite* _sprite = nullptr;
		
		ResourceLoader* _resource_loader;
		
	};

}

