#include "Headers.h"

using namespace godot;




void godot::Player::_register_methods()
{
	register_method((char*)"_process", &Player::_process);
	register_method((char*)"_init", &Player::_init);
	register_method((char*)"_ready", &Player::_ready);
	register_method((char*)"_attack_animation_is_finished", &Player::_attack_animation_is_finished);
	register_method((char*)"_roll_animation_is_finished", &Player::_roll_animation_is_finished);
	
}


void godot::Player::_init() {}


Player::Player()
{
	_speed = 100;
	_damage = 25;

	_motion = Vector2(0, 0);
	_input_vector = Vector2(0, 1);

	_is_alive = true;
}

void godot::Player::_ready()
{
	_animation_tree = cast_to<AnimationTree>(get_node("AnimationTree"));
	_animation_tree->set_active(true);

	_animation_state = _animation_tree->get("parameters/playback");

	_hit_area = cast_to<Area2D>(get_node("HitboxPivot/ShortAttackArea"));
	
}

void godot::Player::_process(float delta)
{
	if (_is_alive)
	{
		_change_state_depend_on_behavior();
	}

}



void godot::Player::_move_state()
{
	_motion = Vector2(0, 0);

	
		Input* i = Input::get_singleton();

		if (i->is_action_pressed("ui_up"))
			_motion.y -= _speed;
		if (i->is_action_pressed("ui_down"))
			_motion.y += _speed;
		if (i->is_action_pressed("ui_left"))
			_motion.x -= _speed;
		if (i->is_action_pressed("ui_right"))
			_motion.x += _speed;

		if (_motion != Vector2(0, 0))
			_input_vector = _motion;


		_motion = _motion.normalized() * _speed;


	

	_animation_tree->set("parameters/Idle/blend_position", _input_vector);
	_animation_tree->set("parameters/Run/blend_position", _input_vector);

	if (_motion != Vector2(0, 0))
		_animation_state->travel("Run");
	else
		_animation_state->travel("Idle");


	move_and_slide(_motion);
}


void godot::Player::_attack_state()
{

	_animation_tree->set("parameters/Attack/blend_position", _input_vector);
	_animation_state->travel("Attack");
}

void godot::Player::_roll_state()
{
	_animation_tree->set("parameters/Roll/blend_position", _input_vector);
	_animation_state->travel("Roll");
	_input_vector = _input_vector.normalized() * _speed;
	move_and_slide(_input_vector*1.4);
}

// call in animation tree
void godot::Player::_attack_animation_is_finished()
{
	_current_state = MOVE;
}

void godot::Player::_roll_animation_is_finished()
{
	_current_state = MOVE;
}

void godot::Player::_change_state_depend_on_behavior()
{
	Input* i = Input::get_singleton();

	if (i->is_action_just_pressed("attack"))
		_current_state = ATTACK;

	if (i->is_action_just_pressed("roll"))
		_current_state = ROLL;


	switch (_current_state)
	{
	case MOVE:
		_move_state();
		break;

	case ROLL:
		_roll_state();
		break;

	case ATTACK:
		_attack_state();
		break;
	}
}

Vector2 godot::Player::_get_input_vector()
{
	return _input_vector;
}

float godot::Player::_get_damage()
{
	return _damage;
}


Player::~Player() {}
