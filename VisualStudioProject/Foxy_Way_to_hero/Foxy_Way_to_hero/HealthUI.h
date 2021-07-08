#pragma once
#include "Headers.h"

namespace godot
{
	class HealthUI : public Control
	{
		GODOT_CLASS(HealthUI, Control);
		
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);

		static HealthUI* _get_singleton();
		
		void _turn_on_hit_anim();
		void _delete_next_full_heart();
		void _set_health(float _new_value);
		float _get_health();


	private:
		static inline HealthUI* _instance=nullptr;

		float _player_health;

		Sprite* _first_heart = nullptr;
		Sprite* _second_heart = nullptr;
		Sprite* _third_heart = nullptr;
		Sprite* _fourth_heart = nullptr;

	};
}

