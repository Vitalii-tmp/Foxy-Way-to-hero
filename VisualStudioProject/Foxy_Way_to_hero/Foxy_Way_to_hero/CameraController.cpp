#include"Headers.h"

using namespace godot;

godot::CameraController::CameraController()
{
}

godot::CameraController::~CameraController()
{
}

void godot::CameraController::_register_methods()
{
	register_method((char*)"_process", &CameraController::_process);
	register_method((char*)"_init", &CameraController::_init);
	register_method((char*)"_ready", &CameraController::_ready);
}

void godot::CameraController::_init()
{
}

void godot::CameraController::_process(float delta)
{
}

void godot::CameraController::_ready()
{
	_top_left_limit = cast_to<Position2D>(get_child(0)->get_child(1));
	_bottom_right_limit = cast_to<Position2D>(get_child(0)->get_child(0));

	
	set("limit_left", _top_left_limit->get_global_position().x);
	set("limit_top", _top_left_limit->get_global_position().y);
	set("limit_right", _bottom_right_limit->get_global_position().x);
	set("limit_bottom", _bottom_right_limit->get_global_position().y);
	
}
