#include "GameManager.h"



godot::GameManager::GameManager()
{
	_current_state = DAY;
	_period = 10;

	_is_day = true;
	_is_night = false;

	_day_color = Color(1, 1, 1, 1);
	_night_color = Color(0.3, 0.3, 0.3, 1);
}


void godot::GameManager::_register_methods()
{
	register_method("_ready", &GameManager::_ready);
	register_method("_init", &GameManager::_init);
	register_method("_process", &GameManager::_process);
	register_method("_set_night", &GameManager::_set_night);
	register_method("_set_day", &GameManager::_set_day);
}

void godot::GameManager::_init()
{
	_instance = this;
}

void godot::GameManager::_ready()
{
	_day_night_canvas = cast_to<CanvasModulate>(this->get_node("CanvasModulate"));

	_timer = Timer::_new();
	this->add_child(_timer);

	if (!_timer->is_connected("timeout", this, "_set_night"))
	{
		_timer->connect("timeout", this, "_set_night");
		_timer->start(_period);
	}
}

void godot::GameManager::_process(float delta)
{

	if (_is_day)
		_current_state = DAY;

	if (_is_night)
		_current_state = NIGHT;

	switch (_current_state)
	{
	case DAY:
		_switch_to_day();
		break;

	case NIGHT:
		_switch_to_night();
		break;
	}
}

void godot::GameManager::_set_night()
{
	_is_night = true;
	_is_day = false;
	Godot::print("_switch_to_night");

	if (_timer->is_connected("timeout", this, "_set_night"))
	{
		_timer->disconnect("timeout", this, "_set_night");
	}
}

void godot::GameManager::_set_day()
{
	_is_night = false;
	_is_day = true;
	Godot::print("_switch_to_day");

	if (_timer->is_connected("timeout", this, "_set_day"))
	{
		_timer->disconnect("timeout", this, "_set_day");
	}
}

void godot::GameManager::_switch_to_day()
{
	
	auto _current_color = _day_night_canvas->get_color();
	
	if (_current_color.r <= _day_color.r)
		_day_night_canvas->set_color(Color(_current_color.r + 0.01, _current_color.g + 0.01, _current_color.b + 0.01, _current_color.a));

	if (_current_color.r >= _day_color.r)
	{
		if (!_timer->is_connected("timeout", this, "_set_night"))
		{
			_timer->connect("timeout", this, "_set_night");
			_timer->start(_period);
		}
	}
}

void godot::GameManager::_switch_to_night()
{
	
	auto _current_color = _day_night_canvas->get_color();
	
	if (_current_color.r >= _night_color.r)
		_day_night_canvas->set_color(Color(_current_color.r - 0.01, _current_color.g - 0.01, _current_color.b - 0.01, _current_color.a));

	if (_current_color.r <= _night_color.r)
	{
		if (!_timer->is_connected("timeout", this, "_set_day"))
		{
			_timer->connect("timeout", this, "_set_day");
			_timer->start(_period);
			
		}
	}

	
}

bool godot::GameManager::_get_is_day()
{
	return this->_is_day;
}

bool godot::GameManager::_get_is_night()
{
	return this->_is_night;
}


godot::GameManager* godot::GameManager::_get_singleton()
{
	return _instance;
}
