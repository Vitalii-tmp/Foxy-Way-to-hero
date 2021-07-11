#include "Item.h"

void godot::Item::_register_methods()
{
	register_method("_process", &Item::_process);
	register_method("_ready", &Item::_ready);
	register_method("_on_item_area_body_entered", &Item::_on_item_area_body_entered);
}

void godot::Item::_init()
{
	connect("body_entered", this, "_on_item_area_body_entered");
}

void godot::Item::_process(float delta)
{
	_move_vector = _move_vector.move_toward(Vector2(0, 0), 7);
	_meat_kinematic_body->move_and_slide(_move_vector.normalized() * _speed);
}

void godot::Item::_ready()
{
	srand(time(NULL));

	_meat_kinematic_body = cast_to<KinematicBody2D>(get_parent());

	auto _x = -100 + rand() % 200;
	auto _y = 0 + rand() % 200;
	_move_vector = Vector2(_x, _y);

	auto name = get_parent()->get_parent()->get_name();

	if (name == "Meat")
	{
		_type = MEAT;
		Godot::print("Meat");
	}
	else if (name == "Cheese")
	{
		_type = CHEESE;
		Godot::print("Cheese");
	}
	else if (name == "Fish")
	{
		_type = FISH;
		Godot::print("Fish");
	}
	else if (name == "SpeedItem")
	{
		_type = SPEED_ITEM;
		Godot::print("Red fish");
	}
	else if (name == "BatWing")
	{
		_type = BAT_WING;
	}
	else if(name == "BoarFur")
	{
		_type = BOAR_FUR;
	}
	else if(name == "SnakeFang")
	{
		_type = SNAKE_FANG;
	}
	else if(name == "DamageItem")
	{
		_type = DAMAGE_ITEM;
	}

	_item_sprite = cast_to<Sprite>(get_child(0));
}

void godot::Item::_on_item_area_body_entered(Node* body)
{
	if (body->get_name() == "Player")
	{
		/*Godot::print("Collision with player");
		if(Player::_get_singleton()->_backpack == nullptr)
		{
			Godot::print("NULLPTR");

		}*/
		if (Player::_get_singleton()->_backpack->_can_add_item(this))
		{
			Godot::print("can add element");
			Player::_get_singleton()->_backpack->_add_item(this);
			Godot::print("aaaaaaaaaaaaaaaaaaaaaaaaaaaa");
			get_parent()->queue_free();
		}
	}
}
