#include <string>
#include "Headers.h"


using namespace godot;

//register methods using in godot
void godot::Player::_register_methods()
{
	register_method("_process", &Player::_process);
	register_method("_init", &Player::_init);
	register_method("_ready", &Player::_ready);

	register_method("_short_attack_animation_is_finished", &Player::_short_attack_animation_is_finished);
	register_method("_roll_animation_is_finished", &Player::_roll_animation_is_finished);
	register_method("_on_hurt_area_area_entered", &Player::_on_hurt_area_area_entered);
	register_method("_on_hit_effect_animation_finished", &Player::_on_hit_effect_animation_finished);
	register_method("_long_attack_animation_is_finished", &Player::_long_attack_animation_is_finished);

	register_method("_fire", &Player::_fire);
	register_method("_death", &Player::_death);

}


void godot::Player::_init()
{
	_instance = this;
}

//set default variables value
Player::Player()
{
	_speed = 100;

	_damage = 25;
	_hp = 100;

	_motion = Vector2(0, 0);
	_input_vector = Vector2(0, 1);

	_is_alive = true;
	_can_fire = true;

}


//calling on scene start
void godot::Player::_ready()
{
	_animation_tree = cast_to<AnimationTree>(get_node("AnimationTree"));
	_animation_tree->set_active(true);

	_animation_state = _animation_tree->get("parameters/playback");

	_hit_area = cast_to<Area2D>(get_node("HitboxPivot/ShortAttackArea"));
	_hit_effect = cast_to<AnimatedSprite>(get_node("HitEffect"));

	_resource_loader = ResourceLoader::get_singleton();

	auto backpack_node = cast_to<Node2D>(get_child(8));
	_backpack = cast_to<Backpack>(backpack_node);

	
	/*_death_timer = Timer::_new();
	this->add_child(_death_timer);*/

	/*Loader::get_singleton()->set_coins(9900);
	Loader::get_singleton()->save_all_fields();

	UI::get_singleton()->change_coins_information();*/
	/*_death_timer = Timer::_new();
	this->add_child(_death_timer);*/

	set_global_position(Loader::get_singleton()->get_start_position());
}


//call every frame
void godot::Player::_process(float delta)
{
	if (_hp <= 0)
	{
		_is_alive = false;
		//destroy player


		Ref<PackedScene> _tmp_tomb = _resource_loader->load("res://Scenes/Items/Tomb.tscn");

		/*get_node("/root/World")->set_name("to_delete");
		get_node("/root/to_delete")->queue_free();
		get_tree()->set_pause(false);

		get_node("/root")->add_child(_tomb->instance());*/
		auto tomb = cast_to<Node2D>(_tmp_tomb->instance());
		tomb->set_global_position(this->get_global_position() + Vector2(0, -12));
		get_node("/root/World/YSort/")->add_child(tomb);

		/*if (!_death_timer->is_connected("timeout", this, "_death"))
		{
			Godot::print("Timer connected");
			_death_timer->connect("timeout", this, "_death");
			_death_timer->start(2);
		}*/


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

	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);
}


//if player attack
void godot::Player::_short_attack_state()
{

	_animation_tree->set("parameters/Attack/blend_position", _input_vector);
	_animation_state->travel("Attack");

	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);
}


void godot::Player::_long_attack_state()
{

	_animation_tree->set("parameters/LongRangeAttack/blend_position", _input_vector);
	_animation_state->travel("LongRangeAttack");

	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);

}


//if player roll
void godot::Player::_roll_state()
{
	_animation_tree->set("parameters/Roll/blend_position", _input_vector);
	_animation_state->travel("Roll");
	_input_vector = _input_vector.normalized() * _speed;
	move_and_slide(_input_vector * 1.4);

	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);
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

	if (Loader::get_singleton()->get_acorns() > 0)
	{
		if (i->is_action_just_pressed("long_attack") && _can_fire)
			_current_state = LONG_ATTACK;
	}



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
	if (_is_alive)
	{
		if (_other_area->get_name() == "BatHitArea")
		{

			auto _bat_damage = cast_to<BatAI>(_other_area->get_parent())->_get_damage();

			//if player is rolling dont damage from bats
			if (_current_state != ROLL)
			{

				_hp -= _bat_damage;
				HealthUI::_get_singleton()->_turn_on_hit_anim();

				_hit_effect->set_visible(true);
				_hit_effect->play();
			}

		}

		if (_other_area->get_name() == "BoarHitArea")
		{
			auto _boar = cast_to<BoarAI>(_other_area->get_parent());
			auto _boar_damage = cast_to<BoarAI>(_other_area->get_parent())->_get_damage();
			auto _boar_agressive = cast_to<BoarAI>(_other_area->get_parent())->_get_agressive();

			if (_boar_agressive == true)
			{
				_hp -= _boar_damage;
				HealthUI::_get_singleton()->_turn_on_hit_anim();

				_hit_effect->set_visible(true);
				_hit_effect->play();
				_knockback_vector = _boar->_get_move_vector().normalized() * 150;
			}



		}



		if (_other_area->get_name() == "SnakeHitArea")
		{
			auto _snake = cast_to<SnakeAI>(_other_area->get_parent());
			auto _snake_damage = cast_to<SnakeAI>(_other_area->get_parent())->_get_damage();


			_hp -= _snake_damage;
			HealthUI::_get_singleton()->_turn_on_hit_anim();

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


void godot::Player::_fire()
{
	Ref<PackedScene> prefab = _resource_loader->load("res://Scenes/Items/Bullet.tscn");
	add_child(prefab->instance());

	Loader::get_singleton()->set_acorns(-1);
	Loader::get_singleton()->save_all_fields();
	UI::get_singleton()->change_acorns_information();
}

void godot::Player::_death()
{
	Godot::print("Timer disconnected");
	_death_timer->disconnect("timeout", this, "_death");

	Ref<PackedScene> _death_menu = _resource_loader->load("res://Scenes/UI/DeathMenu.tscn");

	//get_node("/root/World")->set_name("to_delete");
	//get_node("/root/to_delete")->queue_free();

	get_node("/root")->add_child(_death_menu->instance());

	queue_free();
}


Vector2 godot::Player::_get_input_vector()
{
	return _input_vector;
}


float godot::Player::_get_damage()
{
	return _damage;
}

int godot::Player::_get_current_state()
{
	return _current_state;
}

bool godot::Player::_get_is_alive()
{
	return _is_alive;
}

//void godot::Player::_add_to_backpack(Meat* meat)
//{
//	_backpack->add_element(meat);
//}


Player::~Player() {}


Player* godot::Player::_get_singleton()
{
	return _instance;
}

