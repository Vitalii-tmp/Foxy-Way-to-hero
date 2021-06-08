#include "Headers.h"

using namespace godot;

//register methods using in godot
void godot::Player::_register_methods()
{
	register_method((char*)"_process", &Player::_process);
	register_method((char*)"_init", &Player::_init);
	register_method((char*)"_ready", &Player::_ready);
	register_method((char*)"_short_attack_animation_is_finished", &Player::_short_attack_animation_is_finished);
	register_method((char*)"_roll_animation_is_finished", &Player::_roll_animation_is_finished);
	register_method((char*)"_on_hurt_area_area_entered", &Player::_on_hurt_area_area_entered);
	register_method((char*)"_on_hit_effect_animation_finished", &Player::_on_hit_effect_animation_finished);
	register_method((char*)"_long_attack_animation_is_finished", &Player::_long_attack_animation_is_finished);
	

}


void godot::Player::_init() {}

//set default variables value
Player::Player()
{
	_speed = 100;
	_damage = 25;
	_hp = 100;

	_motion = Vector2(0, 0);
	_input_vector = Vector2(0, 1);

	_is_alive = true;
}


//calling on scene start
void godot::Player::_ready()
{
	_animation_tree = cast_to<AnimationTree>(get_node("AnimationTree"));
	_animation_tree->set_active(true);

	_animation_state = _animation_tree->get("parameters/playback");

	_hit_area = cast_to<Area2D>(get_node("HitboxPivot/ShortAttackArea"));
	_hit_effect = cast_to<AnimatedSprite>(get_node("HitEffect"));
}


//call every frame
void godot::Player::_process(float delta)
{
	if (_hp <= 0)
	{
		_is_alive = false;
		//destroy player
		queue_free();
	}
		

	if (_is_alive)
	{
		_change_state_depend_on_behavior();
	}

}


//if player just moving
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

		//set vector <= 1
		_motion = _motion.normalized() * _speed;


	
		//set animations value in animator(animation tree)
	_animation_tree->set("parameters/Idle/blend_position", _input_vector);
	_animation_tree->set("parameters/Run/blend_position", _input_vector);

	//change animation state depend on player move or not
	if (_motion != Vector2(0, 0))
		_animation_state->travel("Run");
	else
		_animation_state->travel("Idle");

	
	move_and_slide(_motion);
}


//if player attack
void godot::Player::_short_attack_state()
{

	_animation_tree->set("parameters/Attack/blend_position", _input_vector);
	_animation_state->travel("Attack");
}

void godot::Player::_long_attack_state()
{
	_animation_tree->set("parameters/LongRangeAttack/blend_position", _input_vector);
	_animation_state->travel("LongRangeAttack");
}


//if player roll
void godot::Player::_roll_state()
{
	_animation_tree->set("parameters/Roll/blend_position", _input_vector);
	_animation_state->travel("Roll");
	_input_vector = _input_vector.normalized() * _speed;
	move_and_slide(_input_vector*1.4);
}


// after attack change state to move (calling in animation tree)
void godot::Player::_short_attack_animation_is_finished()
{
	_current_state = MOVE;
}

void godot::Player::_long_attack_animation_is_finished()
{
	_current_state = MOVE;
}


// after roll change state to move (calling in animation tree)
void godot::Player::_roll_animation_is_finished()
{
	_current_state = MOVE;
}

//changing current state depend on player behavir 
void godot::Player::_change_state_depend_on_behavior()
{
	Input* i = Input::get_singleton();

	if (i->is_action_just_pressed("short_attack"))
		_current_state = SHORT_ATTACK;

	if (i->is_action_just_pressed("roll"))
		_current_state = ROLL;

	if (i->is_action_just_pressed("long_attack"))
		_current_state = LONG_ATTACK;

	switch (_current_state)
	{
	case MOVE:
		_move_state();
		break;

	case ROLL:
		_roll_state();
		break;

	case SHORT_ATTACK:
		_short_attack_state();
		break;

	case LONG_ATTACK:
		_long_attack_state();
		break;

	}
}

//hurt area take damage from enemies
void godot::Player::_on_hurt_area_area_entered(Area2D* _other_area)
{
	if (_other_area->get_name() == "BatHitArea")
	{
		auto _bat_damage = cast_to<BatAI>(_other_area->get_parent())->_get_damage();

		//if player is rolling dont damage from bats
		if (_current_state != ROLL)
		{

			_hp -= _bat_damage;

			_hit_effect->set_visible(true);
			_hit_effect->play();

		}
		
	}
		
}


//after player take damage hide animated sprite of _hit_effect
void godot::Player::_on_hit_effect_animation_finished()
{
	_hit_effect->set_visible(false);
	_hit_effect->set_frame(0);
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
