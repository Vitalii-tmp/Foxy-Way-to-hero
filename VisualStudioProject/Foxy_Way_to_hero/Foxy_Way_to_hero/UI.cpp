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
		this->get_child(1)->set("text", this->get_acorns_information().c_str());

		if (!Loader::get_singleton()->get_is_first_time())
		{
			cast_to<TextureRect>(get_node("FirstScene"))->set_visible(true);
		}
		else {
			get_tree()->set_pause(false);
			get_node("FirstScene")->queue_free();
		}
	}

	void godot::UI::_process(float delta)
	{
	}

	godot::UI* godot::UI::get_singleton()
	{
		return _instance;
	}
	
	void UI::change_coins_information() const
	{
		this->get_child(0)->set("text", this->get_coins_information().c_str());
	}
	void UI::change_acorns_information() const
	{
		this->get_child(1)->set("text", this->get_acorns_information().c_str());
	}
	std::string UI::get_coins_information() const
	{
		return std::to_string(Loader::get_singleton()->get_coins());
	}
	std::string UI::get_acorns_information() const
	{
		return std::to_string(Loader::get_singleton()->get_acorns());
	}
}

