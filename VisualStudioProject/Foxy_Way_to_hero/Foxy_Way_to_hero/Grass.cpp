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
	register_method("_process", &Grass::_process);
	register_method("_init", &Grass::_init);
	register_method("_ready", &Grass::_ready);
	register_method("_on_player_hit_area_entered", &Grass::_on_player_hit_area_entered);
	register_method("_on_grass_effect_animation_finished", &Grass::_on_grass_effect_animation_finished);
}


void godot::Grass::_init()
{
	
}


void godot::Grass::_ready()
{
	_animated_sprite = cast_to<AnimatedSprite>(get_parent());
	_sprite = cast_to<Sprite>(get_parent()->get_parent()->get_child(0));
	_resource_loader = ResourceLoader::get_singleton();

}


void godot::Grass::_process(float delta)
{
}


void godot::Grass::_on_player_hit_area_entered(Area2D* _other_area)
{
	if (_other_area->get_name() == "ShortAttackArea")
	{
		SoundEffectsManager::_get_singleton()->_play_sound_effect("GrassSE", Player::_get_singleton());

		_sprite->queue_free();
		_animated_sprite->set_visible(true);
		_animated_sprite->play("Animation");

		_add_acorn();
	}
}


void godot::Grass::_on_grass_effect_animation_finished()
{
	
	_animated_sprite->set_visible(false);
	
	_animated_sprite->queue_free();

	

}

void godot::Grass::_add_acorn()
{
	const auto pos = this->get_global_position();

	Ref<PackedScene> prefab = _resource_loader->load("res://Scenes/Items/Acorn.tscn");

	auto acorn = cast_to<KinematicBody2D>(prefab->instance());
	get_node("/root/World/YSort/")->add_child(acorn);

	acorn->set_global_position(pos + Vector2(8, 8));
}



