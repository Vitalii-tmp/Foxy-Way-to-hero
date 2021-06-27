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

		static HealthUI* _get_singleton();
		
		void _turn_on_hit_anim();
		void _delete_next_full_heart();

	private:
		static inline HealthUI* _instance;
	};
}

