#include "SoundEffect.h"

void godot::SoundEffect::_register_methods()
{
	register_method("_init", &SoundEffect::_init);
	register_method("_ready", &SoundEffect::_ready);
	register_method("_on_time_out", &SoundEffect::_on_time_out);

	register_property<SoundEffect, float>("duration", &SoundEffect::_duration, 1);
}

void godot::SoundEffect::_init()
{
}

void godot::SoundEffect::_ready()
{
	_timer = Timer::_new();
	add_child(_timer);
	
	if (!_timer->is_connected("timeout", this, "_on_time_out"))
	{
		_timer->connect("timeout", this, "_on_time_out");
		_timer->start(_duration);
	}
	
	this->play();
}

void godot::SoundEffect::_on_time_out()
{
	this->queue_free();
}
