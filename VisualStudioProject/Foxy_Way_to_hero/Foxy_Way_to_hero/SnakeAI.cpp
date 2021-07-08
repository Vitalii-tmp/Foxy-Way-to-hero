#include "SnakeAI.h"

godot::SnakeAI::SnakeAI()
{
	_hp = 75;
	_damage = 15;
	_speed = 30;

	_is_alive = true;
	_is_attaking = false;

	_knockback_vector = Vector2(0, 0);
	_move_vector = Vector2(0, 0);

	_current_state = IDLE;


}



void godot::SnakeAI::_register_methods()
{
	register_method("_physics_process", &SnakeAI::_physics_process);
	register_method("_init", &SnakeAI::_init);
	register_method("_ready", &SnakeAI::_ready);

	register_method("_on_hurt_area_area_entered", &SnakeAI::_on_hurt_area_area_entered);
	register_method("_on_detection_area_body_entered", &SnakeAI::_on_detection_area_body_entered);
	register_method("_on_detection_area_body_exited", &SnakeAI::_on_detection_area_body_exited);
	register_method("_on_attack_animation_finished", &SnakeAI::_on_attack_animation_finished);

	register_method("_on_hit_effect_animation_finished", &SnakeAI::_on_hit_effect_animation_finished);
	register_method("_change_move_vector", &SnakeAI::_change_move_vector);
	
	

}

void godot::SnakeAI::_init()
{
}

void godot::SnakeAI::_physics_process(float delta)
{
	if (_is_alive)
		_change_state_depend_on_player_position();


	if (_hp <= 0)
	{
		_is_alive = false;
		_animation_state->travel("Die");
	}

	if (_is_alive && !_is_attaking)
	{
		if (_move_vector != Vector2(0, 0))
			_animation_state->travel("Move");
		else
			_animation_state->travel("Idle");
	}

	_animation_tree->set("parameters/Idle/blend_position", _look_vector);
	_animation_tree->set("parameters/Move/blend_position", _look_vector);
	_animation_tree->set("parameters/Attack/blend_position", _look_vector);
	_animation_tree->set("parameters/Die/blend_position", _look_vector);

	
}


void godot::SnakeAI::_ready()
{
	_hit_effect = cast_to<AnimatedSprite>(get_node("HitEffect"));

	_timer = Timer::_new();
	this->add_child(_timer);
	_timer_start_time = RandomNumberGenerator::_new();

	_animation_tree = cast_to<AnimationTree>(get_node("AnimationSnakeTree"));
	_animation_tree->set_active(true);

	_animation_state = _animation_tree->get("parameters/playback");
}

godot::SnakeAI::~SnakeAI()
{
}

void godot::SnakeAI::_change_state_depend_on_player_position()
{


	switch (_current_state)
	{
	case IDLE:
		_idle_state();
		break;
	case WANDER:
		_wander_state();
		break;
	case CHASE:
		_chase_state();
		break;
	}
}


void godot::SnakeAI::_idle_state()
{

	//_move_vector = Vector2(0, 0);
	walk();

	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);

}


void godot::SnakeAI::_wander_state()
{
	walk();
	//check distance to player
	auto _distance_to_player = sqrt(pow((this->get_global_position().x - _player->get_global_position().x), 2) +
		pow((this->get_global_position().y - _player->get_global_position().y), 2));


	//if player too close chase him
	if (_distance_to_player < 75)
		_current_state = CHASE;

	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);

}


void godot::SnakeAI::_chase_state()
{
	//take player possition to move here
	_move_vector = (Player::_get_singleton()->get_global_position() - this->get_global_position()).normalized();

	//check distance to player
	auto _distance_to_player = sqrt(pow((this->get_global_position().x - _player->get_global_position().x), 2) +
		pow((this->get_global_position().y - _player->get_global_position().y), 2));


	if (_distance_to_player < 17)
	{
		_animation_state->travel("Attack");
		_is_attaking = true;
		//_current_state = IDLE;
	}
		



	if (_distance_to_player > 100)
		_current_state = WANDER;

	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);

	move_and_slide(_move_vector * _speed);

	//if snake is attaking
	if (_move_vector != Vector2(0, 0))
		_look_vector = _move_vector.normalized();

	//_animation_tree->set("parameters/Move/blend_position", _look_vector);
	//_animation_tree->set("parameters/Attack/blend_position", _look_vector);
}


float godot::SnakeAI::_get_damage()
{
	return _damage;
}

void godot::SnakeAI::_on_hurt_area_area_entered(Area2D* _other_area)
{
	if (_other_area->get_name() == "ShortAttackArea")
	{
		//play hit affect
		_hit_effect->set_visible(true);
		_hit_effect->play();

		//get vector(direction) player knocks bat and damage
		auto _vector = Player::_get_singleton()->_get_input_vector();
		auto _pl_damage = Player::_get_singleton()->_get_damage();

		//knock back bat
		_knockback_vector = _vector.normalized() * 50;

		_hp -= _pl_damage;
	}

	if (_other_area->get_name() == "LongAttackArea")
	{
		//play hit affect
		_hit_effect->set_visible(true);
		_hit_effect->play();

		//get vector(direction) player knocks bat and damage
		auto _vector = Player::_get_singleton()->_get_input_vector();
		auto _pl_damage = Player::_get_singleton()->_get_damage();

		//knock back bat
		_knockback_vector = _vector.normalized() * 50;
		_hp -= _pl_damage;
	}
}

void godot::SnakeAI::_on_detection_area_body_entered(Node2D* _other_body)
{
	if (_other_body->get_name() == "Player")
	{
		_player = cast_to<Player>(_other_body);
		_current_state = WANDER;
		Godot::print("Player is wandered!");

	}
}

void godot::SnakeAI::_on_detection_area_body_exited(Node2D* _other_body)
{
	if (_other_body->get_name() == "Player")
	{

		_current_state = IDLE;
		//_player = nullptr;
	}
}

void godot::SnakeAI::_on_hit_effect_animation_finished()
{
	_hit_effect->set_visible(false);
	_hit_effect->set_frame(0);
}

void godot::SnakeAI::_on_attack_animation_finished()
{
	_is_attaking = false;
	//_current_state = WANDER;
}

void godot::SnakeAI::walk()
{
	if (!_timer->is_connected("timeout", this, "_change_move_vector"))
	{

		Godot::print("Timer connected");
		_timer->connect("timeout", this, "_change_move_vector");

		_timer_start_time->randomize();
		_start_time = _timer_start_time->randi_range(1, 5);
		_timer->start(_start_time);

		Godot::print(String::num(_start_time));
	}
	move_and_slide(_move_vector * _speed);

	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);

	if (_move_vector != Vector2(0, 0))
		_look_vector = _move_vector.normalized();

	//_animation_tree->set("parameters/Idle/blend_position", _look_vector);
	//_animation_tree->set("parameters/Move/blend_position", _look_vector);
}

void godot::SnakeAI::_change_move_vector()
{
	if (_move_vector == Vector2(0, 0))
	{
		_move_vector.x = -360 + rand() % 721;
		_move_vector.y = -360 + rand() % 721;
		_move_vector = _move_vector.normalized();
	}
	else
		_move_vector = Vector2(0, 0);


	_timer_start_time->randomize();
	_start_time = _timer_start_time->randi_range(1, 10);
	Godot::print("new timerstart time " + String::num(_start_time));


	if (_timer->is_connected("timeout", this, "_change_move_vector"))
	{
		Godot::print("Timer disconnected");
		_timer->disconnect("timeout", this, "_change_move_vector");
	}

}
