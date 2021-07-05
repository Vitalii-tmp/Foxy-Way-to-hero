#include "BackpackItemButton.h"

void godot::BackpackItemButton::_register_methods()
{
	register_method("_ready", &BackpackItemButton::_ready);
	register_method("_process", &BackpackItemButton::_process);
}

void godot::BackpackItemButton::_init()
{
}

void godot::BackpackItemButton::_ready()
{
}

void godot::BackpackItemButton::_process(float delta)
{
	if (cast_to<Label>(get_child(0))->get_text().to_int() > 1)
		cast_to<Label>(get_child(0))->set_visible(true);
}

void godot::BackpackItemButton::_on_item_button_pressed()
{
}
