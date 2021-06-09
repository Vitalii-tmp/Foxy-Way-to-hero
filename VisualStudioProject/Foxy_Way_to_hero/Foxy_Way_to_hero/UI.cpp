#include "Headers.h"


namespace godot
{
	void UI::_register_methods()
	{
		register_method("_ready", &UI::_ready);
		register_method("_process", &UI::_process);
	}

	void godot::UI::_init()
	{
		_instance = this;

	}

	void godot::UI::_ready()
	{
		this->get_child(0)->set("text", this->get_coins_information().c_str());
	}

	void godot::UI::_process(float delta)
	{
	}

	godot::UI* godot::UI::get_singleton()
	{
		return _instance;
	}
	
	void UI::change_coins_information()
	{
		this->get_child(0)->set("text", this->get_coins_information().c_str());
	}
	std::string UI::get_coins_information()
	{
		return "Coins : " + std::to_string(Loader::get_singleton()->get_coins());
	}
}

