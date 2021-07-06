#include "Meat.h"

void godot::Meat::_register_methods()
{
	register_method("_process", &Meat::_process);
	register_method("_ready", &Meat::_ready);
	register_method("_on_item_area_body_entered", &Meat::_on_item_area_body_entered);
}

void godot::Meat::_init()
{
	connect("body_entered", this, "_on_item_area_body_entered");
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

	auto name = get_parent()->get_child(0)->get_name();

	if(name == "Meat")
	{
		_type = MEAT;
		Godot::print("Meat");
	}
	else if(name == "Cheese")
	{
		_type = CHEESE;
		Godot::print("Cheese");
	}
	else if(name == "Fish")
	{
		_type = FISH;
		Godot::print("Fish");
	}
	else if(name == "RedFish")
	{
		_type = RED_FISH;
		Godot::print("Red fish");
	}
}

void godot::Meat::_on_item_area_body_entered(Node* body)
{
	if (body->get_name() == "Player")
	{
		Godot::print("Collision with player");
		if(Player::_get_singleton()->_backpack == nullptr)
		{
			Godot::print("NULLPTR");

		}
		if (Player::_get_singleton()->_backpack->_can_add_element())
		{
			Godot::print("can add element");
			Player::_get_singleton()->_backpack->_add_element(this);
			get_parent()->queue_free();
		}
	}
}
