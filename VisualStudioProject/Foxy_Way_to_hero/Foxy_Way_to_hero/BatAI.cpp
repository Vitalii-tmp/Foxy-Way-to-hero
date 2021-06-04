#include"Headers.h"
using namespace godot;

godot::BatAI::BatAI()
{
	_hp = 50;
	_knockback_vector = Vector2(0, 0);

}


void godot::BatAI::_register_methods()
{
	register_method((char*)"_physics_process", &BatAI::_physics_process);
	register_method((char*)"_init", &BatAI::_init);
	register_method((char*)"_ready", &BatAI::_ready);

	register_method((char*)"_on_player_hit_area_entered", &BatAI::_on_player_hit_area_entered);
	register_method((char*)"_on_die_effect_animation_finished", &BatAI::_on_die_effect_animation_finished);
	
}


void godot::BatAI::_init()
{
}


void godot::BatAI::_ready()
{

	_die_effect = cast_to<AnimatedSprite>(get_child(4));
	_bat_sprite = cast_to<AnimatedSprite>(get_child(0));
}


void godot::BatAI::_physics_process(float delta)
{

	if (_hp > 0)
	{
		move_and_slide(_knockback_vector);
		_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);

	}

	
	if (_hp <= 0)
	{
		_bat_sprite->set_visible(false);
		_die_effect->set_visible(true);
		_die_effect->play();
		
	}
		
}



void godot::BatAI::_on_player_hit_area_entered(Area2D* _other_area)
{
	if (_other_area->get_name() == "ShortAttackArea") 
	{
		auto _vector = cast_to<Player>(_other_area->get_parent()->get_parent())->_get_input_vector();
		auto _pl_damage = cast_to<Player>(_other_area->get_parent()->get_parent())->_get_damage();
		
		_knockback_vector = _vector ;
		
		_hp -= _pl_damage;
	}
		
}

void godot::BatAI::_on_die_effect_animation_finished()
{
	queue_free();
}


godot::BatAI::~BatAI()
{
}