#include "Countryman.h"

void godot::Countryman::_register_methods()
{
	register_method("_process", &Countryman::_process);
	register_method("_ready", &Countryman::_ready);

	register_method("_on_detection_area_entered", &Countryman::_on_detection_area_entered);
}

void godot::Countryman::_init()
{
}

void godot::Countryman::_process(float delta)
{
}

void godot::Countryman::_ready()
{
	_detection_area = cast_to<Area2D>(get_child(1));
	_detection_area->connect("body_entered", this, "_on_detection_area_entered");

	_dialog_window = cast_to<Sprite>(get_child(2));
	_task = cast_to<Label>(_dialog_window->get_child(0));
}

void godot::Countryman::_on_detection_area_entered(Node* node)
{
	if(node->get_name() == "Player")
		_dialog_window->set_visible(true);
}
