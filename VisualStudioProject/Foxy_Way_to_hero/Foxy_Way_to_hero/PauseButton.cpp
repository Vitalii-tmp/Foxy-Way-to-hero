#include "PauseButton.h"

void godot::PauseButton::_register_methods()
{
	register_method("_ready", &PauseButton::_ready);
	register_method("_on_button_pause_pressed", &PauseButton::_on_button_pause_pressed);
}

void godot::PauseButton::_init()
{
}

void godot::PauseButton::_ready()
{
	connect("pressed", this, "_on_button_pause_pressed");
}

void godot::PauseButton::_on_button_pause_pressed()
{
	Godot::print("Pause pressed");
}
