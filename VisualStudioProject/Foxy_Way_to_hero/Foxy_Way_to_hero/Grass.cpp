#include "Grass.h"

using namespace godot;


Grass::Grass()
{

}

Grass::~Grass()
{

}

void godot::Grass::_register_methods()
{
	register_method((char*)"_process", &Grass::_process);
	register_method((char*)"_init", &Grass::_init);
	register_method((char*)"_ready", &Grass::_ready);
	register_method((char*)"_on_player_hit_area_entered", &Grass::_on_player_hit_area_entered);
	register_method((char*)"_on_grass_effect_animation_finished", &Grass::_on_grass_effect_animation_finished);
	
}

void godot::Grass::_init()
{
	//connect("area_entered", this, "_on_player_hit_area_entered");
}

void godot::Grass::_ready()
{
	//Godot::print("crash grass");
	_animated_sprite = cast_to<AnimatedSprite>(get_parent());
	_sprite = cast_to<Sprite>(get_parent()->get_parent()->get_child(0));

}



void godot::Grass::_process(float delta)
{
}


void godot::Grass::_on_player_hit_area_entered(Area2D* _other_area)
{
	if (_other_area->get_name() == "ShortAttackArea")
	{
		_sprite->queue_free();
		_animated_sprite->set_visible(true);
		_animated_sprite->play("Animation");
		
		
	}
}

void godot::Grass::_on_grass_effect_animation_finished()
{
	
	_animated_sprite->queue_free();
	
}
