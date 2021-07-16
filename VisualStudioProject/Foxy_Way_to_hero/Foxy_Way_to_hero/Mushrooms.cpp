#include "Mushrooms.h"

void godot::Mushrooms::_register_methods()
{
	register_method("_ready", &Mushrooms::_ready);
	register_method("_process", &Mushrooms::_process);
}

void godot::Mushrooms::_init()
{
}

void godot::Mushrooms::_ready()
{
	_light = cast_to<Light2D>(get_child(0));
}

void godot::Mushrooms::_process(float delta)
{

	auto _light_energy = _light->get_energy();


	if (GameManager::_get_singleton()->_get_is_day() == true)
	{
		if (_light->get_energy() > 0)
			_light->set_energy(_light_energy - 0.01);
	}



	if (GameManager::_get_singleton()->_get_is_night() == true)
	{
		if (_light->get_energy() < 1)
			_light->set_energy(_light_energy + 0.01);
	}

}
