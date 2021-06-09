#include "Headers.h"
using namespace godot;

godot::Bullet::Bullet()
{
	_move_vector = Vector2(0, 0);
}


void godot::Bullet::_register_methods()
{
	register_method((char*)"_process", &Bullet::_process);
	register_method((char*)"_init", &Bullet::_init);
	register_method((char*)"_ready", &Bullet::_ready);

	register_method((char*)"_on_detect_area_body_entered", &Bullet::_on_detect_area_body_entered);
	register_method((char*)"_on_detect_area_area_entered", &Bullet::_on_detect_area_area_entered);
	register_method((char*)"_on_detect_area_shape_entered", &Bullet::_on_detect_area_shape_entered);
	
}


void godot::Bullet::_init()
{

}


void godot::Bullet::_process(float delta)
{
	move_and_slide(_move_vector * 300);
}


void godot::Bullet::_ready()
{
	set_global_position(Player::_get_singleton()->get_global_position());
	_move_vector = Player::_get_singleton()->_get_input_vector().normalized();
	Godot::print("ready");
}

void godot::Bullet::_on_detect_area_body_entered(Node2D* _other_body)
{

}

void godot::Bullet::_on_detect_area_area_entered(Area2D* _other_area)
{
	if (_other_area->get_name() != "Player")
		queue_free();
}

void godot::Bullet::_on_detect_area_shape_entered(Node2D* _other_shape)
{

	//Godot::print("Collide");
	
}


godot::Bullet::~Bullet()
{
}