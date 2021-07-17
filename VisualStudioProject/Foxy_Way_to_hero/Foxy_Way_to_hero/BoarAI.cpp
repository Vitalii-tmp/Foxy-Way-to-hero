#include "BoarAI.h"

godot::BoarAI::BoarAI()
{
	_is_alive = true;
	_can_move = true;
	_current_state = WALK;
	_agressive = false;
	_hp = 100.f;
	_damage = 30.f;
	_run_speed = 85.f;
	_walk_speed = 30.f;

	_is_stoping = false;
}



void godot::BoarAI::_register_methods()
{
	register_method("_physics_process", &BoarAI::_physics_process);
	register_method("_init", &BoarAI::_init);
	register_method("_ready", &BoarAI::_ready);

	register_method("_on_detection_area_body_entered", &BoarAI::_on_detection_area_body_entered);
	register_method("_on_detection_area_body_exited", &BoarAI::_on_detection_area_body_exited);
	register_method("_on_hurt_area_area_entered", &BoarAI::_on_hurt_area_area_entered);
	register_method("_on_hit_effect_animation_finished", &BoarAI::_on_hit_effect_animation_finished);
	register_method("_set_move_vector", &BoarAI::_set_move_vector);
	register_method("_on_boar_hit_area_area_entered", &BoarAI::_on_boar_hit_area_area_entered);
	register_method("_change_to_can_move", &BoarAI::_change_to_can_move);
}


void godot::BoarAI::_init()
{
}

void godot::BoarAI::_ready()
{
	_hit_effect = cast_to<AnimatedSprite>(get_node("HitEffect"));

	_timer = Timer::_new();
	this->add_child(_timer);

	_animation_tree = cast_to<AnimationTree>(get_node("AnimationBoarTree"));
	_animation_tree->set_active(true);

	_animation_state = _animation_tree->get("parameters/playback");

	_timer_start_time = RandomNumberGenerator::_new();
	_resource_loader = ResourceLoader::get_singleton();
}

void godot::BoarAI::_physics_process(float delta)
{
	if (_is_alive && _can_move)
	{
		_change_state();
	}

	//Godot::print(String::num(_hp));
	if (_hp <= 0)
	{
		
		_is_alive = false;
		_agressive = false;
		_animation_state->travel("Die");
		_animation_tree->set("parameters/Die/blend_position", _look_vector);
		//queue_free();
	}


	if (_is_stoping)
	{

		if (get_node("/root/World")->find_node("Player") != nullptr)
		{
			//Godot::print("MoveVector " + _move_vector);
			//_move_vector = _move_vector.move_toward(Vector2(0, 0), 5);
			move_and_slide(_move_vector.normalized() * _walk_speed);
			//_move_vector = _move_vector.move_toward(Vector2::ZERO, 2);
		}
		else
			_move_vector = _move_vector.normalized();

		Godot::print("LookVector " + _move_vector.normalized());
	}

	if (_is_alive && _can_move)
	{
		if (_move_vector != Vector2(0, 0))
			_animation_state->travel("Run");
		else
			_animation_state->travel("Idle");
	}




	//Godot::print(_animation_state->get_current_node());
}

void godot::BoarAI::_walk_state()
{
	//walk
	_walk();


	//Godot::print(_move_vector.normalized());
	//state changing depend on health
	if (_hp < 100)
		_agressive = true;

	if (_agressive && _player != nullptr && _player->_get_invisible() == false)
		_current_state = WANDER;
}

void godot::BoarAI::_wander_state()
{
	_walk();
	//distance to player



	auto _distance_to_player = sqrt(pow((this->get_global_position().x - Player::_get_singleton()->get_global_position().x), 2) +
		pow((this->get_global_position().y - Player::_get_singleton()->get_global_position().y), 2));


	//Godot::print(String::num(_distance_to_player));


	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);

	if (_distance_to_player < 100)
		_current_state = CHASE;
}

void godot::BoarAI::_chase_state()
{
	if ( _player->_get_invisible() == false)
	{
		_move_vector = (Player::_get_singleton()->get_global_position() - this->get_global_position()).normalized();
		//_move_vector = _move_vector.move_toward(_move_vector, 5);
		//Godot::print(_move_vector);

		//check distance to player
		auto _distance_to_player = sqrt(pow((this->get_global_position().x - Player::_get_singleton()->get_global_position().x), 2) +
			pow((this->get_global_position().y - Player::_get_singleton()->get_global_position().y), 2));

		if (_distance_to_player > 130)
			_current_state = WANDER;

		move_and_slide(_move_vector * _run_speed);

		_animation_tree->set("parameters/Run/blend_position", _move_vector.normalized());
	}

	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);
	
}

void godot::BoarAI::_walk()
{
	if (!_timer->is_connected("timeout", this, "_set_move_vector"))
	{

		Godot::print("Timer connected");
		_timer->connect("timeout", this, "_set_move_vector");

		_timer_start_time->randomize();
		_start_time = _timer_start_time->randi_range(1, 5);
		_timer->start(_start_time);

		Godot::print(String::num(_start_time));
	}
	move_and_slide(_move_vector * _walk_speed);

	_knockback_vector = _knockback_vector.move_toward(Vector2::ZERO, 5);
	move_and_slide(_knockback_vector);

	if (_move_vector != Vector2(0, 0))
		_look_vector = _move_vector.normalized();

	_animation_tree->set("parameters/Idle/blend_position", _look_vector);
	_animation_tree->set("parameters/Run/blend_position", _move_vector.normalized());
}

