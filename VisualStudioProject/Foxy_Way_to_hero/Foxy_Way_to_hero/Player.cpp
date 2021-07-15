#include <string>
#include "Headers.h"


using namespace godot;

//register methods using in godot
void godot::Player::_register_methods()
{
	register_method("_physics_process", &Player::_physics_process);
	register_method("_init", &Player::_init);
	register_method("_ready", &Player::_ready);

	register_method("_short_attack_animation_is_finished", &Player::_short_attack_animation_is_finished);
	register_method("_roll_animation_is_finished", &Player::_roll_animation_is_finished);
	register_method("_on_hurt_area_area_entered", &Player::_on_hurt_area_area_entered);
	register_method("_on_hit_effect_animation_finished", &Player::_on_hit_effect_animation_finished);
	register_method("_long_attack_animation_is_finished", &Player::_long_attack_animation_is_finished);

	register_method("_fire", &Player::_fire);
	register_method("_death", &Player::_death);

	register_method("_on_escape_pressed", &Player::_on_escape_pressed);
	register_method("_reset_player_speed_after_snake", &Player::_reset_player_speed_after_snake);
	register_method("_reset_player_visibility", &Player::_reser_player_visibility);
	register_method("_reser_player_speed_after_item", &Player::_reser_player_speed_after_item);
	
}


void godot::Player::_init()
{
	_instance = this;
}

//set default variables value
Player::Player()
{
	_speed = 100.f;

	_damage = 25.f;
	_hp = 100.f;
	_hunger = 360.f;

	_motion = Vector2(0, 0);
	_input_vector = Vector2(0, 1);

	_is_alive = true;
	_can_fire = true;
	_invisible = false;

	_speed_cooldown = 30;
	_invisibility_cooldown = 30;
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

	auto backpack_node = cast_to<Node2D>(get_node("/root/World/UI/Backpack"));
	_backpack = cast_to<Backpack>(backpack_node);

	HungerUI::_get_singleton()->_set_full_player_hunger(_hunger);

	/*_death_timer = Timer::_new();
	this->add_child(_death_timer);*/

	/*Loader::get_singleton()->set_coins(9900);
	Loader::get_singleton()->save_all_fields();

	UI::get_singleton()->change_coins_information();*/
	/*_death_timer = Timer::_new();
	this->add_child(_death_timer);*/

	_timer = Timer::_new();
	this->add_child(_timer);

	set_global_position(Loader::get_singleton()->get_start_position());

	_player_sprite = cast_to<Sprite>(get_node("PlayerSprite"));
	_shadow = cast_to<Sprite>(get_node("Shadow"));

}


