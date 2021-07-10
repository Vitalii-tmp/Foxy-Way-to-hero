#include "Craftman.h"

void godot::Craftman::_register_methods()
{
	register_method("_process", &Craftman::_process);
	register_method("_ready", &Craftman::_ready);

	register_method("_on_detection_area_entered", &Craftman::_on_detection_area_entered);
	register_method("_from_detection_area_exit", &Craftman::_from_detection_area_exit);
}

void godot::Craftman::_init()
{
}

void godot::Craftman::_ready()
{
	_detection_area = cast_to<Area2D>(get_child(1));
	_detection_area->connect("body_entered", this, "_on_detection_area_entered");
	_detection_area->connect("body_exited", this, "_from_detection_area_exit");

	_recipe_menu = cast_to<Sprite>(get_child(2));
	_dialog_window = cast_to<Sprite>(get_child(3));
}

void godot::Craftman::_process(float delta)
{
	if (_is_in_area)
		_craft();
}

void godot::Craftman::_on_detection_area_entered(Node* node)
{
	if (node->get_name() == "Player") {
		_dialog_window->set_visible(true);
		_is_in_area = true;
	}
}

void godot::Craftman::_from_detection_area_exit(Node* node)
{
	if (node->get_name() == "Player") {
		_dialog_window->set_visible(false);
		_is_in_area = false;
		_recipe_menu->set_visible(false);
	}
}

void godot::Craftman::_craft()
{
	Input* i = Input::get_singleton();

	if (i->is_action_just_pressed("e_action") && !_recipe_menu->is_visible())
	{
		_recipe_menu->set_visible(true);
	}
	else if (i->is_action_just_pressed("e_action") && _recipe_menu->is_visible())
		_recipe_menu->set_visible(false);
}
