#pragma once
#include "Headers.h"

namespace godot
{
	class HungerUI : public Control
	{
		GODOT_CLASS(HungerUI, Control);

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process();

		static HungerUI* _get_singleton();

		void _set_full_player_hunger(float _full_hunger);
		void _set_player_hunger(float _hunger);

		float _get_player_hunger();

	private:
		static inline HungerUI* _instance = nullptr;

		float _player_hunger;
		float _full_player_hunger;

		Sprite* _first_meat = nullptr;
		Sprite* _second_meat = nullptr;
		Sprite* _third_meat = nullptr;
		Sprite* _fourth_meat = nullptr;
	};
}

