#include "Coin.h"

#include "Loader.h"
#include "UI.h"

void godot::Coin::_register_methods()
{
	register_method("On_body_entered", &Coin::On_body_entered);
}

void godot::Coin::_init()
{
	connect("body_entered", this, "On_body_entered");
}

void godot::Coin::On_body_entered(Node* body)
{
	if(body->get_name() == "Player")
	{
		Loader::get_singleton()->set_coins(1);
		Loader::get_singleton()->save_coins_data();

		UI::get_singleton()->change_coins_information();
		
		queue_free();
	}
}
