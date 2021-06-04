#include <string>

#include "Headers.h"

using namespace godot;

enum state
{
	MOVE,
	ROLL,
	ATTACK
};


void Player::_register_methods()
{
	register_method((char*)"_process", &Player::_process);
	register_method((char*)"_init", &Player::_init);
	register_method((char*)"_ready", &Player::_ready);
	register_method((char*)"_attack_animation_is_finished", &Player::_attack_animation_is_finished);
	register_method("_set_coins", &Player::_set_coins);
}


void Player::_init() {}


Player::Player()
{
	_speed = 100;
	_coins = 0;

	_motion = Vector2(0, 0);
	_input_vector = Vector2(0, 0);

	_is_alive = true;
}


void Player::_process(float delta)
{

	Input* i = Input::get_singleton();

	if (i->is_action_just_pressed("attack"))
		_current_state = ATTACK;

	


	switch (_current_state)
	{
	case MOVE:
		_move_state();
		break;
	case ROLL:
		break;
	case ATTACK:
		_attack_state();
		break;

	}

}


void godot::Player::_ready()
{
	_animation_tree = cast_to<AnimationTree>(get_node("AnimationTree"));
	_animation_tree->set_active(true);

	_animation_state = _animation_tree->get("parameters/playback");
}


void Player::_move_state()
{
	_motion = Vector2(0, 0);

	if (_is_alive)
	{
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


	}

	_animation_tree->set("parameters/Idle/blend_position", _input_vector);
	_animation_tree->set("parameters/Run/blend_position", _input_vector);

	if (_motion != Vector2(0, 0))
		_animation_state->travel("Run");
	else
		_animation_state->travel("Idle");


	move_and_slide(_motion);
}


void Player::_attack_state()
{
	_animation_tree->set("parameters/Attack/blend_position", _input_vector);
	_animation_state->travel("Attack");
}

void godot::Player::_attack_animation_is_finished()
{
	_current_state = MOVE;
}

void Player::_set_coins(int coins)
{
	this->_coins += coins;
	printf(std::to_string(this->_coins).c_str());
}

Player::~Player() {}