//call every frame
void godot::Player::_physics_process(float delta)
{
	HealthUI::_get_singleton()->_set_health(_hp);
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
		_on_escape_pressed();
		_change_state_depend_on_behavior();

		_hunger -= delta;
		HungerUI::_get_singleton()->_set_player_hunger(_hunger);

		if (HungerUI::_get_singleton()->_get_player_hunger() <= 0)
			_hunger = 0;

		if (_hunger <= 0)
			_hp -= delta;
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
	move_and_slide(_input_vector * 1.7);

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
				//HealthUI::_get_singleton()->_turn_on_hit_anim();

				_hit_effect->set_visible(true);
				_hit_effect->play();
			}

		}

		if (_other_area->get_name() == "BoarHitArea"&& !_invisible)
		{
			auto _boar = cast_to<BoarAI>(_other_area->get_parent());
			auto _boar_damage = cast_to<BoarAI>(_other_area->get_parent())->_get_damage();
			auto _boar_agressive = cast_to<BoarAI>(_other_area->get_parent())->_get_agressive();

			if (_boar_agressive == true)
			{
				_hp -= _boar_damage;
				//HealthUI::_get_singleton()->_turn_on_hit_anim();

				_hit_effect->set_visible(true);
				_hit_effect->play();
				_knockback_vector = _boar->_get_move_vector().normalized() * 150;
			}



		}



		if (_other_area->get_name() == "SnakeHitArea" && !_invisible)
		{
			auto _snake = cast_to<SnakeAI>(_other_area->get_parent());
			auto _snake_damage = cast_to<SnakeAI>(_other_area->get_parent())->_get_damage();


			_hp -= _snake_damage;
			//HealthUI::_get_singleton()->_turn_on_hit_anim();

			_hit_effect->set_visible(true);
			_hit_effect->play();

			_speed = 50;

			if (!_timer->is_connected("timeout", this, "_reset_player_speed_after_snake"))
			{
				//Godot::print("Timer connected");
				_timer->connect("timeout", this, "_reset_player_speed_after_snake");
				_timer->start(4);
			}

		}

		if (_other_area->get_name() == "CactusHitArea")
		{
			auto _cactus = cast_to<StaticBody2D>(_other_area->get_parent());

			_hp -= 7.f;

			_hit_effect->set_visible(true);
			_hit_effect->play();
			_knockback_vector = (this->get_global_position() - _cactus->get_global_position()).normalized() * 100;
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

bool godot::Player::_get_invisible()
{
	return _invisible;
}


float godot::Player::_get_hp()
{
	return _hp;
}

float godot::Player::_get_hunger()
{
	return _hunger;
}

void godot::Player::_set_hp(float _new_value)
{
	this->_hp = _new_value;
}

void godot::Player::_set_hunger(float _new_value)
{
	this->_hunger = _new_value;
}





void godot::Player::_on_escape_pressed()
{
	Input* i = Input::get_singleton();

	if (i->is_action_just_pressed("ui_cancel") && !get_tree()->is_paused())
	{
		Godot::print("escape");
		get_tree()->set_pause(true);
		Godot::print("set pause");

		Ref<PackedScene> prefab = _resource_loader->load("res://Scenes/UI/PauseMenu.tscn");
		Godot::print("set load prefab");

		auto* menu = cast_to<CanvasLayer>(prefab->instance());
		get_node("/root/World/UI/")->add_child(menu);
		
	}
}

void godot::Player::_reset_player_speed_after_snake()
{
	this->_speed = 100.f;

	if (_timer->is_connected("timeout", this, "_reset_player_speed_after_snake"))
	{
		//Godot::print("Timer connected");
		_timer->disconnect("timeout", this, "_reset_player_speed_after_snake");

	}
}

void godot::Player::_reser_player_visibility()
{
	if (_timer->is_connected("timeout", this, "_reset_player_visibility"))
	{
		//Godot::print("Timer connected");
		_timer->disconnect("timeout", this, "_reset_player_visibility");
		
		auto _player_color = _player_sprite->get_modulate();
		auto _shadow_color = _shadow->get_modulate();

		auto _visibility_color = Color(_player_color.r, _player_color.g, _player_color.b, 1);
		auto _shadow_visibility_color = Color(_shadow_color.r, _shadow_color.g, _shadow_color.b, 1);

		_player_sprite->set_modulate(_visibility_color);
		_shadow->set_modulate(_shadow_visibility_color);

		_invisible = false;
	}
}

void godot::Player::_reser_player_speed_after_item()
{
	this->_speed = 100.f;

	if (_timer->is_connected("timeout", this, "_reser_player_speed_after_item"))
	{
		//Godot::print("Timer connected");
		_timer->disconnect("timeout", this, "_reser_player_speed_after_item");

	}
}

void godot::Player::_set_player_speed(float speed)
{
	_speed = speed;

	if (!_timer->is_connected("timeout", this, "_reser_player_speed_after_item"))
	{
		//Godot::print("Timer connected");
		_timer->connect("timeout", this, "_reser_player_speed_after_item");
		_timer->start(_speed_cooldown);
	}

}

void godot::Player::_set_to_invisible()
{
	auto _player_color = _player_sprite->get_modulate();
	auto _shadow_color =_shadow->get_modulate();

	auto _invisibility_color = Color(_player_color.r, _player_color.g, _player_color.b, 0.2);
	auto _shadow_invisibility_color = Color(_shadow_color.r, _shadow_color.g, _shadow_color.b, 0.5);
	
	_player_sprite->set_modulate(_invisibility_color);
	_shadow->set_modulate(_shadow_invisibility_color);

	_invisible=true;

	if (!_timer->is_connected("timeout", this, "_reset_player_visibility"))
	{
		//Godot::print("Timer connected");
		_timer->connect("timeout", this, "_reset_player_visibility");
		_timer->start(_invisibility_cooldown);
	}
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

