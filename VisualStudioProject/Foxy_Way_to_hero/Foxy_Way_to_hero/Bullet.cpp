#include "Headers.h"
using namespace godot;

godot::Bullet::Bullet()
{
	_move_vector = Vector2(0, 0);

	_current_x = 0.f;
	_current_y = 0.f;

	_time = 0.f;

	_speed = 300;

	_angle = M_PI / 20;
	_diagonal_shoot_angle = M_PI / 10;
}


void godot::Bullet::_register_methods()
{
	register_method((char*)"_process", &Bullet::_process);
	register_method((char*)"_init", &Bullet::_init);
	register_method((char*)"_ready", &Bullet::_ready);

	register_method((char*)"_on_detect_area_body_entered", &Bullet::_on_detect_area_body_entered);
	register_method((char*)"_on_detect_area_area_entered", &Bullet::_on_detect_area_area_entered);
}


void godot::Bullet::_init()
{

}


void godot::Bullet::_process(float delta)
{

	_time += delta;

	_current_x = _start_possition.x + _speed * cos(_angle) * _time * _move_vector.x;


	if (_move_vector.x != 0)
		_current_y = _start_possition.y - _speed * sin(_angle) * _time + 300 * _time * _time / 2;


	if (_move_vector.x == 0)
		_current_y = _start_possition.y + _speed * cos(_angle) * _time * _move_vector.y;

	/////////////////////////////////////////////////////////////////////////////////////////////
	
	//gravity on diagonal shoot 

	if (_move_vector.x == (float)(sqrt(2) / 2) && _move_vector.y == (float)(sqrt(2) / 2))
		_current_y = _start_possition.y + _speed * sin(_diagonal_shoot_angle) * _time + 300 * pow(_time, 2) / 2;

	if (_move_vector.x == -(float)(sqrt(2) / 2) && _move_vector.y == -(float)(sqrt(2) / 2))
		_current_y = _start_possition.y - _speed * sin(_diagonal_shoot_angle) * _time - 300 * pow(_time, 2) / 2;

	if (_move_vector.x == (float)(sqrt(2) / 2) && _move_vector.y == -(float)(sqrt(2) / 2))
		_current_y = _start_possition.y - _speed * sin(_diagonal_shoot_angle) * _time - 300 * pow(_time, 2) / 2;

	if (_move_vector.x == -(float)(sqrt(2) / 2) && _move_vector.y == (float)(sqrt(2) / 2))
		_current_y = _start_possition.y + _speed * sin(_diagonal_shoot_angle) * _time + 300 * pow(_time, 2) / 2;
	
	//////////////////////////////////////////////////////////////////////////////////////////////

	set_global_position(Vector2(_current_x, _current_y));


	auto _distance = sqrt(pow((this->get_global_position().x - _start_possition.x), 2) +
		pow((this->get_global_position().y - _start_possition.y), 2));

	if (_distance > 140)
	{
		SoundEffectsManager::_get_singleton()->_play_sound_effect("AcornFallSE", Player::_get_singleton());
		queue_free();
	}
		

	//Godot::print(String::num(_move_vector.x));
}


void godot::Bullet::_ready()
{
	set_global_position(Player::_get_singleton()->get_global_position() + Vector2::UP * 4);
	_move_vector = Player::_get_singleton()->_get_input_vector().normalized();

	_start_possition = get_global_position();
}


void godot::Bullet::_on_detect_area_body_entered(Node2D* _other_body)
{
	if (_other_body->is_in_group("_enviroment") || _other_body->is_in_group("_wall"))
	{
		SoundEffectsManager::_get_singleton()->_play_sound_effect("AcornFallSE", Player::_get_singleton());
		queue_free();
	}
		
}


void godot::Bullet::_on_detect_area_area_entered(Area2D* _other_area)
{
	if (_other_area->get_name() != "Player")
		queue_free();
}


godot::Bullet::~Bullet()
{
}