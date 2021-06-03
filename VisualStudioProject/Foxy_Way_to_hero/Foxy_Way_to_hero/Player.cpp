#include "Headers.h"

using namespace godot;

void Player::_register_methods() 
{
	register_method((char*)"_process", &Player::_process);
	register_method((char*)"_init", &Player::_init);
	register_method((char*)"_ready", &Player::_ready);
}

void Player::_init() {}

Player::Player() {}

Player::~Player() {}

void Player::_process(float delta) 
{	
	auto _pl_singleton_input = PlayerSingleton::get_singleton()->_get_input_vector();
	auto _motion = PlayerSingleton::get_singleton()->_get_motion();
	PlayerSingleton::get_singleton()->_process(delta,this);
	
	_animation_tree->set("parameters/Idle/blend_position", _pl_singleton_input);
	_animation_tree->set("parameters/Run/blend_position", _pl_singleton_input);
	AnimationNodeStateMachinePlayback* _animation_state = _animation_tree->get("parameters/playback");
	
	if(_motion!=Vector2(0,0))
		_animation_state->travel("Run");
	else
		_animation_state->travel("Idle");
}

void godot::Player::_ready()
{
	_animation_tree = cast_to<AnimationTree>(get_node("AnimationTree"));
	
}

