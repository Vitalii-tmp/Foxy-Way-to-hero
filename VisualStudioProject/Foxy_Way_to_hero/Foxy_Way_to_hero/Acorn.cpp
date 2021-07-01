#include "Acorn.h"

void godot::Acorn::_register_methods()
{
	register_method("_on_acorn_area_body_entered", &Acorn::_on_acorn_area_body_entered);
	register_method("_ready", &Acorn::_ready);
	register_method("_process", &Acorn::_process);
}
		
void godot::Acorn::_init()
{
	connect("body_entered", this, "_on_acorn_area_body_entered");
}

godot::Acorn::Acorn()
{
	_speed = 60;
}

void godot::Acorn::_ready()
{
	srand(time(NULL));

	_acorn_kinematic_body =cast_to<KinematicBody2D>(get_parent());

	auto _x = -100 + rand() % 200;
	auto _y = -100 + rand() % 200;
	_move_vector = Vector2(_x, _y);
}


void godot::Acorn::_process(float delta)
{
	_move_vector = _move_vector.move_toward(Vector2(0, 0), 7);
	_acorn_kinematic_body->move_and_slide(_move_vector.normalized()*_speed);
	//Godot::print(_move_vector);
}

godot::Acorn::~Acorn()
{
}

void godot::Acorn::_on_acorn_area_body_entered(Node* body)
{
	if (body->get_name() == "Player")
	{
		Loader::get_singleton()->set_acorns(1);
		//Loader::get_singleton()->save_acorns_data();

		Loader::get_singleton()->save_all_fields();

		UI::get_singleton()->change_acorns_information();
		
		this->get_parent()->queue_free();
	}
}


