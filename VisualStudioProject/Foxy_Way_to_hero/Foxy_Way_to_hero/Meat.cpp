#include "Meat.h"

void godot::Meat::_register_methods()
{
	register_method("_process", &Meat::_process);
	register_method("_ready", &Meat::_ready);
	register_method("_on_meat_area_body_entered", &Meat::_on_meat_area_body_entered);
}

void godot::Meat::_init()
{
	connect("body_entered", this, "_on_meat_area_body_entered");
}

void godot::Meat::_process(float delta)
{
	_move_vector = _move_vector.move_toward(Vector2(0, 0), 7);
	_meat_kinematic_body->move_and_slide(_move_vector.normalized() * _speed);
}

void godot::Meat::_ready()
{
	srand(time(NULL));

	_meat_kinematic_body = cast_to<KinematicBody2D>(get_parent());

	auto _x = -100 + rand() % 200;
	auto _y = -100 + rand() % 200;
	_move_vector = Vector2(_x, _y);

	
}

void godot::Meat::_on_meat_area_body_entered(Node* body)
{
	if(body->get_name() == "Player")
		get_parent()->queue_free();
}
