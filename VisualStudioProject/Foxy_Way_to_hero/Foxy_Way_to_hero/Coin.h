#pragma once

#include "PlayerSingleton.h"

#include <Godot.hpp>
#include <Area2D.hpp>

namespace godot
{
class Coin:public Area2D
{
private:
	GODOT_CLASS(Coin, Area2D)
public:
	static void _register_methods();
	void _init();

	void On_body_entered(Node* body);
};
}


