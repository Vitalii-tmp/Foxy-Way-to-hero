#include "UI.h"

#include <string>


#include "Loader.h"


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
		auto tmp_coin = "Coins : " + std::to_string(Loader::get_singleton()->get_coins());
		this->get_child(0)->set("text", tmp_coin.c_str());
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
		auto tmp_coin = "Coins : " + std::to_string(Loader::get_singleton()->get_coins());
		this->get_child(0)->set("text", tmp_coin.c_str());
	}
}

