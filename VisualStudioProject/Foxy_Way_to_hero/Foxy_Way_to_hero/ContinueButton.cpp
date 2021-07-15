#include "ContinueButton.h"

using namespace godot;

void ContinueButton::_register_methods()
{
	register_method("_ready", &ContinueButton::_ready);
	register_method("_on_button_continue_pressed", &ContinueButton::_on_button_continue_pressed);
}

void ContinueButton::_init()
{
}

void ContinueButton::_ready()
{
	_menu = cast_to<CanvasLayer>(get_parent());
	//_pause_button = cast_to<TextureButton>(get_node("/root/World/UI/PauseButton"));

	connect("pressed", this, "_on_button_continue_pressed");
}

void godot::ContinueButton::_process(float delta)
{
	
}

void ContinueButton::_on_button_continue_pressed()
{
	Godot::print("Continue button pressed");
	get_tree()->set_pause(false);
	//_pause_button->set_visible(true);

	_menu->queue_free();
}
