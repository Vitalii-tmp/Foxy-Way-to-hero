#pragma once
#include "Headers.h"

namespace godot
{
	class Acorn : public Area2D
	{
	private:
		GODOT_CLASS(Acorn, Area2D)
	public:
		static void _register_methods();
		void _init();

		void _on_acorn_player_entered(Node* body);
	};

}