#include "Headers.h"
using namespace godot;

godot::Bullet::Bullet()
{
	_move_vector = Vector2(0, 0);
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
	move_and_slide(_move_vector * 300);

	auto _current_possition = get_global_position();
	
	auto _distance= sqrt(pow((this->get_global_position().x - _start_possition.x), 2) +
		pow((this->get_global_position().y - _start_possition.y), 2));

	if (_distance > 100)
		queue_free();

}


void godot::Bullet::_ready()
{
	set_global_position(Player::_get_singleton()->get_global_position() + Vector2::UP*4);
	_move_vector = Player::_get_singleton()->_get_input_vector().normalized();

	_start_possition = get_global_position();
}

void godot::Bullet::_on_detect_area_body_entered(Node2D* _other_body)
{
	if (_other_body->is_in_group("_enviroment"))
		queue_free();
}

void godot::Bullet::_on_detect_area_area_entered(Area2D* _other_area)
{
	if (_other_area->get_name() != "Player")
		queue_free();
}




godot::Bullet::~Bullet()
{
}