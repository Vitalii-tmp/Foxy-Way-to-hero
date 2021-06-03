#include "Coin.h"

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
		/*body->call("set_coins", 50);*/
		PlayerSingleton::get_singleton()->set_coins(50);
		queue_free();
	}
}
