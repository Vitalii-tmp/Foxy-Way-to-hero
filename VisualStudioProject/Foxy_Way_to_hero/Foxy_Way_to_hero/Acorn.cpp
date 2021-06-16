#include "Acorn.h"

void godot::Acorn::_register_methods()
{
	register_method("_on_acorn_player_entered", &Acorn::_on_acorn_player_entered);
}


void godot::Acorn::_init()
{
	connect("body_entered", this, "_on_acorn_player_entered");
}

void godot::Acorn::_on_acorn_player_entered(Node* body)
{
	if (body->get_name() == "Player")
	{
		Loader::get_singleton()->set_acorns(1);
		//Loader::get_singleton()->save_acorns_data();

		Loader::get_singleton()->save_all_fields();

		UI::get_singleton()->change_acorns_information();
		
		this->queue_free();
	}
}
