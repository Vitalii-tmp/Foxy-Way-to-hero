#pragma once
#include "Headers.h"

namespace godot
{
	class GameManager :public Node2D
	{
		enum period
		{
			DAY,
			NIGHT
		};


		GODOT_CLASS(GameManager, Node2D)

	public:
		
		static GameManager* _get_singleton();

		GameManager();
		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);

		void _set_night();
		void _set_day();

		void _switch_to_day();
		void _switch_to_night();

		bool _get_is_day();
		bool _get_is_night();
	private:

		static inline GameManager* _instance = nullptr;


		int _current_state;

		CanvasModulate* _day_night_canvas = nullptr;

		Timer* _timer = nullptr;

		int _period;

		bool _is_day;
		bool _is_night;	

		Color _day_color;
		Color _night_color;
	};
}


