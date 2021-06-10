#include"Headers.h"
using namespace godot;

godot::BatAI::BatAI()
{
	_hp = 50;
	_damage = 25;
	_speed = 50;

	_is_alive = true;

	_knockback_vector = Vector2(0, 0);
	_move_vector = Vector2(0, 0);

	_current_state = IDLE;

}


void godot::BatAI::_register_methods()
{
	register_method("_physics_process", &BatAI::_physics_process);
	register_method("_init", &BatAI::_init);
	register_method("_ready", &BatAI::_ready);

	register_method("_on_hurt_area_area_entered", &BatAI::_on_hurt_area_area_entered);
	register_method("_on_die_effect_animation_finished", &BatAI::_on_die_effect_animation_finished);
	register_method("_on_hit_effect_animation_finished", &BatAI::_on_hit_effect_animation_finished);
	register_method("_on_player_detection_area_body_entered", &BatAI::_on_player_detection_area_body_entered);
	register_method("_on_player_detection_area_body_exited", &BatAI::_on_player_detection_area_body_exited);
}


void godot::BatAI::_init()
{
}


void godot::BatAI::_ready()
{

	_die_effect = cast_to<AnimatedSprite>(get_node("DieEffect"));
	_bat_sprite = cast_to<AnimatedSprite>(get_node("BatSprite"));
	_hit_effect = cast_to<AnimatedSprite>(get_node("HitEffect"));

}


void godot::BatAI::_physics_process(float delta)
{

	if (_is_alive)
		_change_state_depend_on_player_position();


	if (_hp <= 0)
	{
		_is_alive = false;
	}

	if (!_is_alive)
	{
		_bat_sprite->set_visible(false);
		_die_effect->set_visible(true);
		_die_effect->play();
	}


}


//hurt area take damage from player
void godot::BatAI::_on_hurt_area_area_entered(Area2D* _other_area)
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
		_knockback_vector = _vector.normalized() * 150;

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
		_knockback_vector = _vector.normalized() * 150;
		_hp -= _pl_damage;
	}

}


//when player go into detection area
void godot::BatAI::_on_player_detection_area_body_entered(Node* _other_body)
{
	if (_other_body->get_name() == "Player")
	{
		_player = cast_to<Player>(_other_body);
		_current_state = WANDER;
		Godot::print("Player is wandered!");

	}

}


//when player go out detection area ston chasing him
void godot::BatAI::_on_player_detection_area_body_exited(Node* _other_body)
{
	if (_other_body->get_name() == "Player")
	{
		_current_state = IDLE;
		_player = nullptr;
	}
	
}


void godot::BatAI::_on_die_effect_animation_finished()
{
	queue_free();
}


//after bat take damage hide animated sprite of _hit_effect
void godot::BatAI::_on_hit_effect_animation_finished()
{
	_hit_effect->set_visible(false);
	_hit_effect->set_frame(0);
}


//state changer
void godot::BatAI::_change_state_depend_on_player_position()
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


void godot::BatAI::_idle_state()
{

	_move_vector = Vector2(0, 0);

	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);

	
}


void godot::BatAI::_wander_state()
{
	//check distance to player
	auto _distance_to_player = sqrt(pow((this->get_global_position().x - _player->get_global_position().x), 2) +
		pow((this->get_global_position().y - _player->get_global_position().y), 2));


	//looking on player
	if (_player->get_global_position().x - this->get_global_position().x < 0)
		_bat_sprite->set_flip_h(true);

	if (_player->get_global_position().x - this->get_global_position().x > 0)
		_bat_sprite->set_flip_h(false);

	//if player too close chase him
	if (_distance_to_player < 60)
		_current_state = CHASE;

	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);

}


void godot::BatAI::_chase_state()
{
	//take player possition to move here
	_move_vector = (Player::_get_singleton()->get_global_position() - this->get_global_position()).normalized();
	_move_vector = _move_vector.move_toward(_move_vector, 5);

	//loking on player
	if (_move_vector.x < 0)
		_bat_sprite->set_flip_h(true);

	if (_move_vector.x > 0)
		_bat_sprite->set_flip_h(false);

	
	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);

	move_and_slide(_move_vector * _speed);
}


float godot::BatAI::_get_damage()
{
	return _damage;
}


godot::BatAI::~BatAI()
{
}