void godot::BoarAI::_change_state()
{
	switch (_current_state)
	{
	case WALK:
		_walk_state();
		break;
	case WANDER:
		_wander_state();
		break;
	case CHASE:
		_chase_state();
		break;
	}
}

void godot::BoarAI::_on_detection_area_body_entered(Node2D* _other_body)
{
	if (_other_body->get_name() == "Player")
	{

		_player = cast_to<Player>(_other_body);
		if (_agressive && _player->_get_invisible() == false)
		{
			_current_state = WANDER;
			Godot::print("attack");

		}

	}
}

void godot::BoarAI::_on_detection_area_body_exited(Node2D* _other_body)
{
	if (_other_body->get_name() == "Player")
	{
		_current_state = WALK;
		_player = nullptr;
	}
}

void godot::BoarAI::_on_hurt_area_area_entered(Area2D* _other_area)
{
	if (_other_area->get_name() == "ShortAttackArea")
	{
		//play hit affect
		_hit_effect->set_visible(true);
		_hit_effect->play();

		auto _vector = Player::_get_singleton()->_get_input_vector();
		auto _pl_damage = Player::_get_singleton()->_get_damage();

		_knockback_vector = _vector.normalized() * 150;
		_hp -= _pl_damage;

		SoundEffectsManager::_get_singleton()->_play_sound_effect("EnemyHitSE", Player::_get_singleton());
	}

	if (_other_area->get_name() == "LongAttackArea")
	{
		//play hit affect
		_hit_effect->set_visible(true);
		_hit_effect->play();

		auto _vector = Player::_get_singleton()->_get_input_vector();
		auto _pl_damage = Player::_get_singleton()->_get_damage();

		_knockback_vector = _vector.normalized() * 100;
		_hp -= _pl_damage;

		SoundEffectsManager::_get_singleton()->_play_sound_effect("EnemyHitSE", Player::_get_singleton());
	}

	if (_hp <= 0 && (_other_area->get_name() == "LongAttackArea" || _other_area->get_name() == "ShortAttackArea"))
	{
		_spawn_coin();
		_spawn_fur();
	}
}

void godot::BoarAI::_on_boar_hit_area_area_entered(Area2D* _other_area)
{
	if (_other_area->get_name() == "PlayerHurtArea" && _agressive && _player->_get_invisible() == false)
	{
		_stoping();
	}
}

void godot::BoarAI::_on_hit_effect_animation_finished()
{
	_hit_effect->set_visible(false);
	_hit_effect->set_frame(0);

}

void godot::BoarAI::_set_move_vector()
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


	if (_timer->is_connected("timeout", this, "_set_move_vector"))
	{
		Godot::print("Timer disconnected");
		_timer->disconnect("timeout", this, "_set_move_vector");
	}

}

void godot::BoarAI::_stoping()
{

	_is_stoping = true;
	_can_move = false;
	if (!_timer->is_connected("timeout", this, "_change_to_can_move"))
	{
		Godot::print("Timer aaaaaaaaaaaaaaaaaaaa connected");
		_timer->connect("timeout", this, "_change_to_can_move");
		_timer->start(0.5);
	}

	_animation_tree->set("parameters/Stop/blend_position", _move_vector.normalized());
	_animation_state->travel("Stop");


}

void godot::BoarAI::_change_to_can_move()
{
	_is_stoping = false;
	_can_move = true;

	if (_timer->is_connected("timeout", this, "_change_to_can_move"))
		_timer->disconnect("timeout", this, "_change_to_can_move");


}

float godot::BoarAI::_get_damage()
{
	return _damage;
}

bool godot::BoarAI::_get_agressive()
{
	return _agressive;
}

godot::Vector2 godot::BoarAI::_get_move_vector()
{
	return _move_vector;
}

void godot::BoarAI::_spawn_coin()
{
	if (Player::_get_singleton()->_get_is_received_task_hunter())
	{
		Player::_get_singleton()->_set_plus_killed_boars(1);
		Godot::print(String::num(Player::_get_singleton()->_get_killed_boars()));
	}
	auto pos = this->get_global_position();

	Ref<PackedScene> prefab = _resource_loader->load("res://Scenes/Items/Coin.tscn");

	auto item = cast_to<Area2D>(prefab->instance());

	get_node(NodePath("/root/World/YSort/Coins/"))->add_child(item);

	item->set_global_position(pos);
}

void godot::BoarAI::_spawn_fur()
{
	auto pos = this->get_global_position();

	Ref<PackedScene> prefab = _resource_loader->load("res://Scenes/Items/BoarFur.tscn");

	auto item = cast_to<KinematicBody2D>(prefab->instance());

	get_node(NodePath("/root/World/YSort/BoarFur/"))->add_child(item);

	item->set_global_position(pos);
}


godot::BoarAI::~BoarAI()
{
}